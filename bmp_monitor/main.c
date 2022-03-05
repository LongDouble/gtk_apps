#include "main.h"
#include "monitoring.h"

int main(int argc, char **argv)
{
    // Struct passed to every callback
    struct CbData *data;

    // Builds UI from file
    GtkBuilder *builder;

    // Character buffer
    char buff[256];

    // Init GTK+
    gtk_init(&argc, &argv);

    // Verify a filename was passed as an argument
    if(argc != 2)
    {
        g_printerr("ERROR: Incorrect program usage! (Usage: ./bmp_monitor <file-prefix>)\n");
        return 1;
    }

    // Create new GtkBuilder object from resource
    builder = gtk_builder_new_from_resource("/org/gtk/bmp_monitor/bmp_monitor.glade");

    // Allocate memory for shared data pointer
    data = g_slice_new(struct CbData);

    // Get objects from UI file
    data->mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    data->image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

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

    // Format new window title string
    if(strchr(data->fileName, '/') != NULL)
    {
        // Insert filename without path into title
        strcpy(data->windowTitle, (strrchr(data->fileName, '/')) + 1);
    }
    else
    {
        // Insert whole filename since there is no path
        strcpy(data->windowTitle, data->fileName);
    }

    // Set window title
    gtk_window_set_title((GtkWindow*)(data->mainWindow), data->windowTitle);

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
