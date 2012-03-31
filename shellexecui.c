#include <stdlib.h>
#include <string.h>
#include <deadbeef/deadbeef.h>
#include <gtk/gtk.h>
#include <deadbeef/gtkui_api.h>
#include <glib/gprintf.h>
#include "interface.h"
#include "callbacks.h"
#include "support.h"
#include "shellexec.h"

#define trace(...) { fprintf(stderr, __VA_ARGS__); }

DB_functions_t *deadbeef;
static DB_misc_t plugin;
static ddb_gtkui_t *gtkui_plugin;
static Shx_plugin_t *shellexec_plugin;
static GtkWidget *conf_dlg;
static Shx_action_t *actions;

enum {
    COL_NAME = 0,
    COL_TITLE,
    COL_SHCMD,
    COL_SINGLE,
    COL_MULTIPLE,
    COL_LOCAL,
    COL_REMOTE,
    COL_DISABLED,
    COL_PLAYLIST,
    COL_META,
    COL_COUNT,
};

static int
name_exists(const char *name, Shx_action_t *skip) {
    Shx_action_t *action = actions;
    while(action) {
        if(action != skip && strcmp(action->parent.name, name) == 0) {
            return 1;
        }
        action = (Shx_action_t*)action->parent.next;
    }
    return 0;
}

static int
is_empty(char *name) {
    char *p = name;
    while(*p) {
        if(*p != ' ' || *p != '\t') {
            return 0;
        }
        p++;
    }
    return 1;
}

static void
disable_save_button() {
    GtkWidget *save_button = lookup_widget(conf_dlg, "save_button");
    gtk_widget_set_sensitive(save_button, FALSE);
}

static void
enable_save_button() {
    GtkWidget *save_button = lookup_widget(conf_dlg, "save_button");
    gtk_widget_set_sensitive(save_button, TRUE);  
}

void
on_save_button_clicked (GtkButton *button,
                          gpointer user_data) {
    shellexec_plugin->shx_save_actions(actions);
    disable_save_button();
}

void
on_add_button_clicked (GtkButton *button,
                          gpointer user_data) {
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(conf_dlg, "command_treeview"));
    GtkListStore *liststore = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    GtkTreeIter iter;

    Shx_action_t *action = calloc(sizeof(Shx_action_t), 1);
    if(!actions) {
        actions = action;
    }
    else {
        Shx_action_t *last = actions;
        while(last->parent.next) {
            last = (Shx_action_t*)last->parent.next;
        }
        last->parent.next = (DB_plugin_action_t*)action;
    }

    char name[15] = "shxcmd";
    int suffix = 0;
    while(name_exists(name, action)) {
        snprintf(name, 15, "shxcmd%d", suffix);
        suffix++;
    }

    action->parent.name = strdup(name);
    action->parent.title = strdup("Shell Command");
    action->shcommand = strdup("xdg-open \"http://deadbeef.sourceforge.net/\"");
    action->shx_flags |= SHX_ACTION_LOCAL_ONLY;
    action->parent.flags |= DB_ACTION_SINGLE_TRACK;
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(liststore, &iter, COL_NAME, name,
                                         COL_META, action,
                                         COL_SHCMD, action->shcommand,
                                         COL_TITLE, action->parent.title,
                                         COL_SINGLE, TRUE,
                                         COL_LOCAL, TRUE, -1);
    enable_save_button();
}

void
on_remove_button_clicked (GtkButton *button,
                          gpointer user_data) {
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(conf_dlg, "command_treeview"));
    GtkTreeModel *treemodel = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    GtkTreeSelection *selection;
    selection = gtk_tree_view_get_selection(treeview);
    if(gtk_tree_selection_get_selected(selection, &treemodel, &iter)) {
        Shx_action_t *action;
        gtk_tree_model_get(treemodel, &iter, COL_META, &action, -1);
        if(actions == action) {
            actions = (Shx_action_t*)action->parent.next;
        }
        else {
            Shx_action_t *prev = actions;
            while(((Shx_action_t*)prev->parent.next) != action) {
                prev = (Shx_action_t*)prev->parent.next;
            }
            prev->parent.next = action->parent.next;
        }
        free((void *)action->shcommand);
        free((void *)action->parent.name);
        free((void *)action->parent.title);
        free(action);
        gtk_list_store_remove(GTK_LIST_STORE(treemodel), &iter);
    }
    enable_save_button();
}

void
on_cancel_button_clicked (GtkButton *button,
                          gpointer user_data) {
    gtk_widget_destroy(conf_dlg);
}

