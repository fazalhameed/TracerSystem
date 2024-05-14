#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define wifissid "CST WIFI"
#define wifipssd "iotdevs123"
#define led 2

void handleOnroot();
void handleOnNotFound();
uint8_t H, T;
WebServer Server(80);

void setup() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifissid,wifipssd);
  Serial.begin(9600);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.print("\nConnected to ");
  Serial.print(wifissid);
  Serial.print(" with local ip ");
  Serial.print(WiFi.localIP());

  Server.begin();
  Server.on("/", handleOnroot);

  Server.onNotFound(handleOnNotFound);



}

void loop() {

  Server.handleClient();
  delay(500);

}


void handleOnroot() {
  digitalWrite(led, 1);
  char temp[800];

  H = random();
  T = random();

  snprintf(temp, 800,
  "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP32 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
  </body>\
</html>",
           H, T
          );
  Server.send(500, "text/html", temp);
  digitalWrite(led, 0);
}

void handleOnNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found bro\n\n";
  message += "URI: ";
  message += Server.uri();
  message += "\nMethod: ";
  message += (Server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += Server.args();
  message += "\n";

  for (uint8_t i = 0; i < Server.args(); i++) {
    message += " " + Server.argName(i) + ": " + Server.arg(i) + "\n";
  }

  Server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void returnfalse(){
  
  

}