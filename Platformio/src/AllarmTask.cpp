#include "Arduino.h"
#include "AllarmTask.h"

AllarmTask::AllarmTask(int pinTemp, ContainerProp& container, LCDManager& lcdManager) 
    : container(container), lcdManager(lcdManager) {
    this->pinTemp = pinTemp;
    this->currentIndex = 0;
    this->totalSamples = 0;
    this->sumSamples = 0;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i] = 0;
    }
}

void AllarmTask::init(int period) {
    Task::init(period);
}

void AllarmTask::tick() {
    // Leggi il valore ADC corrente
    int temp_adc_val = analogRead(pinTemp);

    // Aggiorna il buffer circolare
    sumSamples -= samples[currentIndex];  // Rimuovi il valore più vecchio dalla somma
    samples[currentIndex] = temp_adc_val; // Inserisci il nuovo valore
    sumSamples += temp_adc_val;           // Aggiungi il nuovo valore alla somma

    // Sposta l'indice al prossimo slot, ricominciando da 0 se necessario
    currentIndex = (currentIndex + 1) % NUM_SAMPLES;

    // Incrementa il conteggio dei campioni totali (massimo fino a NUM_SAMPLES)
    if (totalSamples < NUM_SAMPLES) {
        totalSamples++;
    }

    // Calcola la media dei campioni
    float avg_adc_val = sumSamples / (float)totalSamples;

    // Converti la media in temperatura
    float referenceVoltage = 5.0; // Cambia a 3.3V se il tuo Arduino usa 3.3V come riferimento
    float temp_val = (avg_adc_val * referenceVoltage) / 1023.0; // Converti in tensione
    temp_val = temp_val * 100.0; // LM35: 10mV per grado Celsius
    
    this->container.setTempLevel((int)temp_val);

    // Stampa la temperatura
    //Serial.print("Temperatura media = ");
    //Serial.print(temp_val, 2); // Stampa con 2 decimali
    //Serial.println(" °C");

}