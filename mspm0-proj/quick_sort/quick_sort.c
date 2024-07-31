#include "quick_sort.h"

uint16_t partition(uint16_t array[], uint16_t start_inx, uint16_t end_inx) {
    uint16_t pivot = array[end_inx];
    uint16_t i = (start_inx - 1);
    for (uint16_t j = start_inx; j < end_inx; j++) {
        if (array[j] <= pivot) {
            i++;
            uint16_t temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    uint16_t temp = array[i + 1];
    array[i + 1] = array[end_inx];
    array[end_inx] = temp;
    return (i + 1);
}

void quickSort(uint16_t array[], uint16_t start_inx, uint16_t end_inx) {
    if (start_inx < end_inx) {
        uint16_t pi = partition(array, start_inx, end_inx);
        quickSort(array, start_inx, pi - 1);
        quickSort(array, pi + 1, end_inx);
    }
}