/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_shellexec_conf_dialog (void)
{
  GtkWidget *shellexec_conf_dialog;
  GtkWidget *dialog_vbox;
  GtkWidget *hbox1;
  GtkWidget *add_button;
  GtkWidget *remove_button;
  GtkWidget *scrolledwindow;
  GtkWidget *command_treeview;
  GtkWidget *dialog_action_area;
  GtkWidget *cancel_button;
  GtkWidget *save_button;

  shellexec_conf_dialog = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (shellexec_conf_dialog), _("Shellexec Commands"));
  gtk_window_set_position (GTK_WINDOW (shellexec_conf_dialog), GTK_WIN_POS_CENTER);
  gtk_window_set_type_hint (GTK_WINDOW (shellexec_conf_dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_dialog_set_has_separator (GTK_DIALOG (shellexec_conf_dialog), FALSE);

  dialog_vbox = GTK_DIALOG (shellexec_conf_dialog)->vbox;
  gtk_widget_show (dialog_vbox);

  hbox1 = gtk_hbox_new (FALSE, 7);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox), hbox1, FALSE, TRUE, 0);

  add_button = gtk_button_new_with_mnemonic (_("+"));
  gtk_widget_show (add_button);
  gtk_box_pack_start (GTK_BOX (hbox1), add_button, FALSE, FALSE, 0);
  gtk_widget_set_size_request (add_button, 30, -1);

  remove_button = gtk_button_new_with_mnemonic (_("-"));
  gtk_widget_show (remove_button);
  gtk_box_pack_start (GTK_BOX (hbox1), remove_button, FALSE, FALSE, 0);
  gtk_widget_set_size_request (remove_button, 30, -1);

  scrolledwindow = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow);
  gtk_box_pack_start (GTK_BOX (dialog_vbox), scrolledwindow, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow), GTK_SHADOW_IN);

  command_treeview = gtk_tree_view_new ();
  gtk_widget_show (command_treeview);
  gtk_container_add (GTK_CONTAINER (scrolledwindow), command_treeview);
  gtk_widget_set_size_request (command_treeview, 480, 182);

  dialog_action_area = GTK_DIALOG (shellexec_conf_dialog)->action_area;
  gtk_widget_show (dialog_action_area);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

  cancel_button = gtk_button_new_with_mnemonic (_("Cancel"));
  gtk_widget_show (cancel_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (shellexec_conf_dialog), cancel_button, 0);
  GTK_WIDGET_SET_FLAGS (cancel_button, GTK_CAN_DEFAULT);

  save_button = gtk_button_new_with_mnemonic (_("Save"));
  gtk_widget_show (save_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (shellexec_conf_dialog), save_button, 0);
  GTK_WIDGET_SET_FLAGS (save_button, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) add_button, "clicked",
                    G_CALLBACK (on_add_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) remove_button, "clicked",
                    G_CALLBACK (on_remove_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) cancel_button, "clicked",
                    G_CALLBACK (on_cancel_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) save_button, "clicked",
                    G_CALLBACK (on_save_button_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (shellexec_conf_dialog, shellexec_conf_dialog, "shellexec_conf_dialog");
  GLADE_HOOKUP_OBJECT_NO_REF (shellexec_conf_dialog, dialog_vbox, "dialog_vbox");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, add_button, "add_button");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, remove_button, "remove_button");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, scrolledwindow, "scrolledwindow");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, command_treeview, "command_treeview");
  GLADE_HOOKUP_OBJECT_NO_REF (shellexec_conf_dialog, dialog_action_area, "dialog_action_area");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, cancel_button, "cancel_button");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, save_button, "save_button");

  return shellexec_conf_dialog;
}
