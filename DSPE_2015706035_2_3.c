// 2주차_3_2015706035_홍세준 Assignment#3
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>		// Header file
#include <stdlib.h>

#define WIDTH	512		// Image size
#define HEIGHT	512

typedef unsigned char BYTE;

int main()
{
	FILE *fp_in = 0, *fp_out1 = 0, *fp_out2 = 0;				// File pointer
	BYTE **img_in = 0, **img_out1 = 0, **img_out2 = 0;			// Pointers for input and output
	int temp1 = 0, temp2 = 0;
	int i = 0, j = 0;

	fp_in = fopen("Lena(512x512).raw", "rb");					// Input file open
	if (fp_in == NULL)
	{
		printf("File open failed\n");
	}

	img_in = (BYTE**)malloc(sizeof(BYTE*)*HEIGHT);				// Input memory allocation
	for (i = 0; i < HEIGHT; i++)
	{
		img_in[i] = (BYTE*)malloc(sizeof(BYTE)*WIDTH);
	}

	for (i = 0; i < HEIGHT; i++)
	{
		fread(img_in[i], sizeof(BYTE), WIDTH, fp_in);			// Input file read
	}

	img_out1 = (BYTE**)malloc(sizeof(BYTE*)*HEIGHT);			// Output1 memory allocation
	for (i = 0; i < HEIGHT; i++)
	{
		img_out1[i] = (BYTE*)malloc(sizeof(BYTE)*WIDTH);
	}

	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH - 1; j++)
		{
			temp1 = img_in[i][j] - img_in[i][j + 1];			// y(i,j)=x(i,j)-x(i,j+1)
			img_out1[i][j] = (BYTE)((temp1+90)/2);				// clipping
		}
	}

	img_out2 = (BYTE**)malloc(sizeof(BYTE*)*HEIGHT);			// Output2 memory allocation
	for (i = 0; i < HEIGHT; i++)
	{
		img_out2[i] = (BYTE*)malloc(sizeof(BYTE)*WIDTH);
	}

	for (j = 0; j < WIDTH; j++)
	{
		for (i = 0; i < HEIGHT - 1; i++)
		{
			temp2 = img_in[i][j] - img_in[i + 1][j];			// y(i,j)=x(i,j)-x(i+1,j)
			img_out2[i][j] = (BYTE)((temp2 + 90) / 2);			// clipping
		}
	}


	fp_out1 = fopen("[output_horizontal]Lena.raw", "wb");		// Output1 file open(.raw)
	if (fp_out1 == NULL)
	{
		printf("File open failed\n");
	}
	for (i = 0; i < HEIGHT; i++)				
	{
		fwrite(img_out1[i], sizeof(BYTE), WIDTH, fp_out1);		// Output1 file write
	}

	fp_out2 = fopen("[output_vertical]Lena.raw", "wb");			// Output2 file open(.raw)
	if (fp_out2 == NULL)
	{
		printf("File open failed\n");
	}
	for (i = 0; i < HEIGHT; i++)
	{
		fwrite(img_out2[i], sizeof(BYTE), WIDTH, fp_out2);		// Output2 file write
	}

	for (i = 0; i < HEIGHT; i++)								// Memory free
	{
		free(img_in[i]);
		if (i < HEIGHT)
		{
			free(img_out1[i]);
			free(img_out2[i]);
		}

	}

	free(img_in);
	free(img_out1);
	free(img_out2);
	fclose(fp_in);												// File close
	fclose(fp_out1);
	fclose(fp_out2);

	return 0;
}