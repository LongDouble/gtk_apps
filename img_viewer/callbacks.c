#include <gtk/gtk.h>
#include "support.h"

G_MODULE_EXPORT void
cb_configure_event(
    GtkWindow* window,
    GdkEvent* event,
    gpointer user_data)
{
    struct CbData *data = user_data;
    float aspectRatio;
    int width, height;

    // Calculate current aspect ratio of image
    aspectRatio = gdk_pixbuf_get_width(data->srcPixbuf) / gdk_pixbuf_get_height(data->srcPixbuf);
    
    // Get the current width of the scrolled window
    gtk_window_get_size((GtkWindow*)(data->main_window), &width, &height);

    // Verify that neither width or height will be less than 1 pixel
    if((width > 0) && ((int)(width / aspectRatio) > 0))
    {
        // Scale image and store in destination buffer
        data->destPixbuf = gdk_pixbuf_scale_simple(data->srcPixbuf, width, (int)(width / aspectRatio), GDK_INTERP_BILINEAR);

        // Set image from destination buffer
        gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

        // Clear destination buffer
        g_object_unref(G_OBJECT(data->destPixbuf));
    }


    //return FALSE;
}
