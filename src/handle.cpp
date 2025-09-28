#include "handle.h"
#include <Arduino.h>
#include "config.h"
#include <WebServer.h>
#include "DHT.h"
#include "MQ135.h"

// Variabili esterne
extern WebServer server;
extern DHT dht;
extern MQ135 gasSensor;
extern int state;


// Gestione delle richieste HTTP
// Root page
void handleRoot() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float rzero = gasSensor.getRZero();
  float ppm = gasSensor.getPPM();
  Serial.printf("Temperatura: %.2f °C, Umidità: %.2f %%, MQ135 PPM: %.2f, RZero: %.2f\n", t, h, ppm, rzero);

  String page = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  page += "<title>Dati Sensori</title>";
  page += "<link rel='stylesheet' type='text/css' href='/style.css'>";
  page += "</head><body>";
  page += "<div class='container'>";
  page += "<h1>Dati dai sensori</h1>";
  page += "<p><b>Temperatura:</b> " + String(t) + " °C</p>";
  page += "<p><b>Umidità:</b> " + String(h) + " %</p>";
  page += "<p><b>Qualità aria (MQ135):</b> " + String(ppm) + " ppm</p>";
  page += "<p><i>RZero (valore calibrazione):</i> " + String(rzero) + "</p>";
  page += "<h2>Controllo LED</h2>";
  page += "<div class='box'>"; // Contenitore per i bottoni per i led
  page += "<button onclick=\"fetch('/off')\">OFF LED</button>";
  page += "<button onclick=\"fetch('/fade')\">Fade LED</button>";
  page += "<button onclick=\"fetch('/red')\">Blue LED</button>";
  page += "<button onclick=\"fetch('/blue')\">Red LED</button>";
  page += "</div>";
  page += "</div></body></html>";
  server.send(200, "text/html", page);
}

// CSS per la pagina
void handleCSS() {
  String css = "body { font-family: Arial, sans-serif; background:#f0f0f0; text-align:center; }";
  css += "h1 { color: #2c3e50; }";
  css += ".container { background:white; max-width:400px; margin:50px auto; padding:20px; border-radius:10px; box-shadow:0 4px 10px rgba(0,0,0,0.1); }";
  css += "p { font-size:18px; color:#333; }";
  css += "button { padding:10px 20px; font-size:16px; background:#3498db; color:white; border:none; border-radius:5px; cursor:pointer; }";
  css += ".box { margin-top:20px; display:flex; justify-content:space-around; justify-items:center;  }";
  server.send(200, "text/css", css);
}


// Gestione stato LED

void handleFade() {
  state = 3; // Imposta lo stato del fade
  server.sendHeader("Location", "/", true); 
  server.send(200, "text/plain", ""); // reindirizza alla home
}
void handleRed() {
  state = 2; // Imposta lo stato del LED rosso
  server.sendHeader("Location", "/", true); 
  server.send(200, "text/plain", ""); // reindirizza alla home
}
void handleBlue() {
  state = 1; // Imposta lo stato del LED blu
  server.sendHeader("Location", "/", true); 
  server.send(200, "text/plain", ""); // reindirizza alla home
}
void handleOff() {
  state = 0; // Spegne i LED
  server.sendHeader("Location", "/", true); 
  server.send(200, "text/plain", ""); // reindirizza alla home
}

// Task per i LED

void fadeTask(void *pvParameters) {
    int brightness = 0;
    int fadeAmount = 5;

    while(true) {
      if (state == 0) {
            ledcWrite(0, 0); 
            ledcWrite(1, 0); 
        }
      else if (state == 1) {
            ledcWrite(0, 255); 
            ledcWrite(1, 0); 
        }
      else if (state == 2) {
            ledcWrite(0, 0); 
            ledcWrite(1, 255);
        }
      else if (state == 3) {
            ledcWrite(1, 255-brightness);
            ledcWrite(0, brightness);
            brightness += fadeAmount;
            if (brightness <= 0 || brightness >= 255) fadeAmount = -fadeAmount;
        }
            vTaskDelay(30 / portTICK_PERIOD_MS); // 30ms senza bloccare loop principale
  }
}




