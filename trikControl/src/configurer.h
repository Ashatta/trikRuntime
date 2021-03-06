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

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QHash>

class QDomElement;

namespace trikControl {

/// Parses config file and holds information about various configuration parameters.
class Configurer {
public:
	/// Constructor
	/// @param configFilePath - path to config.xml.
	Configurer(QString const &configFilePath);

	/// Returns sh script that shall be run on program startup.
	QString initScript() const;

	/// Returns a list of motor type names from config.
	QStringList servoMotorTypes() const;

	QStringList analogSensorTypes() const;

	int analogSensorTypeRawValue1(QString const &analogSensorType) const;

	int analogSensorTypeRawValue2(QString const &analogSensorType) const;

	int analogSensorTypeNormalizedValue1(QString const &analogSensorType) const;

	int analogSensorTypeNormalizedValue2(QString const &analogSensorType) const;

	/// Returns a list of sensor type names from config.
	QStringList digitalSensorTypes() const;

	/// Returns value of duty_ns corresponding to full reverse of a servo motor for given servo motor type.
	int servoMotorTypeMin(QString const &servoMotorType) const;

	/// Returns value of duty_ns corresponding to full forward of a servo motor for given servo motor type.
	int servoMotorTypeMax(QString const &servoMotorType) const;

	/// Returns value of duty_ns corresponding to breaking stop of a servo motor for given servo motor type.
	int servoMotorTypeZero(QString const &servoMotorType) const;

	/// Returns value of duty_ns corresponding to non-breaking stop of a servo motor for given servo motor type.
	int servoMotorTypeStop(QString const &servoMotorType) const;

	/// Returns true, if it is continious rotation servo, false for angular servos.
	bool isServoMotorTypeContiniousRotation(QString const &servoMotorType) const;

	/// Returns minimal physical reading value of a digital sensor (corresponds to 0 in client program).
	int digitalSensorTypeMin(QString const &digitalSensorType) const;

	int digitalSensorTypeMax(QString const &digitalSensorType) const;

	double encoderTypeRawToDegrees(QString const &encoderType) const;

	QStringList servoMotorPorts() const;

	QString servoMotorDeviceFile(QString const &port) const;

	QString servoMotorPeriodFile(QString const &port) const;

	int servoMotorPeriod(QString const &port) const;

	QString servoMotorDefaultType(QString const &port) const;

	bool servoMotorInvert(QString const &port) const;

	QStringList pwmCapturePorts() const;

	QString pwmCaptureFrequencyFile(QString const &port) const;

	QString pwmCaptureDutyFile(QString const &port) const;

	QStringList powerMotorPorts() const;

	int powerMotorI2cCommandNumber(QString const &port) const;

	bool powerMotorInvert(QString const &port) const;

	QStringList analogSensorPorts() const;

	int analogSensorI2cCommandNumber(QString const &port) const;

	QString analogSensorDefaultType(QString const &port) const;

	QStringList encoderPorts() const;

	int encoderI2cCommandNumber(QString const &port) const;

	QString encoderDefaultType(QString const &port) const;

	QStringList digitalSensorPorts() const;

	QString digitalSensorDeviceFile(QString const &port) const;

	QString digitalSensorDefaultType(QString const &port) const;

	QString playWavFileCommand() const;

	QString playMp3FileCommand() const;

	bool hasAccelerometer() const;

	int accelerometerMin() const;

	int accelerometerMax() const;

	QString accelerometerDeviceFile() const;

	bool hasGyroscope() const;

	int gyroscopeMin() const;

	int gyroscopeMax() const;

	QString gyroscopeDeviceFile() const;

	QString i2cPath() const;

	int i2cDeviceId() const;

	QString ledRedDeviceFile() const;

	QString ledGreenDeviceFile() const;

	int ledOn() const;

	int ledOff() const;

	QString keysDeviceFile() const;

	bool hasGamepad() const;

	int gamepadPort() const;

	bool hasLineSensor() const;

	QString lineSensorScript() const;

	QString lineSensorInFifo() const;

	QString lineSensorOutFifo() const;

	double lineSensorToleranceFactor() const;

	bool hasObjectSensor() const;

	QString objectSensorScript() const;

	QString objectSensorInFifo() const;

	QString objectSensorOutFifo() const;

	double objectSensorToleranceFactor() const;

	bool hasColorSensor() const;

	QString colorSensorScript() const;

