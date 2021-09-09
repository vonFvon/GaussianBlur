/*************************************************************************
	> File Name: hmwk21090401.c
	> Author: V 
	> Mail: @gmail.com 
	> Created Time: Tue 07 Sep 2021 08:08:05 AM CST
 ************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI acos(-1)
#define KERNEL_SIZE 3
#define SIGMA 1.5

// Pixel struct including R G B => aggregate data type
typedef struct Pixel {
    unsigned char B;
    unsigned char G;
    unsigned char R;
} Pixel;

// Axis struct including X Y and weight => aggregate data type
typedef struct Axis {
    double X;
    double Y;
    double weight;
} Axis;

// define round function
unsigned char rounding(double x) {
    return (((int)(x * 10) % 10) >= 5) ? (ceil(x)) : (floor(x));
}

// calculate Gaussian Blur
void gauss_blur(Axis **arr, double sigma) {
    double sum = 0, e = 1, n = 1;
    int count = 1;

    // calculate Euler's number according to formula 1/1! + ... + 1/n! => e
    while(1/n > 1e-10) {
        e += 1 / n;
        count++;
        n = count * n;
    }
#ifdef DEBUG
    printf("Euler's number : %lf\n", e);
    printf("--- break line ---\n\n");
#endif

    // set coordinate matrix on Y
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch(i) {
                case 0:
                    arr[i][j].Y = 1; break;
                case 1:
                    arr[i][j].Y = 0; break;
                case 2:
                    arr[i][j].Y = -1;
            }
        }
    }
    // set coordinate matrix on X
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            switch(j) {
                case 0:
                    arr[i][j].X = -1; break;
                case 1:
                    arr[i][j].X = 0; break;
                case 2:
                    arr[i][j].X = 1;
            }
        }
    }

    // two-dimensional independent gaussian density function
#ifdef DEBUG
    printf("two-dimensional independent gaussian distribution :\n");
#endif    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j].weight = (1 / (2 * PI * sigma * sigma)) * pow(e, -(arr[i][j].X * arr[i][j].X + arr[i][j].Y * arr[i][j].Y) / 2 / sigma / sigma);
#ifdef DEBUG            
            printf("%lf", arr[i][j].weight);
            if (j < 2) {
                printf(" | ");
            }
#endif
        }
#ifdef DEBUG
        printf("\n");
#endif
    }
#ifdef DEBUG
    printf("--- break line ---\n\n");
#endif
    // calculate weight based on two-dimensional independent gaussian density function
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += arr[i][j].weight;
        }
    }
    // weighting
#ifdef DEBUG
    printf("weighting matrix :\n");
#endif
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j].weight /= sum;
#ifdef DEBUG
            printf("%lf", arr[i][j].weight);
            if (j < 2) {
                printf(" | ");
            }
#endif
        }
#ifdef DEBUG
        printf("\n");
#endif
    }
#ifdef DEBUG
    printf("--- break line ---\n\n");
#endif
}

int main(int argc, char* argv[])
{
    FILE* fp, *fp_new;
    int offset, height, width;

    // create weight matrix via malloc
    Axis **arrW = (Axis **)malloc(sizeof(Axis *) * KERNEL_SIZE);
    for (int i = 0; i < KERNEL_SIZE; i++) {
        arrW[i] = (Axis *)malloc(sizeof(Axis) * KERNEL_SIZE);
        memset(arrW[i], 0, sizeof(Axis) * KERNEL_SIZE);
    }

    // follow SIGMA value then calculate gauss weighting matrix
    gauss_blur(arrW, SIGMA);
#ifdef DEBUG
    printf("check center value in weighting matrix : %lf\n", arrW[1][1].weight);
    printf("--- break line ---\n\n");
#endif

    // open bmp file
    if ((fp = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "ERROR: file '%s' open failed !\n", argv[1]);
        exit(1);
    }

    // get file offset to pixel array
    fseek(fp, 10, SEEK_SET);
    fread(&offset, 4, 1, fp);

    // get width
    fseek(fp, 18, SEEK_SET);
    fread(&width, 4, 1, fp);

    // get height
    fseek(fp, 22, SEEK_SET);
    fread(&height, 4, 1, fp);
#ifdef DEBUG
    printf("width : %d x height : %d\n", width, height);
    printf("--- break line ---\n\n");
#endif

    // create pixel matrix and pad KERNEL_SIZE - 1 zeros on every side
    Pixel **arrP = (Pixel **)malloc(sizeof(Pixel *) * (height + (KERNEL_SIZE - 1)));
    for (int i = 0; i < height + (KERNEL_SIZE - 1); i++) {
        arrP[i] = (Pixel *)malloc(sizeof(Pixel) * (width + (KERNEL_SIZE - 1)));
        memset(arrP[i], 0, sizeof(Pixel) * (width + (KERNEL_SIZE - 1)));
    }

    // write source bmp data into pixel matrix center
    fseek(fp, offset, SEEK_SET);
    for (int i = (KERNEL_SIZE - 1) / 2; i <= height; i++) {
        for (int j = (KERNEL_SIZE - 1) / 2; j <= width; j++) {
            fread(&arrP[i][j].B, 1, 1, fp);
            fread(&arrP[i][j].G, 1, 1, fp);
            fread(&arrP[i][j].R, 1, 1, fp);
        }
    }
#ifdef DEBUG
    printf("check pixel in pixel matrix :\n");
    printf("first pixel on last row : %x %x %x\n", arrP[(KERNEL_SIZE - 1) / 2][(KERNEL_SIZE - 1) / 2].B,arrP[(KERNEL_SIZE - 1) / 2][(KERNEL_SIZE - 1) / 2].G, arrP[(KERNEL_SIZE - 1) / 2][(KERNEL_SIZE - 1) / 2].R);
    printf("last pixel on last row  : %x %x %x\n", arrP[(KERNEL_SIZE - 1) / 2][width].B,arrP[(KERNEL_SIZE - 1) / 2][width].G, arrP[(KERNEL_SIZE - 1) / 2][width].R);
    printf("--- break line ---\n\n");
#endif

    // open new bmp file and duplicate bmp file
    unsigned char buffer;
    if ((fp_new = fopen(argv[2], "wb")) == NULL) {
        fprintf(stderr, "ERROR: file '%s' open failed !\n", argv[2]);
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);
    while (fread(&buffer, 1, 1, fp)) {
        fwrite(&buffer, 1, 1, fp_new);
    }

    // locate to PixelArray
    fseek(fp_new, offset, SEEK_SET);
    
    // gaussian blur operation
#ifdef DEBUG
    printf("check gaussian calculation :\n");
#endif
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            double sum_blur_B = 0, sum_blur_G = 0, sum_blur_R = 0;
            // calculate gaussian wqeight
            for (int ii = 0; ii < 3; ii++) {
                for (int jj = 0; jj < 3; jj++) {
                    sum_blur_B += arrP[i + (int)arrW[ii][jj].X][j + (int)arrW[ii][jj].Y].B * arrW[ii][jj].weight;
                    sum_blur_G += arrP[i + (int)arrW[ii][jj].X][j + (int)arrW[ii][jj].Y].G * arrW[ii][jj].weight;
                    sum_blur_R += arrP[i + (int)arrW[ii][jj].X][j + (int)arrW[ii][jj].Y].R * arrW[ii][jj].weight;
                }
            }
            // output results to destination
            //// round up and roudn down
            unsigned char B = rounding(sum_blur_B);
            //// write to new bmp file -> B channel
            fwrite(&B, 1, 1, fp_new);
            //// update pixel matrix -> B channel
            arrP[i][j].B = B;
            //// round up and round down
            unsigned char G = rounding(sum_blur_G);
            //// write to new bmp file -> G channel
            fwrite(&G, 1, 1, fp_new);
            //// update pixel matrix -> G channel
            arrP[i][j].G = G;
            //// round up and round down
            unsigned char R = rounding(sum_blur_R);
            //// write to new bmp file -> R channel
            fwrite(&R, 1, 1, fp_new);
            //// update pixel matrix -> R channel
            arrP[i][j].R = R;
#ifdef DEBUG            
            printf("B %d %lf - G %d %lf - R %d %lf\n", B, sum_blur_B, G,sum_blur_G, R, sum_blur_R);
            if (j < width) {
                printf(" | ");
            }
#endif
        }
        printf("\n");
    }
#ifdef DEBUG
    printf("--- break line ---\n\n");
#endif

#ifdef DEBUG
    // print pixel matrix
    printf("check pixel matrix :\n");
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            printf("%d %d %d", arrP[i][j].B, arrP[i][j].G, arrP[i][j].R);
            if (j < width) {
                printf(" | ");
            }
        }
        printf("\n");
    }
#endif

    // close pointers
    //// close file
    fclose(fp);
    fclose(fp_new);
    //// free arrW
    for (int i = 0; i < 3; i++) {
        free(arrW[i]);
    }
    free(arrW);
    //// free arrP
    for (int i = 0; i < height + 2; i++) {
        free(arrP[i]);
    }
    free(arrP);
  
    return 0;
}
