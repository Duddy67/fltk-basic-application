#include "../main.h"

/*
 * Prevents the escape key to close the application. 
 */
void Application::noEscapeKey_cb(Fl_Widget* w, void* data)
{
    // If the escape key is pressed it's ignored.
    if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape) {
        return;
    }

    // Close the application when the "close" button is clicked.
    exit(0);
}

void Application::new_cb(Fl_Widget *w, void *data)
{
    Application* app = (Application*) data;

    if (app->newDlg == nullptr) {
        app->newDlg = new NewDialog(app->x() + MODAL_WND_POS, app->y() + MODAL_WND_POS, XLARGE_SPACE, LARGE_SPACE, "New project");
    }

    if (app->newDlg->runModal() == DIALOG_OK) {
        // Add new file logic here...
    }
}

void Application::quit_cb(Fl_Widget* w, void* data)
{
    exit(0);
}

