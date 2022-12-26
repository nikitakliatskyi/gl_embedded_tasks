#include <math.h>
#include <stdio.h>

double equation_1(double x, double y) {
  return pow(cos(x), 4) + pow(sin(y), 2) + pow(sin(x * 2), 2) / 4 - 1;
}

double equation_2(double x, double y) { return sin(x + y) * sin(x - y); }

int main() {
  double x, y, z1, z2;

  printf("Enter x: ");
  scanf("%lf", &x);

  printf("Enter y: ");
  scanf("%lf", &y);

  z1 = equation_1(x, y);
  z2 = equation_2(x, y);

  printf("cos(x)^4 + sin(y)^2 + sin(2x)^2/4 - 1 = %lf\n", z1);
  printf("sin(x + y) * sin(x - y) = %lf\n", z2);
}
