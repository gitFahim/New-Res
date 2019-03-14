#include<fstream>
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;


int charToInt(char ch){
	int iValue = (int) ch;
	if(iValue<0) 
		iValue +=255;
	return iValue;
}


void pixel_write(int height, int width, int temp[], char arr[]){

    for(int i=0, j=0; i<height*width*3; i=i+3,j++){

            int gray = charToInt(arr[i]) + charToInt(arr[i+1]) + charToInt(arr[i+2]);
            if(gray > 380)
                temp[j] = 1;
            else
                temp[j] = 0;
        }
}

void getDimentions(){

    char header[52];
    int width, height;

	width = charToInt(header[18])+charToInt(header[19])*pow(2,8)+
			charToInt(header[20])*pow(2,16)+charToInt(header[21])*pow(2,24);
	height = charToInt(header[22])+charToInt(header[23])*pow(2,8)+
			charToInt(header[24])*pow(2,16)+charToInt(header[25])*pow(2,24);
}

void image_write(int height, int width, int temp[], char arr[]) {

    ofstream outFile;
    outFile.open("binFile.txt");

    int binary[height][width];

        for(int i=0, a=0; i<height; i++){
            for(int j=0; j<width; j++){

                binary[i][j] = temp[a];
                a++;
            }
        }
        for(int i=height-1; i>=0; i--){
            for(int j=0; j<width; j++){

                cout<< binary[i][j];
            }
            cout<<endl;
        }
        for(int i=height-1; i>=0; i--){
            for(int j=0; j<width; j++){

                outFile<< binary[i][j];
            }
            outFile<< endl;
        }
        outFile.close();

}

void allbin(FILE *img){
        FILE *ptr_text_out;
        int c;
        ptr_text_out=fopen("test18.bin","w");
        while((c=fgetc(img)) != EOF)
        {
            for(int i=0;i<=7;i++)
            {
                if(c&(1<(7-i)))
                {
                    fputc('1',ptr_text_out);
                }
                else
                {
                    fputc('0',ptr_text_out);
                }
            }
        }


        fclose(img);
        fclose(ptr_text_out);
}

int main(){

    char head[54];
    char fName[11] = {' ', ' ', ' ', ' ', ' ',' ', '.','b', 'm', 'p', '\0'};

    FILE *img;


    for(int index = 100301; index < 100304; index++){

        printf("----------------------------\n");
        for(int i=100000, j=0; i>=1; i=i/10){

            int p = (index/i)%10;
            fName [j] = (char) ('0'+p);
            j++;
        }
        img = fopen(fName, "rb");


        if(!img) {
            cout<< "Could not open file" <<endl;
            return 0;
        }

        fseek(img, 0, SEEK_END);
        int length = ftell(img);
        //cout<<length<<endl;
        fseek(img, 0, SEEK_SET);

        fread(head, 1, 54, img);

        //getDimentions();

        int height = head[18];
        int width = head[22];

        char arr[height*width*3];

        fread(arr, 1, height*width*3, img);

        int temp[height*width+52];

        allbin(img);

        pixel_write(height, width, temp, arr);

        image_write(height, width, temp, arr);

        fclose(img);
    }
}
