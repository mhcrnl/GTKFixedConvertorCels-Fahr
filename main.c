#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <glib.h>

#define max 30

const char *title = "Convertor Celsius to Fahrenheit";
const char *authors[] = {"Mihai Cornel", NULL};
const char *license = "GPLv3";

GtkWidget *en_fahr = NULL;
const gchar *en_celsius_text = NULL;
/*
*   FUNCTIONS:
*/
static void my_func(GtkWidget* widget, GtkWidget *entry);
static void helloWorld(GtkWidget *wid, GtkWidget *win);
static void about_show(void);

static void my_func(GtkWidget *widget, GtkWidget *entry)
{
    g_print("en_celsius_text = %s\n", gtk_entry_get_text(GTK_ENTRY(entry)));
    float celsius = atof(gtk_entry_get_text(GTK_ENTRY(entry)));
    float fahrenheit =(celsius * 9/5) +32;

    gchar sfahr[max];
    g_sprintf(sfahr, "%.2f", fahrenheit);
    gtk_entry_set_text(GTK_ENTRY(en_fahr), sfahr);
}

static void helloWorld (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

static void about_show(void)
{
	GtkWidget * about_dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about_dialog), license);
	gtk_dialog_run(GTK_DIALOG(about_dialog));
	gtk_widget_destroy(about_dialog);
}

float celsius(float cels)
{
    float fahr;
    fahr = (cels * 9/5) + 32;
    return fahr;
}

int main (int argc, char *argv[])
{
  /* BUTTONS */
  GtkWidget *bt_close = NULL;
  GtkWidget *bt_info = NULL;
  GtkWidget *bt_calc = NULL;
  /* LABELS */
  GtkWidget *lb_celsius = NULL;
  GtkWidget *lb_fahr = NULL;
  /* ENTRY */
  GtkWidget *en_celsius = NULL;
  //GtkWidget *en_fahr = NULL;

  GtkWidget *win = NULL;
  GtkWidget *vbox;
  GtkWidget *fixed = NULL;

  GtkWidget *menubar;
  GtkWidget *file;
  GtkWidget *file_menu;
  GtkWidget *file_quit;

  GtkWidget *help_menu;
  GtkWidget *help_about;
  GtkWidget *help_item;

  //setlocale(LC_ALL, "");
  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), title);
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 200);
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  vbox = gtk_vbox_new(FALSE,0);
  gtk_container_add(GTK_CONTAINER(win), vbox);



  menubar = gtk_menu_bar_new();
  file_menu = gtk_menu_new();
  help_menu = gtk_menu_new();


  file = gtk_menu_item_new_with_label("File");
  file_quit = gtk_menu_item_new_with_label("Quit");

  help_item = gtk_menu_item_new_with_label("Help");
  help_about = gtk_menu_item_new_with_label("About");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), file_menu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);

  gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_quit);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

  gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_about);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_item);

  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
  /* Create a vertical box with buttons */
  fixed = gtk_fixed_new ();
  gtk_container_add (GTK_CONTAINER (vbox), fixed);

  lb_celsius = gtk_label_new("CELSIUS");
  gtk_fixed_put(GTK_FIXED(fixed),lb_celsius, 10, 10);
  gtk_widget_set_size_request(lb_celsius, 80, 30);

  lb_fahr = gtk_label_new("FAHRENHEIT");
  gtk_fixed_put(GTK_FIXED(fixed),lb_fahr, 10, 40);
  gtk_widget_set_size_request(lb_fahr, 90, 30);

  en_celsius = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),en_celsius, 100, 10);
  gtk_widget_set_size_request(en_celsius, 90, 30);

  en_fahr = gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),en_fahr, 100, 40);
  gtk_widget_set_size_request(en_fahr, 90, 30);

  bt_info = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
  g_signal_connect (G_OBJECT (bt_info), "clicked", G_CALLBACK (helloWorld), (gpointer) win);
  //gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
  gtk_fixed_put(GTK_FIXED(fixed),bt_info, 200, 10);
  gtk_widget_set_size_request(bt_info, 90, 30);

  bt_close = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (bt_close, "clicked", gtk_main_quit, NULL);
  //gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
  gtk_fixed_put(GTK_FIXED(fixed),bt_close, 300 ,150);
  gtk_widget_set_size_request(bt_close, 90, 30);

  bt_calc = gtk_button_new_with_label("CALCULATE");
  g_signal_connect(G_OBJECT(bt_calc), "clicked", G_CALLBACK(my_func), en_celsius);
  gtk_fixed_put(GTK_FIXED(fixed),bt_calc, 200 ,40);
  gtk_widget_set_size_request(bt_calc, 90, 30);

  g_signal_connect_swapped(G_OBJECT(help_about), "activate", G_CALLBACK(about_show), NULL);
  g_signal_connect_swapped(G_OBJECT(file_quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
