#include "pch.h"
#include <string>
#include "zorro.h"
#include "ArbTriangularFuns.h"


Triangular_Arb::Triangular_Arb(const string& ASSET_A, const string& ASSET_B, const string& ASSET_C)
	: ASSET_A(ASSET_A), ASSET_B(ASSET_B), ASSET_C(ASSET_C)
{
	
	

}

void Triangular_Arb::ValorGatilho(double Gatilho)
{
	asset(ASSET_C);
	this->Gatilho = Gatilho * PIP; 
}

void Triangular_Arb::Calcular_Preco()
{
	asset(ASSET_A);
	PrecoSintetico_Compra = priceClose(0); //Preco do melhor vendedor
	PrecoSintetico_Venda = priceClose(0) - Spread; //Preco do melhor comprador
	asset(ASSET_B);
	PrecoSintetico_Compra /= (priceClose(0) - Spread);  //Preco do melhor comprador
	PrecoSintetico_Venda /= priceClose(0); //Preco do melhor vendedor
	PrecoSintetico_Compra += Corretagem;
	PrecoSintetico_Venda -= Corretagem;

}

void Triangular_Arb::Calcular_Corretagem()
{
	Corretagem = 0;
	asset(ASSET_A);
	Corretagem = Commission * LotAmount / 10000 * PIP / PIPCost;
	asset(ASSET_B);
	Corretagem += Commission * LotAmount / 10000 * PIP / PIPCost;
	asset(ASSET_C);
	Corretagem += Commission * LotAmount / 10000 * PIP / PIPCost;
}
int Triangular_Arb::Checar_Sinal()
{
	Calcular_Corretagem();
	Calcular_Preco();
	asset(ASSET_C);

	double diferenca_compra = (priceClose(0) - Spread) - PrecoSintetico_Compra;
	if (diferenca_compra >= Gatilho)
		return 1;
	
	if (diferenca_compra <= -Gatilho / 2.0)
		return 2;
	
	double diferenca_venda = PrecoSintetico_Venda-priceClose(0);

	if (diferenca_venda >= Gatilho)
		return -1;

	if (diferenca_venda <= -Gatilho / 2.0)
		return -2;


	return 0;
}

void Triangular_Arb::Comprar_Spread()
{
	asset(ASSET_A);
	enterLong();
	asset(ASSET_B);
	enterShort();
	asset(ASSET_C);
	enterShort();

}

void Triangular_Arb::Vender_Spread()
{
	asset(ASSET_A);
	enterShort();
	asset(ASSET_B);
	enterLong();
	asset(ASSET_C);
	enterLong();
}

void Triangular_Arb::Encerrar_Compra()
{
	asset(ASSET_A);
	if (NumOpenLong)
	{
		exitLong();
		asset(ASSET_B);
		exitShort();
		asset(ASSET_C);
		exitShort();
	}
}

void Triangular_Arb::Encerrar_Venda()
{
	asset(ASSET_A);
	if (NumOpenShort)
	{
		exitShort();
		asset(ASSET_B);
		exitLong();
		asset(ASSET_C);
		exitLong();
	}
}



void Triangular_Arb::Operar()
{




	switch (Checar_Sinal()) {
	case 1:
		Comprar_Spread();
		break;
	case 2:
		Vender_Spread();
		break;
	case -1:
		Encerrar_Compra();
		break;
	case -2:
		Encerrar_Venda();
		break;

	}


}

