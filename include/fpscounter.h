#pragma once

#define FPS_COUNTER_BUFFER_LENGTH 40

class FpsCounter
{
	double _circularBuffer[FPS_COUNTER_BUFFER_LENGTH] = {};
	int _index = 0;

public:
	void addFrameTime(double value);
	double getFps();
};
