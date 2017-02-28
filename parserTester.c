#include "mapParser.h"

int main()
{
	int total;
	plane* bidang = readFile("tree.txt", &total);


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

	printf("total %d\n", total);

	return 0;
}