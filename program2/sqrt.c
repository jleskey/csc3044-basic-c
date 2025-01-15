/**
 * @file sqrt.c
 * @author Joseph Leskey
 * @date 15 January 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    float input;

    printf("Enter a real number: ");

    if (scanf("%f", &input) != 1) {
        fprintf(stderr, "Bad input.\n");
        return EXIT_FAILURE;
    }

    float result = input < 0 ? sqrtf(-input) : sqrtf(input);
    char notation = input < 0 ? 'i' : '\0';

    printf("\nThe square root of %f is %f%c\n", input, result, notation);

    return EXIT_SUCCESS;
}
