#define UI_FILE "img_viewer.glade"

#include <gtk/gtk.h>
#include "support.h"

int main(int argc, char **argv)
{
    struct CbData *data;
    GtkBuilder *builder;

    //Init GTK+
    gtk_init(&argc, &argv);

    //Create new GtkBuilder object from file
    builder = gtk_builder_new_from_file(UI_FILE);

    data = g_slice_new(struct CbData);

    // Get objects from UI file
    data->main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    data->image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    // Set the image from file
    data->srcPixbuf = gdk_pixbuf_new_from_file("default.bmp", NULL);

    // Scale the image
    data->destPixbuf = gdk_pixbuf_scale_simple(data->srcPixbuf, gdk_pixbuf_get_width(data->srcPixbuf) / 2, gdk_pixbuf_get_height(data->srcPixbuf) / 2, GDK_INTERP_BILINEAR);

    // Set image from Pixbuf
    gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

    // Clear Pixbuf
    g_object_unref(G_OBJECT(data->destPixbuf));

    // Connect signals
    gtk_builder_connect_signals(builder, data);
    
    // Destroy builder, since we don't need it anymore
    g_object_unref(G_OBJECT(builder));

    // Show window.  All other widgets are automatically shown by GtkBuilder
    gtk_widget_show(data->main_window);

    // Start main loop
    gtk_main();

    g_slice_free(struct CbData, data);

    return(0);
}
