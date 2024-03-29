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
    g_object_ref(G_OBJECT(widget)), (GDestroyNotify) g_object_unref)

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
  GtkWidget *edit_button;
  GtkWidget *scrolledwindow;
  GtkWidget *command_treeview;
  GtkWidget *dialog_action_area;
  GtkWidget *save_button;

  shellexec_conf_dialog = gtk_dialog_new ();
  gtk_container_set_border_width (GTK_CONTAINER (shellexec_conf_dialog), 12);
  gtk_window_set_title (GTK_WINDOW (shellexec_conf_dialog), _("Custom Shell Commands"));
  gtk_window_set_type_hint (GTK_WINDOW (shellexec_conf_dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_dialog_set_has_separator (GTK_DIALOG (shellexec_conf_dialog), FALSE);

  dialog_vbox = gtk_dialog_get_content_area (GTK_DIALOG (shellexec_conf_dialog));
  gtk_widget_show (dialog_vbox);
  gtk_box_set_spacing(GTK_BOX(dialog_vbox), 8);

  hbox1 = gtk_hbox_new (FALSE, 8);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox), hbox1, FALSE, TRUE, 0);

  add_button = gtk_button_new_with_mnemonic (_("Add"));
  gtk_widget_show (add_button);
  gtk_box_pack_start (GTK_BOX (hbox1), add_button, TRUE, TRUE, 0);

  remove_button = gtk_button_new_with_mnemonic (_("Remove"));
  gtk_widget_show (remove_button);
  gtk_box_pack_start (GTK_BOX (hbox1), remove_button, TRUE, TRUE, 0);

  edit_button = gtk_button_new_with_mnemonic (_("Edit"));
  gtk_widget_show (edit_button);
  gtk_box_pack_start (GTK_BOX (hbox1), edit_button, TRUE, TRUE, 0);

  scrolledwindow = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow);
  gtk_box_pack_end (GTK_BOX (dialog_vbox), scrolledwindow, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow), GTK_SHADOW_IN);

  command_treeview = gtk_tree_view_new ();
  gtk_widget_show (command_treeview);
  gtk_container_add (GTK_CONTAINER (scrolledwindow), command_treeview);
  gtk_widget_set_size_request (command_treeview, 300, 200);

  dialog_action_area = gtk_dialog_get_action_area (GTK_DIALOG (shellexec_conf_dialog));
  gtk_widget_show (dialog_action_area);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area), GTK_BUTTONBOX_END);

  save_button = gtk_button_new_with_mnemonic (_("Close"));
  gtk_widget_show (save_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (shellexec_conf_dialog), save_button, 0);
  gtk_widget_set_can_default(save_button, TRUE);

  g_signal_connect ((gpointer) add_button, "clicked",
                    G_CALLBACK (on_add_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) remove_button, "clicked",
                    G_CALLBACK (on_remove_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) edit_button, "clicked",
                    G_CALLBACK (on_edit_button_clicked),
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
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, edit_button, "edit_button");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, scrolledwindow, "scrolledwindow");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, command_treeview, "command_treeview");
  GLADE_HOOKUP_OBJECT_NO_REF (shellexec_conf_dialog, dialog_action_area, "dialog_action_area");
  GLADE_HOOKUP_OBJECT (shellexec_conf_dialog, save_button, "save_button");

  return shellexec_conf_dialog;
}

