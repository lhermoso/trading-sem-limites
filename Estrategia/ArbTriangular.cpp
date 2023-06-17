#include "pch.h"
#include <string>
#include "zorro.h"
#include "ArbTriangularFuns.h"
#define ASSET_A "EURUSD_FXCM"
#define ASSET_B "GBPUSD_AAAFX"
#define ASSET_C "EURGBP_OANDA"


Triangular_Arb Player((string)ASSET_A, (string)ASSET_B, (string)ASSET_C);

DLLFUNC void tick()
{

	Player.Operar();

}

DLLFUNC void run()
{


	LookBack = 0;
	TickTime = 1;
	BarPeriod = 1;
	set(TICKS);
	assetList("AssetsArb.csv");
	int gatilho_pips = 20; 
	asset(ASSET_A);
	asset(ASSET_B);
	asset(ASSET_C);

	if (is(INITRUN))
	{
		Player.ValorGatilho(gatilho_pips);
	}
	
	
}
