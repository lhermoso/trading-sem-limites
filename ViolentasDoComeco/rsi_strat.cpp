#include "pch.h"
#include <zorro.h>
#include "Bots.h"
#include "Risk.h"



void run_rsi()
{


	
	int periodo = (int)round(optimize(14, 7, 21, 3, 0));
	int compra = optimize(30, 5, 30, 5, 0);
	int venda = optimize(70, 70, 95, 5, 0);

	double* precos = series(TypPrice());

	double* rsi = series(RSI(precos, periodo));

	if (crossOver(seriesC(), compra))
	{
		
		SetRisk(true);
		
		enterLong();

	}
	else if (crossUnder(seriesC(), venda))
	{
		
		SetRisk(false);
		
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

	plot("RSI", rsi, NEW | LINE, BLUE);

	






}