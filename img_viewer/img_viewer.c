#define UI_FILE "img_viewer.glade"

#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    GtkWidget *main_window;
    GtkWidget *image;
    GtkBuilder *builder;

    // Used to avoid losing track of unscaled photo address
    GdkPixbuf* srcPixBuf;

    // Contains scaled photo to display
    GdkPixbuf* destPixBuf;

    //Init GTK+
    gtk_init(&argc, &argv);

    //Create new GtkBuilder object from file
    builder = gtk_builder_new_from_file(UI_FILE);

    // Get objects from UI file
    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    // Set the image from file
    srcPixBuf = gdk_pixbuf_new_from_file("default.bmp", NULL);

    // Scale the image and delete original Pixbuf
    destPixBuf = gdk_pixbuf_scale_simple(srcPixBuf, gdk_pixbuf_get_width(srcPixBuf) / 2, gdk_pixbuf_get_height(srcPixBuf) / 2, GDK_INTERP_BILINEAR);
    g_object_unref(G_OBJECT(srcPixBuf));

    // Set image from Pixbuf
    gtk_image_set_from_pixbuf((GtkImage*)image, destPixBuf);

    // Connect signals
    gtk_builder_connect_signals(builder, NULL);
    
    // Destroy builder, since we don't need it anymore
    g_object_unref(G_OBJECT(builder));

    // Show window.  All other widgets are automatically shown by GtkBuilder
    gtk_widget_show(main_window);

    // Start main loop
    gtk_main();

    return(0);
}