	QString colorSensorInFifo() const;

	QString colorSensorOutFifo() const;

	int colorSensorM() const;

	int colorSensorN() const;

	bool hasMailbox() const;

	int mailboxServerPort() const;

private:
	enum ServoType {
		angular
		, continiousRotation
	};

	struct ServoMotorType {
		int min;
		int max;
		int zero;
		int stop;
		ServoType type;
	};

	struct AnalogSensorType {
		int rawValue1;
		int rawValue2;
		int normalizedValue1;
		int normalizedValue2;
	};

	struct DigitalSensorType {
		int min;
		int max;
	};

	struct EncoderType {
		double rawToDegrees;
	};

	struct ServoMotorMapping {
		QString port;
		QString deviceFile;
		QString periodFile;
		int period;
		QString defaultType;
		bool invert;
	};

	struct PwmCaptureMapping {
		QString port;
		QString frequencyFile;
		QString dutyFile;
	};

	struct PowerMotorMapping {
		QString port;
		int i2cCommandNumber;
		bool invert;
	};

	struct AnalogSensorMapping {
		QString port;
		int i2cCommandNumber;
		QString defaultType;
	};

	struct EncoderMapping {
		QString port;
		int i2cCommandNumber;
		QString defaultType;
	};

	struct DigitalSensorMapping {
		QString port;
		QString deviceFile;
		QString defaultType;
	};

	struct OnBoardSensor {
		int min = 0;
		int max = 0;
		QString deviceFile;
		bool enabled = false;
	};

	struct VirtualSensor {
		QString script;
		QString inFifo;
		QString outFifo;
		double toleranceFactor = 1.0;
		bool enabled = false;
	};

	void loadInit(QDomElement const &root);
	void loadServoMotors(QDomElement const &root);
	void loadPwmCaptures(QDomElement const &root);
	void loadPowerMotors(QDomElement const &root);
	void loadAnalogSensors(QDomElement const &root);
	void loadEncoders(QDomElement const &root);
	void loadDigitalSensors(QDomElement const &root);
	void loadServoMotorTypes(QDomElement const &root);
	void loadAnalogSensorTypes(QDomElement const &root);
	void loadDigitalSensorTypes(QDomElement const &root);
	void loadEncoderTypes(QDomElement const &root);
	void loadSound(QDomElement const &root);
	static OnBoardSensor loadSensor3d(QDomElement const &root, QString const &tagName);
	void loadI2c(QDomElement const &root);
	void loadLed(QDomElement const &root);
	void loadKeys(QDomElement const &root);
	void loadGamepadPort(QDomElement const &root);
	VirtualSensor loadVirtualSensor(QDomElement const &root, QString const &tagName);
	void loadMailbox(QDomElement const &root);

	static bool isEnabled(QDomElement const &root, QString const &tagName);

	QHash<QString, ServoMotorType> mServoMotorTypes;
	QHash<QString, AnalogSensorType> mAnalogSensorTypes;
	QHash<QString, DigitalSensorType> mDigitalSensorTypes;
	QHash<QString, EncoderType> mEncoderTypes;
	QHash<QString, ServoMotorMapping> mServoMotorMappings;
	QHash<QString, PwmCaptureMapping> mPwmCaptureMappings;
	QHash<QString, PowerMotorMapping> mPowerMotorMappings;
	QHash<QString, AnalogSensorMapping> mAnalogSensorMappings;
	QHash<QString, EncoderMapping> mEncoderMappings;
	QHash<QString, DigitalSensorMapping> mDigitalSensorMappings;

	OnBoardSensor mAccelerometer;
	OnBoardSensor mGyroscope;

	QString mInitScript;
	QString mPlayWavFileCommand;
	QString mPlayMp3FileCommand;
	QString mI2cPath;
	int mI2cDeviceId = 0;

	QString mLedRedDeviceFile;
	QString mLedGreenDeviceFile;
	QString mKeysDeviceFile;
	int mLedOn = 0;
	int mLedOff = 0;

	int mGamepadPort = 0;
	bool mIsGamepadEnabled = false;

	VirtualSensor mLineSensor;
	VirtualSensor mObjectSensor;
	VirtualSensor mMxNColorSensor;
	int mColorSensorM = 0;
	int mColorSensorN = 0;

	int mMailboxServerPort = 0;
	bool mIsMailboxEnabled = false;
};

}