void
on_cell_edited(GtkCellRendererText *cell, gchar *path_string,
               gchar *new_text, gpointer user_data) {
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(conf_dlg, "command_treeview"));
    GtkTreeModel *treemodel = gtk_tree_view_get_model(treeview);
    guint column = GPOINTER_TO_UINT(user_data);

    GtkTreeIter iter;
    gtk_tree_model_get_iter_from_string(treemodel, &iter, path_string);

    Shx_action_t *action;
    gtk_tree_model_get(treemodel, &iter, COL_META, &action, -1);
    switch(column) {
        case COL_NAME:  {
                            size_t len = strlen(new_text)+10;
                            int suffix = 0;
                            gchar *temp = g_strndup(new_text, len);
                            while(name_exists(temp, action)) {
                                g_snprintf(temp, len, "%s%d", new_text, suffix);
                                suffix++;
                            }
                            g_free((void*)action->parent.name);
                            action->parent.name = g_strdup(temp);
                            gtk_list_store_set(GTK_LIST_STORE(treemodel), &iter, column, temp, -1);
                            g_free(temp);
                            break;
                        }
        case COL_TITLE: if(!is_empty(new_text)) {
                            free((void*)action->parent.title);
                            action->parent.title = strdup(new_text);
                            gtk_list_store_set(GTK_LIST_STORE(treemodel), &iter, column, new_text, -1);
                        }
                        break;
        case COL_SHCMD: if(!is_empty(new_text)) {
                            free((void*)action->shcommand);
                            action->shcommand = strdup(new_text);
                            gtk_list_store_set(GTK_LIST_STORE(treemodel), &iter, column, new_text, -1);
                        }
                        break;
    }
    enable_save_button();
}

void
on_cell_toggled(GtkCellRendererToggle *cell, gchar *path_string,
                gpointer user_data) {
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(conf_dlg, "command_treeview"));
    GtkTreeModel *treemodel = gtk_tree_view_get_model(treeview);
    guint column = GPOINTER_TO_UINT(user_data);

    GtkTreeIter iter;
    gtk_tree_model_get_iter_from_string(treemodel, &iter, path_string);

    gboolean value;
    Shx_action_t *action;
    gtk_tree_model_get(treemodel, &iter, column, &value, -1);
    gtk_tree_model_get(treemodel, &iter, COL_META, &action, -1);

    switch(column) {
        case COL_LOCAL:    action->shx_flags ^= SHX_ACTION_LOCAL_ONLY;
                           break;
        case COL_REMOTE:   action->shx_flags ^= SHX_ACTION_REMOTE_ONLY;
                           break;
        case COL_DISABLED: action->parent.flags ^= DB_ACTION_DISABLED;
                           break;
        case COL_PLAYLIST: action->parent.flags ^= DB_ACTION_PLAYLIST;
                           break;
        case COL_SINGLE:   action->parent.flags ^= DB_ACTION_SINGLE_TRACK;
                           break;
        case COL_MULTIPLE: action->parent.flags ^= DB_ACTION_ALLOW_MULTIPLE_TRACKS;
                           break;
    }
    gtk_list_store_set(GTK_LIST_STORE(treemodel), &iter, column, !value, -1);
    enable_save_button();
}

static GtkTreeModel *
init_treemodel() {
    GtkListStore *liststore;
    GtkTreeIter iter;

    liststore = gtk_list_store_new(COL_COUNT, 
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN,
                                   G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_POINTER);

    actions = shellexec_plugin->shx_get_actions(NULL, FALSE);
    Shx_action_t *action = actions;
    while(action) {
        gtk_list_store_append(liststore, &iter);
        gtk_list_store_set(liststore, &iter,
                           COL_NAME,     action->parent.name,
                           COL_TITLE,    action->parent.title,
                           COL_SHCMD,    action->shcommand,
                           COL_SINGLE,   action->parent.flags & DB_ACTION_SINGLE_TRACK,
                           COL_MULTIPLE, action->parent.flags & DB_ACTION_ALLOW_MULTIPLE_TRACKS,
                           COL_LOCAL,    action->shx_flags & SHX_ACTION_LOCAL_ONLY,
                           COL_REMOTE,   action->shx_flags & SHX_ACTION_REMOTE_ONLY,
                           COL_DISABLED, action->parent.flags & DB_ACTION_DISABLED,
                           COL_PLAYLIST, action->parent.flags & DB_ACTION_PLAYLIST,
                           COL_META,     action, -1);
        action = (Shx_action_t *)action->parent.next;
    }
    return GTK_TREE_MODEL(liststore);
}

