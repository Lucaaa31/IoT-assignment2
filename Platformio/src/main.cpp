#include "Arduino.h"
#include "Scheduler.h"
#include "GateTask.h"
#include "Costants.h"
#include "LedTask.h"
#include "ProximityTask.h"
#include "SerialCommTask.h"
#include "ContainerProp.h"
#include "WasteLevelTask.h"
#include "AllarmTask.h"
#include "LCDManager.h"



Scheduler scheduler;

void setup() {
  scheduler.init(50);
  Serial.begin(9600);
  
  LCDManager lcdManager;
  ContainerProp container(lcdManager);
  Gate gate(5);

  Task* gateTask = new GateTask(8, 9, container, lcdManager, gate);
  gateTask->init(100);

  Task* ledTask = new LedTask(3, 4, container);
  ledTask->init(150);

  Task* serialCommTask = new SerialCommTask(container, gate);
  serialCommTask->init(100);

  Task* proxTask = new ProximityTask(2, lcdManager);
  proxTask->init(500);
 
  Task* allarmTask = new AllarmTask(A1, container, lcdManager);
  allarmTask->init(1000);
  
  Task* wasteLevelTast = new WasteLevelTask(12, 11, container);
  wasteLevelTast->init(200);


  scheduler.addTask(wasteLevelTast);
  scheduler.addTask(allarmTask); 
  scheduler.addTask(gateTask);
  scheduler.addTask(ledTask);
  scheduler.addTask(serialCommTask);
  scheduler.addTask(proxTask);
}

void loop() {
  scheduler.schedule();
}

