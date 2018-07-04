#include <stdio.h>
#include <cs50.h>

int main(void) {
    int min;
    printf("Please input the number of minutes spent in the shower:");
    min = get_int();
    int water = min * 12;
    printf("Minutes: %i\nBottles: %i\n", min, water);
}