static void
init_treeview() {
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(conf_dlg, "command_treeview"));
    GtkTreeModel *treemodel;
    GtkCellRenderer *cell_renderer;

    cell_renderer = gtk_cell_renderer_text_new();
    g_object_set(cell_renderer, "editable", TRUE, NULL);
    g_signal_connect(cell_renderer, "edited", G_CALLBACK(on_cell_edited),
                     GUINT_TO_POINTER(COL_NAME));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Name", cell_renderer,
                                                "text", COL_NAME, NULL);


    cell_renderer = gtk_cell_renderer_text_new();
    g_object_set(cell_renderer, "editable", TRUE, NULL);
    g_signal_connect(cell_renderer, "edited", G_CALLBACK(on_cell_edited),
                     GUINT_TO_POINTER(COL_TITLE));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Title", cell_renderer,
                                                "text", COL_TITLE, NULL);

    cell_renderer = gtk_cell_renderer_text_new();
    g_object_set(cell_renderer, "editable", TRUE, NULL);
    g_signal_connect(cell_renderer, "edited", G_CALLBACK(on_cell_edited),
                     GUINT_TO_POINTER(COL_SHCMD));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Shell Command", cell_renderer,
                                                "text", COL_SHCMD, NULL);

    cell_renderer = gtk_cell_renderer_toggle_new();
    g_object_set(cell_renderer, "activatable", TRUE, NULL);
    g_signal_connect(cell_renderer, "toggled", G_CALLBACK(on_cell_toggled),
                     GUINT_TO_POINTER(COL_SINGLE));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Single", cell_renderer,
                                                "active", COL_SINGLE, NULL);

    cell_renderer = gtk_cell_renderer_toggle_new();
    g_object_set(cell_renderer, "activatable", TRUE, NULL);
    g_signal_connect(cell_renderer, "toggled", G_CALLBACK(on_cell_toggled),
                     GUINT_TO_POINTER(COL_MULTIPLE));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Multiple", cell_renderer,
                                                "active", COL_MULTIPLE, NULL);


    cell_renderer = gtk_cell_renderer_toggle_new();
    g_object_set(cell_renderer, "activatable", TRUE, NULL);
    g_signal_connect(cell_renderer, "toggled", G_CALLBACK(on_cell_toggled),
                     GUINT_TO_POINTER(COL_LOCAL));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Local", cell_renderer,
                                                "active", COL_LOCAL, NULL);

    cell_renderer = gtk_cell_renderer_toggle_new();
    g_object_set(cell_renderer, "activatable", TRUE, NULL);
    g_signal_connect(cell_renderer, "toggled", G_CALLBACK(on_cell_toggled),
                     GUINT_TO_POINTER(COL_REMOTE));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Remote", cell_renderer,
                                                "active", COL_REMOTE, NULL);

    cell_renderer = gtk_cell_renderer_toggle_new();
    g_object_set(cell_renderer, "activatable", TRUE, NULL);
    g_signal_connect(cell_renderer, "toggled", G_CALLBACK(on_cell_toggled),
                     GUINT_TO_POINTER(COL_DISABLED));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Disabled", cell_renderer,
                                                "active", COL_DISABLED, NULL);

    cell_renderer = gtk_cell_renderer_toggle_new();
    g_object_set(cell_renderer, "activatable", TRUE, NULL);
    g_signal_connect(cell_renderer, "toggled", G_CALLBACK(on_cell_toggled),
                     GUINT_TO_POINTER(COL_PLAYLIST));
    gtk_tree_view_insert_column_with_attributes(treeview, -1, "Playlist", cell_renderer,
                                                "active", COL_PLAYLIST, NULL);

    treemodel = init_treemodel();
    gtk_tree_view_set_model(treeview, treemodel);
    g_object_unref(treemodel);
}

static int
shellexecui_action_callback(DB_plugin_action_t *action,
                                void *user_data) {
    conf_dlg = create_shellexec_conf_dialog();
    init_treeview();
    disable_save_button();
    gtk_widget_show(conf_dlg);
    return 0;
}

static DB_plugin_action_t shellexecui_action = {
    .title = "Edit/Shellexec Commands",
    .name = "shellexec_conf",
    .flags = DB_ACTION_COMMON,
    .callback = shellexecui_action_callback,
    .next = NULL,
};

static DB_plugin_action_t *
shxui_getactions(DB_playItem_t *it) {
    return &shellexecui_action;
}

int shxui_connect() {
#if GTK_CHECK_VERSION(3,0,0)
    gtkui_plugin = (ddb_gtkui_t *)deadbeef->plug_get_for_id ("gtkui3");
#else
    gtkui_plugin = (ddb_gtkui_t *)deadbeef->plug_get_for_id ("gtkui");
#endif
    shellexec_plugin = (Shx_plugin_t *)deadbeef->plug_get_for_id ("shellexec");
    if(!gtkui_plugin || !shellexec_plugin) {
        return -1;
    }
    return 0;
}

static DB_misc_t plugin = {
    .plugin.type = DB_PLUGIN_MISC,
    .plugin.api_vmajor = 1,
    .plugin.api_vminor = 0,
    .plugin.version_major = 1,
    .plugin.version_minor = 0,
    .plugin.id = "shellexecui",
    .plugin.name = "Shellexec GTK UI",
    .plugin.descr = "A GTK UI for the Shellexec plugin",
    .plugin.copyright = 
        "Copyright (C) 2010-2012 Azeem Arshad <kr00r4n@gmail.com>\n"
        "\n"
        "This program is free software; you can redistribute it and/or\n"
        "modify it under the terms of the GNU General Public License\n"
        "as published by the Free Software Foundation; either version 2\n"
        "of the License, or (at your option) any later version.\n"
        "\n"
        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
        "GNU General Public License for more details.\n"
        "\n"
        "You should have received a copy of the GNU General Public License\n"
        "along with this program; if not, write to the Free Software\n"
        "Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.\n",
    .plugin.website = "http://azeemarshad.in",
    .plugin.get_actions = shxui_getactions,
    .plugin.connect = shxui_connect,
};

DB_plugin_t *shellexecui_load(DB_functions_t *api) {
    deadbeef = api;
    return DB_PLUGIN(&plugin);
}