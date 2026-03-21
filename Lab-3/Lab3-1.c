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
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
    if (fd < 0) {
        printf("Dosya olusturulamadi!\n");
        exit(-2);
    }
    char buf[26] = "Bu dosya yeni olusturuldu";
    if (write(fd, buf, sizeof(buf)) < 0) {
        printf("Dosyanin icine yazdirilmadi");
        exit(-3);
    }
    close(fd);

    fd = open(argv[1], O_WRONLY | O_APPEND);
    if (fd < 0) {
        printf("Dosya ikinci kez acilmadi\n");
        exit(-5);
    }
    char buf2[28] = "\nDosyanin ikinci satiri";
    if (write(fd, buf2, sizeof(buf2)) < 0) {
        printf("Dosyanin ikinci satiri yazdirilmadi\n");
        exit(-6);
    }
    close(fd);
    return 0;
}