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



#include "Menu.h"

class LogicAction{
private:
    TumblerModes tumblerMode;
    StartButton startButton;
    ServoLf20 servoLf20;
    PnevmoKlapan Klapan;
    Menu menu;

public:

    void Game(){
        // IntroDisplay();
 //Serial.println( tumblerMode.GetCurrentMode() );

        if(tumblerMode.GetModeEnded() == true){ //Если прошлый режим завершился
            tumblerMode.ReadTumblerModes(); //Читаем тумблер режима
        }
            if(tumblerMode.GetCurrentMode() == SINGL){//Если тумбрер в положении Singl Shoot

                if(startButton.ButtonRead() == true){   tumblerMode.SetModeEnded(false);
                    startButton.SetOneTimePressed(true);

                    if( Klapan.KlapanOpenSingl(400)==true){
                        if(servoLf20.MooveDegrees(210)==true){ //Повернуть на 60^
                            startButton.RebootButtonRead();
                            servoLf20.MooveDegreesReset();  Klapan.KlapanOpenResetSingl();
                        
                            tumblerMode.SetModeEnded(true);
                            startButton.SetOneTimePressed(false);
                        }
                    }
                }
            }
            if(tumblerMode.GetCurrentMode() == 2){//Если тумбрер в положении AUTO Shoot

                if(startButton.ButtonRead() == true){   tumblerMode.SetModeEnded(false);
                    startButton.SetOneTimePressed(true);


                    Klapan.KlapanOpenSingl(209*6);
                    servoLf20.MooveDegrees(1169); //Повернуть на 360^
                    if( servoLf20.GetMooveDegreesState() ==true){

                        servoLf20.MooveDegreesReset();    
                        Klapan.KlapanOpenResetSingl();
                        tumblerMode.SetModeEnded(true);

                        startButton.RebootButtonRead();
                        startButton.SetOneTimePressed(false);    
                    }
                }
            }
            if(tumblerMode.GetCurrentMode() == REFILL){//Если тумбрер в положении Singl Shoot

                if(startButton.ButtonRead() == true){   tumblerMode.SetModeEnded(false);
                    startButton.SetOneTimePressed(true);

                    //if( Klapan.KlapanOpenSingl(400)==true){
                        if(servoLf20.MooveDegrees(208)==true){ //Повернуть на 60^
                            startButton.RebootButtonRead();
                            servoLf20.MooveDegreesReset();  Klapan.KlapanOpenResetSingl();
                        
                            tumblerMode.SetModeEnded(true);
                            startButton.SetOneTimePressed(false);
                        }
                    //}
                }
            }
            
            // Display();
            menu.MenuReadInput();
            menu.Draw(servoLf20,tumblerMode);
    }
};
LogicAction* MyLogicActionPtr = nullptr; // Cоздали указатель

void DisplayInit();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  MyLogicActionPtr = new LogicAction();

 // DisplayInit();
 // Wire.begin();
 // Wire.beginTransmission(0x27);
/*
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SpiceGun v1.0");
*/
}


void loop() {
   
    MyLogicActionPtr->Game();
}





















void DisplayInit(){
 
  delay(1000);
}










  //MyStartButtonPtr  = new StartButton();
  //MyServoLf20Ptr    = new ServoLf20(); // Создали обьект в области оперативной памяти куча heap
  //MyKlapanPtr       = new PnevmoKlapan();
  //MyTumblerModesPtr = new TumblerModes();

    // put your main code here, to run repeatedly:
  //keyInputFreq();
  //MyStartButtonPtr->ButtonRead();
  //Serial.println(analogRead(A0) );