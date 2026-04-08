#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Dosya sayisi uyusmuyor uc dosya veriniz.\n");
        exit(-1);
    }
    int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    fchmod(fd, S_IRUSR | S_IWUSR);

    char buf1[] = "Uyari: Bu dosyayi sadece ben okuyabilirim. Benim ismim (Melih Yiğit Kotman).\n";

    if (write(fd, buf1, sizeof(buf1) - 1) < 0) {
        printf("Birinci dosyaya yazilamamistir\n");
        exit(-2);
    }
    int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT);
    fchmod(fd2,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    char buf2[] = "Uyari: Bu dosyayi ben ve grup uyelerim okuyabiliriz.\n";

    if (write(fd2, buf2, sizeof(buf2) - 1) < 0) {
        printf("Ikinci dosyaya yazilamamistir\n");
        exit(-3);
    }
    int fd3 = open(argv[3], O_WRONLY | O_TRUNC | O_CREAT);
    fchmod(fd3, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    char buf3[] = "Uyari yok: Bu dosya herkese acik..\n";

    if (write(fd3, buf3, sizeof(buf3) - 1) < 0) {
        printf("Ucuncu dosyaya yazilamamistir\n");
        exit(-3);
    }

    close(fd);
    close(fd2);
    close(fd3);
}