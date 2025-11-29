# 🐾 Proyecto: Cuadrúpedo Educativo con Arduino + FreeRTOS

## Descripción breve
Este proyecto consiste en el desarrollo de un robot cuadrúpedo de bajo costo orientado al **aprendizaje de robótica para estudiantes en Bolivia**.  
Está construido con **MDF y acrílico cortado en láser**, utiliza **servomotores SG90/MG995**, un **Arduino Nano**, **FreeRTOS** para tareas concurrentes, y un **sensor ultrasónico** que actúa como sistema de detección de obstáculos.  

El robot es capaz de:
- Caminar de forma autónoma.
- Retroceder o girar al detectar obstáculos.
- Reconocer patrones rápidos de movimiento (mano entrando/saliendo 3 veces) y realizar un “bailecito”.
- Ejecutar movimientos de forma suave usando interpolación angular.

---

## Diagrama (FSM / Arquitectura)
El diagrama se encuentra en la carpeta:
![FMS](CodigoGeneral/Imagenes/FMS.png)

---

## Tecnologías utilizadas

### 🔹 Hardware
- Arduino Nano / ATmega328P  
- Servomotores SG90 o MG995  
- Sensor ultrasónico HC-SR04  
- Fuente 5V externa para servos  
- MDF y acrílico cortados en láser  

### 🔹 Software
- **Arduino IDE**
- **FreeRTOS para Arduino**
- **Librería Servo.h**
- Código completamente modularizado:
  - `principal.ino`
  - `funciones.cpp`
  - `funciones.h`

### 🔹 Paradigmas utilizados
- Concurrencia mediante tareas FreeRTOS
- Máquina de estados implícita (caminar / evitar / bailar)
- Modularización en arquitectura tipo librería
- Movimiento suave mediante interpolación

---

## 👥 Integrantes y roles

| Integrante        | Rol en el proyecto                                   |
|------------------|--------------------------------------------------------|
| **Oscar Mancilla** | Líder del proyecto, programación embebida, diseño mecánico, diseño del gait (caminar), integración del sensor y FreeRTOS |

---

## Estado actual del proyecto (avances)

### ✔ Completado
- Diseño e impresión/corte del chasis en acrílico y MDF  
- Montaje mecánico de las cuatro patas y servomotores  
- Implementación y modularización del código del robot  
- Tarea concurrente para el sensor ultrasónico (FreeRTOS)  
- Sistema de detección de obstáculos  
- Sistema de reconocimiento rápido (3 detecciones → baile)  
- Funciones completas del gait: `stepA`, `stepB`, `stepC`, `stepD`  
- Movimiento suave con interpolación (`smoothForced`)  
- Bailecito como comportamiento autónomo especial  

### 🔧 En progreso
- Optimización de estabilidad al caminar  
- Ajuste de ángulos para terrenos irregulares  
- Integración de una FSM formal  
- Prueba de baterías externas y autonomía  

### 🧪 Planeado
- Control remoto por Bluetooth o WiFi  
- Agregar sensores adicionales  
- Añadir control PID para suavizar aún más la locomoción  
- Versión final como kit educativo para colegios  

---

