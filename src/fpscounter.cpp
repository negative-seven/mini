#include "fpscounter.h"


void FpsCounter::addFrameTime(double value)
{
	_circularBuffer[_index] = value;
	_index++;
	_index %= FPS_COUNTER_BUFFER_LENGTH;
}

double FpsCounter::getFps()
{
	double sum = 0;
	for (int i = 0; i < FPS_COUNTER_BUFFER_LENGTH; i++)
	{
		sum += _circularBuffer[i];
	}
	return FPS_COUNTER_BUFFER_LENGTH / sum;
}
