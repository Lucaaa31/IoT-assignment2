#include "ProximityTask.h"
#include "Arduino.h"
#include "Costants.h"
#include <EnableInterrupt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "LCDManager.h"

void interruptHandler();
volatile bool interruptFlag = false;

ProximityTask::ProximityTask(int pinSensor, LCDManager& lcdManager) : lcdManager(lcdManager) {
    this->interruptFlag = false;
    this->lcdManager = lcdManager;
    this->pinSensor = pinSensor;
    this->detectedStatus = false;
    this->val = false;
    tickToSleep = TickCounter();
    pinMode(pinSensor, INPUT);
}

void ProximityTask::init(int period){
    Task::init(period);
}

void ProximityTask::tick(){
    //Serial.println("tack");
    tickToSleep.printRemaining();

    val = digitalRead(pinSensor);  // read input value
    if (val != detectedStatus) {  
        detectedStatus = val;          // check if the input is HIGH
        if (detectedStatus){
            //Serial.println("m");
            tickToSleep.startTimer(TICK_DEEPSLEEP); // da mettere a 20 !!!!!!!!!!!
        }else{
            //Serial.println("f");
        }
    }
    tickToSleep.dec();
    if (tickToSleep.isTimeElapsed()){
        this->sleep();
    }
}

void interruptHandler() {
    disableInterrupt(2);
    interruptFlag = true;
}

void ProximityTask::sleep(){
    // Abilita l'interrupt sul pin specifico
    enableInterrupt(pinSensor, interruptHandler, RISING);
    //lcdManager.setMessage("sleep");
    lcdManager.sleep();
    //Serial.println("sleep");
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    sleep_enable(); 
    sleep_mode();   
    sleep_disable();
    lcdManager.wakeUp();
    // Disabilita l'interrupt sul pin specifico
}
