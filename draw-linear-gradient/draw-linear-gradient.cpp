/*
  Very simple example of an X11 Window, an draw a linear gradient rectangle on the screen.
  I use a thread to force redraw of the screen, using a different gradient.

  TODO:
      As expected a lot of fliquering happens, an equivalent of double douffering should be used here.
      Find a way also to force a redraw on the screen (Emit Expose event), and a redraw from the utility thread is not optimal

*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


const int WIN_X_POS           = 50;
const int WIN_Y_POS           = 50;
const int WIN_WIDTH           = 400;
const int WIN_HEIGHT          = 300;
const int WIN_BORDER          = 1;

const int ESCAPE_KEY          = 9;

const int LEFT_MOUSE_BUTTON   = 1;
const int RIGHT_MOUSE_BUTTON  = 3;

typedef unsigned long  RGBCode;

struct myThreadParams
{
   int count;
   Display *displayPtr;
};

bool initWindow();
void mouseEventHandler(XEvent event);
void drawScreen();
void* refreshDrawThread (void* allParams);



RGBCode RGB(int r, int g, int b);

Display *displayPtr = NULL;
Window window;
GC graphicContext;

RGBCode blackCode, whiteCode, redCode, blueCode;

float startRed   = 223.0;
float startGreen = 255.0;
float startBlue  = 0.0;




RGBCode RGB(int r, int g, int b) {
    return b + (g<<8) + (r<<16);
}


bool initWindow()
{
  displayPtr = XOpenDisplay(NULL);
  if (displayPtr == NULL)
  {
     printf("Unable to build display!\n");
     return false;
  }

  int screen = DefaultScreen(displayPtr);
  blackCode = BlackPixel(displayPtr, screen);
  whiteCode = WhitePixel(displayPtr, screen);
  redCode   = RGB(255,0,0);
  blueCode  = RGB(0,0,255);

  window =XCreateSimpleWindow(displayPtr, DefaultRootWindow(displayPtr), 0, 0, WIN_WIDTH, WIN_HEIGHT, 5, blackCode, blueCode );
  XSetStandardProperties(displayPtr, window, "Linear Gradient", "Hi", None, NULL, 0, NULL);

  // Adding the mouse and redraw (expose) event to be monitored in the main event loop...
  XSelectInput(displayPtr, window, ExposureMask | ButtonPressMask | KeyPressMask);
  XMapWindow(displayPtr,window);

  graphicContext=XCreateGC(displayPtr, window, 0,0);

  return true;
}

void drawScreen()
{
   float deltaRed   = startRed   / (float)WIN_HEIGHT;
   float deltaGreen = startGreen / (float)WIN_HEIGHT;
   float deltaBlue  = startBlue / (float)WIN_HEIGHT;



    XSetForeground(displayPtr,graphicContext,blackCode );
    XFillRectangle(displayPtr,window,graphicContext,0,0,WIN_WIDTH,WIN_HEIGHT);



   for (int y=0;y<WIN_HEIGHT;y++)
   {
        int redValue =deltaRed * y;
        int greenValue =deltaGreen * y;
        int blueValue =deltaBlue * y;

        XSetForeground(displayPtr,graphicContext,RGB(redValue,greenValue,blueValue) );
        XDrawLine(displayPtr, window, graphicContext,0,y,WIN_WIDTH,y);
   }

    printf("I have been exposed.\n");

}



void mouseEventHandler(XEvent event)
{

   if (event.xkey.keycode == LEFT_MOUSE_BUTTON)
   {
      // Do something...
   }
}

void* refreshDrawThread (void* allParams)
{

    myThreadParams *params = (myThreadParams *)allParams;
    printf("Value passed to the thread:  displayPtr = %d, flag = %p\n", params->count, params-> displayPtr);
    int numIterations = (params->count > 0) ? params->count : 0;


    srand(time(NULL));   // Initialization, should only be called once.



     for (int i=0;i<numIterations;i++)
     {

            startRed   = (float)(rand() & 255);
            startGreen = (float)(rand() & 255);
            startBlue  = (float)(rand() & 255);

            printf("Start [r,g,b] = [%f,%f,%f]\n",startRed,startGreen,startBlue);

            fputc ('y', stderr);
            drawScreen();
            //XFlush(params->displayPtr);
            usleep(100000);
     }

     return NULL;
}




int main()
{

   pthread_t thread_redraw;
   myThreadParams params;


  if (  !initWindow() )
  {
    printf("X11 Window initialisation failed, terminate application...\n");
    return -1;
  }


    params.count = 20;
    params.displayPtr = displayPtr;




   pthread_create (&thread_redraw, NULL, &refreshDrawThread, &params);




  XEvent e;

  while (1)
  {
         XNextEvent(displayPtr,&e);

          if (e.type == KeyPress && e.xkey.keycode == ESCAPE_KEY)
          {
             break;
          }

          if(e.type==ButtonPress)
            mouseEventHandler(e);


          if(e.type==Expose && e.xexpose.count==0)
          {
             drawScreen();
             XFlush(displayPtr);
          }

   }


  printf("Exit!\n");

  XCloseDisplay(displayPtr);

  return 0;
}
