// global_* dan GLOBAL_*
#include "framebuffer_init.h"

// deklarasi fungsi
#include "gambarwindow.h"
#include <stdio.h>
#include <math.h>

titik setTitik_window(int x, int y){
    titik temp = {x, y};
    return temp;
}

//mengganti nilai pixel dengan posisi p pada buffer dengan warna c
void DrawDot_window(titik p, warna c){
    if((p.x < 1) || (p.x >= GLOBAL_WINDOW_X) || (p.y < 1) || (p.y >= GLOBAL_WINDOW_Y)){
		return ;
	}

    long int position = (p.x + 1000 + global_vinfo.xoffset) * (global_vinfo.bits_per_pixel / 8) +
       (p.y + global_vinfo.yoffset) * global_finfo.line_length;

    if(global_vinfo.bits_per_pixel == 32){
        *(global_fbp + position) = c.b;
        *(global_fbp + position + 1) = c.g;
        *(global_fbp + position + 2) = c.r;
        *(global_fbp + position + 3) = c.a;
    }else{
        // assume 16 bit color
        int b = c.b;
        int g = c.g;
        int r = c.r;
        unsigned short int t = r<<11 | g << 5 | b;
        *((unsigned short int*)(global_fbp + position)) = t;
    }
}

void bufferDrawDot_window(titik p, warna c){
    if((p.x < 0) || (p.x > GLOBAL_WINDOW_X-1) || (p.y < 0) || (p.y > GLOBAL_WINDOW_Y-1)){
		return ;
	}

    wbuffer_b[p.x][p.y] = c.b;
    wbuffer_g[p.x][p.y] = c.g;
    wbuffer_r[p.x][p.y] = c.r;
    wbuffer_a[p.x][p.y] = c.a;
}

//mengganti nilai seluruh pixel buffer menjadi background color untuk window
void refreshBuffer_window(titik p0, titik p1){
    warna warna_default = {25, 25, 255, 255};

    int i, j;
    if(p0.x < p1.x && p0.y < p1.y){
        for(i = p0.x; i < p1.x; i++)
            for(j = p0.y; j < p1.y; j++){
                wbuffer_r[i][j] = warna_default.r;
                wbuffer_g[i][j] = warna_default.g;
                wbuffer_b[i][j] = warna_default.b;
                wbuffer_a[i][j] = warna_default.a;
            }

        return;
    }

    if(p0.x > p1.x && p0.y < p1.y){
        for(i = p1.x; i < p0.x; i++)
            for(j = p0.y; j < p1.y; j++){
                wbuffer_r[i][j] = warna_default.r;
                wbuffer_g[i][j] = warna_default.g;
                wbuffer_b[i][j] = warna_default.b;
                wbuffer_a[i][j] = warna_default.a;
            }

        return;
    }

    if(p0.x > p1.x && p0.y > p1.y){
        for(i = p1.x; i < p0.x; i++)
            for(j = p1.y; j < p0.y; j++){
                wbuffer_r[i][j] = warna_default.r;
                wbuffer_g[i][j] = warna_default.g;
                wbuffer_b[i][j] = warna_default.b;
                wbuffer_a[i][j] = warna_default.a;
            }

        return;
    }

    if(p0.x < p1.x && p0.y > p1.y){
        for(i = p0.x; i < p1.x; i++)
            for(j = p1.y; j < p0.y; j++){
                wbuffer_r[i][j] = warna_default.r;
                wbuffer_g[i][j] = warna_default.g;
                wbuffer_b[i][j] = warna_default.b;
                wbuffer_a[i][j] = warna_default.a;
            }

        return;
    }
}

//memasukkan nilai buffer ke driver
void loadBuffer_window(){
    int i, j;

    titik titik_sementara;
    warna warna_sementara;
    warna warna_kosong = {0, 0, 0, 0};
    for(i = 0; i < GLOBAL_WINDOW_X; i++)
        for(j = 0; j < GLOBAL_WINDOW_Y; j++){
            titik_sementara.x = i;
            titik_sementara.y = j;

            if(wbuffer_r[i][j] && wbuffer_g[i][j] &&
            wbuffer_b[i][j] && wbuffer_a[i][j]){
                warna_sementara.r = wbuffer_r[i][j];
                warna_sementara.g = wbuffer_g[i][j];
                warna_sementara.b = wbuffer_b[i][j];
                warna_sementara.a = wbuffer_a[i][j];
            }else{
                warna_sementara = warna_kosong;
            }

            DrawDot_window(titik_sementara, warna_sementara);
        }
}

