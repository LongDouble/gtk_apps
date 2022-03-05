#ifndef __MONITORING_H__
#define __MONITORING_H__

// Bitmap header size
#define HEADER_SIZE 54

#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

// Struct passed to every callback function
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

// Called every 100 ms to update the image
gboolean update_bmp(gpointer user_data);

#endif
