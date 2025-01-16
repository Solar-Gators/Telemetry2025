#ifndef TESTFRAME_H
#define TESTFRAME_H

// A testing placeholder for CANFrame
struct TESTFrame {
	uint32_t can_id;
	uint8_t len;
	uint8_t data[20];
	uint8_t Unlock() {
		return 1;
	}
};

#endif
