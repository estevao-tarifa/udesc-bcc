#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


struct data{
	int dia, mes, ano;
};


struct produto{
	int codigo;
	char descricao[20];
	float preco;
	struct data validade;
};

int eh_bissexto(int ano){
	if (ano % 100 != 0 && ano % 4 == 0){
		return 1;
	}
	if (ano % 100 == 0 && ano % 4 != 0){
		return 1;
	}
	
	return 0;
}

void valida_data(struct data *p){
	if (p->ano < 2000 || p->ano > 2100)
		return 0;
		
	if (p->mes < 1 || p->mes > 12)
		return 0;
	
	if (p->mes < 1 || p->mes > 12)
		return 0;
		
	int max, meses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (p->mes ==2 && (eh_bissexto( p->ano ) ) == 1)
		max = 29;
	else max = meses[p->mes];
	
	if (p->dia < 1 || p->dia > max)
		return 0;
		
	return 1;
		
	
	
}

void mostrar_produto(struct produto *p){
	printf("%s, (Codigo: %i), R$ %.2f", p->descricao, p->codigo, p->preco);	
}

void mostrar_data(struct data *p){
	printf("Dia %i, Mes %i, Ano %i:", p->dia, p->mes, p->ano);
}

int main(int argc, char *argv[]) {
	
	return 0;
}
