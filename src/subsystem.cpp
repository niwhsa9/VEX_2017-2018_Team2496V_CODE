#include "subsystem.h"
#include "API.h"

Subsystem::~Subsystem() {
	delete _motors;
	delete _revField;
	delete _sensors;
	delete _name;

}

void Subsystem::setAll(int speed) {
		for(int i = 0; i < _num; i++) {
				setMotor(_motors[i], speed * _revField[i]);
		}
		return;
}
