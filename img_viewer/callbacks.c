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

    // Set width and height of image
    data->destPixbuf = gdk_pixbuf_scale_simple(data->srcPixbuf, width, (int)(width / aspectRatio), GDK_INTERP_BILINEAR);

    gtk_image_set_from_pixbuf((GtkImage*)(data->image), data->destPixbuf);

    g_object_unref(G_OBJECT(data->destPixbuf));

    //return FALSE;
}
