#ifndef HANDLE_H
#define HANDLE_H

#include <WebServer.h>

void handleRoot();
void handleCSS();
void handleFade();
void handleRed();
void handleBlue();
void handleOff();
void fadeTask(void *pvParameters);


#endif