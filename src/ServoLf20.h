#pragma once
//#include <Arduino.h>
 #include <Servo.h>
  
  // 1486 - Покой ;500 -2500 Стороны макс скорость

class ServoLf20{
    private:
    Servo myservo;  // create servo object to control a servo
    #define NoMoove 1484
    #define FULLSPEEDLEFT 2000
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
    
    bool MooveDegrees(uint16_t millisec){ // 200 mc

        if(oneTimeMoove60 == false){ // Один раз
            // Один раз замерять текущее время
            if(oneMeasuring == false){
                    myservo.writeMicroseconds(FULLSPEEDLEFT );
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
    void Moove60DegreesReset(){
            oneMeasuring = false;
            oneTimeMoove60 = false;
    }

    void FullSpeedLeftAuto(){
        myservo.writeMicroseconds(FULLSPEEDLEFT );
    }
    void StopMoove(){ // СТОП
        myservo.writeMicroseconds(NoMoove );
    }

    void SimpleManagement(int freq){ // ДЕБАГ
        myservo.writeMicroseconds(freq );
    }

};
ServoLf20* MyServoLf20Ptr = nullptr; // Cоздали указатель
