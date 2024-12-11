#include "Arduino.h"
#include "AllarmTask.h"

AllarmTask::AllarmTask(int pinTemp, ContainerProp& container, LCDManager& lcdManager) 
    : pinTemp(pinTemp), container(container), lcdManager(lcdManager), currentIndex(0), totalSamples(0), sumSamples(0) {
    
    // Inizializza il buffer con valori medi ADC per 20°C
    int defaultAdcValue = (20 * 1023) / (REFERENCE_VOLTAGE * 100); // Calcola il valore ADC per 20°C
    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i] = defaultAdcValue; 
        sumSamples += defaultAdcValue; // Aggiorna la somma iniziale
    }
    totalSamples = NUM_SAMPLES; // Partiamo con un buffer pieno
}

void AllarmTask::init(int period) {
    Task::init(period);
}

void AllarmTask::tick() {
    int level = this->readLevel();
    // Aggiorna la temperatura nel container
    this->container.setTempLevel(level);
    if (level >= MAX_TEMP){
        this->container.setAllarm(true);
        lcdManager.setMessage(LCD_5);
    }
}

int AllarmTask::readLevel(){
    // Leggi il valore ADC corrente
    int temp_adc_val = analogRead(pinTemp);

    // Debug: stampa il valore letto
    //Serial.print("Valore ADC letto: ");
    //Serial.println(temp_adc_val);

    // Aggiorna il buffer circolare
    sumSamples -= samples[currentIndex];      // Rimuovi il valore più vecchio dalla somma
    samples[currentIndex] = temp_adc_val;     // Inserisci il nuovo valore
    sumSamples += temp_adc_val;               // Aggiungi il nuovo valore alla somma

    // Aggiorna l'indice circolare
    currentIndex = (currentIndex + 1) % NUM_SAMPLES;

    // Calcola la media dei campioni
    float avg_adc_val = sumSamples / (float)totalSamples;

    // Debug: stampa la somma e il conteggio
    //Serial.print("Somma campioni: ");
    //Serial.println(sumSamples);
    //Serial.print("Numero campioni: ");
    //Serial.println(totalSamples);

    // Converti la media ADC in temperatura
    float tempVoltage = (avg_adc_val * REFERENCE_VOLTAGE) / 1023.0; // Tensione in Volt
    float temp_val = tempVoltage * 100.0; // LM35: 10mV per grado Celsius
    // Stampa la temperatura (media ADC e convertita)
    //Serial.print("Media ADC = ");
    //Serial.print(avg_adc_val, 2);
    //Serial.print(", Temperatura = ");
    //Serial.print(static_cast<int>(round(temp_val)));
    //Serial.println(" °C");
    return temp_val;
}