#include "SerialCommTask.h"
#include "ContainerProp.h"

SerialCommTask::SerialCommTask(ContainerProp& container, Gate& gate) : container(container), gate(gate){
    MsgService.init();
    this->msgFullSent = false;
    this->msgAllarmSent = false;
}

void SerialCommTask::init(int period){
    Task::init(period);   
}


void SerialCommTask::tick(){
    if (container.isFull() && !this->msgFullSent ){
        msgFullSent = true;
        MsgService.sendMsg("F");   
    }
    if (container.isAllarmOn() && !this->msgAllarmSent){
        msgFullSent = true;
        MsgService.sendMsg("A");   
    }
    receive();
}

void SerialCommTask::receive(){
    if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();    
        if (container.isAllarmOn() && msg->getContent() == "RESTORE" ){
            this->msgAllarmSent = false;
            this->container.restoreAllarm();
        }else if(container.isFull() && msg->getContent() == "EMPTY"){
            this->msgFullSent = false;
            this->container.emptyContainer();
            gate.emptyGate();
        } else{
            send();
        }
        delete msg;
    }
}

void SerialCommTask::send(){
    String message = "L" + (String)this->container.getWasteLevel() + "T" + (String)this->container.getTempLevel();
    MsgService.sendMsg(message);
}