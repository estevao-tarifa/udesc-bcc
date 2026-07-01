#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

int main(){
	struct evento *v = NULL, novo;
	struct data data_busca;
	struct horario hora_busca;
	FILE *f;
	int n = 0, i, j, opcao, posicao, achou, pode;
	char descricao_busca[50];
	
	f = fopen( "agenda.txt", "rt" );
	if( f != NULL ){
		fscanf( f, "%d", &n );
		if( n > 0 )
			v = malloc( sizeof( struct evento ) * n );
		
		for( i = 0 ; i < n ; i++ ){
			fscanf( f, "%d %d %d", &v[i].data.dia, &v[i].data.mes, &v[i].data.ano );
			fscanf( f, "%d %d", &v[i].inicio.hora, &v[i].inicio.minuto );
			fscanf( f, "%d %d", &v[i].fim.hora, &v[i].fim.minuto );
			fscanf( f, " %49[^\n]", v[i].descricao );
			fscanf( f, " %49[^\n]", v[i].local );
		}
		fclose( f );
	}
	
	do{
		printf("\n1-cadastrar\n2-mostrar todos\n3-buscar por data\n4-buscar por descricao\n5-remover\n6-sair\n");
		printf("Opcao: ");
		scanf("%d", &opcao);
		
		switch( opcao ){
			case 1:
				le_evento( &novo );
				
				if( !valida_data( novo.data ) || !valida_horario( novo.inicio ) ||
					!valida_horario( novo.fim ) || compara_horario( novo.inicio, novo.fim ) >= 0 ){
					printf("Data ou horario invalido.\n");
					break;
				}
				
				pode = 1;
				for( i = 0 ; i < n ; i++ )
					if( sobrepoe( novo, v[i] ) )
						pode = 0;
				
				if( !pode ){
					printf("Esse evento sobrepoe outro evento.\n");
					break;
				}
				
				posicao = n;
				for( i = 0 ; i < n ; i++ ){
					if( compara_data( novo.data, v[i].data ) < 0 ||
						( compara_data( novo.data, v[i].data ) == 0 &&
						  compara_horario( novo.inicio, v[i].inicio ) < 0 ) ){
						posicao = i;
						break;
					}
				}
				
				n++;
				v = realloc( v, sizeof( struct evento ) * n );
				for( i = n - 1 ; i > posicao ; i-- )
					v[i] = v[i - 1];
				v[posicao] = novo;
				printf("Evento cadastrado.\n");
				break;
				
			case 2:
				if( n == 0 )
					printf("Agenda vazia.\n");
				else
					for( i = 0 ; i < n ; i++ )
						mostra_evento( v[i] );
				break;
				
			case 3:
				le_data( &data_busca );
				achou = 0;
				for( i = 0 ; i < n ; i++ )
					if( compara_data( data_busca, v[i].data ) == 0 ){
						mostra_evento( v[i] );
						achou = 1;
					}
				if( !achou )
					printf("Nenhum evento encontrado.\n");
				break;
				
			case 4:
				printf("Descricao: ");
				scanf(" %49[^\n]", descricao_busca);
				achou = 0;
				for( i = 0 ; i < n ; i++ )
					if( strcmp( descricao_busca, v[i].descricao ) == 0 ){
						mostra_evento( v[i] );
						achou = 1;
					}
				if( !achou )
					printf("Nenhum evento encontrado.\n");
				break;
				
			case 5:
				le_data( &data_busca );
				printf("Horario inicial:\n");
				le_horario( &hora_busca );
				
				achou = 0;
				for( i = 0 ; i < n ; i++ ){
					if( compara_data( data_busca, v[i].data ) == 0 &&
						compara_horario( hora_busca, v[i].inicio ) == 0 ){
						for( j = i ; j < n - 1 ; j++ )
							v[j] = v[j + 1];
						n--;
						if( n == 0 ){
							free( v );
							v = NULL;
						}
						else
							v = realloc( v, sizeof( struct evento ) * n );
						achou = 1;
						printf("Evento removido.\n");
						break;
					}
				}
				if( !achou )
					printf("Evento nao encontrado.\n");
				break;
			
			case 6:
				break;
			
			default:
				printf("Opcao invalida.\n");
		}
	}while( opcao != 6 );
	
	f = fopen( "agenda.txt", "wt" );
	fprintf( f, "%d\n", n );
	for( i = 0 ; i < n ; i++ ){
		fprintf( f, "%d %d %d\n", v[i].data.dia, v[i].data.mes, v[i].data.ano );
		fprintf( f, "%d %d\n", v[i].inicio.hora, v[i].inicio.minuto );
		fprintf( f, "%d %d\n", v[i].fim.hora, v[i].fim.minuto );
		fprintf( f, "%s\n", v[i].descricao );
		fprintf( f, "%s\n", v[i].local );
	}
	fclose( f );
	free( v );
	
	return 0;
}
