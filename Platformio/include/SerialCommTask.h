#ifndef __SERIALCOMMUNICATION__
#define __SERIALCOMMUNICATION__

#include "Task.h"
#include "Costants.h"
#include "MsgService.h"
#include "ContainerProp.h"
#include "Gate.h"


class SerialCommTask : public Task {

public:
  SerialCommTask(ContainerProp& container, Gate& gate);  
  void init(int period);  
  void tick();
  void receive();
  void send();
private:
  ContainerProp& container;
  Gate& gate;
  bool msgFullSent;
  bool msgAllarmSent;
};


#endif