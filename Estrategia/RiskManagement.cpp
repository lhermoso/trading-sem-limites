#include "pch.h"
#include "RiskManagement.h"
#include "zorro.h"



void SetRisk(bool ForLongTrade)
{
	SetRisk(1, ForLongTrade);
}

void SetRisk(const double& PercentToRisk, bool ForLongTrade)
{


	if (is(TRAINMODE)&& !is(FACTORS))
	{
		Lots = 1;

	}

	else if (!is(FACTORS))
	{
		Lots = 1;
	}

	else {

		
		double capital_disponivel = Capital / (sqrt(NumAssetsListed));

		double profit = ForLongTrade ? (WinLong - LossLong) : (WinShort - LossShort);
		profit = profit < 0 ? 0 : profit;
		capital_disponivel = capital_disponivel * sqrt(1 + profit / capital_disponivel) ;
		double margin = 0;
		if (ForLongTrade)
			margin = OptimalFLong * capital_disponivel;
		else
			margin = OptimalFShort * capital_disponivel;

		if (margin >= 0)
			Margin = margin;
		else
		{
			Lots = 0;
			Margin = 0;
		}
	
	}




}

