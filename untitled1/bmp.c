#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include  "BMP_Read.h"

#define FILTER_SIZE 3
#define COLORS 255.0
#define SIZE 256



int compareRGB(const void* a, const void* b) {
    const RGB* pa = (const RGB*)a;
    const RGB* pb = (const RGB*)b;
    return (pa->r + pa->g + pa->b) - (pb->r + pb->g + pb->b);
}

void medianFilter(BMPFile* bmp, int filterSize)
{
    if(filterSize % 2 == 0){
        filterSize++;
    }
    int width = bmp->bmpih.Width;
    int height = bmp->bmpih.Height;
    unsigned char* src_data = bmp->data;
    unsigned char* dst_data = (unsigned char*)malloc(bmp->bmpih.DataSize);

    int row_size = width * FILTER_SIZE;
    int padding = (4 - (row_size % 4)) % 4;

    int half_filter = filterSize / 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGB window[filterSize * filterSize];
            int count = 0;
            for (int ky = -half_filter; ky <= half_filter; ky++) {
                for (int kx = -half_filter; kx <= half_filter; kx++) {
                    int ny = y + ky;
                    int nx = x + kx;

                    if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                        int index = ny * (row_size + padding) + nx * FILTER_SIZE;
                        window[count].r = src_data[index + 2];
                        window[count].g = src_data[index + 1];
                        window[count].b = src_data[index];
                        count++;
                    }
                }
            }

            qsort(window, count, sizeof(RGB), compareRGB);
            RGB median = window[count / 2];
            int dst_index = y * (row_size + padding) + x * 3;
            dst_data[dst_index + 2] = median.r;
            dst_data[dst_index + 1] = median.g;
            dst_data[dst_index] = median.b;
        }
    }

    memcpy(src_data, dst_data, bmp->bmpih.DataSize);
    free(dst_data);
}


void gammaCorrection(BMPFile* bmp,int width, int height, double gamma) {
    // Предварительный расчёт таблицы гамма-коррекции
    unsigned char gammaCorrectionTable[SIZE];
    for (int i = 0; i < SIZE; i++) {
        gammaCorrectionTable[i] = (unsigned char)(pow((double)i / COLORS, 1.0 / gamma) * COLORS);
    }
    // Применение гамма-коррекции к каждому пикселю изображения
    for (int i = 0; i <height * FILTER_SIZE; i++) {
        for (int j = 0; j < width * FILTER_SIZE; j++) {
            int index = i * width + j;
            bmp->data[index] = gammaCorrectionTable[bmp->data[index]];
        }
    }

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
    bmp->data = (unsigned char*) malloc(bmp->bmpih.DataSize);
    fseek(fp,bmp->bmph.PixelOffset,SEEK_SET);
    fread(bmp->data, bmp->bmpih.DataSize, 1,fp);
    fclose(fp);
    return bmp;
}

void writeBMPFile(BMPFile* bmp, FILE* fp,int type)
{
    switch (type) {
        //негатив
        case 1:{
            fwrite(&bmp->bmph,sizeof(BMPHeader),1,fp);
            fwrite(&bmp->bmpih,sizeof(BMPInfoHeader),1,fp);
            fseek(fp,bmp->bmph.PixelOffset,SEEK_SET);
            for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
                putc(255 - bmp->data[i], fp);
            }
            printf("Complete\n");
            break;
        }
        //ч/б
        case 2:{
            fwrite(&bmp->bmph,sizeof(BMPHeader),1,fp);
            fwrite(&bmp->bmpih,sizeof(BMPInfoHeader),1,fp);
            fseek(fp,bmp->bmph.PixelOffset,SEEK_SET);
            for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
                putc( (bmp->data[i] + bmp->data[i + 1] + bmp->data[ i + 2]) / 3.0f, fp);
            }
            printf("Complete\n");
            break;
        }
        //гамма- коррекция
        case 3:{
            fwrite(&bmp->bmph,sizeof(BMPHeader),1,fp);
            fwrite(&bmp->bmpih,sizeof(BMPInfoHeader),1,fp);
            fseek(fp,bmp->bmph.PixelOffset,SEEK_SET);
            double gamma = 0;
            printf("Enter degree of gammma correction\n");
            scanf("%lf",&gamma);
            gammaCorrection(bmp,bmp->bmpih.Width,bmp->bmpih.Height,gamma);
            for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
                putc( bmp->data[i], fp);
            }
            printf("Complete\n");
            break;
        }
        case 4:{
            fwrite(&bmp->bmph,sizeof(BMPHeader),1,fp);
            fwrite(&bmp->bmpih,sizeof(BMPInfoHeader),1,fp);
            fseek(fp,bmp->bmph.PixelOffset,SEEK_SET);
            int filterSize = 0;
            printf("Enter filter size\n");

            while(scanf("%i",&filterSize) != 1 || filterSize > 20 || filterSize <= 1){
                printf("This filter not exist\n");
                printf("Enter again!\n");
                int ch = 0;
                while ((ch = getchar()) != EOF && ch != '\n');
            }
            medianFilter(bmp,filterSize);
            for (int i = 0; i < bmp->bmpih.Width * bmp->bmpih.Height * bmp->bmpih.BitsPerPixel / 8; i++) {
                putc( bmp->data[i], fp);
            }
            printf("Complete\n");
            break;
        }

    }

}


void freeBMPFile(BMPFile* bmp){
    if(bmp){
        free(bmp);
    };
}
