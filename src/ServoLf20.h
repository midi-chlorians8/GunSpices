#pragma once
//#include <Arduino.h>
 #include <Servo.h>
  
  // 1486 - Покой ;500 -2500 Стороны макс скорость

class ServoLf20{
    private:
    Servo myservo;  // create servo object to control a servo
    #define NoMoove 1484
    #define FULLSPEEDLEFT 2000
    #define FULLSPEEDRIGHT 1000
    //300ms =60^
    unsigned long timing; 
    bool oneMeasuring = false;
    bool oneTimeMoove60 = false;

    bool oneTimeMoove360 = false;

    public:
    ServoLf20(){
        myservo.attach(9);
        myservo.writeMicroseconds(NoMoove);
    }
    
    bool MooveDegrees(unsigned long millisec){ // 200 mc

        if(oneTimeMoove60 == false){ // Один раз
            // Один раз замерять текущее время
            if(oneMeasuring == false){
                myservo.writeMicroseconds(FULLSPEEDLEFT);
                timing = millis();
                oneMeasuring = true;
            }
            // Как чуть прокрутилось - остановить
            if (millis() - timing > millisec and oneMeasuring == true){  // if (millis() - timing > 200 and oneMeasuring == true){
                myservo.writeMicroseconds(NoMoove );
                oneTimeMoove60 = true;
            }

        }                            // Один раз
        if(oneTimeMoove60 == true){
            return true;
        }else{
            return false;
        }
        
    }
    bool GetMooveDegreesState(){
         if(oneTimeMoove60 == true){
            return true;
        }else{
            return false;
        }
    }
    void MooveDegreesReset(){
            oneMeasuring = false;
            oneTimeMoove60 = false;
    }

    void FullSpeedLeftAuto(){
        myservo.writeMicroseconds(FULLSPEEDLEFT );
    }
    void StopMoove(){ // СТОП
        myservo.writeMicroseconds(NoMoove );
    }

    void SimpleManagement(int freq){ // ДЕБАГ ввод с клавы
        myservo.writeMicroseconds(freq );
    }
    void MooveRightOneDegrees(){
        myservo.writeMicroseconds(FULLSPEEDRIGHT + 400); 
        delay(30);
        myservo.writeMicroseconds(NoMoove ); 
    }
    void MooveLeftOneDegrees(){
        myservo.writeMicroseconds(FULLSPEEDLEFT - 500); 
        delay(30);
        myservo.writeMicroseconds(NoMoove ); 
    }

};
ServoLf20* MyServoLf20Ptr = nullptr; // Cоздали указатель
