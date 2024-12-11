# Assignment #2: Smart Waste Disposal System  
**Academic Year:** 2024-2025  


## Project Description  
This assignment involves designing and implementing an **Embedded System** for a **Smart Waste Disposal Container**, specifically for managing dangerous liquid waste. The prototype features hardware and software components to enable smart waste disposal and operator interaction via a connected PC dashboard.  

---

## Hardware Components  

1. **USERDETECTOR**: A PIR sensor to detect user presence.  
2. **WASTEDETECTOR**: A sonar sensor to measure the container's fill level.  
3. **DOOR**: A servo motor controlling a small door for waste entry.  
4. **USERLCD**: An I2C LCD for user interaction.  
5. **Buttons**:  
   - **OPEN**: Opens the DOOR.  
   - **CLOSE**: Closes the DOOR.  
6. **LEDs**:  
   - **L1 (Green)**: Signals normal operation and system availability.  
   - **L2 (Red)**: Signals unavailability or alarm states.  
7. **TEMP**: An analog temperature sensor to monitor internal temperature.  

---

## Software Components  

### **Operator Dashboard**  
A GUI application running on a PC, connected to the Arduino via a serial line, to:  
- **Monitor Container State**:  
  - Filling percentage (0% - 100%).  
  - Temperature inside the container.  
- **Control the Container**:  
  - **Empty** button to simulate emptying the container.  
  - **Restore** button to reset alarms.

---

## System Behavior  

### **Basic Behavior**  
1. **Startup State**:  
   - Container is empty and available.  
   - **L1 (Green LED)** is ON.  
   - **DOOR** is closed (servo motor at 0°).  
   - **USERLCD** displays:  
     ```
     PRESS OPEN TO ENTER WASTE
     ```  

2. **Sleep Mode**:  
   - Triggered if no user is detected for a time interval `Tsleep`.  
   - Only the current status LED (L1 or L2) remains ON.  
   - System wakes when **USERDETECTOR** detects presence.

---

### **Waste Disposal Process**  

1. **Open Door**:  
   - User presses **OPEN**.  
   - **DOOR** opens (servo rotates to +90°).  
   - **USERLCD** displays:  
     ```
     PRESS CLOSE WHEN DONE
     ```  
   - Timeout `T1` ensures the door closes automatically if the user does not press **CLOSE**.  

2. **Close Door**:  
   - User presses **CLOSE** or timeout occurs.  
   - **DOOR** closes (servo back to 0°).  
   - **USERLCD** displays:  
     ```
     WASTE RECEIVED
     ```  
   - Message is shown for `T2` seconds before reverting to the initial state.  

3. **Full Container**:  
   - Detected by **WASTEDETECTOR** if the distance drops below threshold `D1`.  
   - System transitions to unavailable state:  
     - **L1 (Green LED)** OFF, **L2 (Red LED)** ON.  
     - **USERLCD** displays:  
       ```
       CONTAINER FULL
       ```  
   - If detected during waste entry, the **DOOR** closes immediately.  

---

### **Operator Interaction**  

1. **Emptying the Container**:  
   - Triggered via the **Empty** button on the dashboard.  
   - **DOOR** opens on the reverse side (servo rotates to -90°) for `T3` seconds, simulating waste disposal.  
   - System resets to initial state:  
     - **L1 (Green LED)** ON, **L2 (Red LED)** OFF.  
     - **USERLCD** displays:  
       ```
       PRESS OPEN TO ENTER WASTE
       ```  

2. **Temperature Monitoring**:  
   - **TEMP** continuously monitors internal temperature.  
   - If temperature exceeds `MAXTEMP` for more than `MAXTEMPTIME`:  
     - **L1 (Green LED)** OFF, **L2 (Red LED)** ON.  
     - **USERLCD** displays:  
       ```
       PROBLEM DETECTED
       ```  
     - Current waste process is interrupted, and the **DOOR** closes.  
   - Operator resets system using the **Restore** button.  

3. **State Monitoring**:  
   - Dashboard displays:  
     - Current fill percentage (0% to 100%).  
     - [Optional] History of waste levels.  

---

## Implementation Details  

### **Embedded Software**  
- Developed on **Arduino** in **C++/Wiring**.  
- Designed using **Task-Based Architectures** and **Synchronous Finite State Machines (FSMs)**.  

### **PC Dashboard**  
- GUI developed in **Java** (or any preferred language).  
- Communicates with Arduino over a serial connection.  
