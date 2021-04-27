#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

// https://docs.microsoft.com/pl-pl/previous-versions/dd183376(v=vs.85)
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

int get_headervalue(int *i,int bitSize, FILE *fp)
{
    fread(i,bitSize,1,fp);
}

void printf_histogram(WORD*colour, int size, int colournumb){
    int t = 0, tmp =0;
    int f1 = 0, f2= 0, f3 =0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0, f15=0, f16=0;
    for(t;t<size;t++){
        tmp = colour[t];
        if (tmp<16){
            f1++;
        }
        else if (tmp<32){
            f2++;
        }
        else if (tmp<48){
            f3++;
        }
        else if (tmp<64){
            f4++;
        }
        else if (tmp<80){
            f5++;
        }
        else if (tmp<96){
            f6++;
        }
        else if (tmp<112){
            f7++;
        }
        else if (tmp<128){
            f8++;
        }
        else if (tmp<144){
            f9++;
        }
        else if (tmp<160){
            f10++;
        }
        else if (tmp<48){
            f11++;
        }
        else if (tmp<176){
            f12++;
        }
        else if (tmp<192){
            f13++;
        }
        else if (tmp<208){
            f14++;
        }
        else if (tmp<224){
            f15++;
        }
        else{
            f16++;
        }
    }
    if(colournumb == 1){
    printf("Red\n");
    }
    else if(colournumb == 2){
    printf("Green\n");
    }
    else{
        printf("Blue:\n");
    }
    printf("  0-15: %.2f%%\n  16-31: %.2f%%\n  32-47: %.2f%%\n  48-63: %.2f%%\n  64-79: %.2f%%\n  80-95: %.2f%%\n  96-111: %.2f%%\n  112-127: %.2f%%\n  128-143: %.2f%%\n  144-159: %.2f%%\n  160-175: %.2f%%\n  176-191: %.2f%%\n  192-207: %.2f%%\n  208-223: %.2f%%\n  224-239: %.2f%%\n  240-255: %.2f%%\n", (float)f1*100/size, (float)f2*100/size, (float)f3*100/size, (float)f4*100/size, (float)f5*100/size, (float)f6*100/size, (float)f7*100/size, (float)f8*100/size, (float)f9*100/size, (float)f10*100/size, (float)f11*100/size, (float)f12*100/size, (float)f13*100/size, (float)f14*100/size, (float)f15*100/size, (float)f16*100/size);

}


int main(int argc, char *argv[]){
    char line[90];
    FILE *myfile;
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;

    if ((myfile = fopen(argv[1], "r")) == NULL)
    {
        printf("Error! No file found. \n\n");
        printf("Right format : \"./program PATH-TO-INI-FILE.bmp \" \n");
        exit(1);
    }
       else
    {
        if (argc >= 2)
        {
            WORD intname1, intname2;

            fread(&intname1, 1,1,myfile);
            fread(&intname2, 1,1,myfile);
            rewind(myfile);
            fread(&fileheader.bfType, 2,1,myfile);
            if (fileheader.bfType !=0x4D42)
            {
                fclose(myfile);
                printf("Wrong file format");
                exit(1);
            }
            fread(&fileheader.bfSize, 4,1,myfile);
            fread(&fileheader.bfReserved1, 2,1,myfile);
            fread(&fileheader.bfReserved2, 2,1,myfile);
            fread(&fileheader.bfOffBits, 4,1,myfile);
            printf("BITMAPFILEHEADER:\n  bfType:          0x%X (%c%c)\n  bfSize:          %u\n  bfReserved1:     0x%X\n  bfReserved2:     0x%X\n  bfOffBits:       %u\n\n",(unsigned int)fileheader.bfType, intname1, intname2 ,fileheader.bfSize, fileheader.bfReserved1, fileheader.bfReserved2, fileheader.bfOffBits);


            fread(&infoheader.biSize, 4,1,myfile);
            fread(&infoheader.biWidth, 4,1,myfile);
            fread(&infoheader.biHeight, 4,1,myfile);
            fread(&infoheader.biPlanes, 2,1,myfile);

            fread(&infoheader.biBitCount, 2,1,myfile);
            fread(&infoheader.biCompression, 4,1,myfile);
            fread(&infoheader.biSizeImage, 4,1,myfile);
            fread(&infoheader.biXPelsPerMeter, 4,1,myfile);

            fread(&infoheader.biYPelsPerMeter, 4,1,myfile);
            fread(&infoheader.biClrUsed, 4,1,myfile);
            fread(&infoheader.biClrImportant, 4,1,myfile);

            //printf("%d\n\n", infoheader.biBitCount);
            WORD pixel;

            printf("BITMAPINFOHEADER:\n");
            printf("  biSize:          %u\n",infoheader.biSize);
            printf("  biWidth:         %d\n",infoheader.biWidth);
            printf("  biHeight:        %d\n",infoheader.biHeight);
            printf("  biPlanes:        %d\n",infoheader.biPlanes);

            printf("  biBitCount:      %d\n",infoheader.biBitCount);
            printf("  biCompression:   %u\n",infoheader.biCompression);
            printf("  biSizeImage:     %u\n",infoheader.biSizeImage);
            printf("  biXPelsPerMeter: %d\n",infoheader.biXPelsPerMeter);

            printf("  biYPelsPerMeter: %d\n",infoheader.biYPelsPerMeter);
            printf("  biClrUsed:       %u\n",infoheader.biClrUsed);
            printf("  biClrImportant:  %u\n\n",infoheader.biClrImportant);

            if(infoheader.biCompression != 0 || infoheader.biBitCount != 24){
                printf("histogram calculation is unsupported");
            }
            else{

                int row_lenght = ((infoheader.biBitCount*infoheader.biWidth+31)/32)*4;
                int columns = infoheader.biHeight;
                int rows = infoheader.biWidth;

                int size = columns * rows;
                //int size_with_padding = row_lenght * columns;

                rewind(myfile);
                unsigned char info[54];
                fread(info, sizeof(unsigned char), 54, myfile);

                WORD* datared =  malloc((size) * sizeof *datared);
                WORD* datagreen =  malloc((size) * sizeof *datagreen);
                WORD* datablue =  malloc((size) * sizeof *datablue);

                /*
                for(int i; i<54; i++){
                    printf("%s\n", info);
                }
                */
                int licznik = 0;
                for(int j=0; j<columns; j++){
                    for(int i=0; i<row_lenght;i++){
                        if (i>rows){
                            continue;
                        }
                        else{
                            fread(&datagreen[licznik], 1, 1, myfile);
                            fread(&datared[licznik], 1, 1, myfile);
                            fread(&datablue[licznik], 1, 1, myfile);
                            licznik ++;
                        }
                    }
                }
                //int
                printf_histogram(datared, size, 1);
                printf_histogram(datagreen, size, 2);
                printf_histogram(datablue, size, 3);

                //blue green red
                //malloc( unsigned char[size]);

                //fread(&pixel, 1, 1, myfile);
                //printf("%d", pixel);
                //free(data);
            }
        }
        else
        {
            printf("Not enough arguments\nRight format : \"./program PATH-TO-INI-FILE.bmp \" \n");
            fclose(myfile);
            exit(1);
        }
         fclose(myfile);

    }

}
