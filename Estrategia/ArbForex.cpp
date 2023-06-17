#include "pch.h"
#include <string>
#include "zorro.h"
#define ASSET_A "EURUSD_FXCM"
#define ASSET_B "EURUSD_AAAFX"

DLLFUNC void tick()
{
	asset(ASSET_A);
	double SpreadA = Spread;
	double PrecoA = priceClose(0); // VALOR DE ASK
	double CorretagemA = Commission * LotAmount / 10000 * PIP / PIPCost; // convertendo comissão para preço
	asset(ASSET_B);
	double SpreadB = Spread; 
	double PrecoB = priceClose(0); 
	double CorretagemB = Commission * LotAmount / 10000 * PIP / PIPCost;

	double Threshold = 1.5 * (SpreadA + SpreadB + CorretagemA + CorretagemB); // gatilho de arbitragem
	double ExitThreshold = Threshold / 2.0;
	double Difference = PrecoA - PrecoB;


	asset(ASSET_A);
	if (NumOpenShort && Difference < -ExitThreshold)
	{
		exitShort();
		asset(ASSET_B);
		exitLong();
	}
	else if (NumOpenLong && Difference > ExitThreshold)
	{
		exitLong();
		asset(ASSET_B);
		exitShort();
	}
	else if (!NumOpenShort && Difference > Threshold)	// vende o ativo mais caro 
	{
		
		enterShort();
		asset(ASSET_B);
		enterLong();

	}
	else if (!NumOpenLong && Difference < -Threshold) // compra o ativo mais barato
	{
		enterLong();
		asset(ASSET_B);
		enterShort();

	}

}

DLLFUNC void run()
{


	LookBack = 0;
	TickTime = 1;
	set(TICKS);
	assetList("AssetsArb.csv");
	asset(ASSET_A);
	asset(ASSET_B);
	priceClose(0); // ultimo preco negociado
}
