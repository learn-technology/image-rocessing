#include "src/imageprocessing.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    ImageProcessing m;
    //argv = (char **) "s.pgm";
    cout << argv[1] << endl;

    if(argc < 1){
        cout<<"Correct format of entering is ./main [filename.pgm or filename.ppm]";
        return 0;
    }
    m.readImage(argv);
    m.writeImage(argv);
    return 0;
}
