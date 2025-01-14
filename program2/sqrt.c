#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    float input;
    printf("Enter a real number: ");
    scanf("%f", &input);
    printf("\n");
    printf("The square root of %f is %f\n", input, sqrtf(input));
}
