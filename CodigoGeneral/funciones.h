#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <Arduino.h>
#include <Servo.h>


//  CONSTANTES 


constexpr uint8_t PIN_TRIG = 12;
constexpr uint8_t PIN_ECHO = 11;

constexpr uint32_t PULSE_TIMEOUT_US = 30000;
constexpr float DIST_MIN_CM = 5.0f;
constexpr float DIST_MAX_CM = 20.0f;


constexpr uint16_t FAST_EVENT_WINDOW_MS = 250;
constexpr uint8_t FAST_EVENT_REQUIRED = 3;


constexpr uint16_t SENSOR_TASK_DELAY_MS = 50;


constexpr uint16_t BACKUP_DELAY_MS = 140;


// Pines de servos
constexpr uint8_t PIN_A_H = 2;
constexpr uint8_t PIN_A_V = 3;
constexpr uint8_t PIN_B_H = 4;
constexpr uint8_t PIN_B_V = 5;
constexpr uint8_t PIN_C_H = 6;
constexpr uint8_t PIN_C_V = 7;
constexpr uint8_t PIN_D_H = 8;
constexpr uint8_t PIN_D_V = 9;

// Declaración externa de objetos Servo
extern Servo A_H, A_V;
extern Servo B_H, B_V;
extern Servo C_H, C_V;
extern Servo D_H, D_V;

// Ángulos generales
extern int ANGLE_UP;
extern int ANGLE_DOWN;
extern int ANGLE_FRONT;
extern int ANGLE_BACK;

// Correcciones individuales
extern int FRONT_A, BACK_A;
extern int FRONT_B, BACK_B;
extern int FRONT_C, BACK_C;
extern int FRONT_D, BACK_D;

// Velocidades y variaciones
extern int SPEED_SMOOTH;
extern int ANGLE_UP_B;
extern int ANGLE_DOWN_B;



extern volatile bool obstacleDetected;
extern volatile bool danceTrigger;


// PROTOTIPOS 


// FreeRTOS
void SensorTask(void *pv);

// Inicialización
void initServos();

// Movimiento suave
void smoothForced(Servo &s, int start, int target);
void support(Servo &h1, int t1, Servo &h2, int t2);

// Pasos locomoción
void stepA();
void stepB();
void stepC();
void stepD();

// Movimiento especial
void bailecito();

#endif
