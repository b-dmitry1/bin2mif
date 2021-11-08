/*

BIN2MIF tool (2007-2015) by b-dmitry1

Converts binary file to Quartus Memory Initialization File (MIF)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BITS	64

#define MAX_PATH	1024

int main(int argc, char **argv)
{
	FILE *fi, *fo;
	char outputname[MAX_PATH];
	char *p;
	int bits, bytes;
	int size, records;
	unsigned char data[MAX_BITS / 8 + 1];
	int i, j;
	int argnumber = 1;
	int silent = 0;

	if ((argc < 3) || (argc > 4))
	{
		printf("Usage: bin2mif.exe [silent] bits filename.bin\nExample: bin2mif.exe 32 rom.bin\n");
		return 1;
	}

	if (!strcmp(argv[argnumber], "silent"))
	{
		silent = 1;
		argnumber++;
	}

	bits = atoi(argv[argnumber++]);

	if ((bits < 1) || (bits > MAX_BITS))
	{
		printf("Bits error\n");
		return 1;
	}

	bytes = bits / 8;
	if (bits % 8)
		bytes++;

	if (strlen(argv[argnumber]) > MAX_PATH - 5)
	{
		printf("File path is too long\n");
		return 1;
	}

	strcpy(outputname, argv[argnumber]);
	p = strstr(outputname, ".");
	if (p == NULL)
	{
		printf("File name error\n");
		return 1;
	}

	strcpy(p, ".mif");

	if (!silent)
		printf("Input file: %s\nOutput file: %s\nBits: %d\n",
			argv[argnumber], outputname, bits);

	fi = fopen(argv[argnumber], "rb");
	if (fi == NULL)
	{
		printf("Cannot open input file\n");
		return 1;
	}
	fseek(fi, 0, SEEK_END);
	size = ftell(fi);
	fseek(fi, 0, SEEK_SET);

	records = size / bytes;

	if (!silent)
		printf("File size: %ld bytes / %ld records\n", size, records);

	fo = fopen(outputname, "wt");
	if (fo == NULL)
	{
		fclose(fi);
		printf("Cannot open output file\n");
		return 1;
	}

	fprintf(fo, "WIDTH = %d;\nDEPTH = %ld;\n\n", bits, records);
	fprintf(fo, "ADDRESS_RADIX = HEX;\nDATA_RADIX = HEX;\nCONTENT BEGIN\n");

	for (i = 0; i < records; i++)
	{
		fprintf(fo, "%.4lX : ", i);
		fread(data, bytes, 1, fi);
		for (j = 0; j < bytes; j++)
			fprintf(fo, "%.2X", data[bytes - j - 1]);
		fprintf(fo, ";\n");
	}

	fprintf(fo, "END\n");

	fclose(fo);
	fclose(fi);

	return 0;
}
