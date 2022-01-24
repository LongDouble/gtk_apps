#ifndef __SUPPORT_H__
#define __SUPPORT_H__
struct CbData
{
    GtkWidget *main_window;
    GtkWidget *image;
    GtkWidget *viewport;

    // Unscaled source photo
    GdkPixbuf* srcPixbuf;

    // Unscaled background and source photo
    GdkPixbuf* backPixbuf;

    // Contains scaled photo to display
    GdkPixbuf* destPixbuf;
};
#endif
