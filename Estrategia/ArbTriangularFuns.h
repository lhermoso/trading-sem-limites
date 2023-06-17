#pragma once
#include "zorro.h"

class Triangular_Arb {


	string ASSET_A;
	string ASSET_B;
	string ASSET_C;
	double Corretagem = 0;
	double Gatilho = 20;
	double PrecoSintetico_Compra = 0;
	double PrecoSintetico_Venda = 0;
	void Calcular_Preco();
	void Calcular_Corretagem();
	int Checar_Sinal();
	void Comprar_Spread();
	void Vender_Spread();
	void Encerrar_Compra();
	void Encerrar_Venda();
public:
	void Operar();
	void ValorGatilho(double);
	Triangular_Arb(const string&, const string&, const string&);

};
