#include<fstream>
#include<iostream>
#include<iomanip>
#include <algorithm>
#include<cmath>

using namespace std;

int height = 28, width = 28;
int currentImg[28][28];
int binImgSum [2][10][28][28];
double probImg[2][10][28][28];
double testProb[10];

void create2d(){
    for (int i=0; i<10; i++) {
        for (int j=0; j<28; j++) {
            for (int k=0; k<28; k++){
                binImgSum[1][i][j][k] = 1;
            }
        }
    }
}

int charToInt(char ch) {
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

void imageSum(int label) {
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            binImgSum[1][label][i][j] = binImgSum[1][label][i][j] + currentImg[i][j];
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
/*
    for(int i=height-1; i>=0; i--){
        for(int j=0; j<width; j++){
            cout<< currentImg[i][j];
        }
       cout<<endl;
    }
    */
}

void countProbabilities() {
    for (int i=0; i<28; i++){
        for (int j=0; j<28; j++) {
            int sum[2] = {0, 0};
            for (int k=0; k<10; k++) {
                sum[0] += binImgSum [0][k][i][j];
                sum[1] += binImgSum [1][k][i][j];
            }
            for (int k=0; k<10; k++) {
                probImg[0][k][i][j] += (double) binImgSum [0][k][i][j] / sum[0];
                probImg[1][k][i][j] += (double) binImgSum [1][k][i][j] / sum[1];
            }
           // cout<<sum[0]<<endl;
           // cout<<sum[1]<<endl;
        }

    }
}

void trainNaiveBayes() {
    create2d();
    int start[10] = {100001, 101001, 102001, 103001, 104001, 105001, 106001, 107001, 108001, 109001};
    int finish[10] = {100200, 101200, 102100, 103200, 104200, 105200, 106200, 107200, 108200, 109200};
    for (int i=0; i<10; i++) {
        for(int index = start[i]; index < finish[i]; index++){
            readImage(index);
            imageSum(i);
        }
    }
/*
    for (int j=0; j<28; j++) {
        for (int k=0; k<28; k++)
            cout << binImgSum[1][0][j][k] << " ";
        cout << endl;
    }

    for (int j=0; j<28; j++) {
        for (int k=0; k<28; k++)
            cout << binImgSum[1][1][j][k] << " ";
        cout << endl;
    }

    for (int j=0; j<28; j++) {
        for (int k=0; k<28; k++)
            cout << binImgSum[1][2][j][k] << " ";
        cout << endl;
    }
*/

    for (int i=0; i<10; i++) {
        int element = finish[i] - start[i];
        for (int j=0; j<28; j++) {
            for (int k=0; k<28; k++) {
                binImgSum[0][i][j][k] = element+2-binImgSum[1][i][j][k];
            }
        }
    }
/*
    for (int j=0; j<28; j++) {
        for (int k=0; k<28; k++)
            cout << binImgSum[0][0][j][k] << " ";
        cout << endl;
    }
*/
    countProbabilities();
}

void calculateSubProbability (int j, double* subProb) {
    double sum = 0.0;
    for (int i=0; i<10; i++) {
        for (int k=0; k<28; k++) {
            int pixel = currentImg[j][k];
            subProb[i] *= probImg[pixel][i][j][k];
        }
        sum = sum + subProb[i];
    }

    for (int i=0; i<10; i++) {
        subProb[i] = subProb[i]/sum;
    }
}

void classifyImage() {
    double *i1;
    double index;
    for (int i=0; i<10; i++) {
        testProb[i] = 1;
        for (int j=0; j<28; j++) {
            double subProb[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
            calculateSubProbability(j, subProb);
            testProb[i] *= subProb[i];
            /*for (int k=0; k<28; k++) {
                int pixel = currentImg[j][k];
                subProb[i] *= probImg[pixel][i][j][k];
            }*/
        }
        cout <<i<<"."<<" "<< testProb[i] << endl;
        i1 = max_element(testProb, testProb+10);
        index = distance(testProb, max_element(testProb, testProb + 10));

    }
    cout<<endl;
    cout <<"The highest probability is ->"<< *i1 <<endl;
    cout <<"The number is ->"<< index <<endl;
}

int main(){
    trainNaiveBayes();
    readImage(105152);
    classifyImage();
    return 0;
}
