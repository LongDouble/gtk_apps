#include <gtk/gtk.h>
#include "support.h"

G_MODULE_EXPORT void
cb_configure_event(
    GtkWindow* window,
    GdkEvent* event,
    gpointer user_data)
{
    GdkWindow* viewport;
    struct CbData *data = user_data;
    float aspectRatio;
    int width, height;

    // Get view window of the viewport
    viewport = gtk_viewport_get_view_window((GtkViewport*)data->viewport);

    // Calculate current aspect ratio of image
    aspectRatio = (float)gdk_pixbuf_get_width(data->srcPixbuf) / (float)gdk_pixbuf_get_height(data->srcPixbuf);
    
    // Get the current width and height of the viewport
    width = gdk_window_get_width(viewport);
    height = gdk_window_get_height(viewport);

    // Check if scaling by width will make image larger than window
    if((int)(width / aspectRatio) <= height)
    {
        // Scale image and store in destination buffer
        data->destPixbuf = gdk_pixbuf_scale_simple(data->srcPixbuf, width, (int)(width / aspectRatio), GDK_INTERP_BILINEAR);

        // Set image from destination buffer
        gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

        // Clear destination buffer
        g_object_unref(G_OBJECT(data->destPixbuf));
    }
    // Scale by height 
    else
    {
        // Scale image and store in destination buffer
        data->destPixbuf = gdk_pixbuf_scale_simple(data->srcPixbuf, (int)(height * aspectRatio), height, GDK_INTERP_BILINEAR);

        // Set image from destination buffer
        gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

        // Clear destination buffer
        g_object_unref(G_OBJECT(data->destPixbuf));

    }
}

G_MODULE_EXPORT void
cb_window_destroy(
    GtkWidget* self,
    gpointer user_data)
{
    gtk_main_quit();
}
