#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
int main( int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uc dosya ismi vermelisiniz\n");
        exit(-1);
    }
    int n;
    int fd = open (argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    char buf[] = "Uyari: Bu dosyayi sadece ben okuyabilirim. Benim ismim Melih Yigit Kotman";
    write(fd, buf, sizeof (buf));
    close (fd);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0660);
    char buf2[] = "Uyari: Bu dosyayi ben ve grup uyelerim okuyabiliriz.\n";
    write(fd2, buf2, sizeof(buf2));
    close(fd2);
    umask(0);
    int fd3 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    char buf3[] = "Uyari yok. Bu dosya herkese acik.\n";
    write(fd3, buf3, sizeof(buf3));
    close(fd3);
    return 0;
}