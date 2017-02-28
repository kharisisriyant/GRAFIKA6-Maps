#ifndef GAMBARWINDOW_H
#define GAMBARWINDOW_H

#include "glob_var_type.h"
#include "gambar.h"

unsigned char wbuffer_r[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];
unsigned char wbuffer_g[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];
unsigned char wbuffer_b[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];
unsigned char wbuffer_a[GLOBAL_WINDOW_X][GLOBAL_WINDOW_Y];

//mengembalikan titik dengan nilai x dan y sesuai argumen
titik setTitik_window(int x, int y);

// Melakukan assign warna c pada
// posisi c pada matriks framebuffer
void bufferDrawDot_window(titik p, warna c);

//memasukka warna pixel pada driver
void DrawDot_window(titik p, warna c);

// Melakukan assign warna default ke matriks
// buffer (bukan matriks framebuffer) berupa
// segi empat yang dibentuk oleh dua titik p0 dan p1
void refreshBuffer_window(titik p0, titik p1);

// Memuat/assign nilai dari matriks buffer
// ke matriks framebuffer.
void loadBuffer_window();

//membuat bidang yang menyambungkan titik p[0] ke p[1], p[1] ke p[2], ...., p[n] ke p[0]
//dengan warna solid
void bufferDrawPlaneSolid_window(titik* p, warna c, warna bound_c, int sisi);	
	                                                					
//membuat gambar dengan origin sebagai posisi
//void bufferDrawPlaneSolidCitra(titik* citra, titik origin, warna fill, warna bound, int sisi); 

//melakukan pewarnaan flood denganp sebagai titik api
void fill_window(titik p, warna c, warna bound_c);	
/*

//================================================
void bufferDrawLine(titik p0, titik p1, warna c);	//mmengganti nilai pixel sehingga tergambar garis dari p0 ke p1
void bufferDrawPlane(titik* p, warna c, int sisi);			//membuat bidang yang menyambungkan titik p[0] ke p[1], p[1] ke p[2], ...., p[n] ke p[0]
//================================================
void bufferDrawCircle(titik p, int radius, warna c);	//membuat lingkaran dengan p sebagai pusat
/*int  dotDistance(titik p1, titik p2);		//mengembalikan jarak antara p1 dan p2
//================================================

// membuat pesawat dengan xof sebagai ofside kiri, yof sebagai ofset atas
void drawPlane(int xof, int yof);

// membuat tank dengan xof sebagai ofside kiri, yof sebagai ofset atas
void drawTank(int xof, int yof);

titik getMidPoint(titik *citra, int sisi);
*/
#endif //GAMBARWINDOW_H
