#include<fstream>
#include<iostream>
#include<iomanip>
#include<cmath>
#define SIZE 28*28*110

using namespace std;

double sum = 0, prob = 0, newSum = 0, newProb = 0;
int height = 28, width = 28;
int currentImg[28][28];
int binImgSum [10][28][28];
int binImgAve [10][28][28];
int newCurrentImg[28][28];

void create2d(){

    for (int i=0; i<10; i++) {
        for (int j=0; j<28; j++) {
            for (int k=0; k<28; k++){
                binImgSum[i][j][k] = 0;
            }
        }
    }
}

int charToInt(char ch)
{
	int iValue = (int) ch;
	if(iValue<0) iValue +=255;
	return iValue;
}

void createBinaryImg(int height, int width, char arr[]){
    int temp[height*width+3];
    for(int i=0, j=0; i<height*width*3; i=i+3,j++){
        int gray = charToInt(arr[i]) + charToInt(arr[i+1]) + charToInt(arr[i+2]);
        if(gray > 380)
            temp[j] = 1;
        else
            temp[j] = 0;
    }

    for(int i=0, a=0; i<height; i++){
        for(int j=0; j<width; j++){
            currentImg[i][j] = temp[a];
            a++;
        }
    }
}

void newCreateBinaryImg(int height, int width, char arr[]){
    int temp[height*width+3];
    for(int i=0, j=0; i<height*width*3; i=i+3,j++){
        int gray = charToInt(arr[i]) + charToInt(arr[i+1]) + charToInt(arr[i+2]);
        if(gray > 380)
            temp[j] = 1;
        else
            temp[j] = 0;
    }

    for(int i=0, a=0; i<height; i++){
        for(int j=0; j<width; j++){
            newCurrentImg[i][j] = temp[a];
            a++;
        }
    }
}

void imageSum(int label) {
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            binImgSum[label][i][j] = binImgSum[label][i][j] + currentImg[i][j];
        }
    }
}

void imgMean(int label) {

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            binImgAve[label][i][j] = (binImgSum[label][i][j] + currentImg[i][j])/60;
        }
    }
}

void readImage (int index) {
    char head[54];
    char fName[11] = {' ', ' ', ' ', ' ', ' ',' ', '.','b', 'm', 'p', '\0'};

    FILE *img;

    for(int i=100000, j=0; i>=1; i=i/10){
        int p = (index/i)%10;
        fName [j] = (char) ('0'+p);
        j++;
    }
    img = fopen(fName, "rb");

    if(!img) {
        cout<< "Could not open file" <<endl;
        return ;
    }

    fseek(img, 0, SEEK_END);
    int length = ftell(img);
    fseek(img, 0, SEEK_SET);

    fread(head, 1, 54, img);
    int height = head[18];
    int width = head[22];

    char arr[height*width*3];

    fread(arr, 1, height*width*3, img);
    fclose(img);

    createBinaryImg(height, width, arr);

    for(int i=height-1; i>=0; i--){
        for(int j=0; j<width; j++){
            //cout<< currentImg[i][j];
        }
        //cout<<endl;
    }
}

void newReadImage (int testIndex) {
    char head[54];
    char fName[11] = {' ', ' ', ' ', ' ', ' ',' ', '.','b', 'm', 'p', '\0'};

    FILE *Iimg;

    for(int i=100000, j=0; i>=1; i=i/10){
        int p = (testIndex/i)%10;
        fName [j] = (char) ('0'+p);
        j++;
    }
    Iimg = fopen(fName, "rb");

    if(!Iimg) {
        cout<< "Could not open file" <<endl;
        return ;
    }

    fseek(Iimg, 0, SEEK_END);
    int length = ftell(Iimg);
    fseek(Iimg, 0, SEEK_SET);

    fread(head, 1, 54, Iimg);
    int height = head[18];
    int width = head[22];
    char arr[height*width*3];

    fread(arr, 1, height*width*3, Iimg);
    fclose(Iimg);

    newCreateBinaryImg(height, width, arr);

    for(int i=height-1; i>=0; i--){
        for(int j=0; j<width; j++){
            //cout<< newCurrentImg[i][j];
        }
       // cout<<endl;
    }
}

int main(){

    create2d();

    for(int index = 100305; index < 100415; index++){
        readImage(index);
        imageSum(2);
        //imgMean(2);
        //imgNumeric(2);
    }

    for (int j=height-1; j>=0; j--) {
        for (int k=0; k<width; k++){
            cout << binImgSum[2][j][k];
            sum += binImgSum[2][j][k];
        }
        cout << endl;
    }
    cout<<sum<<endl;

    prob = sum/(SIZE);
    cout<<prob<<endl;
/*
    for (int j=0; j<28; j++) {
        for (int k=0; k<28; k++)
            cout << binImgAve[2][j][k];
        cout << endl;
    }
*/
    int testIndex = 100375;
        newReadImage(testIndex);

    for (int a=height-1; a>=0; a--) {
        for (int b=0; b<width; b++){
            cout << newCurrentImg[a][b];
            newSum += newCurrentImg[a][b];
        }
        cout << endl;
    }
    cout<<newSum<<endl;

    newProb = newSum/(28*28);
    cout<<newProb<<endl;

    if( (prob - 0.03) <= newProb || newProb >= (prob + 0.03)) {
        cout <<"The given number is 2"<< endl;
    }
    else {
        cout <<"Don't know yet"<< endl;
    }

    return 0;
}