void bufferDrawPlane_window(titik* p, warna c, int sisi){
	int i= 0;

	for (i = 0; i < sisi-1; i++) {
		bufferDrawLine_window(p[i], p[i+1], c);
	}


	bufferDrawLine_window(p[i], p[0], c);
}

/*
void bufferDrawCircle_window(titik p, int radius, warna c){
    inline void bufferDrawHorizontalLine(int x1, int x2, int y, warna c)
    {
        int i; titik l;
        for (i = x1; i < x2 ; i++){
            l.x = i; l.y = y;
            bufferDrawDot_window(l, c);
        }
    }
    inline void plot4poin(titik p1, int x, int y, warna c)
    {
        /*
        //Lingkaran kosong
        int a = p1.x+ x;
        int b = p1.x- x;
        int d = p1.y +y;
        int e = p1.y -y;
        titik pa = {a,d};
        titik pb = {b,d};
        titik pc = {a,e};
        titik pd = {b,e};
        bufferDrawDot(pa,c);
        bufferDrawDot(pb,c);
        bufferDrawDot(pc,c);
        bufferDrawDot(pd,c); */

       // Lingkaran berisi
  /*      bufferDrawHorizontalLine(p1.x - x, p1.x + x, p1.y + y,c);
        bufferDrawHorizontalLine(p1.x - x, p1.x + x, p1.y - y,c);
    }

    inline void plot8poin(titik p1, int x, int y, warna c)
    {
        plot4poin(p1, x, y, c);
        plot4poin(p1, y, x, c);
    }


    int error = -radius;
    int x = radius;
    int y = 0;

    while (x >= y)
    {
        plot8poin(p, x, y, c);

        error += y;
        y++;
        error += y;

        if (error >= 0)
        {
            error += -x;
            x--;
            error += -x;
        }
    }
}*/

int is_color_window(titik p, warna c) {
  if ((p.x < 1) || (p.x >= GLOBAL_WINDOW_X) || (p.y < 1) || (p.y >= GLOBAL_WINDOW_Y)) {
      return 1;
  }

    return wbuffer_r[p.x][p.y] == c.r && wbuffer_g[p.x][p.y] == c.g
    && wbuffer_b[p.x][p.y] == c.b && wbuffer_a[p.x][p.y] == c.a;
}

void fill_window(titik p, warna c, warna bound_c) {
    if (!is_color_window(p, c) && !is_color_window(p, bound_c)) {
        bufferDrawDot_window(p, c);
        titik new_p = {p.x, p.y+1};
        fill_window(new_p, c, bound_c);
        new_p.x = p.x-1; new_p.y = p.y;
        fill_window(new_p, c, bound_c);
        new_p.x = p.x+1; new_p.y = p.y;
        fill_window(new_p, c, bound_c);
        new_p.x = p.x; new_p.y = p.y-1;
        fill_window(new_p, c, bound_c);
    }
}

void bufferDrawLine_window(titik p0, titik p1, warna c) {
    int x0 = p0.x; int x1 = p1.x; int y0 = p0.y; int y1 = p1.y;
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    for (;;) {
      titik temp = {x0, y0};
      bufferDrawDot_window(temp, c);
      if (x0==x1 && y0==y1) break;
      e2 = err;
      if (e2 >-dx) { err -= dy; x0 += sx; }
      if (e2 < dy) { err += dx; y0 += sy; }
    }
}

