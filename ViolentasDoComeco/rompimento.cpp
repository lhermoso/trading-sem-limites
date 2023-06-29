#include "pch.h"
#include <zorro.h>
#include "Bots.h"
#include "Risk.h"


void run_rompimento()
{

	

	int periodo_compra = optimize(10, 5, 30, 5, 0);
	int periodo_venda = optimize(10, 5, 30, 5, 0);

	if (priceClose(0) > HH(periodo_compra, 1))
	{
		double minima = LL(periodo_compra, 1);
		double trail = priceClose(0) - minima;
		SetRisk(true);
		enterLong(0, 0, minima, 0, trail);
	}

	else if (priceClose(0) < LL(periodo_venda, 1))
	{
		double maxima = HH(periodo_venda, 1);
		double trail = maxima - priceClose(0);
		SetRisk(false);
		enterShort(0, 0, maxima, 0, trail);
	}


}