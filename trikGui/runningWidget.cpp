/* Copyright 2013 - 2014 Yurii Litvinov, CyberTech Labs Ltd.
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
 * limitations under the License. */

#include "runningWidget.h"

#include <QtGui/QKeyEvent>

using namespace trikGui;

RunningWidget::RunningWidget(QString const &programName, Controller &controller, QWidget *parent)
	: QWidget(parent)
	, mController(controller)
{
	setWindowState(Qt::WindowFullScreen);

	mStatusLabel.setWordWrap(true);
	mStatusLabel.setAlignment(Qt::AlignCenter);
	mStatusLabel.setText(tr("Running ") + programName);

	mAbortLabel.setWordWrap(true);
	mAbortLabel.setAlignment(Qt::AlignCenter);
	mAbortLabel.setText(tr("Press Power to abort"));

	mLayout.addWidget(&mStatusLabel);
	mLayout.addWidget(&mAbortLabel);

	setLayout(&mLayout);
}

void RunningWidget::showError(QString const &error)
{
	mStatusLabel.setAlignment(Qt::AlignLeft);
	mStatusLabel.setText(QString("<font color='red'>%1</font>").arg(error));
	update();
}

void RunningWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_PowerDown: {
			mController.abortExecution();
			releaseKeyboard();
			close();
			break;
		}
		default: {
			QWidget::keyPressEvent(event);
			break;
		}
	}
}
