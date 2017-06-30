#include "subsystem.h"


Subsystem::~Subsystem() {
	delete _motors;
	delete _revField;
	delete _sensors;
	delete _name;

}

void Subsystem::setMotor(int id, int speed) {
		motorSet(_motors[id], speed * _revField[id]);
		return;
}

void Subsystem::setAll(int speed) {
		for(int i = 0; i < _num; i++) {
				motorSet(_motors[i], speed * _revField[i]);
		}
		return;
}
