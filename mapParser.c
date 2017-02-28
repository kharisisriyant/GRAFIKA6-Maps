#include "mapParser.h"

void init(plane* bidang)
{
	if(bidang->n > 0)
	{
		bidang->point = (titik*) malloc(sizeof(titik) * bidang->n);
	}
	else
	{
		printf("mybidang is not ready\n");
	}
}

plane* readFile(char* path, int* total)
{
   FILE *fp;
   char buff[255];
   fp = fopen(path, "r");
   int readTag = 0; //0 baca x, 1 baca y
   plane* bidang = (plane*) malloc(sizeof(plane) * 1000);
   int x; //temporary buat koordinat x titik
   int y; //temporary buat koordinat y titik
   int i; //index array plane yang bakal diisi
   int ii; //index array titik yang bakal diisi

   i = -1;
   ii = 0;

while(fscanf(fp, "%s", buff) != EOF)
{
	if(buff[0] != '\n')
	{
		if(buff[0] == '-')
		{
			i++;
			ii=0;
			//tulis angka banyak titik
			int n = atoi(&buff[1]);
			//printf("%d",n);
			//printf("bangunan\n");

			//inisialisasi array titik
			bidang[i].n = n;
			init(&bidang[i]);
		}
		else
		{
			//baca titik
			if(readTag == 0)
			{
				x = atoi(buff);
				bidang[i].point[ii].x = x;
				//printf("%d ", x); //titik x dibaca
				readTag = 1;
			}
			else //readTag == 1
			{
				y = atoi(buff);
				bidang[i].point[ii].y = y;
				readTag = 0;		//titik y dibaca
				//printf("%d\n", y);

				ii++;
			}
		}
	}
}

   fclose(fp);

   *total = i;

   return bidang;
}