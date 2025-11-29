#include "funciones.h"

// Servos
Servo A_H, A_V;
Servo B_H, B_V;
Servo C_H, C_V;
Servo D_H, D_V;

// Ángulos generales
int ANGLE_UP    = 10;
int ANGLE_DOWN  = 130;
int ANGLE_FRONT = 45;
int ANGLE_BACK  = 135;

// Correcciones
int FRONT_A = ANGLE_FRONT, BACK_A = ANGLE_BACK;
int FRONT_B = ANGLE_BACK,  BACK_B = ANGLE_FRONT;
int FRONT_C = ANGLE_BACK,  BACK_C = ANGLE_FRONT;
int FRONT_D = ANGLE_FRONT, BACK_D = ANGLE_BACK;

int SPEED_SMOOTH = 8;
int ANGLE_UP_B   = 15;
int ANGLE_DOWN_B = 120;

volatile bool obstacleDetected = false;
volatile bool danceTrigger     = false;


// SENSOR TASK 

void SensorTask(void *pv) {
    long lastEvent = millis();
    uint8_t quickEvents = 0;

    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);

    for (;;) {

        // Trigger del sensor
        digitalWrite(PIN_TRIG, LOW);  delayMicroseconds(2);
        digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);
        digitalWrite(PIN_TRIG, LOW);

        long duration = pulseIn(PIN_ECHO, HIGH, PULSE_TIMEOUT_US);
        float distance = duration * 0.034f / 2.0f;

        if (distance > DIST_MIN_CM && distance < DIST_MAX_CM) {
            obstacleDetected = true;

            if (millis() - lastEvent < FAST_EVENT_WINDOW_MS) {
                quickEvents++;

                if (quickEvents >= FAST_EVENT_REQUIRED) {
                    danceTrigger = true;
                    quickEvents = 0;
                }
            }

            lastEvent = millis();
        }
        else {
            obstacleDetected = false;
        }

        vTaskDelay(SENSOR_TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}



//  INICIALIZACIÓN 


void initServos() {
    A_H.attach(PIN_A_H); A_V.attach(PIN_A_V);
    B_H.attach(PIN_B_H); B_V.attach(PIN_B_V);
    C_H.attach(PIN_C_H); C_V.attach(PIN_C_V);
    D_H.attach(PIN_D_H); D_V.attach(PIN_D_V);

    A_H.write(90); A_V.write(ANGLE_DOWN);
    B_H.write(90); B_V.write(ANGLE_DOWN_B);
    C_H.write(90); C_V.write(ANGLE_DOWN);
    D_H.write(90); D_V.write(ANGLE_DOWN);
}



//  FUNCIONES DE MOVIMIENTO 


void smoothForced(Servo &s, int start, int target) {
    int step = (start < target) ? 2 : -2;

    for (int p = start; p != target; p += step) {
        s.write(p);
        delay(SPEED_SMOOTH);
    }
    s.write(target);
}

void support(Servo &h1, int t1, Servo &h2, int t2) {
    smoothForced(h1, h1.read(), t1);
    smoothForced(h2, h2.read(), t2);
}

void stepA() {
    support(B_H, BACK_B, D_H, BACK_D);

    smoothForced(A_V, A_V.read(), ANGLE_UP);
    smoothForced(A_H, A_H.read(), FRONT_A);
    smoothForced(A_V, A_V.read(), ANGLE_DOWN);
    smoothForced(A_H, A_H.read(), BACK_A);
}

void stepC() {
    support(B_H, BACK_B, D_H, BACK_D);

    smoothForced(C_V, C_V.read(), ANGLE_UP);
    smoothForced(C_H, C_H.read(), FRONT_C);
    smoothForced(C_V, C_V.read(), ANGLE_DOWN);
    smoothForced(C_H, C_H.read(), BACK_C);
}

void stepB() {
    support(A_H, BACK_A, C_H, BACK_C);

    smoothForced(B_V, B_V.read(), ANGLE_UP_B);
    smoothForced(B_H, B_H.read(), FRONT_B);
    smoothForced(B_V, B_V.read(), ANGLE_DOWN_B);
    smoothForced(B_H, B_H.read(), BACK_B);
}

void stepD() {
    support(A_H, BACK_A, C_H, BACK_C);

    smoothForced(D_V, D_V.read(), ANGLE_UP);
    smoothForced(D_H, D_H.read(), FRONT_D);
    smoothForced(D_V, D_V.read(), ANGLE_DOWN);
    smoothForced(D_H, D_H.read(), BACK_D);
}



void bailecito() {
    const int BAILE_1 = 60;
    const int BAILE_2 = 120;

    for (int i = 0; i < 2; i++) {

        smoothForced(A_H, A_H.read(), BAILE_1);
        smoothForced(D_H, D_H.read(), BAILE_2);
        smoothForced(B_H, B_H.read(), BAILE_2);
        smoothForced(C_H, C_H.read(), BAILE_1);

        smoothForced(A_H, A_H.read(), BAILE_2);
        smoothForced(D_H, D_H.read(), BAILE_1);
        smoothForced(B_H, B_H.read(), BAILE_1);
        smoothForced(C_H, C_H.read(), BAILE_2);
    }
}
