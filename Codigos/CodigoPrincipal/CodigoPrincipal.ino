#define BLYNK_TEMPLATE_ID "TMPL2uBbhaytc"
#define BLYNK_TEMPLATE_NAME "Solar Power Monitor"
#define BLYNK_AUTH_TOKEN "vXMxTMoqYcoP3xKcdyHTtY8SUJ8QkSxM"

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ORCASITAS";
char pass[] = "63363443";

BlynkTimer timer;
Adafruit_INA219 ina219;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;

const uint32_t sleepTime = 10 * 1000000;

void readINA(){
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage/1000);
  Blynk.virtualWrite(V0, busvoltage);
  Blynk.virtualWrite(V1, current_mA);
  Serial.print("Voltaje: ");
  Serial.print(loadvoltage);
  Serial.print(" V");
  Serial.print('\n');
  Serial.print("Corriente: ");
  Serial.print(current_mA);
  Serial.print(" mA");
  Serial.print('\n');
  delay(1000);
}


void setup(void) {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, readINA);
  uint32_t currentFrequency;
  ina219.setCalibration_32V_5A();
  delay(1000);
}


void loop(void) {
  readINA();
  Blynk.run();
  timer.run();
  esp_sleep_enable_timer_wakeup(sleepTime);
  esp_deep_sleep_start();
}





