#include "pch.h"
#include <zorro.h>
#include "Bots.h"
#include "Risk.h"


double* rsi;
int periodo_saida;
int tmf()
{
	if (TradeIsOpen)
	{
		if (TradeIsLong)
		{
			if (rsi[0] >= 50 )
			{
		
			TradeStopLimit = max(TradeStopLimit, LL(periodo_saida, 0));
			  
			}


		}

		else
		{
			if (rsi[0] <= 50)
			{
				TradeStopLimit = min(TradeStopLimit, HH(periodo_saida, 0));
			}
		}
	
	}
	//plot("Stop", TradeStopLimit, MAIN, BLACK);

	return 0;

}


void run_rsi()
{


	
	int periodo = (int)round(optimize(14, 7, 21, 3, 0));
	int compra = optimize(30, 5, 30, 5, 0);
	int venda = optimize(70, 70, 95, 5, 0);
	periodo_saida = optimize(3, 1, 5, 1, 0);

	double* precos = series(TypPrice());
	
	rsi = series(RSI(precos, periodo));

	if (crossOver(rsi, compra))
	{
		OrderDelay = 10;
		SetRisk(true);
		Stop = ATR(100) * 2;
		Trail = ATR(100);
		TrailLock = 30;
		enterLong(tmf);

	}
	else if (crossUnder(rsi, venda))
	{
		OrderDelay = 10;
		SetRisk(false);
		TrailLock = 30;
		Stop = ATR(100) * 2;
		Trail = ATR(100);
		enterShort(tmf);
	}
	
	
	
	/*
	plot("RSI", rsi, NEW | LINE, BLUE);
	plot("venda", venda, LINE, RED);
	plot("compra", compra, LINE, RED);
	plot("saida", 50, LINE, RED);*/
	

	






}