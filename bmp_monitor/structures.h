#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

 #include <gtk/gtk.h>

// Struct passed to callbacks and refresh function
struct CbData
{
    // Widgets to load from glade
    GtkWidget *mainWindow;
    GtkWidget *image;

    // Geometry information for setting max window size
    GdkGeometry geometry;

    // File prefix
    char prefix[4097];

    // File name
    char fileName[4097];

    // Next file name to monitor
    char nextFileName[4097];

    // Window title
    char windowTitle[4097];

    // Current frame number
    unsigned int frameNumber;

    // Size of the currenly monitored BMP
    unsigned int fileSize;

    // Unmodified source photo
    GdkPixbuf* srcPixbuf;

    // Image drawn from top
    GdkPixbuf * destPixbuf;
};

#endif
