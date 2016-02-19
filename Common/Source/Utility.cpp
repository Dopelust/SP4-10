#include "Utility.h"

void Fall(float& value, float by, float until)
{
	value = value - by < until ? until : value - by;
}

void Rise(float& value, float by, float until)
{
	value = value + by > until ? until : value + by;
}