#include <gtk/gtk.h>
#include "support.h"

// Close process when window is closed
G_MODULE_EXPORT void
cb_window_destroy(
    GtkWidget* self,
    gpointer user_data)
{
    gtk_main_quit();
}
