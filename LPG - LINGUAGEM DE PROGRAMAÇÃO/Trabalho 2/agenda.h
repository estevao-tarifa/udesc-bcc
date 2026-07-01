#ifndef AGENDA_H
#define AGENDA_H

struct data{
	int dia, mes, ano;
};

struct horario{
	int hora, minuto;
};

struct evento{
	struct data data;
	struct horario inicio, fim;
	char descricao[50];
	char local[50];
};

int valida_data( struct data x );
int valida_horario( struct horario x );
int compara_data( struct data a, struct data b );
int compara_horario( struct horario a, struct horario b );
int sobrepoe( struct evento a, struct evento b );

void le_data( struct data *p );
void le_horario( struct horario *p );
void le_evento( struct evento *p );
void mostra_evento( struct evento x );

#endif
