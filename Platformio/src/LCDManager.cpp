#include "LCDManager.h"

LCDManager::LCDManager(){
    currentMessage[0] = '\0';

    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
    lcd->backlight();
}

void LCDManager::setMessage(const char* msg) {
    if (strcmp(currentMessage, msg) != 0)
    {
    strncpy(currentMessage, msg, sizeof(currentMessage) - 1);
    currentMessage[sizeof(currentMessage) - 1] = '\0'; 

    lcd->clear();

    char line1[17] = {'\0'}; 
    char line2[17] = {'\0'}; 

    strncpy(line1, msg, 16);
    if (strlen(msg) > 16) {
        strncpy(line2, msg + 16, 16);
    }

    lcd->setCursor(0, 0);
    lcd->print(line1);
    lcd->setCursor(0, 1);
    lcd->print(line2);

    }
}


String LCDManager::getMessage(){
    return currentMessage;
}

void LCDManager::sleep() { 
    lcd->noDisplay();
    lcd->noBacklight();
}

void LCDManager::wakeUp() {
    lcd->display();
    lcd->backlight();
}
