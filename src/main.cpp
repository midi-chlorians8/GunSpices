//12.03.2021 Пушка специи. При участии Егора Викторовича
#include <Arduino.h>

#include "ServoLf20.h"
#include "keyInputFreq.h" // Дебаг покрутить сервой. Ввод с клавиатуры
#include "StartButton.h"

enum EModes{ // Cписок режимов
    AUTOO = 2,
    REFILL = 3,
    SINGL = 1    
} ;
enum ETypePosition{ // Cписок режимов
    Deg = 1,
    Step = 2,
} ;

#include "TumblerModes.h"
#include "PnevmoKlapan.h"

#include "Menu.h"

#include "MyStepper.h"


//MyStepper* MyStepperPtr = nullptr; // Cоздали указатель
class LogicAction{
private:
    TumblerModes tumblerMode;
    StartButton startButton;
    ServoLf20 servoLf20;
    PnevmoKlapan Klapan;
    MyStepper myStepper;

    Menu menu;
    int singlShootCount = 0;
    bool oneRazReadBarabanCountFromDokrut = false; // REFILL MODE
    uint32_t timing = 0;
public:

    void Game(){
        // IntroDisplay();
        //Serial.println( tumblerMode.GetCurrentMode() );
        myStepper.UpdateStepper();
        myStepper.Moove();
        //mystepper.MooveRightOneStep();

///*
        if(tumblerMode.GetModeEnded() == true){ //Если прошлый режим завершился
            tumblerMode.ReadTumblerModes(); //Читаем тумблер режима
        }
//*/

        if(tumblerMode.GetCurrentMode() == AUTOO){//Если тумбрер в положении AUTO Shoot
                static bool letsBegin = false;
                if(startButton.ButtonRead() == true){  
                    
                        //tumblerMode.SetModeEnded(false);
                        startButton.SetOneTimePressed(true);

                        if (singlShootCount == 0)
                        {      
                            letsBegin=true;  //Serial.println(F("letsBegin"));
                        }
                        if(letsBegin){

                                Klapan.KlapanOpenResetSingl();
                                Klapan.KlapanOpenSingl(300);
                               
                                //Надо считать текущую позицию
                                //ReturnToStartPos()

                                myStepper.SetPlusNewAngle(360);
                                if(myStepper.IsBeTurn()==true and myStepper.ReturnCurrentDegPos() > 10){ //Повернуть на 60^
                                        myStepper.MooveDegreesReset();  
                                        Klapan.KlapanOpenResetSingl();
                                    
                                        tumblerMode.SetModeEnded(true);

                                        startButton.RebootButtonRead();
                                        startButton.SetOneTimePressed(false);

                                        singlShootCount = 6;
                                        letsBegin=false;

                                        Serial.print(F("singlShootCount=AUTO: "));Serial.println(singlShootCount); oneRazReadBarabanCountFromDokrut = false;
                                }
                        }
                }
            }
          //  Serial.print(F("tumblerMode.GetCurrentMode(): "));Serial.println(tumblerMode.GetCurrentMode());
        if(tumblerMode.GetCurrentMode() == REFILL){//Если тумбрер в положении Singl Shoot

                    static bool ProkrutBarabanDoNullPosition = false;
                   // static bool oneRazReadBarabanCountFromDokrut = false; // REFILL MODE

                    //Исполнить один раз 
                    if(oneRazReadBarabanCountFromDokrut == false){
                            if(singlShootCount == 6){
                                ProkrutBarabanDoNullPosition=false;Serial.println(F(" ProkrutBarabanDoNullPosition=false:")); startButton.RebootButtonRead(); startButton.SetOneTimePressed(false);
                            }else{
                                ProkrutBarabanDoNullPosition=true; Serial.print(F("singlShootCount=true: "));Serial.println(singlShootCount);
                            }
                        oneRazReadBarabanCountFromDokrut = true;
                    }
                    //Исполнить один раз 

                    if(ProkrutBarabanDoNullPosition == false){
                        //Serial.print(F("startButton.ButtonRead(): "));Serial.println(startButton.ButtonRead());
                            //if(startButton.ButtonRead() == true){   
                                
                                //tumblerMode.SetModeEnded(false);
                                //startButton.SetOneTimePressed(true);
                                //Serial.print(F("startButton.ButtonRead(): "));Serial.println(startButton.ButtonRead());
                                    if(startButton.ButtonRead() == true){   
                                        tumblerMode.SetModeEnded(false); //myStepper.UpdateStepper();
                                        startButton.SetOneTimePressed(true);
                                        
                                            if (singlShootCount >0)
                                            {   
                                                if(Klapan.KlapanOpenSinglNoON(400)==true ) 
                                                {              
                                                        singlShootCount--;     Serial.print(F("singlShootCount:"));Serial.println(singlShootCount);
                                                        myStepper.SetPlusNewAngle(-60);
                                                        if(myStepper.IsBeTurn()==true){ //Повернуть на 60^
                                                               
                                                                myStepper.MooveDegreesReset();  
                                                                Klapan.KlapanOpenResetSingl();
                                                                tumblerMode.SetModeEnded(true);
                                                                startButton.RebootButtonRead();
                                                                startButton.SetOneTimePressed(false);
                                                        }
                                                }
                                            }
                                            if(singlShootCount <= 0){
                                                tumblerMode.SetModeEnded(true);
                                                startButton.RebootButtonRead(); 
                                                startButton.SetOneTimePressed(false);
                                                // Вернуть шесть выстрелов для СинглШот  
                                                //return6AttemptToSnglShot = true;             
                                            }    
                                   // }      

                                    }
                            //}
                    }
                    if(ProkrutBarabanDoNullPosition == true){
                        // Повернуть на  тоесть прокрутить до конца
                            myStepper.SetPlusNewAngle( (6-singlShootCount )*60 ); Serial.print(F("I rotate na: "));Serial.print((6-singlShootCount )*60);
                             if(myStepper.IsBeTurn()==true){
                                    singlShootCount = 6;  Serial.print(F(" Now singlShootCount =  "));Serial.println(singlShootCount);
                                    ProkrutBarabanDoNullPosition = false;
                                    startButton.RebootButtonRead();
                                    startButton.SetOneTimePressed(false);

                                    myStepper.MooveDegreesReset();  
                             }

                    }

            }
          
        if(tumblerMode.GetCurrentMode() == SINGL){//Если тумбрер в положении Singl Shoot
/*
            if(return6AttemptToSnglShot ==true){ //Если мы зарядили уже пушку в режиме fill
                return6AttemptToSnglShot =false;
            }*/

                if(startButton.ButtonRead() == true){   tumblerMode.SetModeEnded(false); //myStepper.UpdateStepper();
                    startButton.SetOneTimePressed(true);
   
                        if (singlShootCount <6)
                        {                    
                            if( Klapan.KlapanOpenSingl(400)==true){
                                singlShootCount++;     Serial.print(F("singlShootCount:"));Serial.println(singlShootCount);
                                myStepper.SetPlusNewAngle(60);
                                if(myStepper.IsBeTurn()==true){ //Повернуть на 60^
                                
                                    myStepper.MooveDegreesReset();  
                                    Klapan.KlapanOpenResetSingl();
                                
                                    tumblerMode.SetModeEnded(true);

                                    startButton.RebootButtonRead();
                                    startButton.SetOneTimePressed(false);
                                }
                            }
                            oneRazReadBarabanCountFromDokrut = false; // Чтоб решал прокручивать или нет
                        }
                        if(singlShootCount >=6){
                        {   
                            tumblerMode.SetModeEnded(true);
                            startButton.RebootButtonRead();
                            startButton.SetOneTimePressed(false);
                            Serial.print(F("singlShootCount>=6:"));Serial.println(singlShootCount);
                             oneRazReadBarabanCountFromDokrut = false; // Чтоб решал прокручивать или нет
                            }
                    }
                }
            }
    
            // Display();
            menu.MenuReadInput();
            menu.Draw(myStepper,tumblerMode,Deg);
            //  Serial.print("startButton.ButtonRead(): ");Serial.print(startButton.ButtonRead() );
            //  Serial.println();
            /*
            myStepper.Print(250);
            if(millis() - timing >250){
                Serial.print(" tumblerMode.GetModeEnded(): ");Serial.println(tumblerMode.GetModeEnded());
                
            timing = millis();
            }
             */


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
 // MyStepperPtr = new MyStepper();
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
//uint32_t timing = 0;
//MyStepper myStepper;

void loop() {
    /*
    myStepper.UpdateStepper();
    int k = keyInputFreq(myStepper);
    myStepper.SimpleManagement(  0- k );

    if( millis() - timing >500){
        Serial.print("k: ");Serial.print(0-k );
         Serial.println();
        timing = millis();
    }
    */

    // Serial.print("k: ");Serial.print(k );
     //       Serial.println();
  // myStepper.UpdateStepper();
    MyLogicActionPtr->Game(  ) ;
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