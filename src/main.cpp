//12.03.2021 Пушка специи. При участии Егора Викторовича
#include <Arduino.h>



#include "ServoLf20.h"
#include "keyInputFreq.h" // Дебаг покрутить сервой. Ввод с клавиатуры
#include "StartButton.h"



enum EModes{ // Cписок режимов
    SINGL = 1,
    AUTO = 2,
    REFILL = 3
} ;

#include "TumblerModes.h"

#include "PnevmoKlapan.h"

class LogicAction{
private:
    TumblerModes tumblerMode;
    StartButton startButton;
    ServoLf20 servoLf20;
    PnevmoKlapan Klapan;
public:
    void Game(){
        if(tumblerMode.GetModeEnded() == true){ //Если прошлый режим завершился
            tumblerMode.ReadTumblerModes(); //Читаем тумблер режима
        }
            if(tumblerMode.GetCurrentMode() == SINGL){//Если тумбрер в положении Singl Shoot
                if(startButton.ButtonRead() == true){   tumblerMode.SetModeEnded(false);
                    

                    if(servoLf20.Moove60Degrees(300)==true and Klapan.KlapanOpenSingl(400)==true){
                        startButton.RebootButtonRead();

                        servoLf20.Moove60DegreesReset();  Klapan.KlapanOpenResetSingl();
                        
                        tumblerMode.SetModeEnded(true);
                    }
                
            }
        }
       
        //startButton.ButtonRead();

    }
};
LogicAction* MyLogicActionPtr = nullptr; // Cоздали указатель

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  

  //MyStartButtonPtr  = new StartButton();
  //MyServoLf20Ptr    = new ServoLf20(); // Создали обьект в области оперативной памяти куча heap
  //MyKlapanPtr       = new PnevmoKlapan();
  //MyTumblerModesPtr = new TumblerModes();
  MyLogicActionPtr = new LogicAction();
}


void loop() {
  // put your main code here, to run repeatedly:
  //keyInputFreq();
  //MyStartButtonPtr->ButtonRead();
  //Serial.println(analogRead(A0) );
  MyLogicActionPtr->Game();
}

