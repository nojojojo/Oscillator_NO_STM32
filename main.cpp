#define WTB_LEN 1024
#define BUFF_LEN 8192
#define BUFF_LEN_DIV2 BUFF_LEN / 2
#define SAMPLERATE 48000

#include <iostream>
#include "wavetable.h"

class Synth {
public:
	float osc_wtb_pointer = 0.0f;
	float osc;
	float signal = 0.0f;
	float pitch = 0.0f;

	float calculate_oscilator();
};

float Synth::calculate_oscilator() {
	int a, b;
	float da, db;

	float osc_wtb_incr = WTB_LEN * (pitch) / SAMPLERATE;
	float osc_wtb_pointer = osc_wtb_pointer + osc_wtb_incr;
	if (osc_wtb_pointer > WTB_LEN)
	{
		osc_wtb_pointer = osc_wtb_pointer - WTB_LEN;
	}

	osc_wtb_pointer = a;
	da = osc_wtb_pointer - a;
	b = a + 1;
	db = b - osc_wtb_pointer;

	if (b >= WTB_LEN)
		b = 0;

	float osc = db * triangle[a] + da * triangle[b];

	float signal = osc * 32767.0f;
	if (signal > 32767.0f)
		signal = 32767.0f;
	if (signal < -32767.0f)
		signal = -32767.0f;
	return signal;
}

Synth synth;

int audiobuff[BUFF_LEN];

void make_sound(int start_index) {
	for (int i = 0; i < BUFF_LEN_DIV2; i++) {
		float signal = synth.calculate_oscilator();
		audiobuff[start_index + i] = (int)signal;
		audiobuff[start_index + i + 1] = (int)signal;
	}
}

int main(){

synth.pitch = 220.0f; 

make_sound(0);
make_sound(BUFF_LEN_DIV2);

return 0;

}