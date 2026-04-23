#ifndef MAIN_H
#define MAIN_H
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <errno.h>
#include <cstdlib>
#include <iostream>
#include "constants.h"
#include "dialogs/new.h"


class Application : public Fl_Double_Window 
{
    Fl_Menu_Bar* menu = nullptr;
    Fl_Group* toolbar = nullptr;
    Fl_Menu_Item* menuItem = nullptr;
    Fl_Menu_Item* undoMenuItem = nullptr;
    Fl_Menu_Item* redoMenuItem = nullptr;
    Fl_Native_File_Chooser* fileChooser = nullptr;
    Fl_Box* filler = nullptr;
    NewDialog* newDlg = nullptr;
    // Stores menu item labels to prevent trash characters (eg: ^$¨)
    // when updating labels.
    std::map<Fl_Menu_Item*, std::string> menuItemLabels;
    std::string message;

    public:

        Application(int w, int h, const char* l, int argc, char* argv[]);

        void createMenu();
        void open(const char* filename);
        void save(const char* filename);
        const char* untitledDefault();
        int isFileExist(const char* filename);
        void onMenuEdit(EditID id);
        void onCopy();
        void onPaste();
        void onCut();
        void onUndo();
        void onRedo();
        void onDelete();

        // Call back functions.
        static void quit_cb(Fl_Widget* w, void* data);
        static void noEscapeKey_cb(Fl_Widget* w, void* data);
        static void dialog_cb(Fl_Widget* w, void* data);
        static void new_cb(Fl_Widget* w, void* data);
        static void open_cb(Fl_Widget* w, void* data);
        static void save_cb(Fl_Widget* w, void* data);
        static void saveas_cb(Fl_Widget* w, void* data);
        static void ok_cb(Fl_Widget* w, void* data);
        static void cancel_cb(Fl_Widget* w, void* data);
};

#endif
