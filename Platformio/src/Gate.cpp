#include "Gate.h"

Gate::Gate(int pinServo) { 
    currentState = 1;
    this->pinServo = pinServo;
    servo.attach(pinServo);
    servo.write(90);
    currentDir = 12002;
    timer = TickCounter();
}

int Gate::getState() {
    return currentState;
}

void Gate::openGate(){
    timer.startTimer(30);
    move(180);
}

void Gate::closeGate(){
    timer.startTimer(50);
    move(90);
}


void Gate::emptyGate(){
    move(0);
}

bool Gate::isTimerElapsed(){
    if (timer.isTimeElapsed()) {
        return true;
    }else{
        timer.dec();
        return false;
    }
}

void Gate::move(int dir){
    if (dir == 0 || dir == 180){
        currentState = OPEN;
    }else if (dir == 90) {
        currentState = NOT_AVAILABLE;
    } 

    if (dir != currentDir){
        servo.write(dir);
        currentDir = dir;
    }
    
    
}

void Gate::setState(int gateState){
    currentState = gateState;
}