titik get_intersection(titik p0, titik p1) {
  // Dijamin pasti berpotongan dengan window. Perjalanan dihitung dari p0 ke p1
  int x0 = p0.x; int x1 = p1.x; int y0 = p0.y; int y1 = p1.y;
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;

  int err = (dx>dy ? dx : -dy)/2, e2;
  for (;;) {
    titik temp = {x0, y0};
    if ((x0 < 1) || (x0 >= GLOBAL_WINDOW_X) || (y0 < 1) || (y0 >= GLOBAL_WINDOW_Y)) {
      return temp;
    }
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

titik move_to_window(titik p) {
  titik temp;
  temp.x = p.x - windowPosition.x;
  temp.y = p.y - windowPosition.y;
  return temp;
}

// titik getMidPoint(titik *citra, int sisi) {
//   titik ans;
//   int i = 0, midx = 0, midy = 0;
//   for (i = 0; i < sisi; i++) {
//     midx += citra[i].x;
//     midy += citra[i].y;
//   }
//   midx /= sisi; midy /= sisi;
//   ans.x = midx; ans.y = midy;
//   return ans;
// }

int isOnWindow(titik p0, titik p1)
{
	int zone0 = DotZone(p0);
	int zone1 = DotZone(p1);

	if(zone0 == 0 && zone1 == 0)
	{
		return 1; //semua di dalam window
	}

	int crossResult = zone0 & zone1;

	if(crossResult == 0)
	{
//		printf("crox\n");
		//cek mana yang keluar window
		int zoneout;
		if(zone0 != 0)
		{
			zoneout = zone0;
		}
		else
		{
			zoneout = zone1;
		}

		//itung-itung
		int x0 = p0.x;
		int x1 = p1.x;
		int y0 = p0.y;
		int y1 = p1.y;

		int x, y;
		int xleft = windowPosition.x;
		int ytop  = windowPosition.y;


		int length_x = windowSideLength;
		int length_y = windowSideLength;

		int xright  = windowPosition.x + length_x;
		int ybottom = windowPosition.y + length_y;

		if((zoneout == 8) || (zoneout == 9) || (zoneout == 10)) //titik di atas
		{
            if((y1-y0) == 0) // mengindari division by 0
            {
                return 1;
            }

			x = x0 + (x1 - x0) * (ytop - y0) / (y1 - y0);
			y = ytop;
		}
		else if((zoneout == 4) || (zoneout == 5) || (zoneout == 6)) //titik di bawah
		{
            if((y1-y0) == 0) // mengindari division by 0
            {
                return 1;
            }

			x = x0 + (x1 - x0) * (ybottom - y0) / (y1 - y0);
			y = ybottom;
		}
		else if((zoneout == 1)) // titik di kiri
		{
            if((x1-x0) == 0) // mengindari division by 0
            {
                return 1;
            }

			y = y0 + (y1 - y0) * (xleft - x0) / (x1 - x0);
			x = xleft;
		}
		else //titik di kanan
		{
            if((x1-x0) == 0) // mengindari division by 0
            {
                return 1;
            }

			y = y0 + (y1 - y0) * (xright - x0) / (x1 - x0);
			x = xright;
		}

		titik baru = {x,y};
		if(zone0 != 0)
		{
			return isOnWindow(baru, p1);
		}
		else
		{
			return isOnWindow(p0, baru);
		}
	}
	else
	{
//		printf("fail\n");
		return 0; //ngga terpotong
	}
}

int DotZone(titik p)
{
	int xleft = windowPosition.x;
	int ytop  = windowPosition.y;


	int length_x = windowSideLength;
	int length_y = windowSideLength;

	int xright  = windowPosition.x + length_x;
	int ybottom = windowPosition.y + length_y;

	int xp = p.x;
	int yp = p.y;

	if ((xp < xleft) && (yp < ytop)) {
		return 9; //kiri-atas
	} else if ((xp > xright) && (yp < ytop)) {
		return 10; //kanan-atas
	} else if ((xp < xleft) && (yp > ybottom)) {
		return 5; //kiri-bawah
	} else if ((xp > xright) && (yp > ybottom)) {
		return 6; //kanan-bawah
	} else if (yp > ybottom) {
		return 4; //tengah-bawah
	} else if (yp < ytop) {
		return 8; //tengah-atas
	} else if (xp < xleft) {
		return 1; //tengah-kiri
	} else if (xp > xright) {
		return 2; //tengah-kanan
	} else {
		return 0;
	}
}
