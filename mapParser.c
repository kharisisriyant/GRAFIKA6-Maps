#include "mapParser.h"
#include "skala.h"

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
			printf("%d",n);
			printf("bangunan\n");

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

   *total = (i+1);

   return bidang;
}

line* readFileRoad(char *path, int *total) {
	FILE *fp;
	char buff[255];
	fp = fopen(path, "r");
	int readTag = 0; //0 baca x1, 1 baca y1, 2 baca x2, 3 baca y2
	line* lines = (line*) malloc(sizeof(line) * 1000);
	int a;
	int i, j; //index array plane yang bakal diisi
	titik p0 = {0, 0};

	i = 0;
	while(fscanf(fp, "%s", buff) != EOF) {
		if (buff[0] != '\n') {
		 	//baca titik
			a = atoi(buff);
		 	if (readTag == 0) {
			 	lines[i].p1.x = a;
			 	readTag = 1;
		 	} else if (readTag == 1) {
			 	lines[i].p1.y = a;
			 	readTag = 2;
		 	} else if (readTag == 2) {
			 	lines[i].p2.x = a;
			 	readTag = 3;
		 	} else if (readTag == 3) {
			 	lines[i].p2.y = a;
			 	readTag = 0;
				i++;
		 	}
	 	}
	}
	for (int j = 0; j < i; j++) {
		lines[j].p1 = scaleDot(p0, lines[j].p1, 1.37);
		lines[j].p2 = scaleDot(p0, lines[j].p2, 1.37);
	}
	fclose(fp);
	*total = i;
	return lines;
}
