#ifndef GLOB_VAR_TYPE_H
#define GLOB_VAR_TYPE_H

#define GLOBAL_LAYAR_X 1000
#define GLOBAL_LAYAR_Y 700

#define GLOBAL_WINDOW_X 300
#define GLOBAL_WINDOW_Y 300

typedef struct{
    int r,g,b,a;
} warna;

typedef struct{
	int x;
	int y;
} titik;

extern titik windowPosition;

extern int windowSideLength;

extern unsigned char buffer_r[GLOBAL_LAYAR_X][GLOBAL_LAYAR_Y];
extern unsigned char buffer_g[GLOBAL_LAYAR_X][GLOBAL_LAYAR_Y];
extern unsigned char buffer_b[GLOBAL_LAYAR_X][GLOBAL_LAYAR_Y];
extern unsigned char buffer_a[GLOBAL_LAYAR_X][GLOBAL_LAYAR_Y];

extern unsigned char wbuffer_r[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];
extern unsigned char wbuffer_g[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];
extern unsigned char wbuffer_b[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];
extern unsigned char wbuffer_a[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];

#endif //GLOB_VAR_TYPE_H
