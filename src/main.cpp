#include <Arduino.h>



#include "ServoLf20.h"
#include "keyInputFreq.h"


volatile boolean actionState = LOW;
void myEventListener();


class StartButton{
private:

  #define PIN_LED 13
  bool buttonPressed = false;
public:
  StartButton(){
      pinMode(2, INPUT_PULLUP);
      pinMode(PIN_LED, OUTPUT);
      attachInterrupt(0, myEventListener, LOW);
  }
  void ButtonRead(){
    if(actionState == HIGH){
        buttonPressed = HIGH;
        digitalWrite(PIN_LED, buttonPressed);
    }
  }

};
StartButton* MyStartButtonPtr = nullptr; // Cоздали указатель

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  

  

  
  
  MyStartButtonPtr  = new StartButton();
  MyServoLf20Ptr = new ServoLf20(); // Создали обьект в области оперативной памяти куча heap
}


void loop() {
  // put your main code here, to run repeatedly:
  keyInputFreq();
  MyStartButtonPtr->ButtonRead();
}

void myEventListener() {
  actionState = HIGH; //
  // Выполняем другие действия, например, включаем или выключаем светодиод
  
}