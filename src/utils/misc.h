#if WIN32
  #include <windows.h>
#else
  #include <SFML/Graphics.hpp>
  #include <X11/extensions/Xinerama.h>
  #include <X11/Xutil.h>
#endif

void getScreenResolution(int &width, int &height);
