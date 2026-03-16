//
// Created by Melih Yiğit Kotman on 17.03.2026.
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 5) {
        printf("Tam 4 girdi verilmelidir.\n");
        printf("Siz %d girdi verdiniz.\n", argc - 1);
        exit(-1);
    }
    int i;
    for (i; i < argc; i++) {
        printf("%d. girdi: %s\n", i, argv[i]);
    }
    exit(0);
}