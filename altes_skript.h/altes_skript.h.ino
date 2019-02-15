

#define BLYNK_PRINT Serial

// #include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <dummy.h>

#include <ThingSpeak.h>

#include <BlynkSimpleEsp32.h>


#define analogPin 4 //the thermistor attach to 
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistor




void listNetworks();
void printWifiData();

//WifiClient client;

uint64_t chipid;
char ssid[] = "AndroidAPCBA0";     //  your network SSID (name)
char pass[] = "sysa5103";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//ThingSpeak
//unsigned long myChannelNumber = 699138;
//const char *myWriteAPIKey = "2XK2T7DU1SYEK0ZU";


//Blynk
char auth[] = "da5926fd30b94bd29fb28f9f2a35b230";

void setup() {
  
  Serial.begin(115200);
  Serial.begin(9600);
  listNetworks();

  Blynk.begin(auth, ssid, pass);

 while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
 printWifiData();

 //ThingSpeak.begin(client);
 
}


void loop() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 1 seconds for connection:
    delay(1000);
  }
 //printWifiData();
  delay(100);

  //read thermistor value 
  long a =4095 - analogRead(analogPin);
  //the calculating formula of temperature
  float tempC = beta /(log((4095.0 * 10 / a - 10) / 10) + beta / 298.0) - 293.0;
  
  
  Serial.print("Die Temperatur betraegt: ");
  Serial.print(tempC);
  Serial.println("°C");
  
  delay(200); //wait for 100 milliseconds

  //ThingSpeak.setField(1,tempC);
  //ThingSpeak.setField(1,tempC);
  //ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  Blynk.run();
  
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    //printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}
