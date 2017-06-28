#include <stdlib.h>
#include <string.h>


class Subsystem {
	public:
		Subsystem(const char *name, const int *motors, const int *revField,
			const int num, const int *sensors=(const int *)malloc(1), char id=255):
		_name(name), _motors(motors), _revField(revField), _num(num), _sensors(sensors), _id(id)
		{};
		void setAll(int speed);
		virtual void setMotor(const int id, int speed) = 0;
		virtual void debug() = 0;
		virtual void iterateCtl() = 0;//use a function pointer to loop through each subsystem and get this
		virtual int eStop() = 0;
		~Subsystem();
	private:
		const char *_name;
		const int *_motors;
		const int *_revField;
		const int _num;
		const int *_sensors;
		char _id;
};

/*
do implementation specific motors, sensors, buttons
e.g. DR4B
pass motors constructor param of super with the tr, br, tl, bl
motors in the array with specified order. Then in the DR4B
child have constructor assign motor[0] = [field] tr

*/
