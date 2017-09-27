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
  arduino_firebase(const char* device_name, const char* host, const char* auth); //DONE
  ~arduino_firebase(){};
  
  int handleEvent(RequestT*); //DONE
  bool sendJsonToClient(std::string json); //DONE
  bool sendErrorToClient(); //DONE
  bool publish(const char* topic, const char* json, bool retained = 0); //DONE

  char* getProtocol(); //DONE
  const char* getAddress(); //DONE
  char* getVersion(); //DONE
  int getPort(); //DONE


 private:
    const char* device_name;
    RequestT* current_request;
    
    std::string commandPath;
    std::string commandJsonPath;
	std::string historyPath;
};

#endif  // ARDUINO_FIREBASE_H