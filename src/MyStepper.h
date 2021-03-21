#pragma once
#include <Arduino.h>

#include "GyverStepper.h"
class MyStepper{
private:
    // Устанавливаем выводы
    const int8_t dir = 5;
    const int8_t step = 3;
    const int8_t en = 4;

    #define DRIVER_STEP_TIME 4  // меняем задержку на 10 мкс
    // Определение тип интерфейса двигателя
    #define motorInterfaceType 1
    //AccelStepper myStepper;
    GStepper< STEPPER2WIRE> stepper;

    int nowDegreesPosition = 0; // Текущее положение в градусах
    int nowStepPosition  = 0; // Текущее положение в 
    bool oneRazAddAngle = false;
public:
   // MyStepper(): myStepper(motorInterfaceType, stepPin, dirPin){
     MyStepper():  stepper ((200*2), step, dir, en){ 
        stepper.setRunMode(FOLLOW_POS);   // режим следования к целевй позиции
        stepper.setMaxSpeed(600);         // установка макс. скорости в шагах/сек
        stepper.setAcceleration(0);     // установка ускорения в шагах/сек/сек
          // пусть драйвер выключается при достижении позиции
        stepper.autoPower(true);
        stepper.reverse(true);
    }
    void Moove(){
        stepper.setTargetDeg(nowDegreesPosition);
    }
       void MooveStep(){
        stepper.setTarget(nowStepPosition);
    }
    void SetPlusNewAngle(int angl){
        if (oneRazAddAngle == false){
            nowDegreesPosition += angl;
            oneRazAddAngle = true;
        }
    }
    void SetJustNewAngleR(int angl){ 
     // if (oneRazAddAngle == false){     
          nowStepPosition += 3;  nowDegreesPosition = stepper.getCurrentDeg();  
     //     oneRazAddAngle = true;
     // }
    }
    void SetJustNewAngleL(int angl){ 
     // if (oneRazAddAngle == false){     
          nowStepPosition -= 3; nowDegreesPosition = stepper.getCurrentDeg();  
     //     oneRazAddAngle = true;
     // }
    }

    void ReturnToStartPos(){
        nowDegreesPosition =0;
    }

    float ReturnCurrentDegPos(){
        return stepper.getCurrentDeg();
    }

    bool IsBeTurn(){
        if( stepper.getTargetDeg() != stepper.getCurrentDeg() ){
            return false;
        } else{
            return true;
        }
    }

    void Print( int time){
        static uint32_t tmr2;
        if (millis() - tmr2 > time) {
                Serial.print(stepper.getTargetDeg());
                Serial.print(',');
                Serial.print(stepper.getCurrentDeg());
                Serial.print(" analogRead(A0): ");Serial.print(analogRead(A0));
                Serial.println();        
                tmr2 = millis();
        }
    }





    void SimpleManagement( int d){
        stepper.setTargetDeg(d);
    }






















    void MooveDegreesReset(){
        oneRazAddAngle = false;
    }


    void MooveRightOneStep(){
        nowDegreesPosition += 10; //=90; //
        stepper.setTargetDeg(nowDegreesPosition); 

       // stepper.setTargetDeg(a); 
    }
    int GetCurrentPosition(){
       // if(p == Deg){
            return stepper.getCurrentDeg();
       // }else{
       //     return stepper.getTarget();            
       // }
    }
    void UpdateStepper(){
        stepper.tick();
    }
    
};