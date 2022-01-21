#define UI_FILE "img_viewer.glade"

#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    GtkWidget *main_window;
    GtkWidget *image;
    GtkBuilder *builder;

    GdkPixbuf* pixel_buff;

    //Init GTK+
    gtk_init(&argc, &argv);

    //Create new GtkBuilder object from file
    builder = gtk_builder_new_from_file(UI_FILE);

    // Get objects from UI file
    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    // Set the image from file
    pixel_buff = gdk_pixbuf_new_from_file_at_scale("default.bmp", 1920/2.0, 1080, 1, NULL);
    gtk_image_set_from_pixbuf((GtkImage*)image, pixel_buff);

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
