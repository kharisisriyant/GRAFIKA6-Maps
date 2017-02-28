#include "tabrakan.h"
#include "tembakan.h"
#include "rotasi.h"
#include "refleksi.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

//cek apakah terdapat peluru yang berada sejauh offset dari pesawat
//jika iya kedua objek memiliki status true

#define PI 3.14159265

int turns = 0;

extern int pesawatterakhir;
extern int peluruterakhir;
extern int objekterakhir;
tembakan prime;

extern objekTabrak pesawat[10];
extern objekTabrak peluru[10];
extern objekTabrak objek[10];
extern objekTabrak propeller[10];

void cekTabrakanObjek(int offset){
	int qq = pesawatterakhir;
	int ww = peluruterakhir;

	for (int i =0; i<qq ; i++){
		for (int j =0; j<ww ; j++){

			float jarak = sqrt((pesawat[i].posisi.x-peluru[j].posisi.x)*(pesawat[i].posisi.x-peluru[j].posisi.x)+(pesawat[i].posisi.y-peluru[j].posisi.y)*(pesawat[i].posisi.y-peluru[j].posisi.y));

			if (jarak<=offset){
				pesawat[i].status=1;
				peluru[j].status=1;

			}
		}
	}
}

//hilangkan objek pesawat dari memori
void hancurObjek(objekTabrak* o){
	o->status=-1;
}

//ganti posisi seluruh objek sesuai kecepatan dan arah
void jalanObjek(){
	int qq = pesawatterakhir;
	int ww = peluruterakhir;
	int tt = objekterakhir;
	titik putar = {600,1050};

	double val = PI / 180.0;

	//jalanpesawat==========================================================================================
	for (int i =0; i< qq ; i++){

		if(pesawat[i].status==0){
			titik temp = pesawat[i].posisi;
			titik* temp2 = pesawat[i].citra;
			pesawat[i].posisi = rotasi(putar, temp, 1);

			//Spawn propeller if plane still exists
			propeller[i].posisi.x = pesawat[i].posisi.x + pesawat[i].citra[4].x;
			propeller[i].posisi.y = pesawat[i].posisi.y + pesawat[i].citra[4].y;
		}

		//Move propeller if plane is destroyed
		if (propeller[i].status == 0) {
			propeller[i].posisi.x = propeller[i].posisi.x+(cos(propeller[i].arah*val)*propeller[i].kecepatan);
			propeller[i].posisi.y = propeller[i].posisi.y-(sin(propeller[i].arah*val)*propeller[i].kecepatan);
		}

		titik mid = getMidPoint(propeller[i].citra, 12);
		rotasibanyak(mid, propeller[i].citra, 120, 12);
		if (turns++ == 3) {
			turns = 0;
			setupCitraPropeller(&propeller[i]);
		}
		if (propeller[i].posisi.y > 680) {
			propeller[i].arah = 50;
		}
	}
	//jalanpeluru==========================================================================================
	for (int i =0; i<10 ; i++){
		if(peluru[i].status==0){
			peluru[i].posisi.x = peluru[i].posisi.x+(cos(peluru[i].arah*val)*peluru[i].kecepatan);
			peluru[i].posisi.y = peluru[i].posisi.y-(sin(peluru[i].arah*val)*peluru[i].kecepatan);
		}
	}

	//jalanobjek==========================================================================================
	for (int i =0; i<10 ; i++){
		if(objek[i].status==0){
			objek[i].posisi.x = objek[i].posisi.x+(cos(objek[i].arah*val)*objek[i].kecepatan);
			objek[i].posisi.y = objek[i].posisi.y-(sin(objek[i].arah*val)*objek[i].kecepatan);
			if (i == 1) {
				titik mid = getMidPoint(objek[i].citra, 4);
				rotasibanyak(mid, objek[i].citra, 30, 4);
			} else if (i == 2) {
				titik mid = getMidPoint(objek[i].citra, 4);
				rotasibanyak(mid, objek[i].citra, 30, 4);
			} else if (i == 3) {
				titik mid = getMidPoint(objek[i].citra, 4);
				reflectDotArray(objek[i].citra, 4, 'x', mid);
			}
		}
	}
}

