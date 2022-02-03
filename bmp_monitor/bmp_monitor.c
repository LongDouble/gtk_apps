#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>
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
    data->mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    data->image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
    data->frameWidthLabel = GTK_WIDGET(gtk_builder_get_object(builder, "framewidthlabel"));
    data->frameHeightLabel = GTK_WIDGET(gtk_builder_get_object(builder, "frameheightlabel"));

    // Connect signals
    gtk_builder_connect_signals(builder, data);
    
    // Destroy builder, since we don't need it anymore
    g_object_unref(G_OBJECT(builder));

    // Set initial conditions
    data->frameNumber = 1;
    data->state = 0;
    data->fileSize = 0;
    strcpy(data->prefix, argv[1]);
    sprintf(data->fileName, "%s%u.bmp", data->prefix, data->frameNumber);

    // Set window title
    gtk_window_set_title((GtkWindow*)(data->mainWindow), data->fileName);

    // Show window.  All other widgets are automatically shown by GtkBuilder
    gtk_widget_show(data->mainWindow);

    // Run update_bmp function every 100 ms to check for changes
    gint func_ref = g_timeout_add(100, update_bmp, data);

    // Set Canvas labels
    //sprintf(buff, "Frame Width: %d", gdk_pixbuf_get_width(data->srcPixbuf));
    //gtk_label_set_text((GtkLabel*)(data->frameWidthLabel), buff);
    //sprintf(buff, "Frame Height: %d", gdk_pixbuf_get_height(data->srcPixbuf));
    //gtk_label_set_text((GtkLabel*)(data->frameHeightLabel), buff);

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
    struct stat st;
    unsigned int size;
    short int exists;

    // Get file size
    exists = stat(data->fileName, &st);
    size = st.st_size;
    g_print("Exist: (%u) Size: (%u)\n", exists, size);

    // Check if still waiting to load image
    if((data->state) == 0)
    {
        // Check if file exists with header information
        if((exists == 0) && (size > HEADER_SIZE))
        {
            // Indicate image exists and needs to be moitored
            data->state = 1;
        }
    }

    // File exists and needs to be checked for updates
    if((data->state) == 1)
    {
        
        // Check if new file size is larger
        if(size > (data->fileSize))
        {
            data->fileSize = size;

            // Set the image from file
            data->srcPixbuf = gdk_pixbuf_new_from_file(data->fileName, NULL);

            // Set image from Pixbuf
            gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->srcPixbuf);

            //Clear Pixbuf
            g_object_unref(G_OBJECT(data->srcPixbuf));
        }
    }
    return TRUE;
}
