#include "ContainerProp.h"
#include "Arduino.h"
#include "Costants.h"


ContainerProp::ContainerProp(LCDManager& lcdManager) : lcdManager(lcdManager){
    this->allarm = false;
    this->full = false;
    this->contLevel = 0;
    this->tempCount = 0;
    this->tempLevel = 0;
}

void ContainerProp::setWasteLevel(int level){
    this->contLevel = level;
    if (this->contLevel >= MAX_PERC_LEVEL){
        this->full = true;
        lcdManager.setMessage(LCD_4);
    }
}

void ContainerProp::setTempLevel(int level){
    //inizia a caricare i livelli di temperatura dopo che ha fatto la media tra i primi 10, in questo 
    // modo si evitano errori di lettura dovuti a un rumore elettrico del sensore.
    // Inoltre per ottenere un errore ancora minore viene fatta la media sulle ultime 20 letture del sensore

    //Serial.println(tempLevel);
    if (tempCount < 10){
        tempCount++;
    }else{
        this->tempLevel = level;
        if (level >= MAX_TEMP){
            //Serial.print("livello");
            //Serial.println(level);
            this->setAllarm(true);
            lcdManager.setMessage(LCD_5);
        }
    }
}

void ContainerProp::setAllarm(bool state){
    if(this->isAllarmOn() == state){
    }else{
        this->allarm = state;
    }
    
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