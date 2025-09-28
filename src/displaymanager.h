#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dichiarazione delle funzioni
void initDisplay();
void mostraSchermata(int schermata, float t, float h, int ppm, String ip);

#endif