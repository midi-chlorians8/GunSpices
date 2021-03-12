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

// Дисплей
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>


// Дисплей

class LogicAction{
private:
    TumblerModes tumblerMode;
    StartButton startButton;
    ServoLf20 servoLf20;
    PnevmoKlapan Klapan;
    LiquidCrystal_PCF8574 lcd;
    // lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
    bool ShowIntro = false;
public:
    void IntroDisplay(){
        if(ShowIntro == false){
            lcd.setBacklight(255);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("SpiceGun v1.0"));
            delay(1000);
            ShowIntro = true;
        }
    }
    void Display(){
        IntroDisplay();
        lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("Mode:"));
            lcd.setCursor(5, 0);
            if(tumblerMode.GetCurrentMode() == SINGL){
                lcd.print(F("SINGL SHOOT"));
            }
            if(tumblerMode.GetCurrentMode() == AUTO){
                lcd.print(F("AUTO FIRE"));
            }
            if(tumblerMode.GetCurrentMode() == REFILL){
                lcd.print(F("REFILL"));
            }
            delay(100);
    }
    void Game(){
        

        if(tumblerMode.GetModeEnded() == true){ //Если прошлый режим завершился
            tumblerMode.ReadTumblerModes(); //Читаем тумблер режима
        }
            if(tumblerMode.GetCurrentMode() == SINGL){//Если тумбрер в положении Singl Shoot

                if(startButton.ButtonRead() == true){   tumblerMode.SetModeEnded(false);
                    startButton.SetOneTimePressed(true);

                    if( Klapan.KlapanOpenSingl(400)==true){
                        if(servoLf20.MooveDegrees(225)==true){ //Повернуть на 60^
                            startButton.RebootButtonRead();
                            servoLf20.Moove60DegreesReset();  Klapan.KlapanOpenResetSingl();
                        
                            tumblerMode.SetModeEnded(true);
                            startButton.SetOneTimePressed(false);
                        }
                    }
                }
            }
            if(tumblerMode.GetCurrentMode() == AUTO){//Если тумбрер в положении AUTO Shoot

                if(startButton.ButtonRead() == true){   tumblerMode.SetModeEnded(false);
                    startButton.SetOneTimePressed(true);


                    Klapan.KlapanOpenSingl(225*6);
                    servoLf20.MooveDegrees(225*6); //Повернуть на 360^
                    if( servoLf20.GetMooveDegreesState() ==true){

                        servoLf20.Moove60DegreesReset();    
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
                        if(servoLf20.MooveDegrees(225)==true){ //Повернуть на 60^
                            startButton.RebootButtonRead();
                            servoLf20.Moove60DegreesReset();  Klapan.KlapanOpenResetSingl();
                        
                            tumblerMode.SetModeEnded(true);
                            startButton.SetOneTimePressed(false);
                        }
                    //}
                }
            }
            
            Display();
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

  DisplayInit();
  Wire.begin();
  Wire.beginTransmission(0x27);
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