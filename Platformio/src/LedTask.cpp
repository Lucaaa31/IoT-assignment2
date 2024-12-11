#include "LedTask.h"
#include "Arduino.h"

LedTask::LedTask(int pinGreen, int pinRed, ContainerProp& container): container(container){
    greenLed = new Led(pinGreen);
    redLed = new Led(pinRed);
}

void LedTask::init(int period){
    Task::init(period);
}

void LedTask::tick(){
    if (container.genericAllarm()){
        greenLed->switchOff();
        redLed->switchOn();
    }else{
        greenLed->switchOn();
        redLed->switchOff();
    }
}
