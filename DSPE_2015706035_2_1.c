// 2����_2015706035_ȫ���� Assignment #1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>			// Header file
#include <stdlib.h>

#define WIDTH	512			// Image size
#define HEIGH	512

typedef unsigned char BYTE;

int main()
{
	FILE *fp_in = 0, *fp_out = 0;				// File pointer
	BYTE **img_in = 0, **img_out = 0;			// Pointers for input and output
	float temp = 0;
	int i = 0, j = 0, m = 0, n = 0;

	FILE*fp_test;

	fp_in = fopen("Lena(512x512).raw", "rb");			// Input file open
	if (fp_in == NULL)
	{
		printf("File open failed\n");
	}


	img_in = (BYTE**)malloc(sizeof(BYTE*)*(HEIGH + 4));		// input memory allocation
	for (i = 0; i < HEIGH+4; i++)
	{
		img_in[i] = (BYTE*)malloc(sizeof(BYTE)*(WIDTH+4));
	}

	for (i = 0; i < HEIGH; i++)
	{
		fread(img_in[i], sizeof(BYTE), WIDTH, fp_in);	//input file read
	}

	for (i = 0; i < HEIGH; i++)							// Padding
	{
		for (j = 0; j < 4; j++)
		{
			img_in[i][WIDTH + j] = img_in[i][WIDTH - 1];
		}
	}

	for (j = 0; j < WIDTH; j++)
	{
		for (i = 0; i < 4; i++)
		{
			img_in[HEIGH + i][j] = img_in[HEIGH - 1][j];
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			img_in[HEIGH + i][WIDTH + j] = img_in[HEIGH + i][WIDTH - 1];
		}
	}

	img_out = (BYTE **)malloc(sizeof(BYTE*)*HEIGH);		// Output memory allocation
	for (i = 0; i < HEIGH; i++)
	{
		img_out[i] = (BYTE*)malloc(sizeof(BYTE)*WIDTH);
	}
	for (i = 0; i < HEIGH; i++)							// 5*5 average
	{
		for (j = 0; j < WIDTH ; j++)
		{
			temp = 0;
			for (m = 0; m < 5; m++)
			{
				for (n = 0; n < 5; n++)
				{
					temp += img_in[i + m][j + n];
				}
			}
			img_out[i][j] = (BYTE)(temp / 25);
		}
	}

	fp_out = fopen("[Output_ave]Lena(512x512).raw", "wb");	// Output file open(.raw)
	if (fp_out == NULL)
	{
		printf("File open failed\n");
	}

	for (i = 0; i < HEIGH; i++)							// Output file write
	{
		fwrite(img_out[i], sizeof(BYTE), WIDTH, fp_out);
	}

	for (i = 0; i < HEIGH + 4; i++)		// Memory free
	{
		free(img_in[i]);
		if (i < HEIGH)
			free(img_out[i]);
	}

	free(img_in);			
	free(img_out);
	fclose(fp_in);			// File close
	fclose(fp_out);

	return 0;
}