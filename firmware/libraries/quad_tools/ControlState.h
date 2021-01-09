#ifndef __CONTROL_STATE
#define __CONTROL_STATE

enum {
	ENC1_BUTTON=0,
	BUTTON1,
	BUTTON2,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_CENTER
};

#define PID_COUNT 3

#define PITCH  0
#define YAW  1
#define ROLL  2
#define THROTTLE  3

typedef unsigned char byte;

template<class T>
static inline byte compute_hash(T & t) {
	byte old_hash = t.hash;
	t.hash = 0;
	byte h;
	for (int i =0; i < sizeof(T); i++) {
		h ^= reinterpret_cast<char*>(&t)[i];
	}
	t.hash = old_hash;
	return h;
}

template<int MAGIC>
class Packet {
public:
	int magic;
	byte hash;
	enum {magic_value = MAGIC};

	Packet(): magic(0), hash(0) {}
	
	inline bool validate() {
		int h = 0;//compute_hash(*this);
		return magic == MAGIC && hash == h;
	}

	inline void bless() {
		magic = MAGIC;
		hash = 0;//compute_hash(*this);
	}
};

#define CMD_NO_COMMAND 0
#define CMD_CALIBRATE_IMU  1

class ControlState : public Packet<0x1DEA> {
public:
	
	byte throttle;
	char yaw;
	char pitch;
	char roll;
	byte tuning;
	bool armed;
	byte command;
	void * arg;
	
	float P[PID_COUNT];
	float I[PID_COUNT];
	float D[PID_COUNT];
	float C[PID_COUNT];

	char trim[PID_COUNT];

	ControlState() : Packet() {
		C[PITCH] = 0;
		C[ROLL] = 0;
		C[YAW] = 0;
		
		P[PITCH] = 0;
		P[ROLL] = 0;
		P[YAW] = 0;
		
		I[PITCH] = 0;
		I[ROLL] = 0;
		I[YAW] = 0;
		
		C[PITCH] = 0.985;
		C[ROLL] = 0.985;
		C[YAW] = 0.0; // no filter
		
		trim[PITCH] = 0;
		trim[ROLL] = 0;
		trim[YAW] = 0;
		armed = false;
		tuning = 0;
		command = 0;
		arg = (void*)0;

		pitch = 0;
		roll = 0;
		throttle = 0;
		yaw = 0;
	}
	
	inline char * get_name() {
		return "Control";
	}	
};

#define FRONT_LEFT  0
#define FRONT_RIGHT 1
#define BACK_LEFT   2
#define BACK_RIGHT  3


struct Telemetry  : public Packet<0x2DEA> {
public:
	bool disarm;
	byte motors[4];
	float pitch;
	float roll;
	float yaw_rate;
	
	inline char * get_name() {
		return "Telemetry";
	}
};
	
extern ControlState controls;
extern void dump_controls();

#endif
