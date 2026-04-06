#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	if(argc != 2){
		printf("Dosyanin ismi verilmemistir. Lutfen dosya ismi veriniz!\n");
		exit(-1);
	}
	int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd < 0){
		printf("Dosya olusturulamadi icin acilamadi!\n");
		exit(-2);
	}
	char buf[] = "Bu dosya sadece Melih Yigit Kotman tarafindan okunabilir.\n";
	if(write(fd, buf, sizeof(buf) - 1) < 0) {
		printf("Bu dosyaya yazilamamistir\n");
		exit(-3);
	}
	close(fd);

	int fd2 = open(argv[1], O_WRONLY | O_APPEND);
	if (fd2 < 0) {
		printf("Dosya tekrardan acilamamistir.\n");
		exit(-4);
	}
	if (chmod(argv[1], S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH) < 0) {
		printf("Dosya izineri degistirilemedi");
		exit(-6);
	}

	char buf2[] = "Dosya sahibi okur/yazar, grup arkadaşları yazar, diğerleri okur";
	if(write(fd, buf2, sizeof(buf2) - 1) < 0) {
		printf("Bu ikinci kez dosyaya yazilamamistir\n");
		exit(-5);
	}
	close(fd2);
}