void setupCitraPesawat(objekTabrak *pesawat) {
	pesawat->citra = (titik*) malloc(36 * sizeof(titik));
	titik* citra = pesawat->citra;
	citra[0].x = 20; citra[0].y = 20;
	citra[1].x = 90; citra[1].y = 20;
	citra[2].x = 130; citra[2].y = 80;
	citra[3].x = 180; citra[3].y = 90;
	citra[4].x = 190; citra[4].y = 20;
	citra[5].x = 180; citra[5].y = 20;
	citra[6].x = 180; citra[6].y = 10;
	citra[7].x = 240; citra[7].y = 10;
	citra[8].x = 260; citra[8].y = 20;
	citra[9].x = 240; citra[9].y = 20;
	citra[10].x = 280; citra[10].y = 80;
	citra[11].x = 300; citra[11].y = 70;
	citra[12].x = 350; citra[12].y = 70;
	citra[13].x = 390; citra[13].y = 90;
	citra[14].x = 450; citra[14].y = 110;
	citra[15].x = 390; citra[15].y = 130;
	citra[16].x = 260; citra[16].y = 130;
	citra[17].x = 230; citra[17].y = 190;
	citra[18].x = 240; citra[18].y = 200;
	citra[19].x = 150; citra[19].y = 200;
	citra[20].x = 150; citra[20].y = 190;
	citra[21].x = 160; citra[21].y = 190;
	citra[22].x = 180; citra[22].y = 130;
	citra[23].x = 130; citra[23].y = 140;
	citra[24].x = 80; citra[24].y = 180;
	citra[25].x = 40; citra[25].y = 180;
	citra[26].x = 30; citra[26].y = 150;
	citra[27].x = 40; citra[27].y = 140;
	citra[28].x = 40; citra[28].y = 130;
	citra[29].x = 30; citra[29].y = 120;
	citra[30].x = 30; citra[30].y = 110;
	citra[31].x = 40; citra[31].y = 100;
	citra[32].x = 60; citra[32].y = 90;
	citra[33].x = 60; citra[33].y = 80;
	citra[34].x = 30; citra[34].y = 30;
	citra[35].x = 20; citra[35].y = 30;
}

void setupCitraPeluru(objekTabrak *peluru) {
	peluru->citra = (titik*) malloc(5 * sizeof(titik));
	titik* citra = peluru->citra;
	citra[0].x = -10; citra[0].y = 25;
	citra[1].x = -10; citra[1].y = 0;
	citra[2].x = 0; citra[2].y = -25;
	citra[3].x = 10; citra[3].y = 0;
	citra[4].x = 10; citra[4].y = 25;
}

void setupCitraPecah(objekTabrak *pecah, int type) {
	pecah->citra = (titik*) malloc(5 * sizeof(titik));
	int xp = pecah->posisi.x; int yp = pecah->posisi.y;
	titik* citra = pecah->citra;
	int xof = xp-600;
	int yof = yp-200;

	if(type == 0)
	{
		titik puing[] = {{xof,yof+25}, {xof,yof+50}, {xof+25,yof+45}, {xof+15,yof+25}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 1)
	{
		titik puing[] = {{xof+90,yof+45}, {xof+190,yof+45}, {xof+190,yof+70}, {xof+90, yof+70}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 2)
	{
		titik puing[] = {{xof+70,yof}, {xof+85,yof}, {xof+105, yof+45}, {xof+80,yof+45}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 3)
	{
		titik puing[] = {{xof+70,yof+70}, {xof+95,yof+70}, {xof+80, yof+120}, {xof+55, yof+120}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 4)
	{
		titik puing[] = {{xof+190,yof+45}, {xof+220,yof+50}, {xof+225, yof+70}, {xof+190, yof+70}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
}

void setupCitraPropeller(objekTabrak *propeller) {
	propeller->citra = (titik*) malloc(12 * sizeof(titik));
	titik* citra = propeller->citra;
	citra[0].x = 260; citra[0].y = 90;
	citra[1].x = 245; citra[1].y = 100;
	citra[2].x = 245; citra[2].y = 100;
	citra[3].x = 260; citra[3].y = 100;
	citra[4].x = 260; citra[4].y = 115;
	citra[5].x = 270; citra[5].y = 115;
	citra[6].x = 270; citra[6].y = 100;
	citra[7].x = 285; citra[7].y = 100;
	citra[8].x = 285; citra[8].y = 90;
	citra[9].x = 270; citra[9].y = 90;
	citra[10].x = 270; citra[10].y = 75;
	citra[11].x = 260; citra[11].y = 75;
}

//membuat objek baru(a=pesawat; b=peluru) pada posisi p
void spawnObjek(char t, titik p){
	if (t=='a') {
		pesawat[pesawatterakhir].posisi = p;
		pesawat[pesawatterakhir].arah = 0;
		pesawat[pesawatterakhir].kecepatan = 5;
		pesawat[pesawatterakhir].status = 0;
		setupCitraPesawat(&pesawat[pesawatterakhir]);

		// propeller
		titik propPoint;
		propPoint.x = pesawat[pesawatterakhir].posisi.x + pesawat[pesawatterakhir].citra[4].x;
		propPoint.y = pesawat[pesawatterakhir].posisi.y + pesawat[pesawatterakhir].citra[4].y;
		propeller[pesawatterakhir].posisi = propPoint;
		propeller[pesawatterakhir].arah = 280;
		propeller[pesawatterakhir].kecepatan = 25;
		propeller[pesawatterakhir].status = -1;
		setupCitraPropeller(&propeller[pesawatterakhir]);

		pesawatterakhir++;
	} else if (t=='b') {
		peluru[peluruterakhir].posisi = p;
		peluru[peluruterakhir].kecepatan = 25;
		peluru[peluruterakhir].arah = 90 - prime.kemiringan;
		peluru[peluruterakhir].status = 0;
		setupCitraPeluru(&peluru[peluruterakhir]);
		peluruterakhir++;
	} else if (t=='z') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 20;
		objek[objekterakhir].arah = 270;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 0);
		objekterakhir++;
	} else if (t=='x') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 20;
		objek[objekterakhir].arah = 260;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 1);
		objekterakhir++;
	} else if (t=='y') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 20;
		objek[objekterakhir].arah = 300;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 2);
		objekterakhir++;
	} else if (t=='w') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 20;
		objek[objekterakhir].arah = 240;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 3);
		objekterakhir++;
	}
}

