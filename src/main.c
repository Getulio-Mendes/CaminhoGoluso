#include "methods.h"

// TODO: Pedir o usuário qual a pos inicial

int main() {

  FILE *f;
  int size, result, total = 0;

  size = readFile(&f);
  int **matrix = allocateMatrix(size);

  for(int i=1;!feof(f);i++) {

    readMatrix(f, size, matrix);
    result = solveMatrix(matrix, size);
    printMatrix(matrix,size);
    
    total += result;
    printf("A matriz %d tem o caminho total = %d\n\n", i, result);

  }

  printf("O total do arquivo foi: %d\n",total);
  
  free(matrix[0]);
  free(matrix);
  fclose(f);
}