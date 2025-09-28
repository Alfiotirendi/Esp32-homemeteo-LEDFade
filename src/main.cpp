#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
#include "MQ135.h"
#include "displaymanager.h"
#include "config.h"
#include "handle.h"


// ===== Sensori =====
DHT dht(DHTPIN, DHTTYPE);
MQ135 gasSensor = MQ135(MQ135PIN);

// ===== Web server =====
WebServer server(80);
// ===== Variabili globali =====
std::string ip_str;
int state = 0; // Stato led (0=spento, 1=rosso, 2=blu, 3=fade) 

void setup() {
  Serial.begin(115200);

  dht.begin();
  initDisplay(); // Mostra schermata iniziale
  mostraSchermata(0, dht.readTemperature(), dht.readHumidity(), (int)gasSensor.getPPM(), String(ip_str.c_str()));
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUTTON_LED, INPUT);

  // Configurazione LED con PWM
  ledcSetup(0, 5000, 8); // Canale 0
  ledcAttachPin(PINRED, 0); // LED rosso
  ledcSetup(1, 5000, 8); // Canale 1
  ledcAttachPin(PINBLUE, 1); // LED blu
  
  // Crea il task per il fade
  xTaskCreatePinnedToCore(fadeTask, "Fade Task", 1000, NULL, 1, NULL, 0);

  // WiFi
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Server attivo! IP address: ");
  Serial.println(WiFi.softAPIP());
  ip_str = WiFi.softAPIP().toString().c_str();

  // Web server routes
  server.on("/", handleRoot);
  server.on("/style.css", handleCSS);
  server.on("/fade", handleFade);
  server.on("/red", handleRed);
  server.on("/blue", handleBlue);
  server.on("/off", handleOff);
  server.begin();
  Serial.println("Web server avviato!");
  
 
}

void loop() {
  server.handleClient();
  if (digitalRead(BUTTON_PIN) == LOW) { // Bottone premuto (assumendo LOW quando premuto)
    static unsigned long lastPress = 0;
    if (millis() - lastPress > 1000) { // Debounce di 1000ms
      static int schermata = 0;
      schermata = 1 - schermata; // Alterna tra 0 e 1
      mostraSchermata(schermata, dht.readTemperature(), dht.readHumidity(), (int)gasSensor.getPPM(), String(ip_str.c_str()));
      lastPress = millis();
    }
  }

  if (digitalRead(BUTTON_LED) == LOW) { // Bottone LED premuto
    static unsigned long lastPressLED = 0;
    if (millis() - lastPressLED > 1000) { // Debounce di 1000ms
      state = (state + 1) % 4; // Cambia stato dei led
      lastPressLED = millis();
    }
  }

}