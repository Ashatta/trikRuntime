/* Copyright 2014 CyberTech Labs Ltd.
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

#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QScopedPointer>
#include <QtCore/QVector>

#include "declSpec.h"
#include "sensor.h"

namespace trikControl {

class ObjectSensorWorker;

/// Uses virtual line sensor to detect x coordinate of a center of an object that was in camera's field of view
/// when "detect" method was called. Used mainly to follow the line.
class TRIKCONTROL_EXPORT ObjectSensor : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	/// @param script - file name of a scrit used to start or stop a sensor.
	/// @param inputFile - sensor input fifo. Note that we will write data here, not read it.
	/// @param outputFile - sensor output fifo. Note that we will read sensor data from here.
	/// @param toleranceFactor - a value on which hueTolerance, saturationTolerance and valueTolerance is multiplied
	///        after "detect" command. Higher values allow to count more points on an image as tracked object.
	ObjectSensor(QString const &script, QString const &inputFile, QString const &outputFile, double toleranceFactor);

	~ObjectSensor() override;

public slots:
	/// Initializes a camera.
	/// @param showOnDisplay - true if we want an image from a camera to be drawn on robot display.
	void init(bool showOnDisplay);

	/// Detects the color of an object in center of current frame and memorizes it.
	void detect();

	/// Returns x, y coordinates and size of an object in a form of vector [x; y; size].
	/// Returns 0 in every field if detect() was not called.
	QVector<int> read();

	/// Stops detection until init() will be called again.
	void stop();

private:
	/// Worker object that handles sensor in separate thread.
	QScopedPointer<ObjectSensorWorker> mObjectSensorWorker;

	/// Worker thread.
	QThread mWorkerThread;
};

}
