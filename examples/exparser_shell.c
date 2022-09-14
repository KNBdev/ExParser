#include <complex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "exparser.h"

int main (int argc, char *argv[]) {

  printf("\nExParser (build: %s, %s)\n\n", __DATE__, __TIME__);

  const char *prompt = ">>> ";

  char *buffer = NULL;
  size_t size = 1024;

  int error;

  while (true) {

    printf("%s", prompt);
    getline(&buffer, &size, stdin);

    if (strlen(buffer) == 1) {
      continue;
    }

    epExpression *expr = epExpression__compile(buffer, &error, NULL);

    if (expr) {

      double complex result = epExpression__eval_complex(expr);

      if (cimag(result) == 0) {
        printf("Result: %.10f\n", creal(result));
      } else {
        printf("Result: %.10f + %.10f * i\n", creal(result), cimag(result));
      }

      epExpression__delete(expr);

    } else {

      for (unsigned int j = 0; j < ((error == -1) ? 0 : error) + strlen(prompt); j++) {
        printf(" ");
      }
      printf("^ Error near here!\n");
    }
  }

  return 0;
}
