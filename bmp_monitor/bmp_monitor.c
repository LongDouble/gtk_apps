//#define UI_FILE "bmp_monitor.glade"

#include <gtk/gtk.h>
#include "support.h"
#include <string.h>

int main(int argc, char **argv)
{
    struct CbData *data;
    GtkBuilder *builder;
    GdkWindow* viewport;

    // Character buffer
    char buff[256];

    // Initial viewport width and height
    int width, height;

    // Original image aspect ratio
    float aspectRatio;

    // Init GTK+
    gtk_init(&argc, &argv);

    // Verify a filename was passed as an argument
    if(argc != 2)
    {
        g_printerr("ERROR: No file prefix! (Usage: ./bmp_monitor <file-prefix>)\n");
        return 1;
    }

    //Create new GtkBuilder object from file
    builder = gtk_builder_new_from_resource("/org/gtk/bmp_monitor/bmp_monitor.glade");

    // Allocate memory for shared data pointer
    data = g_slice_new(struct CbData);

    // Get objects from UI file
    data->main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    data->image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
    data->viewport = GTK_WIDGET(gtk_builder_get_object(builder, "viewport"));
    data->frameWidthLabel = GTK_WIDGET(gtk_builder_get_object(builder, "framewidthlabel"));
    data->frameHeightLabel = GTK_WIDGET(gtk_builder_get_object(builder, "frameheightlabel"));

    // Connect signals
    gtk_builder_connect_signals(builder, data);
    
    // Destroy builder, since we don't need it anymore
    g_object_unref(G_OBJECT(builder));

    // Set window title
    gtk_window_set_title((GtkWindow*)(data->main_window), argv[1]);

    // Show window.  All other widgets are automatically shown by GtkBuilder
    gtk_widget_show(data->main_window);

    // Get view window of viewport
    viewport = gtk_viewport_get_view_window((GtkViewport*)data->viewport);
    width = gdk_window_get_width(viewport);
    height = gdk_window_get_height(viewport);

    // Set the image from file
    data->srcPixbuf = gdk_pixbuf_new_from_file(argv[1], NULL);

    // Set image from Pixbuf
    gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->srcPixbuf);

    // Clear Pixbuf
    g_object_unref(G_OBJECT(data->srcPixbuf));

    // Set Canvas labels
    sprintf(buff, "Frame Width: %d", gdk_pixbuf_get_width(data->srcPixbuf));
    gtk_label_set_text((GtkLabel*)(data->frameWidthLabel), buff);
    sprintf(buff, "Frame Height: %d", gdk_pixbuf_get_height(data->srcPixbuf));
    gtk_label_set_text((GtkLabel*)(data->frameHeightLabel), buff);

    // Start main loop
    gtk_main();

    // Free data allocated for shared memory
    g_slice_free(struct CbData, data);

    return(0);
}
