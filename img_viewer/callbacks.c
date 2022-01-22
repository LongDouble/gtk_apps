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

    viewport = gtk_viewport_get_view_window((GtkViewport*)data->viewport);

    // Calculate current aspect ratio of image
    aspectRatio = gdk_pixbuf_get_width(data->srcPixbuf) / gdk_pixbuf_get_height(data->srcPixbuf);
    
    // Get the current width of the scrolled window
    width = gdk_window_get_width(viewport);
    height = gdk_window_get_height(viewport);

    // Check if scaling by width will make image less than 1 pixel or larger than window
    if((width > 0) && ((int)(width / aspectRatio) > 0) && ((int)(width / aspectRatio) <= height))
    {
        // Scale image and store in destination buffer
        data->destPixbuf = gdk_pixbuf_scale_simple(data->srcPixbuf, width, (int)(width / aspectRatio), GDK_INTERP_BILINEAR);

        // Set image from destination buffer
        gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

        // Clear destination buffer
        g_object_unref(G_OBJECT(data->destPixbuf));
    }
    // Check if scaling by height will make image less than 1 pixel or larger than window
    else if((height > 0) && ((int)(height * aspectRatio) > 0) && ((int)(width * aspectRatio) <= width))
    {
        // Scale image and store in destination buffer
        data->destPixbuf = gdk_pixbuf_scale_simple(data->srcPixbuf, height, (int)(height * aspectRatio), GDK_INTERP_BILINEAR);

        // Set image from destination buffer
        gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

        // Clear destination buffer
        g_object_unref(G_OBJECT(data->destPixbuf));

    }
}
