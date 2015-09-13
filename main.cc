#include "gui.h"
#include <gtkmm/application.h>

int main(int argc, char ** argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "test");

	Gui gui;

	return app->run(gui);
}