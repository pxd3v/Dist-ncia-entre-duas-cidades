#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define nomeDaCidadeMaxLenght 21

struct estrada{
    char cidadeA[nomeDaCidadeMaxLenght];
    char cidadeB[nomeDaCidadeMaxLenght];
    int dist;
};

struct trajeto{
    char cidadeA[nomeDaCidadeMaxLenght];
    char cidadeB[nomeDaCidadeMaxLenght];
};
int len = 100;


int pegaIndexDaCidade(int _numeroDeVertices, char _array[_numeroDeVertices][nomeDaCidadeMaxLenght], char _cidade[nomeDaCidadeMaxLenght]){
    for(int i = 0; i < _numeroDeVertices; i++){
        if(strcmp(_array[i], _cidade) == 0)
        return i;
    }
    return 0;
}

// referencia: https://www.vivaolinux.com.br/script/Algoritmo-de-Dijkstra
int dijkstra(int vertices,int origem,int destino,int *custos, char _array[vertices][nomeDaCidadeMaxLenght])
{
   int i,v, cont = 0;
   int *ant, *tmp;  
   int *z;     /* vertices para os quais se conhece o caminho minimo */
   double min;
   double dist[vertices]; /* vetor com os custos dos caminhos */


   /* aloca as linhas da matriz */
   ant = calloc (vertices, sizeof(int *));
   tmp = calloc (vertices, sizeof(int *));
   if (ant == NULL) {
      printf ("** Erro: Memoria Insuficiente **");
      exit(-1);
   }

   z = calloc (vertices, sizeof(int *));
   if (z == NULL) {
      printf ("** Erro: Memoria Insuficiente **");
      exit(-1);
   }

   for (i = 0; i < vertices; i++) {
      if (custos[(origem - 1) * vertices + i] !=- 1) {
         ant[i] = origem - 1;
         dist[i] = custos[(origem-1)*vertices+i];
      }
      else {
         ant[i]= -1;
         dist[i] = HUGE_VAL;
      }
      z[i]=0;
   }
   z[origem-1] = 1;
   dist[origem-1] = 0;

   /* Laco principal */
   do {

      /* Encontrando o vertice que deve entrar em z */
      min = HUGE_VAL;
      for (i=0;i<vertices;i++)
         if (!z[i])
            if (dist[i]>=0 && dist[i]<min) {
               min=dist[i];v=i;
            }

      /* Calculando as distancias dos novos vizinhos de z */
      if (min != HUGE_VAL && v != destino - 1) {
         z[v] = 1;
         for (i = 0; i < vertices; i++)
            if (!z[i]) {
               if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i]) {
                     dist[i] = dist[v] + custos[v*vertices+i];
                  ant[i] =v;
                  }
              }
      }
   } while (v != destino - 1 && min != HUGE_VAL);

   /* Mostra o Resultado da busca */
   if (min == HUGE_VAL) {
      return 0;
   }
   else {
      i = destino;
      i = ant[i-1];
      while (i != -1) {
      //   printf("<-%d",i+1);
         tmp[cont] = i+1;
         cont++;
         i = ant[i];
      }
      printf("Menor percurso: ");
      for (i = cont; i > 0 ; i--) {
         printf("%s ", _array[tmp[i-1] - 1]);
      }
      printf("%s", _array[destino - 1]);

      return dist[destino-1];
   }
}

int lerNumero(FILE *_arquivo){
    char *aux = malloc(len);

	fscanf(_arquivo, "%s", aux);
    getc(_arquivo);

    int valor = atoi(aux);
    free(aux);
	return valor;
}

char lerChar(FILE *_arquivo){
    char aux = getc(_arquivo);

    getc(_arquivo);
	return aux; 
}

char * lerCidade(FILE *_arquivo){
    char *aux = malloc(nomeDaCidadeMaxLenght);
    fscanf(_arquivo, "%s", aux);
    getc(_arquivo);
    return aux;
}

int lerNumeroDeEstradas(FILE *_arquivo){
    return lerNumero(_arquivo);
}

struct estrada lerCidadesEDistancia(FILE *_arquivo){
    struct estrada aux;

    strcpy(aux.cidadeA, lerCidade(_arquivo));
    strcpy(aux.cidadeB, lerCidade(_arquivo));

    aux.dist = lerNumero(_arquivo);

	return aux; 
}

struct estrada * lerEstradas(FILE *_arquivo, int _numeroDeEstradas, struct estrada _estradas[]){
    struct estrada * aux = _estradas;
    for(int i = 0; i < _numeroDeEstradas; i++){
        aux[i] = lerCidadesEDistancia(_arquivo);
    }

    return aux;
}

