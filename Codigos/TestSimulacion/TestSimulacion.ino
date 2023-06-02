#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

Adafruit_INA219 ina219;

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    delay(1);
  }
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Varimetro");
  lcd.setCursor(0, 1);
  lcd.print("digital DC");
  delay(2000);
  lcd.clear();

  uint32_t currentFrequency;

  if(! ina219.begin()){
    lcd.setCursor(0, 0);
    lcd.print("Failed to find");
    lcd.setCursor(0, 1);
    lcd.print("INA219 chip");
    while (1) {delay(10);}
  }

  lcd.clear();
  ina219.setCalibration_32V_5A();

  lcd.setCursor(0, 0);
  lcd.print("Measuring voltage");
  lcd.setCursor(0, 2);
  lcd.print("INA219...");
  delay(2000);
  lcd.clear();
}

void loop(void) {
  // put your main code here, to run repeatedly:
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  lcd.clear();
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  int potencia = power_mW/1000;
  loadvoltage = busvoltage + (shuntvoltage/1000);
  lcd.setCursor(0, 0);
  lcd.print("Voltage: "); lcd.print(loadvoltage); lcd.print("V");
  lcd.setCursor(0, 1);
  lcd.print("Current: "); lcd.print(current_mA); lcd.print("mA");
  lcd.setCursor(0, 2);
  lcd.print("Power: "); lcd.print(current_mA); lcd.print("mW");
  Serial.write(potencia);
  delay(1000);
}
