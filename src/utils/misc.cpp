#include "misc.h"

void getScreenResolution(int &width, int &height)
{
#if WIN32
    width  = (int) GetSystemMetrics(SM_CXSCREEN);
    height = (int) GetSystemMetrics(SM_CYSCREEN);
#else
    Display *d = XOpenDisplay(nullptr);
    bool success = false;
    if (d) {
        int screen = DefaultScreen(d);
        // Get the mouse cursor position
        int win_x, win_y, root_x, root_y = 0;
        unsigned int mask = 0;
        Window child_win, root_win;
        XQueryPointer(d, XRootWindow(d, screen), &child_win, &root_win,
                         &root_x, &root_y, &win_x, &win_y, &mask);
        int dummy1, dummy2;
        // Get all the screens
        if (XineramaQueryExtension(d, &dummy1, &dummy2))
        {
            if (XineramaIsActive(d))
            {
                int heads=0;
                XineramaScreenInfo *p=XineramaQueryScreens(d, &heads);
                if (heads>0) 
                {
                    for (int i=0; i < heads ; i++)
                        // Check if where the mouse cursor is
                        if (root_x >= p[i].x_org && root_x <= p[i].x_org + p[i].width &&
                            root_y >= p[i].y_org && root_y <= p[i].y_org + p[i].height)
                        {
                            width = p[i].width;
                            height = p[i].height;
                            success = true;
                        }
                }
                XFree(p);
            }
        }
        XCloseDisplay(d);
    }
    if (!success)
    {
        width = sf::VideoMode::getDesktopMode().width;
        height = sf::VideoMode::getDesktopMode().height;
    }
#endif
}
