#ifndef __SUPPORT_H__
#define __SUPPORT_H__
struct CbData
{
    // Widgets to load from glade
    GtkWidget *main_window;
    GtkWidget *image;
    GtkWidget *viewport;
    GtkWidget *frameWidthLabel;
    GtkWidget *frameHeightLabel;

    // Unscaled source photo
    GdkPixbuf* srcPixbuf;

    // Contains scaled photo to display
    GdkPixbuf* destPixbuf;
};
#endif
