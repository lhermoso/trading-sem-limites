#include "pch.h"
#include <zorro.h>
#include "Bots.h"





DLLFUNC void run()
{

	BarPeriod = 60;
	StartDate = 2022;
	MaxLong = MaxShort = -1;
	set(PARAMETERS);
	NumWFOCycles = 12;
	NumCores = 8;


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


