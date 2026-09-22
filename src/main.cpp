#include <Arduino.h>
#include "led/Led.h"

const int LED1_PIN = 41;
const int LED2_PIN = 40;

 //Instance de la del
 Led led1(LED1_PIN);
 Led led2(LED2_PIN);

 //Le handler de la tache

 TaskHandle_t  task1Handler = NULL;
 TaskHandle_t  task2Handler = NULL;
//Tache pour la Led1

void vLedTask(void *pvParameters){

  /*Led *led = static_cast <Led*>(pvParameters);*/ /*Pointeur à eviter*/
  Led &led = *static_cast <Led*>(pvParameters);  /* Reference, mieux*/
  while(1){
      led.on();
      vTaskDelay(pdMS_TO_TICKS(1000));
      led.off();
      vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void vLedSuspend(void *pvParameters){
  TaskHandle_t &handle= * (TaskHandle_t*)pvParameters;
  vTaskSuspend(handle);
  vTaskDelay(pdMS_TO_TICKS(10000));
  vTaskResume(handle);
  vTaskDelete(NULL);
}

void setup() {

  led1.init();
  led2.init();

  //Lancer la tache
  BaseType_t retour1 = xTaskCreate(vLedTask,
              "Led1-blink",
              1024,
              &led1,
              1,
              &task1Handler
            );

  BaseType_t retour2 = xTaskCreate(vLedTask,
              "Led2-blink",
              1024,
              &led2,
              1,
              &task2Handler
            );

   BaseType_t retour3 = xTaskCreate(vLedSuspend,
              "Led2-blink",
              1024,
              &task1Handler,
              1,
              NULL
            );
}

void loop() {
  // Rien ici
}
