#pragma once
#include <Arduino.h>

#include "MyStepper.h"
#include "GyverEncoder.h"

// Дисплей
    #include <LiquidCrystal_PCF8574.h>
    #include <Wire.h>
// Дисплей


 #include <Servo.h>


class Menu{
private:
// Переменные энкодера
    #define CLK 10
    #define DT 11
    #define SW 12
    Encoder enc1;
// Переменные энкодера

// Переменные меню логики
    int8_t menuLayer = 0;
    int cursorPos =1;
    int old_cursorPos=554;
    bool pressed = false;
// Переменные меню логики

// Переменные дисплея
    LiquidCrystal_PCF8574 lcd;
    bool showIntro = false;

    bool oneRazDraw1 = false;
    bool needRefresh = false;
// Переменные дисплея
EModes old_tumblerMode ;
public:
// =================================== Конструктор ===================================
    Menu(): enc1(CLK, DT, SW){    
        enc1.setType(TYPE2);
        enc1.setTickMode(AUTO);
        
        Wire.begin();
        Wire.beginTransmission(0x27);

        lcd.begin(16, 2); // initialize the lcd
        lcd.setBacklight(255);
    }
// =================================== Конструктор ===================================

    void IntroDisplay(){
        if(showIntro == false){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(F("SpiceGun v1.0"));
            delay(1000);
            showIntro = true;
        }
    }

    void RotaryRightRead(){
        if (enc1.isRight()){
            cursorPos++;
            Serial.print(F("Right "));  Serial.print(F("coutsorPos "));  Serial.println(cursorPos );        
        }
    }
    void RotaryLeftRead(){
        if (enc1.isLeft()){
            cursorPos--;
            Serial.print(F("Left ")); Serial.print(F("coutsorPos "));  Serial.println(cursorPos ); 
        }
    }
    void GraniciKursora(){
        if(cursorPos < 0){
            cursorPos = 0;
        }
        //Serial.print(F("coutsorPos "));  Serial.println(cursorPos ); 
    }


    void MenuReadInput(){
       
        RotaryRightRead();
        RotaryLeftRead();
        GraniciKursora();

        if (enc1.isPress()){ 
            Serial.println(F("Press"));         // нажатие на кнопку (+ дебаунс)
            pressed = !pressed;
        }
    }
    void Draw(MyStepper& myStepper,TumblerModes& tumblerMode,ETypePosition tp){
        IntroDisplay(); // Один раз при старте вывести заставку
        if(menuLayer == 0){


        if(old_tumblerMode != tumblerMode.GetCurrentMode() or needRefresh == true){
             lcd.setCursor(0, 0); lcd.print(F("               "));
                    
                      
                    if(tumblerMode.GetCurrentMode() == 1){
                        lcd.setCursor(0, 0);
                        lcd.print(F("Mode:"));
                        lcd.setCursor(5, 0);   lcd.print("SINGL ");
                    }
                     if(tumblerMode.GetCurrentMode() == 2){
                       lcd.setCursor(0, 0);
                        lcd.print(F("Mode:"));     
                       lcd.setCursor(5, 0); lcd.print("AUTO  ");
                    }
                    if(tumblerMode.GetCurrentMode() == 3){
                        lcd.setCursor(0, 0);
                        lcd.print(F("Mode:"));
                        lcd.setCursor(5, 0);  lcd.print(F("REFILL"));
                    }
                    old_tumblerMode =  tumblerMode.GetCurrentMode();
                    needRefresh = false;
        }




            if (cursorPos == 1 and pressed == false){
                   



                if(oneRazDraw1 == false){

                   

                    lcd.setCursor(0, 1);
                    lcd.print(F(">"));
                    lcd.setCursor(1, 1);
                    lcd.print(F("Set Null Pos"));
                    oneRazDraw1=true;
                }
            }
            if (cursorPos == 1 and pressed == true){
                cursorPos=0; // Чтоб показало что серва стоит в нуле
                //tumblerMode.SetModeEnded(false);
                while(pressed != false){
                    RotaryRightRead();
                    RotaryLeftRead(); 

                    myStepper.UpdateStepper();
                    myStepper.MooveStep();
                    if (old_cursorPos != cursorPos){

                        lcd.clear();
                        lcd.setCursor(0, 1);lcd.print(F(">"));
                        lcd.setCursor(1, 1);lcd.print(myStepper.ReturnCurrentDegPos());lcd.print(F("^"));
                        //lcd.setCursor(6, 1);lcd.print("CurPos"); lcd.setCursor(12, 1);lcd.print(cursorPos);
                        

                        if(cursorPos > old_cursorPos){
                             Serial.println("->");//myStepper.UpdateStepper();
                             //myStepper.SetPlusNewAngle( cursorPos  ); myStepper.MooveDegreesReset();  
                             myStepper.SetJustNewAngleR( (cursorPos) );myStepper.MooveDegreesReset();  
                            // myStepper.SetJustNewAngle(cursorPos);  myStepper.MooveDegreesReset();  
                             //myStepper.MooveRightOneStep();
                             //servoLf20.MooveRightOneDegrees();
                        }else{
                             Serial.println("<-");
                             //myStepper.UpdateStepper();
                             myStepper.SetJustNewAngleL( (cursorPos) ); myStepper.MooveDegreesReset();  
                            // servoLf20.MooveLeftOneDegrees();
                        }

                        old_cursorPos = cursorPos;
                          
                    //myStepper.MooveRightOneStep();
                    }
                 
                    // Если нажат энкодер то выйти
                    if (enc1.isPress()){  pressed = !pressed; oneRazDraw1 = false; cursorPos=1;needRefresh = true; //tumblerMode.SetModeEnded(true);
                    } //Serial.println(F("Press"));         // нажатие на кнопку (+ дебаунс)
                    
                }
            //delay(500);
            }
        }
    }
};