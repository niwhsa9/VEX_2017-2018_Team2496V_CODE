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
};

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
		}
		//printf("\n \n \n");
		return;
}
void Subsystem::setPID(float p, float i, float d, int limit) {
		pK = p;
		iK = i;
		dK = d;
		integ_limit = limit;
		integ_data = 0;
		prevError = 0;
		integ_count = 0;
}
void Subsystem::setAltPID(float p, float i, float d) {
		apK = p;
		aiK = i;
		adK = d;

}
void Subsystem::setConst(char c, float val) {
		if(c == 'P') pK = val;
		else if(c == 'I') iK = val;
		else if(c == 'D') dK = val;
}

float Subsystem::PID(float error) {
	float deltaT = millis() - prevTime;
	prevTime = millis();
	p = pK * error;
	i = iK * (integ_data+=error);
	d = dK * (error - prevError)/deltaT;
 	float PID = p + i + d;
	prevError = error;
	integ_count++;
	if(integ_count >= integ_limit) {
		integ_data = 0;
		integ_count = 0;
	}
	return PID;
}

float Subsystem::altPID(float error) {
	float p = pK * error;
	float i = iK * (ainteg_data+=error);
	float d = dK * (error - aprevError);
 	float PID = p + i + d;
	aprevError = error;
	if(integ_count >= integ_limit) {
		ainteg_data = 0;
	}
	return PID;
}
