#include "MultiThreading.h"
#include "Eight7SegmentController.h"

Eight7SegmentController controller(4, 2, 3); //ldc

unsigned long sayi = 1;

thread(changer) {
  controller.number(sayi+=13);
  delay_thread(changer, 100);
}

thread(sender) {
  controller.show8();
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  controller.clear();
}

void loop() {
  use_thread(sender);
  use_thread(changer);
}