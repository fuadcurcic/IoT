#include "ESP8266WiFi.h"

// WiFi parameters to be configured
const char* ssid = "ZTE-FC";
const char* password = "foofoo73";

WiFiClient client;

// ThingSpeak Settings
// const channelID = XXX;
String writeAPIKey = "EO8CJUONQCLYCGA7"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000; // post data every 20 seconds


void setup(void)
{
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");


  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

}
void loop() {
  /*
  digitalWrite(LED, HIGH);  // Turn the LED off because the LED is active low
  delay(1000);            // Wait a second
  digitalWrite(LED, LOW);   // Turn the LED on because the LED is active low
  delay(500);
  */

  if (client.connect(server, 80)) {

    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();

    // Construct API request body
    String body = "field1=";
           body += String(rssi);

    Serial.print("RSSI: ");
    Serial.println(rssi);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");

  }
  client.stop();

  // wait and then post again
  delay(postingInterval);
}
