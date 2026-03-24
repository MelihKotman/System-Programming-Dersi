#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Arguman sayisi az!\n");
		exit(-1);
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		printf("Ilk dosya okumak icin acilamadi!\n");
		exit(-2);
	}
	int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, FILE_MODE);
	if(fd2 < 0){
		printf("Ikınci dosya yazmak icin acilamadi!\n");
		exit(-3);
	}
	char buf[] = "Bu dosya Melih Yıgıt Kotman tarafindan olusturulmustur.\n";
	if(write(fd2, buf, sizeof(buf) - 1) < 0){
		printf("Ikinci dosyaya yazi yazdiralamadi!\n");
		exit(-4);
	}
	int word_count = 1;
	int word_in = 0;
	char buf2[1024];
	int n;
	while((n = read(fd, buf2, sizeof(buf2))) > 0){
		for(int i = 0;i < n; i++){
                char  chars = buf2[i];
                if(chars != ' ' && chars != '\n'){
                        if(word_in == 0){
                          word_in = 1;
                        }
                        if(word_count % 2 != 0){
                                write(fd2, &chars, 1);
                        }
                }
                else {
                        if(word_in == 1){
                                if(word_count % 2 != 0){
                                        char bosluk = ' ';
                                        write(fd2, &bosluk, 1);
                                }
                                word_count++;
                                word_in = 0;
                        }
                }
        }
}
        close(fd);
        close(fd2);
}

