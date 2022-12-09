#include <math.h>
#include <stdio.h>

double equation_1(double x, double y) {
  return pow(cos(x), 4) + pow(sin(y), 2) + pow(sin(x * 2), 2) / 4 - 1;
}

double equation_2(double x, double y) { return sin(x + y) * sin(x - y); }

void clear_stdin() {
  int current_char;
  do {
    current_char = getchar();
  } while (current_char != '\n' && current_char != EOF);
}

int main() {
  double x, y, z1, z2;

  // input value of x validation
  printf("Enter x: ");
  while (scanf("%lf", &x) != 1) {
    printf("Please, enter valid x value: ");
    clear_stdin(); // in the case user's input fails validation, clear stdin, so
                   // that it isn't passed in the next try
  }

  clear_stdin(); // clear stdin to avoid passing input from x in the case user
                 // enters two valid values

  // input value of y validation (works the same as it was with x)
  printf("Enter y: ");
  while (scanf("%lf", &y) != 1) {
    printf("Please, enter valid y value: ");
    clear_stdin();
  }

  z1 = equation_1(x, y);
  z2 = equation_2(x, y);

  printf("cos(x)^4 + sin(y)^2 + sin(2x)^2/4 - 1 = %lf\n", z1);
  printf("sin(x + y) * sin(x - y) = %lf\n", z2);
}