void gambarHancur(titik p) {

	//titik pe = {p.x,p.y};
	static int ii = 0;
	static int stage = 0;
	//titik pd = {p.x+10,p.y-10};
	if(ii==0 && stage == 0){
		titik pp = p;
		spawnObjek('z', p);
		p.x = pp.x+5; p.y =pp.y+9;

		spawnObjek('x', p);
		p.x = pp.x-20; p.y =pp.y-14;

		spawnObjek('y', p);
		p.x = pp.x-5; p.y =pp.y+20;

		spawnObjek('w', p);

		propeller[pesawatterakhir-1].status = 0;
	}

	if(ii<10 && stage == 0){
		warna c = {255, 10+20*ii, 0, 255};
		bufferDrawCircle(p, 10-1*ii, c);
		ii++;
	}
	else{
		stage = 1;
	}


	if(ii>0 && stage == 1){
		warna c = {255, 200-15*ii, 0, 255};
		bufferDrawCircle(p, 20-2*ii, c);
		ii--;
	}
}


//**************************************************************************************************
void gambarObjek() {
	titik p[12];
	warna green = {1, 255, 1, 255};
	warna red = {255, 1, 1, 255};
	warna yellow = {255, 255, 1, 255};
	warna black = {0, 0, 0, 255};
	warna gold = {255, 215, 1, 255};

	// Draw airplane
	for (int i = 0; i < pesawatterakhir; i++) {
		if (pesawat[i].status == 0) {
			bufferDrawPlaneSolidCitra(pesawat[i].citra, pesawat[i].posisi, green, red, 36);
			bufferDrawPlaneSolidCitra(propeller[i].citra, propeller[i].posisi, yellow, black, 12);
		}
	}

	// Draw propeller if airplane is destroyed
	for (int i = 0; i < pesawatterakhir; i++) {
		if (propeller[i].status == 0) {
			bufferDrawPlaneSolidCitra(propeller[i].citra, propeller[i].posisi, yellow, black, 12);
		}
	}

	// Draw bullet
	for (int i = 0; i < peluruterakhir; i++) {
		if (peluru[i].status == 0) {
			bufferDrawPlaneSolidCitra(peluru[i].citra, peluru[i].posisi, gold, red, 5);
		}
	}

	// Draw debris
	for (int i = 0; i < objekterakhir; i++) {
		if (objek[i].status == 0) {
			bufferDrawPlaneSolidCitra(objek[i].citra, objek[i].posisi, green, red, 4);
		}
	}
}

//**************************************************************************************************
