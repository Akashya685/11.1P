
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = "Aka";
const char PASS[]     = "Aka47Pro";

void onAutoModeChange();
void onPasswordInputChange();

bool autoMode;
String passwordInput;

void initProperties(){
  ArduinoCloud.addProperty(autoMode, READWRITE, ON_CHANGE, onAutoModeChange);
  ArduinoCloud.addProperty(passwordInput, READWRITE, ON_CHANGE, onPasswordInputChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
