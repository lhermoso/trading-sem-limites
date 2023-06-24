#include "pch.h"
#include <zorro.h>
#include "Bots.h"



void run_rsi()
{


	int periodo = (int)round(optimize(14, 7, 21, 3, 0));
	int compra = optimize(30, 5, 30, 5, 0);
	int venda = optimize(70, 70, 95, 5, 0);

	double* precos = series(TypPrice());

	double* rsi = series(RSI(precos, periodo));

	if (crossOver(seriesC(), compra))
	{
		enterLong();

	}
	else if (crossUnder(seriesC(), venda))
	{
		enterShort();
	}

	if (NumOpenLong && rsi[0] >= 50)
	{
		exitLong();
	}

	if (NumOpenShort && rsi[0] <= 50)
	{

		exitShort();
	}






}