#include "pch.h"
#include <zorro.h>
#include "utils.h"




double cumsum(double* prices, int period)
{

	double sum = 0;

	for (int i = 0; i < period; ++i)
	{

		sum += prices[i];
	}
	return sum;

}