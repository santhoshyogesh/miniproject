 ARDUINO CODE:
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // Using Node MCU ESP8266 Library.
#include <UniversalTelegramBot.h>  // including the library of Telegram Bot
#include <ArduinoJson.h> // Using JSON Library.
const char* ssid = "ethukku intha vela"; //WIFI Name.
const char* password = "naveen 74"; //WIFI Password.
#define BOTtoken "6645523122:AAF79rT7VMqJ1FmYqXo3NkeW1MdxHgl2xps"  // your Bot Token (Get from Botfather)
#define CHAT_ID "1877980506" // Your bot ID.
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };
client.setInsecure();
// Attempt to connect to Wifi network:
Serial.print("Connecting Wifi: ");
//Display SSID
Serial.println(ssid); // Display SSID
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password); //Start WIFI.
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(5);
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
//Send message to Telegram for program start up.
bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  //delay(500);
  if (mlx.readObjectTempF() >= 100) {
bot.sendMessage(CHAT_ID, "FEVER DETECTED : ", "");
Serial.println("FEVER DETECTED");
//bot.sendMessage(CHAT_ID, analogSensor);
}
else {
bot.sendMessage(CHAT_ID, "FEVER NOT DETECTED");
//bot.sendMessage(CHAT_ID, analogSensor);
Serial.println("FEVER NOT DETECTED");
}
//If String value is Greater Than or Equal to 25
//delay(20);
{
