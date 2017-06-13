#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint-gcc.h>
#include "mbntool.h"

int parse_mbn(char* image)
{
	int i = 0;
	char str[16] = {0};
	uint32_t offset = 0;
	uint32_t buf[10] = {0};

	for (i=0; i<10; i++)
	{
		buf[i] = *(uint32_t*)(image + (i*4));
	}

	for (i=0; i<26; i++)
	{
		if (buf[0] == type[i].image_id)
		{
			printf("%s [0x%x]\n\n", type[i].image, type[i].image_id);
			printf("***** %s\n\n", type[i].name);
			break;
		}
	}
	for (i=0; i<10; i++)
	{
		printf("%s 0x%X\n", mbn[i].name, buf[i]);
	}
	printf("\n");
	offset = ((buf[8] - buf[3]) + (HW_ID_OFFSET + MBN_HEADER_LEN));

	memcpy(str, (image+offset), 8);
	printf("HW_ID:    %s\n", str);

	offset -= 0x24;
	memcpy(str, (image+offset), 8);
	printf("Rollback: %s\n\n", str);
	return 0;
}

int parse_sbl(char* image)
{
	int i = 0;
	uint32_t buf[13] = {0};

	if (*(uint32_t*)(image+8) == 0x15)
	{
		printf("***********************");
		printf("\nSBL1 Image Detected!\n");
		printf("***********************\n\n");
	}
	else if (*(uint32_t*)(image+8) == 0x0D)
	{
		printf("***********************");
		printf("\neHostDL Image Detected!\n");
		printf("***********************\n\n");
	}
	else
	{
		printf("Could not identify image type!\n");
	}
	
	for (i=0; i<13; i++)
	{
		buf[i] = *(uint32_t*)(image+sbl[i].offset);
		printf("%s: 0x%X\n", sbl[i].name, buf[i]);
	}
	printf("\n");
	return 0;
}

int parse_header(char* image)
{
	FILE* inf;
	int i = 0;
	uint32_t size, result;
	char* data;
	
	inf = fopen(image, "rb");
	if (!inf)
	{
		printf("Error opening image %s\n", image);
		return 1;
	}
	
	fseek(inf, 0, SEEK_END);
	size = ftell(inf);
	rewind(inf);

	data = (char*)malloc(sizeof(char)*(size));
	if (!data)
	{
		printf("Failed to allocate buffer!\n");
		return 1;
	}
	
	result = fread((data), 1, size, inf);
	if (result != size)
	{
		printf("Error reading image %s\n\r", image);
		return 1;
	}
	fclose(inf);
	
	result = *(uint32_t*)data;
	if (result == SBL_IMAGE)
	{
		printf("Detected SBL1 image!\n\n");
		parse_sbl(data);
	}

	else if (result < IMG_MAX)
	{
		printf("Detected MBN image!\n\n");
		parse_mbn(data);
	}
	else if (result == ELF_IMAGE)
	{
		printf("Detected ELF image, not support!\n\n");
	}
	else
	{
		printf("Image could not be identified!\n\n");
	}	

	free(data);

	return 0;
}

int main(int argc, char* argv[])
{	
	char image[200] = {0};
	
	if (argc < 2)
	{
		printf("No MBN file specified\n");
		return 1;
	}
	if (argc > 2)
	{
		printf("Too many arguments. Specify only MBN file\n");
		return 1;
	}	
	sscanf(argv[1], "%s", image);
	
	printf("Processing...\n\n");
	parse_header(image);
	
	return 0;
}
