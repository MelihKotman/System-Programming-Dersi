#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("En az bir dosya verilmelidir!\n");
        return -1;
    }
    int i;
    FILE* in;
    FILE* out;
    char name[20];
    int harf;
    int kelime;
    int cumle;
    int c;
    for(i = 1; i < argc; i++)
    {

        if((in = fopen(argv[i],"r")) == NULL)
        {
            printf("Dosya acilamadi.\n");
            return -2;
        }
        snprintf(name,20,"%s.ist",argv[i]);
        out = fopen(name,"w");
        harf = 0;
        kelime = 1;
        cumle = 0;

        while((c = getc(in)) != EOF)
        {
            if(c != ' ' && c != '.' && c != ',' && c != '!' && c != '?' && c != '\n')
            {
                harf++;
            }
            else if(c == '.' ||  c == '!' || c == '?')
            {
                cumle++;
            }
            else if(c == ' ')
            {
                kelime++;
            }
        }

        fprintf(out, "Incelenen dosya: %s\n",argv[i]);
        fprintf(out, "Harf sayisi: %d\n",harf);
        fprintf(out, "Kelime sayisi: %d\n",kelime);
        fprintf(out, "Cumle sayisi: %d\n",cumle);


        fclose(in);
        fclose(out);
    }

    return 0;
}