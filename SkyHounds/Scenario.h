#ifndef SCENARIO_H
#define SCENARIO_H

#include <allegro5/allegro.h>

#include <string>

class Scenario {
public:
	Scenario (const char * name) {
		std::string mapName = std::string ("scenarios") + name + "/map.png";
	}

	void Physics () {
	}

	void AI () {
	}

	void Display (ALLEGRO_DISPLAY * display) {
	}
};

#endif
