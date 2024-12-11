#include "GateTask.h"
#include "Arduino.h"
#include "GateButton.h"
#include "Gate.h"

GateTask::GateTask(int button1Pin, int button2Pin, ContainerProp& container, LCDManager& lcdManager, Gate& gate) 
    : container(container), lcdManager(lcdManager), gate(gate) {  
    open = new GateButton(button1Pin);
    close = new GateButton(button2Pin);
    allarmOn = false;
}

void GateTask::init(int period) {
    Task::init(period);
}
/**
 * 1 --> può aprire
 * 2 --> aperto
 * 3 --> non aprire
 */

void GateTask::tick() {
    gate.checkServo();
    if (!container.genericAllarm()){
        if (allarmOn == true && gate.getState() == NOT_AVAILABLE){
            gate.setState(AVAILABLE);
            allarmOn = false;
        }
        
        switch (gate.getState()){
            case AVAILABLE:
                handleAvailableState();
                break;
            case OPEN:
                handleOpenState();
                break;
            case NOT_AVAILABLE:
                handleNotAvaiableState();
                break;
        }
    } else {
        allarmOn = true;
        gate.closeGate();
    }
    
}

void GateTask::handleAvailableState(){
    lcdManager.setMessage(LCD_1);
    if (open->isPressed()){
        lcdManager.setMessage(LCD_2);
        //timer.startTimer(30);
        gate.openGate();
    }
}

void GateTask::handleOpenState(){
    if (gate.isTimerElapsed() || close->isPressed()){
        lcdManager.setMessage(LCD_3);
        gate.closeGate();
    }
}

void GateTask::handleNotAvaiableState(){
    if (gate.isTimerElapsed()){
        lcdManager.setMessage(LCD_1);
        gate.setState(1);
    }
}
