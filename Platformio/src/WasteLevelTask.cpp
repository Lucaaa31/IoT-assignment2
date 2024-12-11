    #include "Arduino.h"
    #include "WasteLevelTask.h"
    #include "ContainerProp.h"
    #include "Costants.h"

    const float temperature = 20;
    const float vs = 331.45 + 0.62*temperature;

    WasteLevelTask :: WasteLevelTask (int pinTrig, int pinEcho, ContainerProp& container, LCDManager& lcdManager) 
    : container(container), lcdManager(lcdManager){
        this->pinTrig = pinTrig;
        this->pinEcho = pinEcho;
    }

    void WasteLevelTask :: init(int period){
        pinMode(this->pinTrig, OUTPUT);
        pinMode(this->pinEcho, INPUT);  
        Task::init(period);
        var = 0;
    }

    void WasteLevelTask :: tick(){
        int level = this->readLevel();
        this->container.setWasteLevel(level); 
        if (level >= MAX_PERC_LEVEL){
            this->container.setFull(true);
            lcdManager.setMessage(LCD_4);
        }
    }

    int WasteLevelTask:: readLevel(){
        digitalWrite(this->pinTrig, LOW);
        delayMicroseconds(3);
        digitalWrite(this->pinTrig, HIGH);
        delayMicroseconds(5);
        digitalWrite(this->pinTrig, LOW);

        // Read the result:
        float tUS = pulseIn(this->pinEcho, HIGH);
        float t = tUS / 1000.0 / 1000.0 / 2;
        float d = t*vs;

        int percLevel = ((MAX_CONT_LEVEL - (d*100) + SONAR_HEIGHT) * 100)/MAX_CONT_LEVEL;
        
        if (percLevel <= 0){
            return 0;
        }else if (percLevel >100){
            return 100;
        }else{
            return percLevel;
        }
    }