#include "GateButton.h"
#include "Arduino.h"
#include "Costants.h"


GateButton::GateButton(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);     
} 
  
bool GateButton::isPressed(){
    return digitalRead(pin) == HIGH;
}

