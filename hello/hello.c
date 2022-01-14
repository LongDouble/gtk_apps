/*
 * Creates a 200x200 window with a button that occupies the full size of the 
 * window. Clicking the button prints "Hello World" to the terminal.
 */

#include <gtk/gtk.h>

// Callback function is called when button is clicked
static void print_hello(GtkWidget *widget, gpointer data)
{
    // Print Hello World to terminal
    g_print("Hello World\n");
}

// Callback function which is called when application is first started
static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;

    // Create a new application window for the application
    window = gtk_application_window_new(app);

    // Set the window title
    gtk_window_set_title (GTK_WINDOW(window), "Window");

    // Set the default size
    gtk_window_set_default_size (GTK_WINDOW(window), 200, 200);

    // Create a push button with a label
    button = gtk_button_new_with_label("Hello World");

    // Connect the event-handler for "clicked" signal of button
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    // Add the button to the window
    gtk_container_add(GTK_CONTAINER(window), button);

    // Display the window
    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    // Create new GtkApplication with a unique application ID
    app = gtk_application_new("org.gtk.hello", G_APPLICATION_FLAGS_NONE);

    // Connect the event handler for "activate" signal of GApplication
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Start the application, terminate by closing the window
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // Deallocate the application object
    g_object_unref(app);

    return status;
}
