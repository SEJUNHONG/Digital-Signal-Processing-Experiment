// DSPE_2015706035_홍세준_3주차_1

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH	512
#define HEIGHT	512

typedef unsigned char BYTE;

unsigned char** MemAlloc_2D(int width, int height);
void MemFree_2D(unsigned char** arr, int height);		// BYTE
void GaussianFilter_5x5(unsigned char** img_in, unsigned char** img_out, int width, int height);		// BYTE
void GaussianFilter_9x9(unsigned char** img_in, unsigned char** img_out, int width, int height);

int main()
{
	FILE *fp_in = 0, *fp_out = 0;
	BYTE **img_in = 0, **img_out = 0;
	int i = 0, n = 0;

	fp_in = fopen("Lena(512x512).raw", "rb");
	if (fp_in == NULL)
	{
		printf("File open failed\n");
		return -1;
	}

	printf("2D-가우시안 필터링의 마스크 사이즈를 입력하세요.(5 or 9) : ");
	scanf("%d", &n);

	img_in = MemAlloc_2D(WIDTH, HEIGHT);
	img_out = MemAlloc_2D(WIDTH, HEIGHT);

	for (i = 0; i < HEIGHT; i++)
	{
		fread(img_in[i], sizeof(BYTE), WIDTH, fp_in);
	}

	if (n == 5)
	{
		GaussianFilter_5x5(img_in, img_out, WIDTH, HEIGHT);
		fp_out = fopen("[Gaussian_5x5]Lena(512x512).raw", "wb");		// Output file open(.raw
	}

	else if (n == 9)
	{
		GaussianFilter_9x9(img_in, img_out, WIDTH, HEIGHT);
		fp_out = fopen("[Gaussian_9x9]Lena(512x512).raw", "wb");		// Output file open(.raw)
	}
	else
	{
		printf("Not valid mask size\n");
		return -1;
	}

	if (fp_out == NULL)
	{
		printf("File open failed\n");
		return -1;
	}

	for (i = 0; i < HEIGHT; i++)										// Output file write
	{
		fwrite(img_out[i], sizeof(BYTE), WIDTH, fp_out);
	}

	MemFree_2D(img_in, HEIGHT);
	MemFree_2D(img_out, HEIGHT);
	fclose(fp_in);														// File close
	fclose(fp_out);

	return 0;
}

void GaussianFilter_5x5(unsigned char** img_in, unsigned char** img_out, int width, int height)
{
	int i, j, m, n;
	double temp;
	unsigned char **img_in_pad;
	double Gauss_5x5[5][5] = {															// 5x5 Gaussian mask
		{0.0037, 0.0147, 0.0256, 0.0147, 0.0037},
	{0.0147, 0.0586, 0.0952, 0.0586, 0.0147},
	{0.0256, 0.0952, 0.1502, 0.0952, 0.0256},
	{0.0147, 0.0586, 0.0952, 0.0586, 0.0147},
	{0.0037, 0.0147, 0.0256, 0.0147, 0.0037}
	};

	img_in_pad = (unsigned char**)malloc(sizeof(unsigned char*)*(height + 4));			// Memory allocation
	for (i = 0; i < height + 4; i++)
	{
		img_in_pad[i] = (unsigned char*)malloc(sizeof(unsigned char)*(width + 4));
	}

	for (i = 0; i < height; i++)														// Data copy
	{
		for (j = 0; j < width; j++)
		{
			img_in_pad[i + 2][j + 2] = img_in[i][j];
		}
	}
	for (i = 2; i < height + 2; i++)													// Padding
	{
		for (j = 0; j < 2; j++)
		{
			img_in_pad[i][j] = img_in_pad[i][2];
			img_in_pad[i][width + 2 + j] = img_in_pad[i][width + 2 - 1];
		}
	}

	for (j = 2; j < width; j++)
	{
		for (i = 0; i < 2; i++)
		{
			img_in_pad[i][j] = img_in_pad[2][j];
			img_in_pad[height + 2 + i][j] = img_in_pad[height + 2 - 1][j];
		}
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			img_in_pad[i][j] = img_in_pad[2][2];
			img_in_pad[i][width + 2 + j] = img_in_pad[2][width + 2 - 1];
			img_in_pad[height + 2 + i][j] = img_in_pad[height + 2 - 1][2];
			img_in_pad[height + 2 + i][width + 2 + j] = img_in_pad[height + 2 - 1][width + 2 - 1];
		}
	}

	for (i = 0; i < height; i++)														// 2-D Gaussian filtering
	{
		for (j = 0; j < width; j++)
		{
			temp = 0;
			for (m = 0; m < 5; m++)
			{
				for (n = 0; n < 5; n++)
				{
					temp += img_in_pad[i + m][j + n] * Gauss_5x5[m][n];
				}
			}
			img_out[i][j] = (unsigned char)floor(temp + 0.5);
		}
	}
	for (i = 0; i < height + 4; i++)													// Memory free
		free(img_in_pad[i]);
	free(img_in_pad);
}

