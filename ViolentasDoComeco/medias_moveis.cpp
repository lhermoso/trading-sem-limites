#include "pch.h"
#include <map>
#include <zorro.h>
#include "Bots.h"
#include "Risk.h"

int periodo_stop;

std::map<string, double> medias;
std::map < string, int> parcial;

int tmf_medias()
{
	if (TradeIsOpen && TradeProfit > 0)
	{
		if (TradeIsLong)
		{
			if (priceClose(0) < medias[TradeAsset] && !parcial[TradeAsset])
			{
				if (TradeLots > 1)
				{

					exitLong(0, 0, (int)round(TradeLots * 0.8));
					parcial[TradeAsset] = 1;
				}
			}

			TradeStopLimit = max(TradeStopLimit, LL(periodo_stop, 0));
		}

		else
		{
			if (priceClose(0) > medias[TradeAsset] && !parcial[TradeAsset])
			{
				if (TradeLots > 1)
				{

					exitShort(0, 0, (int)round(TradeLots * 0.8));
					parcial[TradeAsset] = 1;
				}
			}
			TradeStopLimit = min(TradeStopLimit, HH(periodo_stop, 0));
		}


	}
	//plot("Stop", TradeStopLimit, MAIN | MINV, BLACK);

	return 0;

}


void run_medias()
{

	if (is(INITRUN))
	{
		parcial[Asset] = 0;
	}

	int periodo_rapida = optimize(9, 7, 21, 3, 0);
	int periodo_lenta = optimize(22, 22, 39, 3, 0);
	int periodo_stop = optimize(50, 5, 50, 5, 0);
	/*
	int tipos_media[9] = { MAType_SMA, MAType_EMA, MAType_WMA, MAType_DEMA, MAType_TEMA, MAType_TRIMA, MAType_KAMA, MAType_MAMA, MAType_T3 };
	int tipo_media_rapida = tipos_media[(int)round(optimize(0, 1, 9, 1, 0))];
	int tipo_media_lenta = tipos_media[(int)round(optimize(0, 1, 9, 1, 0))];
	double* media_rapida = series(MovingAverage(seriesC(), periodo_rapida, tipo_media_rapida));
	double* media_lenta = series(MovingAverage(seriesC(), periodo_lenta, tipo_media_lenta));
	*/
	double* media_rapida = series(EMA(seriesC(), periodo_rapida));
	double* media_lenta = series(EMA(seriesC(), periodo_lenta));
	medias[Asset] = media_lenta[0];

	if (!NumOpenTotal)
	{
		parcial[Asset] = 0;
	}


	if (crossOver(media_rapida, media_lenta)) {
		SetRisk(true);
		Stop = ATR(100) * 5;
		Trail = ATR(100);

		enterLong(tmf_medias);
	}

	else if (crossUnder(media_rapida, media_lenta)) {
		SetRisk(false);
		Trail = ATR(100);
		Stop = ATR(100) * 5;
		enterShort(tmf_medias);


	}

	plot("rapida", media_rapida, MAIN | LINE, BLUE);
	plot("lenta", media_lenta, MAIN | LINE, RED);

}