// DSPE_2015706035_È«¼¼ÁØ_4ÁÖÂ÷
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH	256
#define HEIGHT	256

typedef unsigned char BYTE;

unsigned char** MemAlloc_2D(int width, int height);
void MemFree_2D(unsigned char** arr, int height);

void FileRead(char* filename, unsigned char** img_in, int width, int height);
void FileWrite(char* filename, unsigned char** img_out, int widtg, int height);

void UpSampling_Copy(unsigned char** img_in, unsigned char** img_out, int width, int height);
void UpSampling_Average(unsigned char** img_in, unsigned char** img_out, int width, int height);
void UpSampling_Filter(unsigned char** img_in, unsigned char** img_out, int width, int height);

float GetPSNR(unsigned char** img_ori, unsigned char** img_dist, int width, int height);

int main()
{
	BYTE** img_in, ** img_out_copy, ** img_out_average, ** img_out_filter;

	img_in = MemAlloc_2D(WIDTH, HEIGHT);
	FileRead("Lena(256x256).raw", img_in, WIDTH, HEIGHT);

	img_out_copy = MemAlloc_2D(WIDTH * 2, HEIGHT * 2);
	img_out_average = MemAlloc_2D(WIDTH * 2, HEIGHT * 2);
	img_out_filter = MemAlloc_2D(WIDTH * 2, HEIGHT * 2);

	UpSampling_Copy(img_in, img_out_copy, WIDTH, HEIGHT);
	UpSampling_Average(img_in, img_out_average, WIDTH, HEIGHT);
	UpSampling_Filter(img_in, img_out_filter, WIDTH, HEIGHT);

	FileWrite("[Upsampling_Copy]Lena(256x256).raw", img_out_copy, WIDTH * 2, HEIGHT * 2);
	FileWrite("[Upsampling_Average]Lena(256x256).raw", img_out_average, WIDTH * 2, HEIGHT * 2);
	FileWrite("[Upsampling_Filter]Lena(256x256).raw", img_out_filter, WIDTH * 2, HEIGHT * 2);

	printf("Copy method PSNR: %.2f dB\n\n", GetPSNR(img_out_filter, img_out_copy, WIDTH * 2, HEIGHT * 2));
	printf("Average method PSNR: %.2f dB\n\n", GetPSNR(img_out_filter, img_out_average, WIDTH * 2, HEIGHT * 2));

	MemFree_2D(img_in, HEIGHT);
	MemFree_2D(img_out_copy, HEIGHT * 2);
	MemFree_2D(img_out_average, HEIGHT * 2);
	MemFree_2D(img_out_filter, HEIGHT * 2);

	return 0;
}

unsigned char** MemAlloc_2D(int width, int height)
{
	unsigned char** arr;
	int i;

	arr = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for (i = 0; i < height; i++)
		arr[i] = (unsigned char*)malloc(sizeof(unsigned char*) * width);

	return arr;
}

void MemFree_2D(unsigned char** arr, int height)
{
	int i;
	for (i = 0; i < height; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

void FileRead(char* filename, unsigned char** img_in, int width, int height)
{
	FILE* fp_in;
	int i;

	fp_in = fopen(filename, "rb");
	for (i = 0; i < height; i++)
		fread(img_in[i], sizeof(unsigned char), width, fp_in);
	fclose(fp_in);
}

void FileWrite(char* filename, unsigned char** img_out, int width, int height)
{
	FILE* fp_out;
	int i;

	fp_out = fopen(filename, "wb");
	for (i = 0; i < height; i++)
		fwrite(img_out[i], sizeof(unsigned char), width, fp_out);
	fclose(fp_out);
}

void UpSampling_Copy(unsigned char** img_in, unsigned char** img_out_copy, int width, int height)
{
	int i, j, m, n;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			for (m = 0; m < 2; m++)
			{
				for (n = 0; n < 2; n++)
				{
					img_out_copy[2 * i + m][2 * j + n] = img_in[i][j];
				}
			}
		}
	}
}

void UpSampling_Average(unsigned char** img_in, unsigned char** img_out_average, int width, int height)
{

}

void UpSampling_Filter(unsigned char** img_in, unsigned char** img_out_filter, int width, int height)
{
	int interpolFilter[8] = { -1, 4, -11, 40, 40, -11, 4, -1 };
	int sum = 64;
	float temp;
	unsigned char** img_out_padding;
	int i=0, j=0, m=0;

	img_out_padding = (unsigned char**)malloc(sizeof(unsigned char*) * ((height * 2) + 14));
	for (i = 0; i < height * 2 + 14; i++)
		img_out_padding[i] = (unsigned char*)malloc(sizeof(unsigned char) * ((width * 2) + 14));




	for (i = 0; i < height * 2; i++)
	{
		for (j = 0; j < width * 2; j++)
		{
			img_out_filter[i][j] = img_out_padding[i + 7][j + 7];
		}
	}
	for (i = 0; i < height + 14; i++)
		free(img_out_padding[i]);
	free(img_out_padding);
}

float GetPSNR(unsigned char** img_ori, unsigned char** img_dist, int width, int height) 
{

}
