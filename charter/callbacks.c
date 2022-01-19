#include "support.h"

G_MODULE_EXPORT gboolean
cb_draw_chart(  GtkWidget *widget,
                cairo_t* cr,
                gpointer user_data  )
{
    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context(widget);

    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);

    gtk_render_background(context, cr, 0, 0, width, height);

    cairo_arc(  cr,
                width / 2.0, height / 2.0,
                MIN (width, height) / 2.0,
                0, 2 * G_PI);

    gtk_style_context_get_color(    context,
                                    gtk_style_context_get_state(context),
                                    &color);
    gdk_cairo_set_source_rgba(cr, &color);

    cairo_fill(cr);

    return FALSE;
}
