// DSPE 2015706035 È«¼¼ÁØ 3ÁÖÂ÷ Assignment2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH	512
#define HEIGHT	512

typedef unsigned char BYTE;

unsigned char** MemAlloc_2D(int width, int height);
void MemFree_2D(unsigned char** arr, int height);
void SobelMask_Horizontal(unsigned char** img_in, unsigned char** img_out, int width, int height);
void SobelMask_Vertical(unsigned char** img_in, unsigned char** img_out, int width, int height);

int main()
{
	FILE *fp_in = 0, *fp_out1 = 0, *fp_out2 = 0;
	BYTE **img_in = 0, **img_out1 = 0, **img_out2 = 0;
	int i = 0;

	fp_in = fopen("Lena(512x512).raw", "rb");
	if (fp_in == NULL)
	{
		printf("File open failed\n");
		return -1;
	}

	img_in = MemAlloc_2D(WIDTH, HEIGHT);
	img_out1 = MemAlloc_2D(WIDTH, HEIGHT);
	img_out2 = MemAlloc_2D(WIDTH, HEIGHT);

	for (i = 0; i < HEIGHT; i++)
	{
		fread(img_in[i], sizeof(BYTE), WIDTH, fp_in);
	}

	SobelMask_Horizontal(img_in, img_out1, WIDTH, HEIGHT);
	fp_out1 = fopen("[Horizontal_edge]Lena.raw", "wb");

	SobelMask_Vertical(img_in, img_out2, WIDTH, HEIGHT);
	fp_out2 = fopen("[Vertical_edge]Lena.raw", "wb");

	if (fp_out1 == NULL || fp_out2 == NULL)
	{
		printf("File open failed\n");
		return -1;
	}

	for (i = 0; i < HEIGHT; i++)
	{
		fwrite(img_out1[i], sizeof(BYTE), WIDTH, fp_out1);
		fwrite(img_out2[i], sizeof(BYTE), WIDTH, fp_out2);
	}

	MemFree_2D(img_in, HEIGHT);
	MemFree_2D(img_out1, HEIGHT);
	MemFree_2D(img_out2, HEIGHT);
	fclose(fp_in);
	fclose(fp_out1);
	fclose(fp_out2);

	return 0;
}

void SobelMask_Horizontal(unsigned char** img_in, unsigned char** img_out1, int width, int  height)
{
	int i, j, m, n;
	int temp;
	unsigned char **img_in_pad;
	int Sobel_h[3][3] = {
		{-1, 0, 1},
	{-2, 0, 2}, 
	{-1, 0, 1}
	};

	img_in_pad = (unsigned char**)malloc(sizeof(unsigned*)*(height + 2));
	for (i = 0; i < height + 2; i++)
	{
		img_in_pad[i] = (unsigned char*)malloc(sizeof(unsigned char)*(width + 2));
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img_in_pad[i + 1][j + 1] = img_in[i][j];
		}
	}
	for (i = 1; i < height + 1; i++)
	{
		for (j = 0; j < 1; j++)
		{
			img_in_pad[i][j] = img_in_pad[i][1];
			img_in_pad[i][width + 1 + j] = img_in_pad[i][width + 1 - 1];
		}
	}

	for (j = 1; j < width; j++)
	{
		for (i = 0; i < 1; i++)
		{
			img_in_pad[i][j] = img_in_pad[1][j];
			img_in_pad[height + 1 + i][j] = img_in_pad[height + 1 - 1][j];
		}
	}

	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 1; j++)
		{
			img_in_pad[i][j] = img_in_pad[1][1];
			img_in_pad[i][width + 1 + j] = img_in_pad[1][width + 1 - 1];
			img_in_pad[height + 1 + i][j] = img_in_pad[height + 1 - 1][1];
			img_in_pad[height + 1 + i][width + 1 + j] = img_in_pad[height + 1 - 1][width + 1 - 1];
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			temp = 0;
			for (m = 0; m < 3; m++)
			{
				for (n = 0; n < 3; n++)
				{
					temp += img_in_pad[i + m][j + n] * Sobel_h[m][n];
				}
			}
			img_out1[i][j] = (unsigned char)floor(temp + 128);
		}
	}
	for (i = 0; i < height + 1; i++)
		free(img_in_pad[i]);
	free(img_in_pad);
}

void SobelMask_Vertical(unsigned char** img_in, unsigned char** img_out2, int width, int  height)
{
	int i, j, m, n;
	int temp;
	unsigned char **img_in_pad;
	int Sobel_v[3][3] = {
		{-1, -2, -1},
	{0, 0, 0},
	{1, 2, 1}
	};

	img_in_pad = (unsigned char**)malloc(sizeof(unsigned*)*(height + 2));
	for (i = 0; i < height + 2; i++)
	{
		img_in_pad[i] = (unsigned char*)malloc(sizeof(unsigned char)*(width + 2));
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img_in_pad[i + 1][j + 1] = img_in[i][j];
		}
	}
	for (i = 1; i < height + 1; i++)
	{
		for (j = 0; j < 1; j++)
		{
			img_in_pad[i][j] = img_in_pad[i][1];
			img_in_pad[i][width + 1 + j] = img_in_pad[i][width + 1 - 1];
		}
	}

	for (j = 1; j < width; j++)
	{
		for (i = 0; i < 1; i++)
		{
			img_in_pad[i][j] = img_in_pad[1][j];
			img_in_pad[height + 1 + i][j] = img_in_pad[height + 1 - 1][j];
		}
	}

	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 1; j++)
		{
			img_in_pad[i][j] = img_in_pad[1][1];
			img_in_pad[i][width + 1 + j] = img_in_pad[1][width + 1 - 1];
			img_in_pad[height + 1 + i][j] = img_in_pad[height + 1 - 1][1];
			img_in_pad[height + 1 + i][width + 1 + j] = img_in_pad[height + 1 - 1][width + 1 - 1];
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			temp = 0;
			for (m = 0; m < 3; m++)
			{
				for (n = 0; n < 3; n++)
				{
					temp += img_in_pad[i + m][j + n] * Sobel_v[m][n];
				}
			}
			img_out2[i][j] = (unsigned char)floor(temp + 128);
		}
	}
	for (i = 0; i < height + 1; i++)
		free(img_in_pad[i]);
	free(img_in_pad);
}

unsigned char** MemAlloc_2D(int width, int height)
{
	unsigned char** MemA;
	MemA = (unsigned char**)malloc(sizeof(unsigned char*)*height);
	for (int i = 0; i < height; i++)
	{
		MemA[i] = (unsigned char*)malloc(sizeof(unsigned char)*width);
	}
	return MemA;
}

void MemFree_2D(unsigned char** arr, int height)
{
	for (int i = 0; i < height; i++)
		free(arr[i]);
	free(arr);
}