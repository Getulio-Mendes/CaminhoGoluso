#include "methods.h"

int readFile(FILE **f) {

  char filename[] = "dataset/input.data";
  *f = fopen(filename, "r");

  if (f == NULL) {
    printf("Error ao abrir arquivo\n");
    exit(1);
  }

  int size;
  char buffer[80];
  fgets(buffer, 80, *f);
  sscanf(buffer, "%d", &size);

  return size;
}

int **allocateMatrix(int size) {
  int **matrix;
  // alloca as linhas da matrix
  matrix = malloc(sizeof(int *) * size);
  // alloca todo o armazenamento no primeiro ponteiro
  matrix[0] = malloc(sizeof(int) * size * size);

  for (int i = 0; i < size; i++) {
    // coloca cada ponteiro em sua posição
    matrix[i] = matrix[0] + i * size;
  }

  return matrix;
}

void readMatrix(FILE *f, int size, int **matrix) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      fscanf(f, "%d", &matrix[i][j]);
    }
  }
  // le a linha em branco apos cada matrix
  char buffer[80];
  fgets(buffer, 80, f);
  return;
}

int selectDirection(int **matrix, int size, int x, int y) {
  // popula o array com os valores de todas as direções
  int directions[5] = {-1};

  if (x < size - 1 && y < size - 1) {
    directions[0] = matrix[y + 1][x + 1];
  }
  if (y < size - 1) {
    directions[1] = matrix[y + 1][x];
  }
  if (x < size - 1) {
    directions[2] = matrix[y][x + 1];
  }
  if (x > 0 && y < size - 1) {
    directions[3] = matrix[y + 1][x - 1];
  }
  if (x > 0) {
    directions[4] = matrix[y][x - 1];
  }

  // Acha o maior valor entre as direções
  int index = 0;
  int max = -1;
  for (int i = 0; i < 5; i++) {
    if (directions[i] > max) {
      max = directions[i];
      index = i;
    }
  }
  // Na ultima linha somente anda para direita
  if (y == size - 1) {
    index = 2;
  }

  return index;
}

void printMatrix(int **matrix,int size){
  for(int i=0; i < size;i++){
    for(int j=0; j < size;j++){
      if(matrix[i][j] == -1){
        // print in bold and green
        printf("\x1b[1;32m%d\t",matrix[i][j]);
      }
      else{
        // reset styles to normal
        printf("\x1b[0m%d\t",matrix[i][j]);
      }
    }
    printf("\n");
  }
  printf("\x1b[0m\n");
}

int solveMatrix(int **matrix, int size) {
  int x=0, y=0;
  
  printf("Digite a posição inicial (x,y): ");
  scanf("%d,%d",&x,&y);
  printf("\n");
  
  int total = matrix[y][x];
  matrix[y][x] = -1;

  while (x != size - 1 || y != size - 1) {
    int index = selectDirection(matrix, size, x, y);
    // Move conforme a direção selecionada
    switch (index) {
    case 0:
      x += 1;
      y += 1;
      break;
    case 1:
      y += 1;
      break;
    case 2:
      x += 1;
      break;
    case 3:
      x -= 1;
      y += 1;
      break;
    case 4:
      x -= 1;
      break;
    }

    total += matrix[y][x];
    matrix[y][x] = -1;
  }

  return total;
}