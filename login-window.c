#include <gtk/gtk.h>

//
// ACCOUNT WINDOW
// 

int account_window(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *button;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Account");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    FILE *fp = fopen("name.txt", "r");
    char name[256];
    fgets(name, sizeof(name), fp);
    fclose(fp);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), name);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
    
    void close_window(GtkWidget *widget, gpointer data) {
          gtk_widget_destroy(GTK_WIDGET(data));
            gtk_main_quit();       
    }
    button = gtk_button_new_with_label("Exit");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 1, 1);
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
    g_signal_connect(button, "clicked", G_CALLBACK(close_window), window);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

//
// LOGIN WINDOW
//

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry_name;
    GtkWidget *entry_pswd;
    GtkWidget *button;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Login</b>");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
    
    entry_name = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_name, 0, 1, 1, 1);
    gtk_entry_set_text(GTK_ENTRY(entry_name), "username");
    //gtk_entry_set_max_length(GTK_ENTRY(entry_name), 12);
    gtk_widget_set_halign(entry_name, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(entry_name, GTK_ALIGN_CENTER);

    entry_pswd = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_pswd, 0, 2, 1, 1);
    gtk_entry_set_text(GTK_ENTRY(entry_pswd), "password");
    gtk_widget_set_halign(entry_pswd, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(entry_pswd, GTK_ALIGN_CENTER);

    struct LoginData {
        GtkWidget *entry_name;
        GtkWidget *entry_pswd;
    };
    void store_login(GtkWidget *button, gpointer data) {
        struct LoginData *login_data = (struct LoginData *) data;
        //GtkWidget *entry_name = (GtkWidget *)data;
        //GtkWidget *entry_pswd = (GtkWidget *)data;
        const gchar *name = gtk_entry_get_text(GTK_ENTRY(login_data->entry_name));
        //const char *username = gtk_entry_get_text(GTK_ENTRY(entry_name));
        const gchar *pswd = gtk_entry_get_text(GTK_ENTRY(login_data->entry_pswd));
        //const char *password = gtk_entry_get_text(GTK_ENTRY(entry_pswd));
        FILE *fp = fopen("name.txt", "w");
        fprintf(fp, "%s\n", name);
        fclose(fp);
        fp = fopen("pswd.txt", "w");
        fprintf(fp, "%s\n", pswd);
        fclose(fp);
    }
    void close_window(GtkWidget *widget, gpointer data) {
        gtk_widget_destroy(GTK_WIDGET(data));
        gtk_main_quit();
        account_window(argc, argv);
    }
    button = gtk_button_new_with_label("Login");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 1, 1);
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
    struct LoginData login_data;
    login_data.entry_name = entry_name;
    login_data.entry_pswd = entry_pswd;
    g_signal_connect(button, "clicked", G_CALLBACK(store_login), &login_data);
    g_signal_connect(button, "clicked", G_CALLBACK(close_window), window);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
