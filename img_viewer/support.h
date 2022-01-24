#ifndef __SUPPORT_H__
#define __SUPPORT_H__
struct CbData
{
    // Widgets to load from glade
    GtkWidget *main_window;
    GtkWidget *image;
    GtkWidget *viewport;
    GtkWidget *canvasWidthLabel;
    GtkWidget *canvasHeightLabel;
    GtkWidget *imageWidthLabel;
    GtkWidget *imageHeightLabel;

    // Unscaled source photo
    GdkPixbuf* srcPixbuf;

    // Unscaled background and source photo
    GdkPixbuf* backPixbuf;

    // Contains scaled photo to display
    GdkPixbuf* destPixbuf;
};
#endif
