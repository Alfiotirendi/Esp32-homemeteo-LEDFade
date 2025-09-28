# HomeMeteo ESP32 – LED Fade e Dashboard Web

## Descrizione
HomeMeteo è un progetto basato su ESP32 che misura **temperatura, umidità e qualità dell’aria** e li visualizza su un **display OLED**.  
Il dispositivo funge anche da **Access Point Wi-Fi** e ospita una **pagina web** dove è possibile consultare i dati dei sensori e controllare l’effetto **fade di due LED** sia tramite un bottone fisico che via web.  

---

## Funzionalità principali

- Misurazione di:
  - Temperatura (°C) tramite sensore DHT
  - Umidità (%) tramite sensore DHT
  - Qualità dell’aria (ppm) tramite MQ135
- Visualizzazione dati su **display OLED 128x64**
- Cambio schermata sul display tramite **bottone fisico**
- Controllo dei **LED RGB con effetto fade**
  - LED rosso e blu
  - Fade attivabile sia da bottone fisico sia da pagina web
- ESP32 come **Access Point**
  - SSID e password personalizzabili
  - IP della pagina web mostrato sul display
- Server web con:
  - Visualizzazione dei dati in tempo reale
  - Bottone per attivare il fade dei LED

---

## Hardware richiesto

- ESP32 
- Sensore DHT11 o DHT22
- Sensore MQ135 per qualità dell’aria
- Display OLED 128x64 I2C (SSD1306)
- 2 LED (rosso e blu) + resistori
- Pulsanti per cambio schermata e attivazione fade
- Cavi di collegamento e breadboard (o saldature)

---

## Librerie utilizzate

- `WiFi.h` – gestione Wi-Fi
- `WebServer.h` – server web su ESP32
- `DHT.h` – sensore temperatura e umidità
- `MQ135.h` – sensore qualità aria
- `Adafruit_SSD1306` – gestione display OLED

---

## Connessioni consigliate

| Componente      | Pin ESP32          |
|-----------------|------------------|
| DHT             | DHTPIN (definito in config.h) |
| MQ135           | MQ135PIN (definito in config.h) |
| Display OLED SDA| SDA_PIN (es. 25) |
| Display OLED SCL| SCL_PIN (es. 33) |
| LED rosso       | PINRED (PWM LEDC 0) |
| LED blu         | PINBLUE (PWM LEDC 1) |
| Bottone schermata| BUTTON_PIN |
| Bottone fade     | altro PIN o via web |


