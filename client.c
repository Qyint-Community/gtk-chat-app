#include <gtk/gtk.h>

//
// CLIENT WINDOW
// 

int client_window(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *text_view;
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *entry_message;
    GtkWidget *button_send;
    GtkWidget *button_refresh;
    GtkWidget *button_exit;
    GtkWidget *button_server_switch;
    GtkTextBuffer *buffer;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chat Client");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    FILE *fp = fopen("name.txt", "r");
    char name[256];
    fgets(name, sizeof(name), fp);
    fclose(fp);

    label = gtk_label_new(NULL);
    gchar *loggedinas = g_strdup_printf("Logged in as: %s", name);
    gtk_label_set_markup(GTK_LABEL(label), loggedinas);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_START);
    gtk_widget_set_margin_top(label, 10);

    text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_view), buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    //gtk_grid_attach(GTK_GRID(grid), text_view, 0, 1, 1, 1);
    gtk_widget_set_halign(text_view, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(text_view, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(text_view, 500, -1);
    FILE *fp2 = fopen("server.txt", "r");
    GtkTextBuffer *text_buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_view), text_buffer);
    char line[256];
    while (fgets(line, sizeof(line), fp2)) {
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter(text_buffer, &iter);
        gtk_text_buffer_insert(text_buffer, &iter, line, -1);
    }
    fclose(fp2);
    gtk_text_buffer_set_text(buffer, line, -1);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 1, 1, 1);
    gtk_widget_set_size_request(scrolled_window, 500, 150);

    entry_message = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_message, 0, 2, 1, 1);
    gtk_entry_set_text(GTK_ENTRY(entry_message), "message...");
    //gtk_entry_set_max_length(GTK_ENTRY(entry_message), 12);
    //gtk_widget_set_halign(entry_message, GTK_ALIGN_START);
    gtk_widget_set_halign(entry_message, GTK_ALIGN_CENTER);
    //gtk_widget_set_margin_start(entry_message, 50);
    gtk_widget_set_margin_end(entry_message, 50);
    gtk_widget_set_valign(entry_message, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(entry_message, 400, -1);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 0);
    
    void send_message(GtkWidget *widget, gpointer data) {
        FILE *file = fopen("server.txt", "a");
        const char *text = gtk_entry_get_text(GTK_ENTRY(entry_message));
        gchar *fullmessage = g_strdup_printf("%s » %s", name, text);
        fprintf(file, "%s\n", fullmessage);
        fclose(file);
    }
    void refresh_text_view() {
        GtkTextBuffer *new_buffer = gtk_text_buffer_new(NULL);
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_view), new_buffer);
        FILE *fp2 = fopen("server.txt", "r");
        char line[256];
        while (fgets(line, sizeof(line), fp2)) {
            GtkTextIter iter;
            gtk_text_buffer_get_end_iter(new_buffer, &iter);
            gtk_text_buffer_insert(new_buffer, &iter, line, -1);
        }
        fclose(fp2);
    }
    button_send = gtk_button_new_with_label("➤");
    gtk_grid_attach(GTK_GRID(grid), button_send, 0, 2, 1, 1);
    gtk_widget_set_halign(button_send, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(button_send, 400);
    gtk_widget_set_valign(button_send, GTK_ALIGN_CENTER);
    g_signal_connect(button_send, "clicked", G_CALLBACK(send_message), NULL);
    g_signal_connect(button_send, "clicked", G_CALLBACK(refresh_text_view), NULL);

    void close_window(GtkWidget *widget, gpointer data) {
        gtk_widget_destroy(GTK_WIDGET(data));
        gtk_main_quit();       
    }
    button_refresh = gtk_button_new_with_label("🗘");
    gtk_grid_attach(GTK_GRID(grid), button_refresh, 0, 3, 1, 1);
    gtk_widget_set_halign(button_refresh, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_end(button_refresh, 200);
    gtk_widget_set_valign(button_refresh, GTK_ALIGN_CENTER);
    g_signal_connect(button_refresh, "clicked", G_CALLBACK(refresh_text_view), NULL);
    
    button_server_switch = gtk_button_new_with_label("Switch Servers");
    gtk_grid_attach(GTK_GRID(grid), button_server_switch, 0, 3, 1, 1);
    gtk_widget_set_halign(button_server_switch, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button_server_switch, GTK_ALIGN_CENTER);
    g_signal_connect(button_server_switch, "clicked", G_CALLBACK(refresh_text_view), NULL);

    button_exit = gtk_button_new_with_label("X");
    gtk_grid_attach(GTK_GRID(grid), button_exit, 0, 3, 1, 1);
    gtk_widget_set_halign(button_exit, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(button_exit, 200);
    gtk_widget_set_valign(button_exit, GTK_ALIGN_CENTER);
    g_signal_connect(button_exit, "clicked", G_CALLBACK(close_window), NULL);

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
        fprintf(fp, "%s", name);
        fclose(fp);
        fp = fopen("pswd.txt", "w");
        fprintf(fp, "%s", pswd);
        fclose(fp);
    }
    void close_window(GtkWidget *widget, gpointer data) {
        gtk_widget_destroy(GTK_WIDGET(data));
        gtk_main_quit();
        client_window(argc, argv);
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
