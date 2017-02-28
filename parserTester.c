#include "mapParser.h"

int main()
{
	plane* bidang = readFile("building.txt");


	printf("========================================================\n");
	for(int i=0; i<10; i++)
	{
		printf("bidang punya %d titik\n", bidang[i].n);
		for(int ii=0; ii<bidang[i].n; ii++)
		{
			printf("[%d, ", bidang[i].point[ii].x);
			printf("%d]\n", bidang[i].point[ii].y);
		}
	}

	return 0;
}