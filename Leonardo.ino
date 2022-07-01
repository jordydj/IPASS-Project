#include <Wire.h>
#include <Mouse.h>
#include <Keyboard.h>

// reveives info from master via I2C
  void receiveEvent(int howMany){
        while(Wire.available()){
          char input = Wire.read();

// if board receives "u" mouse wheel scrolls up
          if (input == 'u'){
            Serial.print("UP \n");
            Mouse.move(0, 0, 5);
            }

// if board receives "d" mouse wheel scrolls down
          if (input == 'd'){
            Serial.print("DOWN \n");
            Mouse.move(0, 0, -5);
            }

// if board receives "l" website goes to previous page
          if (input == 'l'){
            Serial.print("LEFT \n");
            Keyboard.press(0x82);
            Keyboard.press(0xD8);
            Keyboard.releaseAll();
            }
            
// if board receives "r" website goes to next page        
          if (input == 'r'){
            Serial.print("RIGHT \n");
            Keyboard.press(0x82);
            Keyboard.press(0xD7);
            Keyboard.releaseAll();
            }
        }
    }


void setup() {
  // put your setup code here, to run once:
  Wire.begin(); 
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
     receiveEvent(8);
  
}
