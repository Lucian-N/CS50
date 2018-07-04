#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h, w, s, c;
    printf("Please select the pyramid height: ");

    h = get_int();

    while (h < 0 || h > 23) {
        printf("Retry: ");
        h = get_int();
    }
    for (w = 1; w <= h; w++) {
            for ( s = h - w; s >= 1; s--) {
                printf("%c", ' ' );
            }

            for ( c = 1; c <= w; c++ ) {
                printf("%c", '#');
            }

            printf("%c ", ' ');
            for ( c = 1; c <= w; c++ ) {
                printf("%c", '#');
            }

            printf("\n");
    }
}