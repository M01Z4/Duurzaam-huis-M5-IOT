#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 5, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// DHT11
#include "DHT.h"
#define DHTTYPE DHT11
uint8_t DHTPin = 24;
DHT dht(DHTPin, DHTTYPE);

float Temperature, Humidity, HeatIndex;

void setup() {
  Serial.begin(115200);
lcd.begin(16, 3);

}

void loop() {
  ReadDHT11();
  lcd.setCursor(0, 1);
  lcd.print("Het is " + String(Temperature) + " .C");
  lcd.print("Het is " + String(Humidity));
  lcd.print("Hoe heet? ") + String(HeatIndex) + "/n";
  delay(10000);
}

void ReadDHT11() {
  float temperature = round(dht.readTemperature() * 10) / 10;
  float humidity = round(dht.readHumidity() * 10) / 10;
  float heatIndex = round(dht.computeHeatIndex(temperature, humidity, false) * 10) / 10;

  if (isnan(temperature) || isnan(humidity) || isnan(heatIndex)) {
    Serial.println("DHT11 sensor error");
  }
  else {
    Temperature = temperature;
    Humidity = humidity;
    HeatIndex = heatIndex;

    Serial.println("Temp: " + String(Temperature) + " .C");
    Serial.println("Humidity: " + String(Humidity));
    Serial.println("% HeatIndex: " + String(HeatIndex) + "\n");
  }


}
