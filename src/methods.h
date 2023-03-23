#ifndef METHODS_H
#define METHODS_H

#include <stdio.h>
#include <stdlib.h>

int readFile(FILE **f);

void readMatrix(FILE *F, int size, int **matrix);

void printMatrix(int **matrix,int size);

int **allocateMatrix(int size);

int selectDirection(int **matrix,int size,int x,int y);

int solveMatrix(int **matrix, int size);

#endif