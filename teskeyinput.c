#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


int main(){

	pthread_t thread0; 		//thread input capture
	int fd; 				//something-something keylogger
	struct input_event ev;	//something-something keylogger
	ssize_t n;

//**setup-pendengar-keyboard********************************************************************
	// Input keyboard device file
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    const char *dev = "/dev/input/event4";
    //const char *dev = "/dev/input/by-id/usb-_USB_Keyboard-event-kbd";
    // Open device for reference
    fd = open(dev, O_RDONLY);


    while(1){
   	    n = read(fd, &ev, sizeof ev);
		if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
	        if(ev.value == 1){ // when it pressed, 0 is released
	    		// get stored value on keyboard device reference file
			    printf("-----%d-----\n", ev.code);
			}
		}
	}

    return 0;
}