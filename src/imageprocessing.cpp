#include "imageprocessing.h"
#include<iostream>
#include<cstdlib>
#include<cstdio>

#define FALSE 0
#define TRUE 1
using namespace std;

void print(){
    cout << "Hi" << endl;
}

void ImageProcessing::readImage(char **argv){
    FILE * fpIn;

    char * string;
    char c;
    int doneReading = FALSE;

    fpIn = fopen(argv[1], "rb");
    if( fpIn == NULL){
        cerr<<"Such File not exist";
        exit(0);
    }

    string = (char *) calloc(256, 1);

    while(!doneReading && (c = (char)fgetc(fpIn)) != '\0'){
        switch (c){
            case 'P':
                c = (char) fgetc(fpIn);
                switch(c){
                    case '2':
                        this->header = 2;
                        this->bands = 1;
                        //pgm palin
                        break;
                    case '5':
                        this->header = 5;
                        this->bands = 1;
                        //pgm normal
                        break;
                    case '3':
                        this->header = 3;
                        this->bands = 3;
                        //ppm plain
                        break;
                    case '6':
                        this->header = 6;
                        this->bands = 3;
                        //ppm normal
                        break;

                }
                c = (char) fgetc(fpIn);
                if(c != 0x0A){ //0xo1 '\n' new line
                    ungetc(c, fpIn);
                }
                else {
                    ungetc(c, fpIn);
                    fgets(string, 256, fpIn);
                }
                break;
                case '#':
                     fgets(string, 256, fpIn);
                cout << "File you entered is " << string << endl;
                break;

                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    ungetc(c, fpIn);
                    fscanf(fpIn, "%d %d %d", &(this->cols), &(this->rows), &(this->highVal));
                    doneReading = TRUE;
                    fgetc(fpIn);
                    break;
        }
    }
        this->totalPixels = this->cols * this->rows * this->bands * 3;
        cout << this->totalPixels <<endl;
        this->image = (unsigned char *) malloc(this->totalPixels);
        fread(this->image, 1, this->totalPixels, fpIn);
        cout << this->image <<endl;
        cout << "Reading the image " << argv[1] << " successful\n";
}

void ImageProcessing::writeImage(char **argv){
    FILE * fpOut;

    fpOut = fopen(argv[2], "wb");
    if(fpOut == NULL){
        cerr<<"Error couldn't write image " << argv[2] << endl;
        exit(0);
    }

    fprintf(fpOut, "P%d\n%d %d\n%d\n", this->header, this->cols, this->rows, this->highVal);
    fwrite(this->image, 1, this->totalPixels, fpOut);
    cout << "Write complete into file " << argv[2] << endl;

}
