// #include <dht.h>
// #include <SPI.h>
// #include <WiFi101.h>

char ssid[] = "MGUEST";
char pass[] = "guest+internet";
int status = WL_IDLE_STATUS;
// Initialize the Wifi client library
WiFiClient client;
char server[] = "api.thingspeak.com";
String writeAPIKey = "EO8CJUONQCLYCGA7";

int brojac = 0;

void setup() {
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.begin(9600);
}

void loop() {
    Serial.print("===");
    brojac = brojac + 1;
    Serial.println(brojac);
    httpRequest(brojac);
    delay(5000);
}

void httpRequest(String data) {

  //client.stop();
  //client.connect(server, 80);
  client.println("POST /update HTTP/1.1");
  client.println("Host: api.thingspeak.com");
  client.println("Connection: close");
  client.println("User-Agent: ArduinoWiFi/1.1");
  client.println("X-THINGSPEAKAPIKEY: "+writeAPIKey);
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.print(data.length());
  client.print("\n\n");
  client.print(data);
  
}
