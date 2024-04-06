/*
  Very simple example of an X11 Window responding to the user key abd mouse events
  Will close the window if Escape key is pressed
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




void displayMouseEvent(XEvent e)
{
   char buttonClicked[15];

   if (e.xkey.keycode == LEFT_MOUSE_BUTTON) strcpy(buttonClicked, "Left Button");
   else if (e.xkey.keycode == RIGHT_MOUSE_BUTTON) strcpy(buttonClicked, "Right Button");
   else if (e.xkey.keycode == MOUSE_WHEEL_UP) strcpy(buttonClicked, "Wheel Up");
   else if (e.xkey.keycode == MOUSE_WHEEL_DOWN) strcpy(buttonClicked, "Wheel Down");
   else strcpy(buttonClicked, "Unknown");

   printf("Mouse Click Button EVENT  TYPE IS %d , button is %s, coords are [%d,%d]\n",e.type, buttonClicked, e.xkey.x, e.xkey.y);
}

int main()
{

  Display *d = XOpenDisplay(NULL);
  if (d == NULL)
  {
     printf("Unable to build display!\n");
     return -1;
  }

  int s = DefaultScreen(d);

  Window w =XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, WIN_WIDTH, WIN_HEIGHT, 5, BlackPixel(d,s), WhitePixel(d,s));

  XSetStandardProperties(d, w, "Howdy", "Hi", None, NULL, 0, NULL);


  // Adding the mouse and redraw (expose) event to be monitored in the main event loop...
  XSelectInput(d, w, ExposureMask | ButtonPressMask | KeyPressMask);

  XMapWindow(d,w);

  XEvent e;

  while (1)
  {
         XNextEvent(d,&e);

          if (e.type == KeyPress )
          {
            if (e.xkey.keycode == ESCAPE_KEY) break;
            else printf("Key EVENT: Type is %d , Key Code is %d\n", e.type,e.xkey.keycode);
          }

           if(e.type==ButtonPress)           displayMouseEvent(e);
   }


  printf("Exit!\n");

  XCloseDisplay(d);

  return 0;
}
