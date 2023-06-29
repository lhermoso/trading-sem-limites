#include "pch.h"
#include <zorro.h>
#include "Bots.h"
#include "Risk.h"


void run_bollinger()
{
	double* fechmaento = series(TypPrice()); 
	int periodBB = optimize(20, 18, 36, 2, 0);
	double desvios = optimize(2, 1.5, 2.5, 0, 0);
	BBands(fechmaento, periodBB, desvios, desvios, MAType_EMA);

	if (crossOver(seriesC(), rRealLowerBand))
	{
		SetRisk(true);
		enterLong();
	}

	else if (crossUnder(seriesC(), rRealUpperBand))
	{
		SetRisk(false);
		enterShort();
	}

	if (NumOpenLong && priceClose(0) >= rRealMiddleBand)
	{
		exitLong();
	}

	if (NumOpenShort && priceClose(0) <= rRealMiddleBand)
	{
		exitShort();
	}

}