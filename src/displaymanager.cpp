#include "DisplayManager.h"
#include <Wire.h>
#include "config.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define SDA_PIN 25
#define SCL_PIN 33



// Crea l'oggetto display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
    Wire.begin(SDA_PIN, SCL_PIN);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.display();
}

void mostraSchermata(int schermata, float t, float h, int ppm, String ip) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  if(schermata == 0) { // schermata con i dati dei sensori
    display.setTextSize(2);
    display.println("AirStation");
    display.setTextSize(1);
    display.println("Temperatura: " + String(t) + " C");
    display.println("Umidita: " + String(h) + " %");
    display.println("Qualita aria: " + String(ppm) + " ppm");

  } else { // schermata con le credenziali WiFi
    display.setTextSize(2); 
    display.println("AirStation");
    display.setTextSize(1);
    display.println("Credenziali WiFi:");
    display.println("ssid: " + String(WIFI_SSID));
    display.println("password: " + String(WIFI_PASSWORD));  
    display.println("ip pagina: " + String(ip.c_str()));
  }

  display.display();
}