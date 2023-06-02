// Se definen credenciales para acceder al proyecto en la nube de BLYNK
#define BLYNK_TEMPLATE_ID "TMPL2uBbhaytc"
#define BLYNK_TEMPLATE_NAME "Solar Power Monitor"
#define BLYNK_AUTH_TOKEN "vXMxTMoqYcoP3xKcdyHTtY8SUJ8QkSxM"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial

// Librerias
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//Credenciales para acceder a wifi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "RedmiNote10S"; // Nombre de la red
char pass[] = "12345678"; // Contraseña


BlynkTimer timer;

//Variables para almacenar datos a enviar
float vol = 0;
float cur = 0;
float po = 0;

// Tiempo para la funcion de deepsleep
const uint32_t sleepTime = 10 * 1000000;


//Funcion que se encarga de leer y transmitir
void com(){
  //Lectura de los pines analogicos
  vol = analogRead(34)*25/4095;
  cur = analogRead(35)*5000/4095;
  po = vol*cur/1000;

  //Escritura en los pines virtuales de BLYNK
  Blynk.virtualWrite(V0, vol);
  Blynk.virtualWrite(V1, cur);
  Blynk.virtualWrite(V2, po);

  //Impresion de valores en el monitor serial
  Serial.print("Voltaje: ");
  Serial.print(vol);
  Serial.print('\n');
  Serial.print("Corriente: ");
  Serial.print(cur);
  Serial.print('\n');
  Serial.print("Potencia: ");
  Serial.print(po);
  Serial.print('\n');
  delay(500);
}
void setup()
{
  Serial.begin(115200);
  //Conexion a internet
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, com);
  delay(500);
}

void loop() {
  com();
  Blynk.run();
  timer.run();
  //Se entra en modo deepsleep
  esp_sleep_enable_timer_wakeup(sleepTime);
  esp_deep_sleep_start();
}