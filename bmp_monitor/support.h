#ifndef __SUPPORT_H__
#define __SUPPORT_H__
struct CbData
{
    // Widgets to load from glade
    GtkWidget *mainWindow;
    GtkWidget *image;
    GtkWidget *frameWidthLabel;
    GtkWidget *frameHeightLabel;
    GtkWidget *progressLabel;

    // File prefix
    char prefix[4097];

    // File name
    char fileName[4097];

    // Next file name to monitor
    char nextFileName[4097];

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
