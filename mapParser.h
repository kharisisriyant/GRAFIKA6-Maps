typedef struct{
	int n; //banyak titik
	titik* points; //titik pada bidang
} plane; //maksudnya bidang

void init();

plane* readFile(char* path);