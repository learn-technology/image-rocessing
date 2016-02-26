#ifndef _IMAGEPROCESSING_H_
#define _IMAGEPROCESSING_H_

class ImageProcessing{
  public:
  //variables -> image header
    int cols, rows, bands, highVal, totalPixels, header;
    unsigned char * image;


    //function
    void readImage(char **argv);

    void writeImage(char **argv);

};

#endif
