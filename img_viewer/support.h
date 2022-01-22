#ifndef __SUPPORT_H__
#define __SUPPORT_H__
struct CbData
{
    GtkWidget *main_window;
    GtkWidget *image;

    // Used to avoid losing track of unscaled photo address
    GdkPixbuf* srcPixbuf;

    // Contains scaled photo to display
    GdkPixbuf* destPixbuf;
};
#endif
