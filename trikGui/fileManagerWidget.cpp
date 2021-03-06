/* Copyright 2013 Roman Kurbatov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file was modified by Yurii Litvinov to make it comply with the requirements of trikRuntime
 * project. See git revision history for detailed changes. */

#include "fileManagerWidget.h"

#include <QtCore/QDir>
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>

using namespace trikGui;

FileManagerWidget::FileManagerWidget(Controller &controller, QWidget *parent)
	: TrikGuiDialog(parent)
	, mController(controller)
{
	mRootDirPath = mController.scriptsDirPath();

	QDir::setCurrent(mController.startDirPath());
	QDir dir;
	dir.mkdir(mController.scriptsDirName());
	QDir::setCurrent(mRootDirPath);

	mFileSystemModel.setRootPath(mRootDirPath);
	mFileSystemModel.setFilter(QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDot);

	connect(&mFileSystemModel
			, SIGNAL(directoryLoaded(QString))
			, this
			, SLOT(onDirectoryLoaded(QString))
			);

	mFileSystemView.setModel(&mFileSystemModel);

	mLayout.addWidget(&mCurrentPathLabel);
	mLayout.addWidget(&mFileSystemView);
	setLayout(&mLayout);

	mFileSystemView.setSelectionMode(QAbstractItemView::SingleSelection);
	mFileSystemView.setFocus();

	showCurrentDir();
}

FileManagerWidget::~FileManagerWidget()
{
}

QString FileManagerWidget::menuEntry()
{
	return tr("File Manager");
}

void FileManagerWidget::renewFocus()
{
	mFileSystemView.setFocus();
}

void FileManagerWidget::open()
{
	QModelIndex const &index = mFileSystemView.currentIndex();
	if (mFileSystemModel.isDir(index)) {
		if (QDir::setCurrent(mFileSystemModel.filePath(index))) {
			showCurrentDir();
		}
	} else {
		mOpenDeleteBox.showMessage();
		FileManagerMessageBox::FileState const choice = mOpenDeleteBox.userAnswer();
		switch (choice) {
		case FileManagerMessageBox::FileState::Open:
			mController.runFile(mFileSystemModel.filePath(index));
			break;
		case FileManagerMessageBox::FileState::Delete:
			mFileSystemModel.remove(index);
			break;
		default:
			break;
		}
	}
}

void FileManagerWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Return: {
			open();
			break;
		}
		default: {
			TrikGuiDialog::keyPressEvent(event);
			break;
		}
	}
}

QString FileManagerWidget::showCurrentPath()
{
	QString result = QDir::currentPath();
	result.remove(mRootDirPath);

	if (result.isEmpty()) {
		result = "/";
	}

	return result;
}

void FileManagerWidget::showCurrentDir()
{
	mCurrentPathLabel.setText(showCurrentPath());

	QDir::Filters filters = mFileSystemModel.filter();
	if (QDir::currentPath() == mRootDirPath) {
		filters |= QDir::NoDotDot;
	} else {
		filters &= ~QDir::NoDotDot;
	}
	mFileSystemModel.setFilter(filters);

	mFileSystemView.setRootIndex(mFileSystemModel.index(QDir::currentPath()));

	/// @todo Here and several lines down we use QTimer
	/// to fix a bug with selecting first item. Rewrite it.
	QTimer::singleShot(200, this, SLOT(renewCurrentIndex()));
}

void FileManagerWidget::onDirectoryLoaded(QString const &path)
{
	if (QDir::currentPath() != path) {
		return;
	}

	QTimer::singleShot(200, this, SLOT(renewCurrentIndex()));
}

void FileManagerWidget::renewCurrentIndex()
{
	mFileSystemView.setFocus();

	QModelIndex const currentIndex = mFileSystemModel.index(
			0
			, 0
			, mFileSystemModel.index(QDir::currentPath())
			);

	mFileSystemView.selectionModel()->select(currentIndex, QItemSelectionModel::ClearAndSelect);
	mFileSystemView.setCurrentIndex(currentIndex);
}
