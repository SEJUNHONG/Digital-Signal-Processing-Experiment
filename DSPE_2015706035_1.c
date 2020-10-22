//1ÁÖÂ÷_2015706035_È«¼¼ÁØ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>		// Header file
#include <stdlib.h>

#define N	512			// The number of input data

int main()
{
	FILE *fp_in = 0, *fp_out1 = 0, *fp_out2 = 0, *fp_out3=0;		// File pointer
	unsigned char *idata = 0, *odata = 0;				// Pointers for input and output
	int temp = 0;
	int idx = 0;

	fp_in = fopen("input1.raw", "rb");									// input file open
	idata = (unsigned char*)malloc(sizeof(unsigned char)*N);			// input data mamory allocation unsigned char : 8bits, 0~255

	fread(idata, sizeof(unsigned char), N, fp_in);						// input file read

	odata = (unsigned char*)malloc(sizeof(unsigned char)*(N - 1));		// output data memory allocation

	for (idx = 0; idx < N - 1; idx++)									// y(x) = f(x) - f(x+1)
	{
		temp = idata[idx] - idata[idx + 1];								// clipping
		if (temp < 0)
		{
			temp = 0;
		}
		else if (temp > 255)
		{
			temp = 255;
		}
		odata[idx] = (unsigned char)temp;
	}

	fp_out1 = fopen("output.raw", "wb");								// Output file open(.raw)
	fwrite(odata, sizeof(unsigned char), N - 1, fp_out1);				// Output file write

	fp_out2 = fopen("output.xls", "wt");								// Output file open(.xls)
	for (idx = 0; idx < N - 1; idx++)									// Output file write
	{
		fprintf(fp_out2, "%u\n", odata[idx]);
	}

	 fp_out3 = fopen("input.xls", "wt");
	 for (idx = 0; idx < N; idx++)
	 {
	 	fprintf(fp_out3, "%u\n", idata[idx]);
	 }

	free(idata);
	free(odata);
	fclose(fp_in); 
	fclose(fp_out1);
	fclose(fp_out2);
	fclose(fp_out3);

	return 0;
}