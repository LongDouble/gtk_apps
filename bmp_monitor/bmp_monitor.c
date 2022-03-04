#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include "support.h"

#define HEADER_SIZE 54

gboolean update_bmp(gpointer user_data);

int main(int argc, char **argv)
{
    struct CbData *data;
    GtkBuilder *builder;

    // Character buffer
    char buff[256];

    // Init GTK+
    gtk_init(&argc, &argv);

    // Verify a filename was passed as an argument
    if(argc != 2)
    {
        g_printerr("ERROR: No file prefix! (Usage: ./bmp_monitor <file-prefix>)\n");
        return 1;
    }

    // Create new GtkBuilder object from resource
    builder = gtk_builder_new_from_resource("/org/gtk/bmp_monitor/bmp_monitor.glade");

    // Allocate memory for shared data pointer
    data = g_slice_new(struct CbData);

    // Get objects from UI file
    data->mainWindow = GTK_WIDGET(
                            gtk_builder_get_object(builder, "mainWindow"));
    data->image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
    data->frameWidthLabel = GTK_WIDGET(gtk_builder_get_object(builder, "framewidthlabel"));
    data->frameHeightLabel =    GTK_WIDGET(gtk_builder_get_object(builder, "frameheightlabel"));
    data->progressLabel = GTK_WIDGET(gtk_builder_get_object(builder, "progresslabel"));

    // Connect signals
    gtk_builder_connect_signals(builder, data);
    
    // Destroy builder, since we don't need it anymore
    g_object_unref(G_OBJECT(builder));

    // Set initial conditions
    data->frameNumber = 1;
    data->fileSize = 0;
    strcpy(data->prefix, argv[1]);
    sprintf(data->fileName, "%s%u.bmp", data->prefix, data->frameNumber);
    sprintf(data->nextFileName, "%s%u.bmp", data->prefix, (data->frameNumber) + 1);

    // Set window title
    gtk_window_set_title((GtkWindow*)(data->mainWindow), (strrchr(data->fileName, '/')) + 1);

    // Show window.  All other widgets are automatically shown by GtkBuilder
    gtk_widget_show(data->mainWindow);

    // Run update_bmp function every 100 ms to check for changes
    gint func_ref = g_timeout_add(100, update_bmp, data);

    // Start main loop
    gtk_main();

    // Free data allocated for shared memory
    g_slice_free(struct CbData, data);

    // Remove the timeout function
    g_source_remove(func_ref);

    return(0);
}


// Run every 100 ms
gboolean update_bmp(gpointer user_data)
{
    struct CbData *data = user_data;

    // Structs needed to retrieve file size
    struct stat st;
    struct stat nextSt;

    // Retrieved file sizes
    unsigned int size;
    unsigned int nextSize;

    // 0 if files exist
    short int exists;
    short int nextExists;

    // General use character buffer
    char buff[64];

    // Calculated full size of image when complete (not including header)
    unsigned int fullSize;

    // Number of lines present in current bitmap
    unsigned int numLines;

    // Get file size
    exists = stat(data->fileName, &st);
    size = st.st_size;

    // Check if file exists with header information
    if((exists == 0) && (size > HEADER_SIZE))
    {
        // Check if new file size is different size
        if(size != (data->fileSize))
        {
            // Update file size
            data->fileSize = size;

            // Set the image from file
            data->srcPixbuf = gdk_pixbuf_new_from_file(data->fileName, NULL);

            // Create black background
            data->destPixbuf =  gdk_pixbuf_new(
                                    GDK_COLORSPACE_RGB, 
                                    0, 
                                    8, 
                                    gdk_pixbuf_get_width(data->srcPixbuf), 
                                    gdk_pixbuf_get_height(data->srcPixbuf)
                                );

            gdk_pixbuf_fill(data->destPixbuf, 0);

            // Calculate finished full size of image in bytes (not including header)
            fullSize = (gdk_pixbuf_get_width(data->srcPixbuf) * gdk_pixbuf_get_height(data->srcPixbuf))*3;

            // Calculate number of lines present in current bitmap
            numLines = floor((double)((((float)(size - HEADER_SIZE)) / 
                            ((float)(fullSize))) * 
                            (float)(gdk_pixbuf_get_height(data->srcPixbuf))));

            // Copy occupied area of bitmap to top of canvas
            gdk_pixbuf_copy_area(
                data->srcPixbuf,
                0,
                gdk_pixbuf_get_height(data->srcPixbuf) - numLines,
                gdk_pixbuf_get_width(data->srcPixbuf),
                numLines,
                data->destPixbuf,
                0,
                0
            );

            // Set image from Pixbuf
            gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

            // Set Canvas labels
            sprintf(buff, "Frame Width: %d", gdk_pixbuf_get_width(data->srcPixbuf));
            gtk_label_set_text((GtkLabel*)(data->frameWidthLabel), buff);

            sprintf(buff, "Frame Height: %d", gdk_pixbuf_get_height(data->srcPixbuf));
            gtk_label_set_text((GtkLabel*)(data->frameHeightLabel), buff);

            sprintf(buff, "Progress: %.2f%%", ((float)(size - HEADER_SIZE) / (float)(fullSize)) * 100.0);
            gtk_label_set_text((GtkLabel*)(data->progressLabel), buff);

            //Clear Pixbuf
            g_object_unref(G_OBJECT(data->srcPixbuf));
            g_object_unref(G_OBJECT(data->destPixbuf));
        }
    }

    // Check for next file to monitor
    nextExists = stat(data->nextFileName, &nextSt);
    nextSize = nextSt.st_size;

    // Check if next file exists and contains header information
    if((nextExists == 0) && (nextSize > HEADER_SIZE))
    {
        // Update data for new file
        data->frameNumber = (data->frameNumber) + 1;
        data->fileSize = 0;
        sprintf(data->fileName, "%s%u.bmp", data->prefix, data->frameNumber);
        sprintf(data->nextFileName, "%s%u.bmp", data->prefix, (data->frameNumber) + 1);

        // Set new window title
        gtk_window_set_title((GtkWindow*)(data->mainWindow), (strrchr(data->fileName, '/')) + 1);

        // Clear image for new one
        gtk_image_clear((GtkImage*)(data->image));
    }

    // Return TRUE so function keeps getting called
    return TRUE;
}
