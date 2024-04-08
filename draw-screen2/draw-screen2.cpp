/*
  Very simple example of an X11 Window responding to the user click.
  Will draw a red line on left click, and write 'Hello World' on Right click
  Will close the window if Escape key is pressed

  TODO:
      Draw one line by mouse left click
      Redraw on Expose event...
      Add a cleanup function (for the drawing context )
      Fix

*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>


const int WIN_X_POS           = 50;
const int WIN_Y_POS           = 50;
const int WIN_WIDTH           = 400;
const int WIN_HEIGHT          = 300;
const int WIN_BORDER          = 1;

const int ESCAPE_KEY          = 9;

const int LEFT_MOUSE_BUTTON   = 1;
const int RIGHT_MOUSE_BUTTON  = 3;
const int MOUSE_WHEEL_UP      = 4;
const int MOUSE_WHEEL_DOWN    = 5;

typedef unsigned long  RGBCode;

bool initWindow();
void mouseEventHandler(XEvent event);
void leftButtonEventHandler(XEvent event);
void rigthButtonEventHandler(XEvent event);
void drawScreen();

RGBCode RGB(int r, int g, int b);



Display *displayPtr = NULL;
Window window;
GC graphicContext;


RGBCode blackCode, whiteCode, redCode, blueCode;



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
  XSetStandardProperties(displayPtr, window, "Drawing", "Hi", None, NULL, 0, NULL);

  // Adding the mouse and redraw (expose) event to be monitored in the main event loop...
  XSelectInput(displayPtr, window, ExposureMask | ButtonPressMask | KeyPressMask);
  XMapWindow(displayPtr,window);

  graphicContext=XCreateGC(displayPtr, window, 0,0);

  //int displayHeight = XDisplayHeight(displayPtr,screen);
  //int displayWidth = XDisplayWidth(displayPtr,screen);


  return true;
}

void drawScreen()
{
   RGBCode yellowCode = RGB(223,255,0);
   RGBCode purpleCode = RGB(255,0,255);


   //Yellow Rectangle
    XSetForeground(displayPtr,graphicContext,yellowCode);
    XFillRectangle( displayPtr, window, graphicContext, 0, 0, 50, 50 );

    XSetForeground(displayPtr,graphicContext,purpleCode);
    // X11 uses a very strange system of 1/64 of degree for the angle... So there are 360deg * 64 parts/deg...
    XDrawArc(displayPtr, window, graphicContext, WIN_WIDTH/2, WIN_HEIGHT/2, 100,100,0,360*64);
}



void mouseEventHandler(XEvent event)
{

   if (event.xkey.keycode == LEFT_MOUSE_BUTTON)        leftButtonEventHandler(event);
   else if (event.xkey.keycode == RIGHT_MOUSE_BUTTON)  rigthButtonEventHandler(event);

}

void leftButtonEventHandler(XEvent event)
{
   XSetForeground(displayPtr,graphicContext,redCode);
   XDrawLine(displayPtr,window,graphicContext,20,20 ,  WIN_WIDTH-20, WIN_HEIGHT-20);
}

void rigthButtonEventHandler(XEvent event)
{
   char message[15];
   strcpy(message,"Hello World");
   XSetForeground(displayPtr,graphicContext,whiteCode);
   XDrawString(displayPtr,window,graphicContext,100,100,message,strlen(message));
}




int main()
{

  if (  !initWindow() )
  {
    printf("X11 Window initialisation failed, terminate application...\n");
    return -1;
  }

  XEvent e;

  while (1)
  {
         XNextEvent(displayPtr,&e);

          if (e.type == KeyPress )
          {
            if (e.xkey.keycode == ESCAPE_KEY) break;
            else printf("Key EVENT: Type is %d , Key Code is %d\n", e.type,e.xkey.keycode);
          }

          if(e.type==ButtonPress)
            mouseEventHandler(e);
            //displayMouseEvent(e);


          if(e.type==Expose && e.xexpose.count==0)
          {
             drawScreen();
          }

   }


  printf("Exit!\n");

  XCloseDisplay(displayPtr);

  return 0;
}
