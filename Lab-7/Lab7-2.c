#include <stdio.h>   /* Sadece ciktilari formatlamak (snprintf, printf) icin biraktik */
#include <fcntl.h>   /* open() fonksiyonu ve O_RDONLY, O_WRONLY vb. bayraklar icin */
#include <unistd.h>  /* read(), write(), close() fonksiyonlari icin */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Hata: Lutfen en az bir dosya ismi giriniz. Kullanim: ./prog8_fd dosya1.txt\n");
        return 1;
    }

    for (int f = 1; f < argc; f++) {
        int fd_in = open(argv[f], O_RDONLY);

        if (fd_in < 0) {
            printf("Hata: '%s' dosyasi acilamadi.\n", argv[f]);
            return 1;
        }

        char out_filename[256];
        int i = 0;
        while (argv[f][i] != '\0') {
            out_filename[i] = argv[f][i];
            i++;
        }
        out_filename[i++] = '.'; out_filename[i++] = 'i';
        out_filename[i++] = 's'; out_filename[i++] = 't';
        out_filename[i] = '\0';


        int fd_out = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0) {
            printf("Hata: '%s' dosyasi olusturulamadi.\n", out_filename);
            close(fd_in);
            return 1;
        }

        char buffer[1024];
        ssize_t bytes_read;

        int letter_count = 0;
        int word_count = 0;
        int sentence_count = 0;
        int in_word = 0;

        while ((bytes_read = read(fd_in, buffer, sizeof(buffer))) > 0) {
            for (ssize_t j = 0; j < bytes_read; j++) {
                char ch = buffer[j];

                int is_letter = (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');

                if (is_letter) {
                    letter_count++;
                    if (!in_word) {
                        in_word = 1;
                        word_count++;
                    }
                } else {
                    in_word = 0;
                }

                if (ch == '.' || ch == '?' || ch == '!') {
                    sentence_count++;
                }
            }
        }

        char out_buffer[512];
        int len = snprintf(out_buffer, sizeof(out_buffer),
                           "Incelenen dosya: %s\nHarf sayisi: %d\nKelime sayisi: %d\nCumle sayisi: %d\n",
                           argv[f], letter_count, word_count, sentence_count);

        write(fd_out, out_buffer, len);

        close(fd_in);
        close(fd_out);

    }

    return 0;
}