//
// Created by Melih Yiğit Kotman on 21.03.2026.
//
//
// Created by Melih Yiğit Kotman on 21.03.2026.
//
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Dosya ismini lutfen duzgunce giriniz!\n");
        exit(-1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("Dosya okunmak icin acilamadi!\n");
        exit(-1);
    }


    int fd2 = open("metin_sesli_harfsiz.txt", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
    if (fd2 < 0) {
        printf("Ikinci dosya olusturulamadi\n");
        exit(-2);
    }
    char buf_rd[1];
    int n;
    while(n = read(fd, buf_rd, sizeof(buf_rd)) > 0) {
        if (buf_rd[0] != 'a' && buf_rd[0] != 'e' && buf_rd[0] != 'i' && buf_rd[0] != 'o' && buf_rd[0] != 'u') {
            if (write(fd2, buf_rd, sizeof(buf_rd)) < 0) {
                printf("Dosyanin icine yazdirilmadi");
                exit(-3);
            }
        }
    }
    close(fd);
    close(fd2);
    return 0;
}