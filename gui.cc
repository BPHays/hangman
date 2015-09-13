#include "gui.h"
#include <iostream>

Gui::Gui() {
	// start a new hangman game
	h.newGame();

	// add the guess button
	guess_button.add_label("_guess", true);
	set_border_width(10);
	guess_button.signal_clicked().connect(sigc::mem_fun(*this, &Gui::on_button_clicked));	
	// add a box for the controls
	ctrlBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	ctrlBox.pack_start(guess_button);
	ctrlBox.pack_start(guess_entry);
	secret_word.set_text(h.getHiddenWord());

	// add the background images
	background.set("./images/bg.png");
	alive.set("./images/alive_bg.png");
	hung.set("./images/hung.png");
	l_arm.set("./images/l_arm.png");
	r_arm.set("./images/r_arm.png");
	l_leg.set("./images/l_leg.png");
	r_leg.set("./images/r_leg.png");
	body.set("./images/body.png");
	head.set("./images/head.png");

	imageLayers.put(background, 0 , 0);
	imageLayers.put(alive, 0, 0);
	imageLayers.put(hung, 0, 0);
	imageLayers.put(l_arm, 0, 0);
	imageLayers.put(r_arm, 0, 0);
	imageLayers.put(l_leg, 0, 0);
	imageLayers.put(r_leg, 0, 0);
	imageLayers.put(body, 0, 0);
	imageLayers.put(head, 0, 0);

	mainBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
	mainBox.pack_start(imageLayers);
	mainBox.pack_start(secret_word);
	mainBox.pack_start(ctrlBox);

	add(mainBox);

	show_all_children();

	update_image();
}

Gui::~Gui() {
	
}

void Gui::on_button_clicked() {
	h.guess(guess_entry.get_text()[0]);
	guess_entry.set_text("");
	secret_word.set_text(h.getHiddenWord());
	update_image();
}

void Gui::update_image() {
	int misses = h.getMissed();
	switch (misses) {
		case 0:
			body.hide();
			head.hide();
			r_arm.hide();
			l_arm.hide();
			r_leg.hide();
			l_leg.hide();
			hung.hide();
			break;
		case 1:
			body.show();
			break;
		case 2:
			head.show();
			break;
		case 3:
			r_arm.show();
			break;
		case 4:
			l_arm.show();
			break;
		case 5:
			r_leg.show();
			break;
		case 6:
			l_leg.show();
			break;
		case 7:
			alive.hide();
			body.hide();
			head.hide();
			r_arm.hide();
			l_arm.hide();
			r_leg.hide();
			l_leg.hide();

			hung.show();
			break;
	}
}
