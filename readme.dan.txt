Based on the YouTube video:  https://www.youtube.com/watch?v=nIXmRmAIO1Y

the video is a great introduction to basic windowing and graphic under Linux's X11 system


Compilation
===========

  X11 project can be compiled using:
     * the cmake command (which will produce a Make file that can be invoked from the Terminal)
     * (For single source file project), from the command: gcc <source.cpp> -o <outputfile> -lX11
       Note: the X11 library system has to be included into the linking, hence the -lX11 param... 