int * gerarArrayDeCustos(int _nVertices, int _numeroDeEstradas, struct estrada _estradas[], char _cidades[_nVertices][nomeDaCidadeMaxLenght]){
    int * aux;
    int cont = -1;
    aux = (int *) malloc(sizeof(int)*_nVertices*_nVertices);
    
    for(int cidadeA = 0; cidadeA < _nVertices; cidadeA++){
        char auxA[nomeDaCidadeMaxLenght];
        strcpy(auxA, _cidades[cidadeA]);
        for(int cidadeB = 0; cidadeB < _nVertices; cidadeB++){
            char auxB[nomeDaCidadeMaxLenght];
            strcpy(auxB, _cidades[cidadeB]);
            for(int estrada = 0; estrada < _numeroDeEstradas; estrada++){
                // printf("%s %s %s %s %d\n", _estradas[estrada].cidadeA, auxA, _estradas[estrada].cidadeB, auxB, _estradas[estrada].dist);
                if((strcmp(_estradas[estrada].cidadeA, auxA) == 0 && strcmp(_estradas[estrada].cidadeB, auxB) == 0) || (strcmp(_estradas[estrada].cidadeA, auxB) == 0 && strcmp(_estradas[estrada].cidadeB, auxA) == 0 )){
                    cont = _estradas[estrada].dist;
                }
            }
            if(cont == -1){
                aux[cidadeA*_nVertices + cidadeB] = -1;   
            }else {
                aux[cidadeA*_nVertices + cidadeB] = cont;
                cont = -1;
            }
        }
    }
    
    return aux;
}

struct trajeto lerTrajeto(FILE *_arquivo){
    struct trajeto aux;
    strcpy(aux.cidadeA, lerCidade(_arquivo));
    strcpy(aux.cidadeB, lerCidade(_arquivo));
    return aux;
}

int contaVertices(struct estrada _estradas[], int _numeroDeEstradas){
    char aux[_numeroDeEstradas * 2][nomeDaCidadeMaxLenght];
    char saida[_numeroDeEstradas * 2][nomeDaCidadeMaxLenght];

    for(int i = 0, j = 0; i < _numeroDeEstradas; i++){
        strcpy(aux[j], _estradas[i].cidadeA);
        j++;
        strcpy(aux[j], _estradas[i].cidadeB);
        j++;
    }
    int n = 0;
    for(int i = 0; i < _numeroDeEstradas * 2; i++)
    {
        int j;
        int k = 0;
        for(j = 0; j < _numeroDeEstradas; j++){
            if(strcmp(aux[i], saida[j]) == 0){
                k++;
            }
            // printf("%s %d\n", saida[j], j);
        }
        if(k == 0){
            strcpy(saida[n], aux[i]);
            n++;
        }
    }
    
    return n;
}

void montaArrayDeCidades(struct estrada _estradas[], int _numeroDeEstradas, int _numeroDeVertices, char _array[_numeroDeVertices][nomeDaCidadeMaxLenght]){
    char aux[_numeroDeEstradas * 2][nomeDaCidadeMaxLenght];
    

    for(int i = 0, j = 0; i < _numeroDeEstradas; i++){
        strcpy(aux[j], _estradas[i].cidadeA);
        j++;
        strcpy(aux[j], _estradas[i].cidadeB);
        j++;
    }
    int k = 0;
    int n = 0;
    for(int i = 0; i <_numeroDeEstradas * 2; i++){
        k = 0;
        for(int j = 0; j < _numeroDeVertices; j++){
            if(strcmp(aux[i], _array[j]) == 0){
                k++;
            }
        }
        if(k == 0){
            strcpy(_array[n], aux[i]);

            n++;
        }
    }
    
}

void testaEntrada(struct estrada _estradas[], int _numeroDeEstradas, struct trajeto _trajeto){
    printf("%d \n", _numeroDeEstradas);

    for(int i = 0; i < _numeroDeEstradas; i++){
        printf("%s ", _estradas[i].cidadeA);
        printf("%s ", _estradas[i].cidadeB);
        printf("%d \n", _estradas[i].dist);
    }
    
    printf("%s %s \n", _trajeto.cidadeA, _trajeto.cidadeB);
}


int main() {

    // Abre o arquivo.
	char nomeDoArquivo[len];
    printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", nomeDoArquivo);
	FILE *arquivo = fopen(nomeDoArquivo, "r");
	if(!arquivo) {
	    printf("Erro na abertura do arquivo.\n");
	    return 0;
	}

    // Monta as estruturas de dados.
    int numeroDeEstradas = lerNumeroDeEstradas(arquivo);
    struct estrada estradas[numeroDeEstradas]; lerEstradas(arquivo, numeroDeEstradas, estradas);
    struct trajeto trajeto = lerTrajeto(arquivo);
    int nVertices = contaVertices(estradas, numeroDeEstradas);
    char cidades[nVertices][nomeDaCidadeMaxLenght];
    montaArrayDeCidades(estradas, numeroDeEstradas, nVertices, cidades);
    int *custos = NULL; custos = gerarArrayDeCustos(nVertices, numeroDeEstradas, estradas, cidades);


    int menorCaminho = dijkstra(nVertices, pegaIndexDaCidade(nVertices, cidades, trajeto.cidadeA) + 1,
                                            pegaIndexDaCidade(nVertices, cidades,trajeto.cidadeB) + 1, custos, cidades);

    printf("\nDistancia total: %d Km\n", menorCaminho);

    // testaEntrada(estradas, numeroDeEstradas, trajeto);
    // for(int i = 0; i < nVertices * nVertices; i++){
    //     printf("%d. %d\n", i+1, custos[i]);
    // }
    
	fclose(arquivo);
	return 0;
}

