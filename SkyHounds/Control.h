#ifndef CONTROL_H
#define CONTROL_H

#include "Scenario.h"

/**
 * Control class translates raw UI events into game events.
 * Subclasses translate differently for different platforms.
 */
class Control {
public:
	virtual void Mouse (int, int, Scenario *) { }
	virtual void MouseButton (int, Scenario *) { }
	virtual void LostMouse (Scenario *) { }
	virtual void GotMouse (Scenario *) { }
	virtual void Character (int, Scenario *) { }
	virtual void ControlCharacter (int, Scenario *) { }
	virtual void Keyboard (int, Scenario *) { }
};

/**
 * ControlPC class translates PC UI events into game events.
 */
class ControlPC : public Control {
public:
	virtual void Mouse (int x, int y, Scenario * scenario) {
	}

	virtual void MouseButton (int button, Scenario * scenario) {
	}

	virtual void LostMouse (Scenario * scenario) {
	}

	virtual void GotMouse (Scenario * scenario) {
	}

	virtual void Character (int c, Scenario * scenario) {
	}

	virtual void ControlCharacter (int c, Scenario * scenario) {
	}

	virtual void Keyboard (int k, Scenario * scenario) {
	}
};

#endif
