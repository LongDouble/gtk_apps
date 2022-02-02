#ifndef __SUPPORT_H__
#define __SUPPORT_H__
struct CbData
{
    // Widgets to load from glade
    GtkWidget *mainWindow;
    GtkWidget *image;
    GtkWidget *frameWidthLabel;
    GtkWidget *frameHeightLabel;

    // File prefix
    char prefix[4097];

    // File name
    char fileName[4097];

    // Current frame number
    unsigned int frameNumber;

    /* State
     * 0 - Waiting for file to be created
     * 1 - Monitoring file for changes in size
     */
    unsigned short int state;

    // Size of the currenly monitored BMP
    unsigned int fileSize;

    // Unscaled source photo
    GdkPixbuf* srcPixbuf;
};
#endif
