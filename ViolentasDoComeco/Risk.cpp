#include "pch.h"
#include "zorro.h"
#include "Risk.h"




void SetRisk(bool Compra)
{

	if (is(TRAINMODE) && !is(FACTORS))
	{

		Lots = 1;
		
	}
	else if (!is(FACTORS))
	{
		Lots = 1;
	

	}
	else {

		double pnl = Compra ? (WinLong - LossLong) : (WinShort - LossShort);
		double capital = Capital * sqrt(1 + (pnl / Capital));


		double capitalPorComponente = capital / sqrt(NumAssetsListed );
		double margin = (Compra ? OptimalFLong : OptimalFShort) * capitalPorComponente * 0.5;

		
		if (margin >= 0)
		{
			Margin = margin;

		}
		else {

			Lots = 0;
			Margin = 0;
		}







	}





}