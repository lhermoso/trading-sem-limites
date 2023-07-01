#include "pch.h"
#include <zorro.h>
#include "Bots.h"
#include "Risk.h"





DLLFUNC void run()
{
	LookBack = 300 ;
	BarPeriod = 1440;
	StartDate = 2020;
	Capital = 500000;
	MaxLong = MaxShort = -1;

	NumWFOCycles = 12;
	NumCores = 8;
	ReTrainDays = 63;

	assetList("history\\bovespalite.csv");


	setf(PlotMode, PL_ALL + PL_FINE);
	if (is(TRAINMODE))
	{
		set(PARAMETERS + FACTORS + TESTNOW + PLOTNOW);
		setf(TrainMode, PHANTOM);

	}
	else
	{

		set(PARAMETERS + FACTORS + LOG );
		

	}


	Detrend = PRICES + TRADES;



	if (ReTrain)
	{
		EndDate = 0;
		UpdateDays = -1;
		SelectWFO = -1;


	}




	// "rsi" , "medias", "bollinger", "rompimento"
	while (algo(loop("rsi", "medias", "bollinger", "rompimento")))
	{

		while (asset(loop(Assets)))
		{


			if (strcmp(Algo, "rsi") == 0)
			{
				run_rsi();
			}
			else if (strcmp(Algo, "medias") == 0)
			{
				run_medias();
			}
			else if (strcmp(Algo, "bollinger") == 0)
			{
				run_bollinger();
			}
			else if (strcmp(Algo, "rompimento") == 0)
			{
				run_rompimento();
			}

		}
	}





}


