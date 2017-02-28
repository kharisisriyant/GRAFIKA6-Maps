#include "tembakan.h"
#include "tabrakan.h"
#include "gambarwindow.h"
#include "mapParser.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

void drawObjects();		//menggambar tembakan dan objekTabrak ke buffer
void *preUpdate();		//(1)cek inputuser
void updatePosisi();	//(1)ubah posisi. (2)spawnObjek, (3)drawBuffer
void postUpdate();	 	//(1)cek kolisi, (2)loadbuffer ke layar
void zoomOut();
void zoomIn();

int windowSideLength= 300;
int zoomDiff=5;

titik windowPosition = {350,50};
plane building, road, tree;

titik pl0 = {0,0};
titik pl1 = {999,699};
titik pw0 = {0,0};
titik pw1 = {299,299};

pthread_t thread0; 		//thread input capture
int fd; 				//something-something keylogger
struct input_event ev;	//something-something keylogger
ssize_t n;
int user_input = -99;
int keypress = 0;

int main(){
	int isBuildingDisplayed = 1;
	int isTreeDisplayed = 1;
	int isRoadDisplayed = 1;

//**setup-pendengar-keyboard********************************************************************
	// Input keyboard device file
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    const char *dev = "/dev/input/event4";
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    // Open device for reference
    fd = open(dev, O_RDONLY);

    // Check if device is opened
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

//**setup-objek-game****************************************************************************
	init_fb();


//**setup-building******************************************************************************

	//read file with parser
	int nbuilding;
	plane* building = readFile("building.txt",&nbuilding);
	

//**setup-jalan******************************************************************************

	//read file with parser
	int ntree;
	plane* tree = readFile("tree.txt", &ntree);
	ntree = tree[0].n;

//**setup-pohon******************************************************************************

	//read file with parser
	warna cRed ={255,25,25,255};
	warna cGreen = {25,255,25,255};
	warna cBlue = {25,25,255,255};
	warna cWhite = {255,255,255,255};

	warna c0 = {255,255,255,255};
	c0.r += 30;
    c0.g += 30;
    c0.b += 30;
/*
	titik pt[3];
	pt[0] = pl0;
	pt[1] = p0;
	pt[2] = p1;*/

	printf("\n");
	refreshBuffer(pl0,pl1);
	drawBuildings(building,nbuilding,cWhite);
	drawTrees(tree,ntree,cGreen);

	loadBuffer();

	refreshBuffer_window(pw0,pw1);
	loadBuffer_window();

//**game-loop***********************************************************************************
	pthread_create(&thread0, NULL, preUpdate, NULL);
	while(1)
	{
		//preUpdate();
//		updatePosisi();

		refreshBuffer(pl0,pl1);
		refreshBuffer_window(pw0,pw1);
		drawBuildings(building,nbuilding,cWhite);
		drawTrees(tree,ntree,cGreen);
		drawWindow(windowPosition);

		postUpdate();
		usleep(17);
	}

//**garbaging***********************************************************************************
	//pthread_join(thread0, NULL);
	garbage_fb();
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
	return 0;
}

void *preUpdate(){
	while(1){
		// get stored value on keyboard device reference file
	    n = read(fd, &ev, sizeof ev);
	    // check if no stored value on device file
	    if (n == (ssize_t)-1) {

	    }
	    int wt = 50; //window transition
	    // if keystroke is stored on keyboard device reference file
	    if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
	        if(ev.value == 1){ // when it pressed, 0 is released
	        	printf("----%d----",ev.code);
	            switch(ev.code){
	                case 57:
	                    // Space trigger
	                    user_input = 0;
//	                    printf("%d\n", peluruterakhir);
	                    break;

	                case 105:
	                    // Left arrow trigger //zoom out
	                    user_input = -1;
	                    zoomOut();
	                    break;

	                case 106:
	                    // Right arrow trigger //zoom in
	                    user_input = 1;
	                    zoomIn();
	                    break;

	                case 30:
	                	// Case A -> window goes left
	                	if(windowPosition.x -wt >= 0){
	                		windowPosition.x -= wt;
	                	} else {
	                		windowPosition.x = 0;
	                	}
	                	break;

	                case 31:
	                	// Case S -> window goes down
	                	if(windowPosition.y + 200 + wt < GLOBAL_LAYAR_Y){
	                		windowPosition.y+= wt;
	                	}
	                	else {
	                		windowPosition.y = 500;
	                	}
	                	break;

	                case 32:
	                	// Case D -> window goes right
	                	if(windowPosition.x + 300 + wt < GLOBAL_LAYAR_X){
	                		windowPosition.x += wt;
	                	}
	                	else {
	                		windowPosition.x = 700;
	                	}
	                	break;

	                case 17:
	                	// Case W -> window goes up
	                	if(windowPosition.y -wt >= 0){
	                		windowPosition.y-=wt;
	                	}
	                	else {
	                		windowPosition.y = 0;
	                	}
	                	break;
	

	                case 36:
	                	// Case J -> just display building
	                	break;

	                case 37:
	                	// Case K -> just display tree
	                	break;

	                case 38:
	                	// Case L -> just display road
	                	break;

	                default:
	                    break;

	            }
	            keypress = 1;
	        }

	        if(ev.value == 0){
	        	keypress = 0;
	        }
	    }
	}
}

void updatePosisi(){
	//CEK INPUT
/*	if(user_input == 0){
		tembakTembakan();
		if(keypress == 0) user_input = -99;
	}
	else if(user_input == 1){
		puterTembakan(user_input);
		if(keypress == 0) user_input = -99;
	}
	else if(user_input == -1){
		puterTembakan(user_input);
		if(keypress == 0) user_input = -99;
	}
*/

	refreshBuffer(pl0,pl1);
	refreshBuffer_window(pw0,pw1);
	drawWindow(windowPosition);
}

void postUpdate(){
	loadBuffer();
	loadBuffer_window();
}

void zoomOut(){
	if(windowSideLength >=6){
		windowSideLength -= zoomDiff;
	}
	else {
		windowSideLength = 1;
	}
}


void zoomIn(){
	if(windowSideLength < 700-6){
		//masih bisa nambah
		if(windowPosition.x+windowSideLength > GLOBAL_LAYAR_X-6){
			windowPosition.x -= zoomDiff;
		}
		if(windowPosition.y+windowSideLength > GLOBAL_LAYAR_Y-6){
			windowPosition.y -= zoomDiff;
		}
		windowSideLength += zoomDiff;

	}
	else {
		windowPosition.x = 0;
		windowSideLength = 700;

	}
}
