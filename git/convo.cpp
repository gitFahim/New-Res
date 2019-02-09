#include <stdio.h>

int main(){

FILE *ptr_bmp_in;
FILE *ptr_text_out;
int c;

ptr_bmp_in=fopen("img_18.bmp","rb");
ptr_text_out=fopen("test18.bin","w");

if(!ptr_bmp_in)
{
    printf("Unable to open file\n");
    return 1;
}

while((c=fgetc(ptr_bmp_in)) != EOF)
    {
        for(int i=0;i<=7;i++)
        {
            if(c&(1<<(7-i)))
            {
                fputc('1',ptr_text_out);
            }
            else
            {
                fputc('0',ptr_text_out);
            }
        }
    }


    fclose(ptr_bmp_in);
    fclose(ptr_text_out);
    printf("Writing done\n");

    return 0;
}
