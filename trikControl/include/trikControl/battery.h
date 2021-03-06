/* Copyright 2013 - 2014 Matvey Bryksin, Yurii Litvinov, CyberTech Labs Ltd.
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

#include "declSpec.h"

namespace trikControl {

class I2cCommunicator;

/// Provides battery voltage info.
class TRIKCONTROL_EXPORT Battery : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	/// @param communicator - I2C communicator to use to query battery status.
	Battery(I2cCommunicator &communicator);

public slots:

	/// Returns current battery voltage in volts.
	float readVoltage();

	/// Returns current raw reading of battery.
	float readRawDataVoltage();

private:
	I2cCommunicator &mCommunicator;
};

}
