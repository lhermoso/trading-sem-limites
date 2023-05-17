#include "pch.h"
#include <map>
#include "bots.h"
#include <list>
#include <string>
#include <zorro.h>

#include "RiskManagement.h"




void MediaMovel()
{


	

	int periods_high_buy = optimize(9, 7, 20, 3, 0);
	int periods_high_sell = optimize(40, 22, 56, 3, 0);
	

	int periods_low_sell = optimize(9, 5, 30, 5, 0);
 	//int periods_low_buy = optimize(21, 22, 35, 5, 0);
	



	double* alma_high_sell = series(ALMA(series(priceHigh(0)), periods_high_sell));
	double* alma_high_buy = series(ALMA(series(priceHigh(0)), periods_high_buy));
	double* alma_low_sell = series(ALMA(series(priceLow(0)), periods_low_sell));

	
	//double* alma_low_buy = series(ALMA(series(priceLow(0)), periods_low_buy));



	//Compra
	//Média Rápida => Minimas
	//Média Lenta => Máximas
	if (alma_high_buy[0] > alma_high_sell[0] )
	{
		//exitShort();
		SetRisk(true);
		enterLong();

	}

	else if (crossUnder(alma_high_buy, alma_high_sell))
	{


		exitLong();
	}

	//Venda
	//Media Rápida => Máximas
	//Média Lenta => Minimas 
	/*if (crossUnder(alma_high_sell, alma_low_sell))
	{
		exitLong();
		SetRisk(false);
		enterShort();


	}

	if (crossOver(alma_high_sell, alma_low_sell))
	{
		exitShort();


	}*/

	plot("HIGH_BUY", alma_high_buy, LINE | NEW, RED);
	plot("HIGH_SELL", alma_high_sell, LINE, GREEN);
	
	plot("ALMA_HIGH_SELL", alma_high_sell, LINE | NEW, BLUE);
	plot("LOW_SELL", alma_low_sell, LINE, CYAN);

}