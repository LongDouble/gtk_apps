#include "monitoring.h"

// Run every 100 ms
gboolean update_bmp(gpointer user_data)
{
    struct CbData *data = user_data;

    // Set when user requested mazimized window
    static int setMax = 0;

    // Holds current window width and height
    int windowWidth, windowHeight;

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

            // Create new destination Pixbuf
            data->destPixbuf =  gdk_pixbuf_new(
                                    GDK_COLORSPACE_RGB, 
                                    0, 
                                    8, 
                                    gdk_pixbuf_get_width(data->srcPixbuf), 
                                    gdk_pixbuf_get_height(data->srcPixbuf)
                                );

            // Fill destination Pixbuf with black
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

            // Set max width and height geometry values
            (data->geometry).max_width = gdk_pixbuf_get_width(data->destPixbuf);
            (data->geometry).max_height = gdk_pixbuf_get_height(data->destPixbuf);

            // Apply max width and height geometry values to window
            gtk_window_set_geometry_hints(
                GTK_WINDOW(data->mainWindow),
                NULL,
                &(data->geometry),
                GDK_HINT_MAX_SIZE
            );

            // Set image from Pixbuf
            gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);
            
            // Format new window title string
            if(strchr(data->fileName, '/') != NULL)
            {
                // Insert filename without path
                strcpy(data->windowTitle, (strrchr(data->fileName, '/')) + 1);
            }
            else
            {
                // Insert whole filename since there is no path
                strcpy(data->windowTitle, data->fileName);
            }

            // Add dimensions and progress to window title
            sprintf(buff, " (%d", gdk_pixbuf_get_width(data->srcPixbuf));
            strcat(data->windowTitle, buff);

            sprintf(buff, "x%d) ", gdk_pixbuf_get_height(data->srcPixbuf));
            strcat(data->windowTitle, buff);

            sprintf(buff, "(%.2f%%)", ((float)(size - HEADER_SIZE) / (float)(fullSize)) * 100.0);
            strcat(data->windowTitle, buff);

            // Set window title
            gtk_window_set_title((GtkWindow*)(data->mainWindow), data->windowTitle);

            // Clear Pixbuf
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

        // Format new window title string
        if(strchr(data->fileName, '/') != NULL)
        {
            // Insert filename without path
            strcpy(data->windowTitle, (strrchr(data->fileName, '/')) + 1);
        }
        else
        {
            // Insert whole filename since there is no path
            strcpy(data->windowTitle, data->fileName);
        }

        // Set new window title
        gtk_window_set_title((GtkWindow*)(data->mainWindow), data->windowTitle);

        // Clear image for new one
        gtk_image_clear((GtkImage*)(data->image));
    }

    // Get size of window
    gtk_window_get_size((GtkWindow*)(data->mainWindow), &windowWidth, &windowHeight);

    // Check if user requested maximized window when this function last ran
    if(setMax == 1)
    {
        // Resize window to max size
        gtk_window_resize(
            (GtkWindow*)(data->mainWindow), 
            (data->geometry).max_width, 
            (data->geometry).max_height
        );
        
        // Reset flag
        setMax = 0;
    }

    // Check if current window is too large (if user maximized)
    if(
    (windowWidth > ((data->geometry).max_width)) || 
    (windowHeight > ((data->geometry).max_height))
    )
    {
        // Unmaximize window
        gtk_window_unmaximize((GtkWindow*)(data->mainWindow));

        // Set max flag
        setMax = 1;
    }

    // Return TRUE so function keeps getting called every 100 ms
    return TRUE;
}
