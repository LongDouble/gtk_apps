#define UI_FILE "charter.glade"

#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    GtkWidget *main_window;
    GtkWidget *chart_area;
    GtkBuilder *builder;

    //Init GTK+
    gtk_init(&argc, &argv);

    //Create new GtkBuilder object from file
    builder = gtk_builder_new_from_file(UI_FILE);

    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    chart_area = GTK_WIDGET(gtk_builder_get_object(builder, "chart_area"));

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
