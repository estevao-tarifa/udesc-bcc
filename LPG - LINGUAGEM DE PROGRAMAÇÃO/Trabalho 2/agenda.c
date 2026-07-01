#include "agenda.h"
#include <stdio.h>

int valida_data( struct data x ){
	int max, meses[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int bissexto = ( x.ano % 4 == 0 && x.ano % 100 != 0 ) || x.ano % 400 == 0;
	
	if( x.ano < 1 || x.mes < 1 || x.mes > 12 )
		return 0;
	
	max = meses[x.mes - 1];
	if( x.mes == 2 && bissexto )
		max = 29;
	
	return x.dia >= 1 && x.dia <= max;
}

int valida_horario( struct horario x ){
	return x.hora >= 0 && x.hora <= 23 && x.minuto >= 0 && x.minuto <= 59;
}

int compara_data( struct data a, struct data b ){
	if( a.ano != b.ano ) return a.ano - b.ano;
	if( a.mes != b.mes ) return a.mes - b.mes;
	return a.dia - b.dia;
}

int compara_horario( struct horario a, struct horario b ){
	if( a.hora != b.hora ) return a.hora - b.hora;
	return a.minuto - b.minuto;
}

int sobrepoe( struct evento a, struct evento b ){
	if( compara_data( a.data, b.data ) != 0 )
		return 0;
	
	return compara_horario( a.inicio, b.fim ) < 0 &&
		   compara_horario( a.fim, b.inicio ) > 0;
}

void le_data( struct data *p ){
	printf("Dia: ");
	scanf("%d", &p->dia);
	printf("Mes: ");
	scanf("%d", &p->mes);
	printf("Ano: ");
	scanf("%d", &p->ano);
}

void le_horario( struct horario *p ){
	printf("Hora: ");
	scanf("%d", &p->hora);
	printf("Minuto: ");
	scanf("%d", &p->minuto);
}

void le_evento( struct evento *p ){
	printf("Data:\n");
	le_data( &p->data );
	printf("Horario de inicio:\n");
	le_horario( &p->inicio );
	printf("Horario de fim:\n");
	le_horario( &p->fim );
	printf("Descricao: ");
	scanf(" %49[^\n]", p->descricao);
	printf("Local: ");
	scanf(" %49[^\n]", p->local);
}

void mostra_evento( struct evento x ){
	printf("%02d/%02d/%04d - %02d:%02d ate %02d:%02d - %s - %s\n",
		x.data.dia, x.data.mes, x.data.ano,
		x.inicio.hora, x.inicio.minuto,
		x.fim.hora, x.fim.minuto,
		x.descricao, x.local);
}
