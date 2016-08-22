#include <gtk/gtk.h>
#include <string>

#include <stdio.h>

#include "IcWin.h"

G_DEFINE_TYPE(IcWin, ic_win, GTK_TYPE_WINDOW /*GTK_TYPE_APPLICATION_WINDOW*/);

static void ic_win_init(IcWin *win)
{
}

static void ic_win_class_init(IcWinClass *klass)
{

}

void ic_win_refresh(IcWin *win,
                    int x,
                    int y,
                    int w,
                    int h,
                    std::string& strInput,
                    std::deque<IMItem> *items)
{
    GtkWindow *icwin = GTK_WINDOW (win);
    IcWinClass *klass = IC_WIN_GET_CLASS(win);

    gtk_label_set_text(GTK_LABEL (klass->input_label), strInput.c_str());

    int pi = 0;
    if (items != NULL) {
        int len = items->size() < PREEDIT_ITEMS_MAX ? items->size() : PREEDIT_ITEMS_MAX;
        for (; pi < len ; pi++) {
            std::string text = "  ";
            char pichr = 0x31 + pi;
            text += pichr;
            text += ": ";
            text += items->at(pi).val;
            gtk_label_set_text(GTK_LABEL (klass->preedit_label[pi]), text.c_str());
        }

        delete items;
    }

    for (; pi < PREEDIT_ITEMS_MAX; pi++)
        gtk_label_set_text(GTK_LABEL (klass->preedit_label[pi]), " ");

    gtk_widget_show_all(GTK_WIDGET (icwin));

    gtk_window_resize(icwin, w, h);
    gtk_window_move(icwin, x, y);

}

IcWin *ic_win_new()
{
    #define ICWIN_W  410
    #define ICWIN_H  80

    IcWin* icwin = (IcWin *)g_object_new (IC_WIN_TYPE,
                                          "type", GTK_WINDOW_POPUP,
                                          "decorated", FALSE,
                                          "resizable", FALSE,
                                          "window-position", GTK_WIN_POS_CENTER,
                                          "accept-focus", FALSE,
                                          NULL);
    IcWinClass *klass = IC_WIN_GET_CLASS(icwin);

    GtkWidget *window = ( GtkWidget *)(GTK_WINDOW(icwin));
    //gtk_widget_set_size_request(window, ICWIN_W, ICWIN_H);    
    GtkWidget *gridc = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window), gridc);
    //g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

    klass->input_label = gtk_label_new(NULL);
    gtk_grid_attach(GTK_GRID (gridc), klass->input_label, 0, 0, 3, 1);

    for (int i = 0; i < PREEDIT_ITEMS_MAX; i++) {
        klass->preedit_label[i] = gtk_label_new(NULL);
        gtk_grid_attach(GTK_GRID (gridc), klass->preedit_label[i], i, 1, 1, 1);
    }

    /*GtkWidget *button = gtk_button_new_with_label("<");
    gtk_grid_attach(GTK_GRID (gridc), button, PREEDIT_ITEMS_MAX, 1, 1, 1);

    button = gtk_button_new_with_label(">");
    gtk_grid_attach(GTK_GRID (gridc), button, PREEDIT_ITEMS_MAX+1, 1, 1, 1);*/

    //gtk_widget_show_all (window);
    return icwin;
}
