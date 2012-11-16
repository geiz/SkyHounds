// Main Program

#include "Scenario.h"

#include "porting.h"

#include <cstdio>
#include <cstdlib>

#include <allegro5/allegro.h>

// System state variables.
struct SystemState {
	// Scenario contains entire game state.
	Scenario * scenario;

	ALLEGRO_DISPLAY * display;
};

static SystemState s_system;

void SystemInitialize ();
void SystemEventLoop ();
void SystemClose ();

int main () {
	SystemInitialize ();
	s_system.scenario = new Scenario ("startup");
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

	s_system.display = al_create_display (640, 480);
	if (s_system.display) {
		breakpoint ();
		exit (-1);
	}
}

void SystemEventLoop () {
	al_clear_to_color (al_map_rgb (0,0,0));

	al_flip_display ();

	al_rest (10.0);

/*	for (;;) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ALLEGRO_EVENT_TIMER == ev.type) {
		}

		g_scenario->Tick ();
	}*/
}

void SystemClose () {
	delete s_system.scenario;

	al_destroy_display (s_system.display);
}

