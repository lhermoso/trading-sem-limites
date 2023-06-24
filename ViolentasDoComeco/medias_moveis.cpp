#include "pch.h"
#include <zorro.h>
#include "Bots.h"


void run_medias()
{

	int periodo_rapida = optimize(9, 7, 21, 3, 0); 
	int periodo_lenta = optimize(22, 22, 39, 3, 0);
	/*
	int tipos_media[9] = { MAType_SMA, MAType_EMA, MAType_WMA, MAType_DEMA, MAType_TEMA, MAType_TRIMA, MAType_KAMA, MAType_MAMA, MAType_T3 };
	int tipo_media_rapida = tipos_media[(int)round(optimize(0, 1, 9, 1, 0))];
	int tipo_media_lenta = tipos_media[(int)round(optimize(0, 1, 9, 1, 0))];
	double* media_rapida = series(MovingAverage(seriesC(), periodo_rapida, tipo_media_rapida));
	double* media_lenta = series(MovingAverage(seriesC(), periodo_lenta, tipo_media_lenta));
	*/
	double* media_rapida = series(EMA(seriesC(), periodo_rapida));
	double* media_lenta = series(EMA(seriesC(), periodo_lenta));


	if (crossOver(media_rapida, media_lenta)) {

		enterLong();
	}

	else if (crossUnder(media_rapida, media_lenta)) {

		enterShort();


	}

}