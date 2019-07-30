#include "clock.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#define APP_ID "org.poul.wlclock"

int main(int argc, char** argv)
{
   auto app = Gtk::Application::create(argc, argv, APP_ID);

   Gtk::Window win;
   win.set_title("Wayland Clock");
   win.set_default_size(400, 400);
   win.set_startup_id(APP_ID);
   win.set_wmclass(APP_ID, APP_ID);

   Clock c;
   win.add(c);
   c.show();

   return app->run(win);
}
