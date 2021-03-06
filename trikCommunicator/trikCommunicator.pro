# Copyright 2013 Yurii Litvinov
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include(../global.pri)

HEADERS += \
	$$PWD/include/trikCommunicator/trikCommunicator.h \
	$$PWD/src/connection.h \

SOURCES += \
	$$PWD/src/trikCommunicator.cpp \
	$$PWD/src/connection.cpp \

TEMPLATE = lib

QT += network

DEFINES += TRIKCOMMUNICATOR_LIBRARY

uses(trikScriptRunner trikControl trikKernel qslog)

INCLUDEPATH += \
	$$PWD/../trikScriptRunner/include/ \
	$$PWD/../trikControl/include/ \
	$$PWD/../trikKernel/include/ \
	$$PWD/../qslog/ \
