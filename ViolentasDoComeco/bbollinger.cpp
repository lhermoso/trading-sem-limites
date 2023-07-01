#include "pch.h"
#include <map>
#include <zorro.h>
#include "Bots.h"
#include "Risk.h"



std::map<string, double> BandaCentral;


int periodo_stop_bb;


int tmf_bb()
{
	if (TradeIsOpen)
	{
		if (TradeIsLong)
		{
			
			if (TypPrice() >= BandaCentral[TradeAsset])
			{



				TradeStopLimit = max(TradeStopLimit, LL(periodo_stop_bb, 0));

			}


		}

		else
		{
			if (TypPrice() <= BandaCentral[TradeAsset])
			{

				TradeStopLimit = min(TradeStopLimit, HH(periodo_stop_bb, 0));
			}
		}

	}
	//plot("Stop_BB", TradeStopLimit, MAIN | MINV, BLACK);

	return 0;

}



void run_bollinger()
{
	double* fechamento = series(TypPrice()); 
	double desvios = optimize(1, 1.5, 2.5, 0, 0);
	int periodBB = optimize(20, 5, 36, 2, 0);
	periodo_stop_bb = optimize(5, 3, 21, 3, 0);
	
	BBands(fechamento, periodBB, desvios, desvios, MAType_EMA);
	
	

	
	BandaCentral[Asset] = rRealMiddleBand;

	
		if (crossOver(fechamento, rRealLowerBand))
		{
			Stop = ATR(100) * 5;
			SetRisk(true);
			enterLong(tmf_bb);
		}

		else if (crossUnder(fechamento, rRealUpperBand))
		{
			Stop = ATR(100) * 5;
			SetRisk(false);
			enterShort(tmf_bb);
		}
	
/*
	if (NumOpenLong && fechamento[0] >= rRealMiddleBand)
	{
		exitLong();
	}

	if (NumOpenShort && fechamento[0] <= rRealMiddleBand)
	{
		exitShort();
	}
	*/

}