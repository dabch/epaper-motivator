#include "shuffle.h"
#include <stdlib.h>
#include <Arduino.h>
#include <Adafruit_EPD.h>

void swap_ptr(char **c1, char **c2) {
    char *tmp = *c2;
    *c2 = *c1;
    *c1 = tmp;
}

void shuffle_ptr_array(char **arr, int16_t n) {
    for(int16_t i = 0; i < n; i++) {
        int16_t idx1 = rand() % n;
        int16_t idx2 = rand() % n;
        if(idx1 == idx2)
            continue;
        swap_ptr(&arr[idx1], &arr[idx2]);
    }
}
