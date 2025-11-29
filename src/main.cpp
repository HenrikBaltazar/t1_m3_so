#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>


#define LED_AMARELO  9
#define LED_VERDE    8
#define LED_AZUL     7
#define BTN1_PIN     3
#define BTN2_PIN     2
#define AMARELO_T1 200
#define AMARELO_T2 2000
#define VERDE_T1   500
#define VERDE_T2   1500
#define AZUL_T     1000
#define DEBOUNCE_MS 150

TaskHandle_t tVerde, tAzul, tAmarelo;
QueueHandle_t queueBtn1;
QueueHandle_t queueBtn2;

typedef struct {
    unsigned long timestamp;
} ButtonEvent;

volatile unsigned long lastPressBTN1 = 0;
volatile unsigned long lastPressBTN2 = 0;

void isrBtn1() {
    unsigned long now = millis();
    if (now - lastPressBTN1 < DEBOUNCE_MS) return;
    lastPressBTN1 = now;

    ButtonEvent e = {now};
    xQueueSendFromISR(queueBtn1, &e, NULL); 
}

void isrBtn2() {
    unsigned long now = millis();
    if (now - lastPressBTN2 < DEBOUNCE_MS) return;
    lastPressBTN2 = now;

    ButtonEvent e = {now};
    xQueueSendFromISR(queueBtn2, &e, NULL);
}


void vReceiverTaskLED_Amarelo(void *pv) {
    pinMode(LED_AMARELO, OUTPUT);
    TickType_t intervaloTicks = pdMS_TO_TICKS(AMARELO_T1);
    unsigned long lastTimePressed = 0;
    ButtonEvent evt;
    bool ledState = false;

    for (;;) {
        if (xQueueReceive(queueBtn1, &evt, intervaloTicks) == pdPASS) {
            unsigned long delta = (evt.timestamp - lastTimePressed) / 1000;
            lastTimePressed = evt.timestamp;
            Serial.print("[AMARELO ");
            if (intervaloTicks == pdMS_TO_TICKS(AMARELO_T1)) {
                intervaloTicks = pdMS_TO_TICKS(AMARELO_T2);
                Serial.print(AMARELO_T2);
            } else {
                intervaloTicks = pdMS_TO_TICKS(AMARELO_T1);
                Serial.print(AMARELO_T1);
            }
            Serial.print("ms] Botao 1 pressionado. Tempo decorrido: ");
            Serial.print(delta);
            Serial.println("s");
        } else {
            ledState = !ledState;
            digitalWrite(LED_AMARELO, ledState ? HIGH : LOW);
        }
    }
}

void vReceiverTaskLED_Verde(void *pv) {
    pinMode(LED_VERDE, OUTPUT);
    TickType_t intervaloTicks = pdMS_TO_TICKS(VERDE_T1);
    unsigned long lastTimePressed = 0;
    ButtonEvent evt;
    bool ledState = false;

    for (;;) {
        if (xQueueReceive(queueBtn2, &evt, intervaloTicks) == pdPASS) {
            unsigned long delta = (evt.timestamp - lastTimePressed) / 1000;
            lastTimePressed = evt.timestamp;
            Serial.print("[VERDE ");
            if (intervaloTicks == pdMS_TO_TICKS(VERDE_T1)) {
                intervaloTicks = pdMS_TO_TICKS(VERDE_T2);
                Serial.print(VERDE_T2);
            } else {
                intervaloTicks = pdMS_TO_TICKS(VERDE_T1);
                Serial.print(VERDE_T1);
            }
            Serial.print("ms] Botao 2 pressionado. Tempo decorrido: ");
            Serial.print(delta);
            Serial.println("s");
        } else {
            ledState = !ledState;
            digitalWrite(LED_VERDE, ledState ? HIGH : LOW);
        }
    }
}

void vReceiverTaskLED_Azul(void *pv) {
    pinMode(LED_AZUL, OUTPUT);
    const TickType_t xDelay = pdMS_TO_TICKS(AZUL_T);
    
    for (;;) {
        digitalWrite(LED_AZUL, HIGH);
        vTaskDelay(xDelay);
        digitalWrite(LED_AZUL, LOW);
        vTaskDelay(xDelay);
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(BTN1_PIN, INPUT_PULLUP);
    pinMode(BTN2_PIN, INPUT_PULLUP);


    queueBtn1 = xQueueCreate(5, sizeof(ButtonEvent));
    queueBtn2 = xQueueCreate(5, sizeof(ButtonEvent)); 

    attachInterrupt(digitalPinToInterrupt(BTN1_PIN), isrBtn1, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN2_PIN), isrBtn2, FALLING);

    xTaskCreate(vReceiverTaskLED_Amarelo, "LED Amarelo", 128, NULL, 1, &tAmarelo);
    xTaskCreate(vReceiverTaskLED_Verde,   "LED Verde",   128, NULL, 1, &tVerde);
    xTaskCreate(vReceiverTaskLED_Azul,    "LED Azul",    128, NULL, 1, &tAzul);
}

void loop() {
}