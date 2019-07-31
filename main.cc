#include "clock.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/cssprovider.h>
#include "colors.h"

#define APP_ID "org.poul.wlclock"

int main(int argc, char **argv) {
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
//    Glib::RefPtr<Gtk::StyleContext> style_context = Gtk::StyleContext::create();

    auto app = Gtk::Application::create(argc, argv, APP_ID);
    Gtk::Window win;

    if (css_provider->load_from_data(std::string(
            ".background { background: ") + WINDOW_BG_COLOR_CSS + "; }\nframe border { border: 0px; }"
    )) {
        Glib::RefPtr<Gdk::Screen> screen = win.get_screen();
        Gtk::StyleContext::add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    }

    win.set_title("Wayland Clock");
    win.set_default_size(400, 400);
    win.set_startup_id(APP_ID);
    win.set_wmclass(APP_ID, APP_ID);

    Clock c;

    Gtk::AspectFrame aspect_frame("", Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER, 1, false);
    aspect_frame.unset_label();
    aspect_frame.add(c);
    aspect_frame.show();

    win.add(aspect_frame);
    c.show();

    return app->run(win);
}
