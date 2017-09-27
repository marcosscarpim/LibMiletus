#include <arduino_firebase.h>

// JSON to send COMMAND_EXECUTE on example code:
// {\"name\":\"lamp.toggleLED\",\"component\":\"lamp\"}

// #define DEBUG

/*
TODO: salvar histórico!!!
*/

#define ERR_MSG(...)           \
do {                         \
  Serial.println("ERROR: "); \
  Serial.print(__VA_ARGS__); \
} while (0)

#ifdef DEBUG
#define DBG_MSG(...)           \
do {                         \
  Serial.print(__VA_ARGS__); \
} while (0)
#define DBG_LNMSG(...)           \
do {                           \
  Serial.println(__VA_ARGS__); \
} while (0)
#else
#define DBG_MSG(...)
#define DBG_LNMSG(...)
#endif

arduino_firebase::arduino_firebase(const char* device_name, const char* host, const char* auth) {
    initialized = true;
    deviceTransportClass = TransportClass::CLOUD;
    this->device_name = device_name;
    Firebase.begin(host, auth);
    commandPath = device_name;
    commandPath.append("/command");
    commandJsonPath = device_name;
    commandJsonPath.append("/cmdjson");
	historyPath = device_name;
	historyPath.append("/history");
	
    // put UNKNOWN on command to start
    Firebase.set(commandPath.c_str(), UNKNOWN); 
	
    ArduinoJson2::StaticJsonBuffer<500> jsonStringBuffer;
	ArduinoJson2::JsonObject& jsonString = jsonStringBuffer.parseObject(
		"{\"name\":\"lamp.toggleLED\",\"component\":\"lamp\"}");
    // put "" on json to start
    Firebase.set(commandJsonPath.c_str(), jsonString);
}

char* arduino_firebase::getProtocol() { return PROTOCOL; }
const char* arduino_firebase::getAddress() { return "null"; }
char* arduino_firebase::getVersion() { return VERSION; }
int arduino_firebase::getPort() { return 0; }

bool arduino_firebase::sendErrorToClient(){
    DBG_LNMSG("arduino_firebase::sendErroToClient()");
}

int arduino_firebase::handleEvent(RequestT* request) {
    int command = Firebase.getInt(commandPath.c_str());

    switch(command) {
        case UNKNOWN:
            request->status = UNKNOWN;
            return -1;
            break;
        case TRAITS:
            request->status = TRAITS;
            break;
        case INFO:
            request->status = INFO;
            break;
        case COMPONENTS:
            request->status = COMPONENTS;
            break;
        case FB_COMMAND_EXECUTE:
            request->status = COMMANDS;
            request->commandID = COMMAND_EXECUTE;
            {
				// convert FirebaseObject to char
                FirebaseObject fobject = Firebase.get(commandJsonPath.c_str());
				ArduinoJson2::JsonObject& obj = fobject.getJsonVariant();
				char jsonChar[100];
				obj.printTo((char*)jsonChar, obj.measureLength() + 1);
				
                request->commandJson = jsonChar;
            }
            break;
        case FB_COMMAND_CANCEL:
            request->status = COMMANDS;
            request->commandID = COMMAND_CANCEL;
            request->commandJson = Firebase.getString(commandJsonPath.c_str()).c_str();
            break;
        case FB_COMMAND_LIST:
            request->status = COMMANDS;
            request->commandID = COMMAND_LIST;
            request->commandJson = Firebase.getString(commandJsonPath.c_str()).c_str();
            break;
        case FB_COMMAND_STATUS:
            request->status = COMMANDS;
            request->commandID = COMMAND_STATUS;
            request->commandJson = Firebase.getString(commandJsonPath.c_str()).c_str();
            break;
    }
	Firebase.set(commandPath.c_str(), UNKNOWN);
	
    return 0;
}

bool arduino_firebase::sendJsonToClient(std::string json) {
    Serial.println("SendingJSONToClient!");
    //Serial.println(json.c_str());
    return this->publish("answer", json.c_str(), true);
}

bool arduino_firebase::publish(const char* subTopic, const char* json,
    bool retained) {
    DBG_LNMSG("Publish message: ");
    DBG_LNMSG(json);
    
    Serial.print("Publish in ");
    Serial.print(subTopic);
    Serial.print(": ");
    Serial.println(json);

    std::string returnPath = device_name;
    returnPath.append("/");
    returnPath.append(subTopic);
	
	// send data to Firebase as it is
	Firebase.set(returnPath.c_str(), json);
	
	// handle error
	if (Firebase.failed()) {
		Serial.print("pushing ");
		Serial.print(subTopic);
		Serial.print(" failed");
		Serial.println(Firebase.error());
	}
	
	
	// if subTopic is components, save values as history
	if(strcmp(subTopic, "out/components") == 0) {
	    ArduinoJson2::StaticJsonBuffer<500> jsonStringBuffer;
		ArduinoJson2::JsonObject& jsonString = jsonStringBuffer.parseObject(json);
		ArduinoJson2::JsonObject& tempTime = jsonString.createNestedObject("timestamp");
		tempTime[".sv"] = "timestamp";

	    Firebase.push(historyPath.c_str(), jsonString);
		
		// handle error
		if (Firebase.failed()) {		
			Serial.print("pushing ");
			Serial.print(historyPath.c_str());
			Serial.print(" failed");
			Serial.println(Firebase.error());
		}
	} 

    return true;
}

DBG_LNMSG(json);