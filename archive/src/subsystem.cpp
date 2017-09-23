#include "subsystem.h"

//define unresolved C function __cxa_pure_virtual() with loud behavior
extern "C" {void __cxa_pure_virtual(){while(1);}}


int t;
Subsystem::Subsystem(const char *name, int motors[10], int revField[10],
	const int num, int sensors[10], const char id=255):
_name(name), _num(num), _id(id)
{
	for(int i = 0; i < 10; i++) _revField[i] = revField[i];
	for(int i = 0; i < 10; i++) _motors[i] = motors[i];
	for(int i = 0; i < 10; i++) _sensors[i] = sensors[i];
	//while(1) printf("DEBUG: %d", _revField[2]);
	//memcpy(_revField, revField, 10 * sizeof(int));
	//t = revField[2];
	//printf("DEBUG: %d", _revField[2]);
	//revField
};
/*
Subsystem::Subsystem(const char *name, const int *motors, const int *revField,
	int num, const int *sensors=(const int *)malloc(1), char id=255) {
		_name = name;
		_motors = motors;
		_revField = revField;
		_num = num;
		_sensors = sensors;
		_id = id;
	}
*/
Subsystem::~Subsystem() {
	//delete _motors;
	//delete _revField;
	//delete _sensors;
	delete _name;

}

void Subsystem::setMotor(int id, int speed) {
		//printf("\n \n %d, %s", _revField[2], _name); //rm
		motorSet(_motors[id], speed * _revField[id]);
		return;
}

void Subsystem::setAll(int speed) {
		for(int i = 0; i < _num; i++) {
				motorSet(_motors[i], speed * _revField[i]);

				//motorSet(6, 100);
				//printf("\n %d %d", _motors[i], _revField[i]*speed);
		}
		//printf("\n \n \n");
		return;
}
