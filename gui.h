#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include "hangman.h"

class Gui : public Gtk::Window {
	public:
		Gui();
		virtual ~Gui();

	protected:
		void on_button_clicked();
		void update_image();
		Gtk::Button guess_button;

		Gtk::Image background;
		Gtk::Image hung;
		Gtk::Image alive;
		Gtk::Image l_arm;
		Gtk::Image r_arm;
		Gtk::Image body;
		Gtk::Image head;
		Gtk::Image r_leg;
		Gtk::Image l_leg;

		Gtk::Box mainBox;
		Gtk::Entry guess_entry;
		Gtk::Box ctrlBox;
		Gtk::Fixed imageLayers;
		Gtk::Label secret_word;

		Hangman h;
};

#endif
