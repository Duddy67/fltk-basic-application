#include "../main.h"


void Application::createMenu()
{
    menu->add(MenuLabels[MenuItemID::FILE_SUB].c_str(), 0, 0, 0, FL_SUBMENU);
    // Use callback function.
    menu->add(MenuLabels[MenuItemID::FILE_NEW].c_str(), FL_ALT + 'n', new_cb, (void*) this);
    menu->add(MenuLabels[MenuItemID::FILE_OPEN].c_str(), 0, open_cb, (void*) this);
    menu->add(MenuLabels[MenuItemID::FILE_SAVE].c_str(), 0, save_cb, (void*) this);
    menu->add(MenuLabels[MenuItemID::FILE_SAVE_AS].c_str(), 0, saveas_cb, (void*) this);
    menu->add(MenuLabels[MenuItemID::FILE_QUIT].c_str(), FL_CTRL + 'q',(Fl_Callback*) quit_cb, (void*) this);
    menu->add(MenuLabels[MenuItemID::EDIT_SUB].c_str(), 0, 0, 0, FL_SUBMENU);
    // Use lambda function.
    menu->add(MenuLabels[MenuItemID::EDIT_UNDO].c_str(), 0, [](Fl_Widget* w, void* userData) { 
                                      Application* app = static_cast<Application*>(userData);
                                      app->onMenuEdit(EditID::UNDO);
                                  }, (void*) this);
    menu->add(MenuLabels[MenuItemID::EDIT_REDO].c_str(), 0, [](Fl_Widget* w, void* userData) { 
                                      Application* app = static_cast<Application*>(userData);
                                      app->onMenuEdit(EditID::REDO);
                                  }, (void*) this);
    menu->add(MenuLabels[MenuItemID::EDIT_DELETE].c_str(), 0, [](Fl_Widget* w, void* userData) { 
                                      Application* app = static_cast<Application*>(userData);
                                      app->onMenuEdit(EditID::DELETE);
                                  }, (void*) this);
    menu->add(MenuLabels[MenuItemID::EDIT_COPY].c_str(), FL_CTRL + 'c',0, 0, 0);
    menu->add(MenuLabels[MenuItemID::EDIT_PASTE].c_str(), FL_CTRL + 'v',0, 0, FL_MENU_INACTIVE);
    menu->add(MenuLabels[MenuItemID::EDIT_CUT].c_str(), FL_CTRL + 'x',0, 0, 0);
    menu->add("Help", 0, 0, 0, FL_SUBMENU);
    menu->add("Help/Index", 0, 0, 0, 0);
    menu->add("Help/About", 0, 0, 0, 0);
    // etc...

    return;
}

int Application::isFileExist(const char* filename) {
    FILE* fp = fl_fopen(filename, "r");

    if (fp) {
        fclose(fp);
        return(1);
    }
    else {
        return(0);
    }
}

/*
 * "Open" the file.
 */
void Application::open(const char* filename)
{
    // A real app would do something useful here.
    printf("Open: '%s'\n", filename);
}

/*
 * Return an 'untitled' default pathname.
 */
const char* Application::untitledDefault()
{
    static char* filename = 0;

    if (!filename) {
        const char* home = getenv("HOME") ? getenv("HOME") : // Unix
        getenv("HOME_PATH") ? getenv("HOME_PATH") :          // Windows
        ".";                                                 // other

        filename = (char*)malloc(strlen(home) + 20);
        sprintf(filename, "%s/untitled.txt", home);
    }

    return(filename);
}

/*
 * Maps the edit menu item clicked to the according functions.
 */
void Application::onMenuEdit(EditID id)
{
    switch (id) {
        case EditID::DELETE:
            onDelete();
            break;

        case EditID::COPY:
            onCopy();
            break;

        case EditID::PASTE:
            onPaste();
            break;

        case EditID::CUT:
            onCut();
            break;

        case EditID::UNDO:
            onUndo();
            break;

        case EditID::REDO:
            onRedo();
            break;

        case EditID::NONE:
            return;
    }
}

//================== Callback functions called from menu  =========================

/*
 * Handle an 'Open' request from the menu.
 */
void Application::open_cb(Fl_Widget* w, void* data)
{
    Application* app = (Application*) data;
    app->fileChooser->title("Open file");
    // Only picks files that exist.
    app->fileChooser->type(Fl_Native_File_Chooser::BROWSE_FILE);     

    switch (app->fileChooser->show()) {
        case -1: break; // Error
        case  1: break; // Cancel
        default:        // Choice (ie: 0)
            app->fileChooser->preset_file(app->fileChooser->filename());
            app->open(app->fileChooser->filename());
        break;
    }
}

/*
 * Save the file, create the file if it doesn't exist
 * and save something in it.
 */
void Application::save(const char* filename) {
    printf("Saving '%s'\n", filename);

    if (!isFileExist(filename)) {
        // Create file if it doesn't exist.
        FILE *fp = fl_fopen(filename, "w");               

        if (fp) {
            // A real app would do something useful here.
            fprintf(fp, "Hello world.\n");
            fclose(fp);
        }
        else {
            fl_message("Error: %s: %s", filename, strerror(errno));
        }
    }
    else {
        // A real app would do something useful here.
    }
}

/*
 * Handle a 'Save as' request from the menu.
 */
void Application::saveas_cb(Fl_Widget* w, void* data)
{
    Application* app = (Application*) data;

    app->fileChooser->title("Save As");
    // Need this if file doesn't exist yet.
    app->fileChooser->type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);    

    switch ( app->fileChooser->show() ) {
        case -1: break;  // Error
        case  1: break;  // Cancel
        default:         // Choice (ie: 0)
            app->fileChooser->preset_file(app->fileChooser->filename());
            app->save(app->fileChooser->filename());
        break;
    }
}

/*
 * Handle a 'Save' request from the menu.
 */
void Application::save_cb(Fl_Widget* w, void* data)
{
    Application* app = (Application*) data;

    if (strlen(app->fileChooser->filename()) == 0) {
        saveas_cb(w, data);
    }
    else {
        app->save(app->fileChooser->filename());
    }
}

