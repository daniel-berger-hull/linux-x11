/*
  Very simple example of an X11 Window responding to the user key events
  Will close the window if Escape key is pressed
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdio>



const int WIN_X_POS     = 50;
const int WIN_Y_POS     = 50;
const int WIN_WIDTH     = 200;
const int WIN_HEIGHT    = 100;
const int WIN_BORDER    = 1;

const int ESCAPE_KEY    = 9;



int main()
{

  Display *d = XOpenDisplay(NULL);
  if (d == NULL)
  {
     printf("Unable to build display!\n");
     return -1;
  }

  int s = DefaultScreen(d);

  /*
  Window w = XCreateSimpleWindow(d,
                                 RootWindow(d,s), WIN_X_POS, WIN_Y_POS ,
                                 WIN_WIDTH, WIN_HEIGHT,
                                 WIN_BORDER,
                                 BlackPixel(d,s), WhitePixel(d,s)); */


  Window w =XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, 300, 600, 5, BlackPixel(d,s), WhitePixel(d,s));



  XSetStandardProperties(d, w, "Howdy", "Hi", None, NULL, 0, NULL);


  //XSelectInput(d,w,KeyPressMask);
  XSelectInput(d, w, ExposureMask | ButtonPressMask | KeyPressMask);

  XMapWindow(d,w);

  XEvent e;

  while (1)
  {
         XNextEvent(d,&e);
          printf("EVENT 2: Type is %d , Key Code is %d\n", e.type,e.xkey.keycode);

          if (e.type == KeyPress && e.xkey.keycode == ESCAPE_KEY)
          {
            break;
          }

           if(e.type==ButtonPress)
           {
                printf("EVENT Button\n");
           }

  /*
    if ( XPending(d) )
    {

     } */
   }


  printf("Exit!\n");

  XCloseDisplay(d);

  return 0;
}
