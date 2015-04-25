#ifndef QUADENC_H
#define QUADENC_H

struct encoder {
	char state;
	unsigned int steps;
};

void quad_init(void);
signed char step(volatile struct encoder * enc, char new_state);

#endif
