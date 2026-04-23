#include "main.h"


Application::Application(int w, int h, const char *l, int argc, char *argv[]) : Fl_Double_Window(w, h, l)
{
    box(FL_DOWN_BOX);
    color((Fl_Color) FL_INACTIVE_COLOR);

    // Create and build the menu.
    menu = new Fl_Menu_Bar(0, 0, w, SMALL_SPACE);
    menu->box(FL_THIN_UP_BOX);
    createMenu();
    menu->textsize(TEXT_SIZE);

    // Set menu item pointers.
    // Note: It's much easier to access menu items later than to rely on the find_item function.
    undoMenuItem = (Fl_Menu_Item *)menu->find_item(MenuLabels[MenuItemID::EDIT_UNDO].c_str());
    undoMenuItem->deactivate();
    redoMenuItem = (Fl_Menu_Item *)menu->find_item(MenuLabels[MenuItemID::EDIT_REDO].c_str());
    redoMenuItem->deactivate();

    toolbar = new Fl_Group(0, SMALL_SPACE, w, SMALL_SPACE);
    toolbar->box(FL_FLAT_BOX);

        // Other widgets go here...

    toolbar->end();

    // Initialize the file chooser
    fileChooser = new Fl_Native_File_Chooser();
    // Sets the current filename filter patterns (ie: extension).
    fileChooser->filter("Text\t*.txt\n");
    // Sets the default filename for the chooser.
    fileChooser->preset_file(untitledDefault());

    // Stop adding children to this window.
    end();

    // Add an invisible box to absorb resizing
    // It must be placed over the remaining space

    // Matches group size (ie: toolbar).
    filler = new Fl_Box(0, SMALL_SPACE * 2, w, h - SMALL_SPACE); 
    // Make it invisible.
    filler->hide(); 
    // Set this box as the resizable area.
    resizable(filler); 
    // Prevent toolbar (and its children) from being resized.
    toolbar->resizable(nullptr);

    show();

    this->callback(noEscapeKey_cb, this);
}

int main(int argc, char *argv[])
{
    Application app(600, 400, "Basic Application", argc, argv);

    return Fl::run();
}