unsigned char** MemAlloc_2D(int width, int height)								// BYTE 추가
{
	unsigned char** MemA;
	MemA = (unsigned char**)malloc(sizeof(unsigned char*)*height);
	for (int i = 0; i < height; i++) {
		MemA[i] = (unsigned char*)malloc(sizeof(unsigned char)*width);
	}
	return MemA;
}

void MemFree_2D(unsigned char** arr, int height)								// BYTE 추가
{
	for (int i = 0; i < height; i++)
		free(arr[i]);
	free(arr);
}

void GaussianFilter_9x9(unsigned char** img_in, unsigned char** img_out, int width, int height)
{
	int i, j, m, n;
	double temp;
	unsigned char **img_in_pad;
	double Gauss_9x9[9][9] = {															// 9x9 Gaussian mask
		{0.0033, 0.0033, 0.0033, 0.0067, 0.0067, 0.0067, 0.0033, 0.0033, 0.0033},
	{0.0033, 0.0033, 0.0067, 0.0067, 0.0134, 0.0067, 0.0067, 0.0033, 0.0033},
	{0.0033, 0.0067, 0.0067, 0.0134, 0.0268, 0.0134, 0.0067, 0.0067, 0.0033},
	{0.0067, 0.0067, 0.0134, 0.0268, 0.0535, 0.0268, 0.0134, 0.0067, 0.0067},
	{0.0067, 0.0134, 0.0268, 0.0535, 0.1070, 0.0535, 0.0268, 0.0134, 0.0067},
	{0.0067, 0.0067, 0.0134, 0.0268, 0.0535, 0.0268, 0.0134, 0.0067, 0.0067},
	{0.0033, 0.0067, 0.0067, 0.0134, 0.0268, 0.0134, 0.0067, 0.0067, 0.0033},
	{0.0033, 0.0033, 0.0067, 0.0067, 0.0134, 0.0067, 0.0067, 0.0033, 0.0033},
	{0.0033, 0.0033, 0.0033, 0.0067, 0.0067, 0.0067, 0.0033, 0.0033, 0.0033}
	};

	img_in_pad = (unsigned char**)malloc(sizeof(unsigned char*)*(height + 8));			// Memory allocation
	for (i = 0; i < height + 8; i++)
	{
		img_in_pad[i] = (unsigned char*)malloc(sizeof(unsigned char)*(width + 8));
	}

	for (i = 0; i < height; i++)														// Data copy
	{
		for (j = 0; j < width; j++)
		{
			img_in_pad[i + 4][j + 4] = img_in[i][j];
		}
	}
	for (i = 4; i < height + 4; i++)													// Padding
	{
		for (j = 0; j < 4; j++)
		{
			img_in_pad[i][j] = img_in_pad[i][4];
			img_in_pad[i][width + 4 + j] = img_in_pad[i][width + 4 - 1];
		}
	}

	for (j = 4; j < width; j++)
	{
		for (i = 0; i < 4; i++)
		{
			img_in_pad[i][j] = img_in_pad[4][j];
			img_in_pad[height + 4 + i][j] = img_in_pad[height + 4 - 1][j];
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			img_in_pad[i][j] = img_in_pad[4][4];
			img_in_pad[i][width + 4 + j] = img_in_pad[4][width + 4 - 1];
			img_in_pad[height + 4 + i][j] = img_in_pad[height + 4 - 1][4];
			img_in_pad[height + 4 + i][width + 4 + j] = img_in_pad[height + 4 - 1][width + 4 - 1];
		}
	}

	for (i = 0; i < height; i++)														// 2-D Gaussian filtering
	{
		for (j = 0; j < width; j++)
		{
			temp = 0;
			for (m = 0; m < 9; m++)
			{
				for (n = 0; n < 9; n++)
				{
					temp += img_in_pad[i + m][j + n] * Gauss_9x9[m][n];
				}
			}
			img_out[i][j] = (unsigned char)floor(temp + 0.5);
		}
	}
	for (i = 0; i < height + 8; i++)													// Memory free
		free(img_in_pad[i]);
	free(img_in_pad);
}