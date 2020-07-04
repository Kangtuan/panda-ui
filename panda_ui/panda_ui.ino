#include <SoftwareSerial.h>
#include "panda_ui.h"
SoftwareSerial softSerial(2, 3);   // RX:2 TX: 3

PANDA_UI pandaUi(&softSerial, &Serial);

void setup() {
  Serial.begin(9600);
  softSerial.begin(115200);
  softSerial.listen();

}

void loop() {
  
  pandaUi.ShowPicture(GIF_DLY, 0, NULL, -1);
  delay(5000);
  pandaUi.ShowPicture(GIF_CLR, 0, NULL, -1);
  delay(5000);
}
