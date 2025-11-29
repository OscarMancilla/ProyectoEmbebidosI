#include <Arduino_FreeRTOS.h>
#include "funciones.h"


void setup() {
    initServos();

    xTaskCreate(
        SensorTask,
        "Sensor",
        128,
        NULL,
        2,
        NULL
    );
}


void loop() {

    if (danceTrigger) {
        bailecito();
        danceTrigger = false;
        return;
    }

    if (!obstacleDetected) {
        stepA();
        stepC();
        stepB();
        stepD();
    }
    else {

        smoothForced(A_H, A_H.read(), BACK_A);
        smoothForced(B_H, B_H.read(), BACK_B);
        smoothForced(C_H, C_H.read(), BACK_C);
        smoothForced(D_H, D_H.read(), BACK_D);

        delay(BACKUP_DELAY_MS);

        smoothForced(A_H, A_H.read(), FRONT_A);
        smoothForced(C_H, C_H.read(), BACK_C);
    }
}
