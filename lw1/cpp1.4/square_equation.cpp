#include <cstdio>
#include <cmath>

int main()
{
    // 1. prompt user to enter coefficients
    std::puts("please enter a,  b and c for `ax^2 + bx + c = 0`:");

    // 2. read coefficients for equation `ax^2 + bx + c = 0`
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);

    // 3. solve equation `ax^2 + bx + c = 0`
    // solution: `-b ± sqrt(b * b - 4 * 1 * c`
    float x1 = (-b + sqrt(b * b - 4 * 1 * c)) / 2 * a;
    float x2 = (-b - sqrt(b * b - 4 * 1 * c)) / 2 * a;
    std::printf("solution 1: %f\n"
                "solution 2: %f\n",
                x1, x2);
}
