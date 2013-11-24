#include <gtk/gtk.h>
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    
    g_print ("delete event occurred\n");

    
    return TRUE;
}


static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

static gint
my_popup_handler (GtkWidget *widget, GdkEvent *event)
{
  GtkMenu *menu;
  GdkEventButton *event_button;
  g_return_val_if_fail (widget != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_MENU (widget), FALSE);
  g_return_val_if_fail (event != NULL, FALSE);
  /* The "widget" is the menu that was supplied when
   * g_signal_connect_swapped() was called.
   */
  menu = GTK_MENU (widget);
  if (event->type == GDK_BUTTON_PRESS)
    {
      event_button = (GdkEventButton *) event;
      if (event_button->button == 1)
    {
	gtk_widget_show_all(GTK_WIDGET(menu));
      gtk_menu_popup (menu, NULL, NULL, NULL, NULL,
              event_button->button, event_button->time);
      return TRUE;
    }
    }
  return FALSE;
}




void save_file (gpointer user_data)
{
    gchar filename[] = "testfile1.txt";
    gchar *contents;
    GtkTextIter *start, *end;

    
    gtk_text_buffer_get_bounds (gtk_text_view_get_buffer(GTK_TEXT_VIEW (user_data)), start, end);
    contents = gtk_text_buffer_get_text (gtk_text_view_get_buffer(GTK_TEXT_VIEW (user_data)), start, end, TRUE);
    g_file_set_contents (filename, contents, -1, NULL);
    g_free(contents);
}

int main( int   argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *text;
    GtkWidget *menu;
    GtkWidget *menuitem;
    GtkWidget *menuitem1;
    GtkWidget *menuitem2;




    GdkColor color1;
    GtkAccelGroup *accel_group;
    
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    
    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);
    
    gtk_widget_set_size_request((window),600,400);
    gtk_window_set_title(GTK_WINDOW(window),"Editor");
    gtk_window_fullscreen(GTK_WINDOW(window));
    gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);
   
    
    text=gtk_text_view_new();
   // gtk_text_view_set_indent(GtkTextView *text_view,gint indent);
 
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text),260);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text),260);
    
   
    gdk_color_parse("black",&color1);
    gtk_widget_modify_base(text,GTK_STATE_NORMAL,&color1);

    gdk_color_parse("green",&color1);
    gtk_widget_modify_text(text,GTK_STATE_NORMAL,&color1);

    
  
    menu=gtk_menu_new();
                              
    menuitem=gtk_menu_item_new_with_label ("Quit");
    menuitem1=gtk_menu_item_new_with_label ("Save");


    gtk_menu_attach(GTK_MENU(menu),menuitem1,1,2,2,3);                                              
    gtk_menu_attach(GTK_MENU(menu),menuitem,1,2,1,2);
    gtk_container_add(GTK_CONTAINER(window),text);
    //gtk_container_add(GTK_CONTAINER(window),menu);
   g_signal_connect_swapped (text, "button_press_event",
    G_CALLBACK (my_popup_handler), menu);   
 gtk_widget_show_all(GTK_WIDGET(window));
 //    gtk_widget_show_all((menu));
   // gtk_menu_popup(GTK_MENU(menu),NULL,NULL,NULL,NULL,1,gtk_get_current_event_time());
g_signal_connect(menuitem,"button_press_event",G_CALLBACK(destroy),NULL);
g_signal_connect(menuitem1,"button_press_event",G_CALLBACK(save_file),text);    
gtk_main();

    return 0;
}
