#include <stdlib.h>
#include <string.h>
#include "main.h"

#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

class Subsystem {
	public:
		Subsystem(const char *name, int motors[10], int revField[10],
			const int num, int sensors[10], const char id);
		void setAll(int speed);
		void setMotor(const int id, int speed);
		virtual void debug() = 0;
		virtual void iterateCtl() = 0;//use a function pointer to loop through each subsystem and get this
		virtual int eStop() = 0;
		~Subsystem();
	protected:
		const char *_name;
		int _motors[10];
		int _revField[10];
		const int _num;
		int _sensors[10];
		const char _id;
};

/*
do implementation specific motors, sensors, buttons
e.g. DR4B
pass motors constructor param of super with the tr, br, tl, bl
motors in the array with specified order. Then in the DR4B
child have constructor assign tr = 0
br = 1
..


setMotor(i, speed) {
	setMotor(motor[i], speed * revField[i]);
}
*/
#endif
