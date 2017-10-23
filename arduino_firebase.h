/*************************************************************************
The MIT License (MIT)
Copyright (c) 2017 Marcos Scarpim -- marcos.scarpim@gmail.com

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*************************************************************************/

#ifndef ARDUINO_FIREBASE_H
#define ARDUINO_FIREBASE_H

#include <Arduino.h>
#include <FirebaseArduino.h>
#include <libMiletusPubSubIf.h>
#ifndef PROTOCOL
#define PROTOCOL "firebase"
#endif
#ifndef VERSION
#define VERSION "1.0"
#else
#define VERSION "unknown"
#endif  // VERSION

#define FB_COMMAND_EXECUTE 231
#define FB_COMMAND_CANCEL 232
#define FB_COMMAND_LIST 233
#define FB_COMMAND_STATUS 234


class arduino_firebase : public MiletusPubSubIf {
 public:
  arduino_firebase(const char* device_name, const char* host, const char* auth);
  ~arduino_firebase(){};
  
  int handleEvent(RequestT*);
  bool sendJsonToClient(std::string json);
  bool sendErrorToClient();
  bool publish(const char* topic, const char* json, bool retained = 0);

  char* getProtocol();
  const char* getAddress();
  char* getVersion();
  int getPort();


 private:
    const char* device_name;
    RequestT* current_request;
    
    std::string commandPath;
    std::string commandJsonPath;
	std::string historyPath;
};

#endif  // ARDUINO_FIREBASE_H