GtkWidget*
create_shellexec_conf_edit_dialog (void)
{
  GtkWidget *shellexec_conf_edit_dialog;
  GtkWidget *dialog_vbox1;
  GtkWidget *table1;
  GtkWidget *title_label;
  GtkWidget *cmd_label;
  GtkWidget *name_entry;
  GtkWidget *cmd_entry;
  GtkWidget *name_label;
  GtkWidget *title_entry;
  GtkWidget *single_check;
  GtkWidget *multiple_check;
  GtkWidget *local_check;
  GtkWidget *remote_check;
  GtkWidget *playlist_check;
  GtkWidget *disabled_check;
  GtkWidget *dialog_action_area1;
  GtkWidget *edit_cancel_button;
  GtkWidget *edit_ok_button;

  shellexec_conf_edit_dialog = gtk_dialog_new ();
  gtk_container_set_border_width (GTK_CONTAINER (shellexec_conf_edit_dialog), 12);
  gtk_window_set_title (GTK_WINDOW (shellexec_conf_edit_dialog), _("Edit Command"));
  gtk_window_set_modal (GTK_WINDOW (shellexec_conf_edit_dialog), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (shellexec_conf_edit_dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_dialog_set_has_separator (GTK_DIALOG (shellexec_conf_edit_dialog), FALSE);

  dialog_vbox1 = gtk_dialog_get_content_area (GTK_DIALOG (shellexec_conf_edit_dialog));
  gtk_widget_show (dialog_vbox1);
  gtk_box_set_spacing(GTK_BOX(dialog_vbox1), 8);

  table1 = gtk_table_new (3, 2, FALSE);
  gtk_widget_show (table1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), table1, FALSE, TRUE, 0);
  gtk_table_set_row_spacings (GTK_TABLE (table1), 8);
  gtk_table_set_col_spacings (GTK_TABLE (table1), 8);

  title_label = gtk_label_new (_("Title:"));
  gtk_widget_show (title_label);
  gtk_table_attach (GTK_TABLE (table1), title_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (title_label), 0, 0.5);

  cmd_label = gtk_label_new (_("Shell Command:"));
  gtk_widget_show (cmd_label);
  gtk_table_attach (GTK_TABLE (table1), cmd_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (cmd_label), 0, 0.5);

  name_entry = gtk_entry_new ();
  gtk_widget_show (name_entry);
  gtk_table_attach (GTK_TABLE (table1), name_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (name_entry), 8226);

  cmd_entry = gtk_entry_new ();
  gtk_widget_show (cmd_entry);
  gtk_table_attach (GTK_TABLE (table1), cmd_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (cmd_entry), 8226);

  name_label = gtk_label_new (_("Name:"));
  gtk_widget_show (name_label);
  gtk_table_attach (GTK_TABLE (table1), name_label, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (name_label), 0, 0.5);

  title_entry = gtk_entry_new ();
  gtk_widget_show (title_entry);
  gtk_table_attach (GTK_TABLE (table1), title_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_entry_set_invisible_char (GTK_ENTRY (title_entry), 8226);

  single_check = gtk_check_button_new_with_mnemonic (_("Single Tracks"));
  gtk_widget_show (single_check);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), single_check, FALSE, FALSE, 0);

  multiple_check = gtk_check_button_new_with_mnemonic (_("Multiple Tracks"));
  gtk_widget_show (multiple_check);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), multiple_check, FALSE, FALSE, 0);

  local_check = gtk_check_button_new_with_mnemonic (_("Local"));
  gtk_widget_show (local_check);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), local_check, FALSE, FALSE, 0);

  remote_check = gtk_check_button_new_with_mnemonic (_("Remote"));
  gtk_widget_show (remote_check);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), remote_check, FALSE, FALSE, 0);

  playlist_check = gtk_check_button_new_with_mnemonic (_("Playlist"));
  gtk_widget_show (playlist_check);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), playlist_check, FALSE, FALSE, 0);

  disabled_check = gtk_check_button_new_with_mnemonic (_("Disabled"));
  gtk_widget_show (disabled_check);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), disabled_check, FALSE, FALSE, 0);

  dialog_action_area1 = gtk_dialog_get_action_area (GTK_DIALOG (shellexec_conf_edit_dialog));
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

  edit_cancel_button = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (edit_cancel_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (shellexec_conf_edit_dialog), edit_cancel_button, GTK_RESPONSE_CANCEL);
  gtk_widget_set_can_default(edit_cancel_button, TRUE);

  edit_ok_button = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (edit_ok_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (shellexec_conf_edit_dialog), edit_ok_button, GTK_RESPONSE_OK);
  gtk_widget_set_can_default(edit_ok_button, TRUE);

  g_signal_connect ((gpointer) edit_cancel_button, "clicked",
                    G_CALLBACK (on_edit_cancel_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) edit_ok_button, "clicked",
                    G_CALLBACK (on_edit_ok_button_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (shellexec_conf_edit_dialog, shellexec_conf_edit_dialog, "shellexec_conf_edit_dialog");
  GLADE_HOOKUP_OBJECT_NO_REF (shellexec_conf_edit_dialog, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, table1, "table1");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, title_label, "title_label");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, cmd_label, "cmd_label");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, name_entry, "name_entry");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, cmd_entry, "cmd_entry");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, name_label, "name_label");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, title_entry, "title_entry");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, single_check, "single_check");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, multiple_check, "multiple_check");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, local_check, "local_check");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, remote_check, "remote_check");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, playlist_check, "playlist_check");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, disabled_check, "disabled_check");
  GLADE_HOOKUP_OBJECT_NO_REF (shellexec_conf_edit_dialog, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, edit_cancel_button, "edit_cancel_button");
  GLADE_HOOKUP_OBJECT (shellexec_conf_edit_dialog, edit_ok_button, "edit_ok_button");

  return shellexec_conf_edit_dialog;
}

