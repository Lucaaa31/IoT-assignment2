#ifndef __ALLARMTASK__
#define __ALLARMTASK__

#define REFERENCE_VOLTAGE 5
#include "Task.h"
#include "Costants.h"
#include "ContainerProp.h"
#include "LCDManager.h"

class AllarmTask: public Task {
public:
    AllarmTask(int pinTemp, ContainerProp& container, LCDManager& lcdManager);  
    void init(int period);  
    void tick();
private:
    int pinTemp;
    ContainerProp& container;
    LCDManager& lcdManager;
    int readLevel();
    // Aggiunta dei membri privati necessari per il buffer circolare
    static const int NUM_SAMPLES = 100;  // Numero massimo di campioni per la media
    int samples[NUM_SAMPLES];           // Buffer circolare dei campioni
    int currentIndex;                   // Indice del buffer circolare
    int totalSamples;                   // Numero di campioni attualmente validi
    long sumSamples;                    // Somma dei campioni (per calcolo della media)
};

#endif