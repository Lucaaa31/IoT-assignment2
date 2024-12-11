#include "ContainerProp.h"
#include "Arduino.h"
#include "Costants.h"


ContainerProp::ContainerProp(LCDManager& lcdManager) : lcdManager(lcdManager){
    this->allarm = false;
    this->full = false;
    this->contLevel = 0;
    this->tempLevel = 0;
}

void ContainerProp::setWasteLevel(int level){
    this->contLevel = level;
}
void ContainerProp::setFull(bool state){
    this->full = true;
}

void ContainerProp::setTempLevel(int level){
    this->tempLevel = level;
}

void ContainerProp::setAllarm(bool state){
    this->allarm = state;
}

int ContainerProp::getWasteLevel(){
    return this->contLevel;
}

int ContainerProp::getTempLevel(){
    return this->tempLevel;
}

bool ContainerProp::isFull(){
    return this->full;
}

bool ContainerProp::isAllarmOn(){
    return this->allarm;
}

bool ContainerProp::genericAllarm(){
    return(this->isAllarmOn() || this->isFull());
}

void ContainerProp::restoreAllarm(){
    this->allarm = false;
}
void ContainerProp::emptyContainer(){
    this->full = false;
}
