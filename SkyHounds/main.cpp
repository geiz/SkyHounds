// Main Program

#include "Control.h"
#include "Scenario.h"

#include "porting.h"

#include <cstdio>
#include <cstdlib>

#include <allegro5/allegro.h>

struct SystemState {
	// Scenario contains entire game state.
	Scenario * scenario;

	// Control mappings for translating commands on various platforms.
	Control * control;

	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * frame_timer;
};

static SystemState s_system;

void SystemInitialize ();
void SystemEventLoop ();
void SystemClose ();

int main () {
	SystemInitialize ();
	s_system.scenario = new Scenario ("startup");
	s_system.control = new ControlPC ();
	SystemEventLoop ();
	SystemClose ();
	return 0;
}

//----- Function Implementations -----//

void SystemInitialize () {
	if (!al_init ()) {
		breakpoint ();
		exit (-1);
	}

	// Event Queue
	s_system.event_queue = al_create_event_queue();
	if (!s_system.event_queue) {
		breakpoint ();
		exit (-1);
	}

	// Mouse
	if (!al_install_mouse ()) {
		breakpoint ();
		exit (-1);
	}
	al_register_event_source (s_system.event_queue,
		al_get_mouse_event_source ());

	// Keyboard
	if (!al_install_keyboard ()) {
		breakpoint ();
		exit (-1);
	}
	al_register_event_source (s_system.event_queue,
		al_get_keyboard_event_source ());

	// Window
	al_set_new_display_flags (ALLEGRO_WINDOWED);
	s_system.display = al_create_display (640, 480);
	if (!s_system.display) {
		breakpoint ();
		exit (-1);
	}
	al_register_event_source (s_system.event_queue,
		al_get_display_event_source (s_system.display));

	// Frame Timer
	s_system.frame_timer = al_create_timer (1.0 / 60.0);
	if(!s_system.frame_timer) {
		breakpoint ();
		exit (-1);
	}
	al_register_event_source (s_system.event_queue,
		al_get_timer_event_source (s_system.frame_timer));
	al_start_timer (s_system.frame_timer);
}

void SystemEventLoop () {
	bool redraw = true;
	for (;;) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(s_system.event_queue, &ev);

		// Window closed?
		if (ALLEGRO_EVENT_DISPLAY_CLOSE == ev.type)
			return;

		// Timer event.
		else if (ALLEGRO_EVENT_TIMER == ev.type) {
			// Frame timer. Step physics, flag display redraw.
			if (ev.timer.source == s_system.frame_timer) {
				s_system.scenario->Physics ();
				redraw = true;
			}
		}

		// Mouse movement.
		else if (ALLEGRO_EVENT_MOUSE_AXES == ev.type) {
			s_system.control->Mouse (ev.mouse.x, ev.mouse.y, s_system.scenario);
		}

		// Mouse button press.
		else if (ALLEGRO_EVENT_MOUSE_BUTTON_DOWN == ev.type) {
			s_system.control->MouseButton (ev.mouse.button, s_system.scenario);
		}

		// Mouse left display area.
		else if (ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY == ev.type) {
			s_system.control->LostMouse (s_system.scenario);
		}

		// Mouse entered display area.
		else if (ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY == ev.type) {
			s_system.control->GotMouse (s_system.scenario);
		}

		// Character input.
		else if (ALLEGRO_EVENT_KEY_CHAR == ev.type) {
			int c = ev.keyboard.unichar;
			if (c < 32 || c == 127)
				s_system.control->ControlCharacter (c, s_system.scenario);
			else
				s_system.control->Character (c, s_system.scenario);
		}

		// Key press (non-repeating).
		else if (ALLEGRO_EVENT_KEY_DOWN == ev.type) {
			// Quit on Escape.
			if (ALLEGRO_KEY_ESCAPE == ev.keyboard.keycode)
				return;
			// Other key press.
			s_system.control->Keyboard (ev.keyboard.keycode, s_system.scenario);
		}

		// Draw next frame.
		if (redraw && al_is_event_queue_empty (s_system.event_queue)) {
			s_system.scenario->AI (); // TO DO: dispatch to other threads
			s_system.scenario->Display (s_system.display);
			al_flip_display ();
			redraw = false;
		}
	}
}

void SystemClose () {
	delete s_system.control;
	delete s_system.scenario;
	al_destroy_timer (s_system.frame_timer);
	al_destroy_display (s_system.display);
	al_destroy_event_queue (s_system.event_queue);
}

