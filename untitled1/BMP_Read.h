
#ifndef BMP_BMP_READ_H
#define BMP_BMP_READ_H

#pragma pack(push,1)

typedef struct {

    unsigned char ID[2];
    unsigned int  Size;
    unsigned char Reserv[4];
    unsigned PixelOffset;
}BMPHeader;

typedef struct{

    unsigned int HeaderSize;
    unsigned int Width;
    unsigned int Height;
    unsigned short Planes;
    unsigned short BitsPerPixel;
    unsigned int biCompress;
    unsigned int DataSize;
    unsigned int pWidth;
    unsigned int pHeight;
    unsigned int ColorsCount;
    unsigned int ImpColorsCount;
}BMPInfoHeader;

typedef struct {

    BMPHeader bmph;
    BMPInfoHeader bmpih;
    unsigned char*  data;

}BMPFile;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

#pragma pop

int compareRGB(const void* a, const void* b);
void medianFilter(BMPFile* bmp,int filterSize);
void gammaCorrection(BMPFile* bmp,int width,int height, double gamma);
void writeBMPFile(BMPFile* bmp,FILE* fp,int type);
void printBMPInfo(BMPFile* bmp);
BMPFile* loadBMPFile(char* FileName);
void freeBMPFile(BMPFile* bmp);

#endif //BMP_BMP_READ_H
