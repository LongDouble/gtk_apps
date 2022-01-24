#define UI_FILE "img_viewer.glade"

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
    if(argc != 4)
    {
        g_printerr("ERROR: No file name! (Usage: ./img_viewer <file> <canvasWidth> <canvasHeight>)\n");
        return 1;
    }

    //Create new GtkBuilder object from file
    builder = gtk_builder_new_from_file(UI_FILE);

    // Allocate memory for shared data pointer
    data = g_slice_new(struct CbData);

    // Get objects from UI file
    data->main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    data->image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
    data->viewport = GTK_WIDGET(gtk_builder_get_object(builder, "viewport"));
    data->canvasWidthLabel = GTK_WIDGET(gtk_builder_get_object(builder, "canvaswidthlabel"));
    data->canvasHeightLabel = GTK_WIDGET(gtk_builder_get_object(builder, "canvasheightlabel"));
    data->imageWidthLabel = GTK_WIDGET(gtk_builder_get_object(builder, "imagewidthlabel"));
    data->imageHeightLabel = GTK_WIDGET(gtk_builder_get_object(builder, "imageheightlabel"));

    // Connect signals
    gtk_builder_connect_signals(builder, data);
    
    // Destroy builder, since we don't need it anymore
    g_object_unref(G_OBJECT(builder));

    // Show window.  All other widgets are automatically shown by GtkBuilder
    gtk_widget_show(data->main_window);

    // Get view window of viewport
    viewport = gtk_viewport_get_view_window((GtkViewport*)data->viewport);
    width = gdk_window_get_width(viewport);
    height = gdk_window_get_height(viewport);

    // Set the image from file
    data->srcPixbuf = gdk_pixbuf_new_from_file(argv[1], NULL);

    // Create black background
    data->backPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, atoi(argv[2]), atoi(argv[3]));
    gdk_pixbuf_fill(data->backPixbuf, 0);

    // Copy image onto the background
    gdk_pixbuf_copy_area(data->srcPixbuf, 0, 0, gdk_pixbuf_get_width(data->srcPixbuf), gdk_pixbuf_get_height(data->srcPixbuf), data->backPixbuf, 0, 0);

    // Calculate current aspect ratio of image
    aspectRatio = gdk_pixbuf_get_width(data->backPixbuf) / gdk_pixbuf_get_height(data->backPixbuf);

    // Try scaling by width first
    if((int)(width / aspectRatio) <= height)
    {
        // Scale image and store in destination buffer
        data->destPixbuf = gdk_pixbuf_scale_simple(data->backPixbuf, width, (int)(width / aspectRatio), GDK_INTERP_BILINEAR);
    }
    // Scale by height if width made image outside window
    else
    {
        // Scale image and store in destination buffer
        data->destPixbuf = gdk_pixbuf_scale_simple(data->backPixbuf, (int)(height * aspectRatio), height, GDK_INTERP_BILINEAR);
    }

    // Set image from Pixbuf
    gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

    // Clear Pixbuf
    g_object_unref(G_OBJECT(data->destPixbuf));

    // Set Canvas labels
    sprintf(buff, "CanvasWidth: %s", argv[2]);
    gtk_label_set_text((GtkLabel*)(data->canvasWidthLabel), buff);
    sprintf(buff, "CanvasHeight: %s", argv[3]);
    gtk_label_set_text((GtkLabel*)(data->canvasHeightLabel), buff);
    sprintf(buff, "ImageWidth: %d", gdk_pixbuf_get_width(data->srcPixbuf));
    gtk_label_set_text((GtkLabel*)(data->imageWidthLabel), buff);
    sprintf(buff, "ImageHeight: %d", gdk_pixbuf_get_height(data->srcPixbuf));
    gtk_label_set_text((GtkLabel*)(data->imageHeightLabel), buff);

    // Start main loop
    gtk_main();

    // Free data allocated for shared memory
    g_slice_free(struct CbData, data);

    return(0);
}
