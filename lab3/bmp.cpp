#include  "BMP_Read.h"

void gammaCorrection(BMPFile* bmp,int width, int height, double gamma) {
    // Предварительный расчёт таблицы гамма-коррекции
    unsigned char gammaCorrectionTable[256];
    for (int i = 0; i < 256; i++) {
        gammaCorrectionTable[i] = (unsigned char)(pow((double)i / 255.0, 1.0 / gamma) * 255.0);
    }
    // Применение гамма-коррекции к каждому пикселю изображения
    for (int i = 0; i <height * 3; i++) {
        for (int j = 0; j < width * 3; j++) {
            int index = i * width + j;
            bmp->Pixel[index] = gammaCorrectionTable[bmp->Pixel[index]];
        }
    }
}

void writeBMPFile(BMPFile*bmp,char* fileNAme){

    FILE* NewFile = fopen(fileNAme,"wb");


    fwrite(&bmp->bmph,sizeof(BMPHeader),1,NewFile);
    fwrite(&bmp->bmpih,sizeof(BMPInfoHeader),1,NewFile);
    fseek(NewFile,bmp->bmph.PixelOffset,SEEK_SET);
    printf("Negativ -- press 1\nBlack/White -- press 2\nGamma-Correct -- press 3\n");
    int filter = 0;
    while (scanf("%i",filter) != 1 || filter > 3 || filter < 1){
        printf("This filter don't <>\n");
        printf("Enter filter again\n");
        rewind(stdin);
    }
    switch (filter) {
        case 1: {
            for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
                putc(255 - bmp->Pixel[i], NewFile);
            }
            break;
        }
        case 2:{
            for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
                putc((bmp->Pixel[i] + bmp->Pixel[i + 1] + bmp->Pixel[i + 2]) / 3.0f, NewFile); // чб
            }
            break;
        }
        case 3:{
            printf("Pow of gamma:\n");
            int gam;
            while (scanf("%f",gam) != 1 || gam < 0.1 || gam < 5){
                printf("This filter don't <>\n");
                printf("Enter filter again\n");
                rewind(stdin);
            }
            gammaCorrection(bmp,bmp->bmpih.Width,bmp->bmpih.Height,0.7);
            break;
        }
    }
    //  for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
    //putc(255 - bmp->Pixel[i], NewFile);
    //putc((bmp->Pixel[i] + bmp->Pixel[i + 1] + bmp->Pixel[i + 2]) / 3.0f, NewFile); // чб
//    }
    //medianFilter(bmp,427);
    gammaCorrection(bmp,bmp->bmpih.Width,bmp->bmpih.Height,0.7);
    for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
        putc( bmp->Pixel[i], NewFile);
    }
    fclose(NewFile);
}


void printBMPInfo(BMPFile* bmp){

    printf("ID[2] = %c%c;\nSize = %i;\n"
           "PixelOffset = %i;\n",
           bmp->bmph.ID[0],bmp->bmph.ID[1],bmp->bmph.Size,bmp->bmph.PixelOffset);
    printf("\n"
           "HeaderSize = %i;\n"
           "Width =%i;\n"
           "Height = %i;\n"
           "Planes = %i;\n"
           "BitsPerPixel =%i;\n"
           "biCompress =%i;\n"
           "PixelSize =%i;\n"
           "pWidth =%i;\n"
           "pHeight = %i;\n"
           "ColorsCount =%i ;\n"
           "ImpColorsCount =%i;\n",
           bmp->bmpih.HeaderSize,
           bmp->bmpih.Width,
           bmp->bmpih.Height,
           bmp->bmpih.Planes,
           bmp->bmpih.BitsPerPixel,
           bmp->bmpih. biCompress,
           bmp->bmpih. DataSize,
           bmp->bmpih. pWidth,
           bmp->bmpih. pHeight,
           bmp->bmpih. ColorsCount,
           bmp->bmpih. ImpColorsCount);
}
BMPFile* loadBMPFile(char* FileName){

    FILE* fp = fopen(FileName,"r");
    if (!fp){
        printf("THIS FILE '%s' DOES NOT EXIST",FileName);
        exit(-1);
    };

    BMPFile* bmp = (BMPFile*) malloc(sizeof(BMPFile));
    fread(&bmp->bmph,sizeof(BMPHeader),1,fp);
    fread(&bmp->bmpih,sizeof(BMPInfoHeader),1,fp);
    bmp->Pixel = (unsigned char*) malloc(bmp->bmpih.DataSize);
    fseek(fp,bmp->bmph.PixelOffset,SEEK_SET);
    int rowSize = (bmp->bmpih.BitsPerPixel * bmp->bmpih.Width + 31) / 32 * 4;
    int pixelArraySize = rowSize * bmp->bmpih.Height;
    Pixel*pixel =(Pixel*)malloc(pixelArraySize);
    fread(pixel, pixelArraySize, 1,fp);
    fclose(fp);
    return bmp;
}

void freeBMPFile(BMPFile* bmp){
    if(bmp){
        free(bmp);
    };
}
