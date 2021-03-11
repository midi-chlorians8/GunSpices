#pragma once
//#include <Arduino.h>
 #include <Servo.h>
  
  // 1486 - Покой ;500 -2500 Стороны макс скорость

class ServoLf20{
    private:
    Servo myservo;  // create servo object to control a servo
    #define NoMoove 1486
    #define FULLSPEEDLEFT 2500
    public:
    ServoLf20(){
      myservo.attach(9);
      myservo.writeMicroseconds(NoMoove );
    }
    void SimpleManagement(int freq){
        myservo.writeMicroseconds(freq );
    }
    void FullSpeedLeftAuto(){
        myservo.writeMicroseconds(FULLSPEEDLEFT );
    }
    void StopMoove(){
        myservo.writeMicroseconds(NoMoove );
    }

};
ServoLf20* MyServoLf20Ptr = nullptr; // Cоздали указатель
