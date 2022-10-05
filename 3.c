#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int faz_binario(int numero, int fator){
    if (numero == 0)
    {
        return 0;
    }
    return (numero % 2) * fator + faz_binario(numero/2, fator *10);
}

void binario_string (int numero, char *binario){
    int aux, j, digito; 
    aux = numero;
    memset(binario, '\0', 9);
    for ( j = 0; j < 8; j++)
    {   
        digito = aux % 10;
        if (digito == 0)
        {
            binario[8-1-j] = 'B';
        }
        else 
        {
            binario[8-1-j] = 'A';
        }
        aux = aux / 10;
        
    }
}


void nrz (int tamanho, int *numeros){
    int i; 
    char binario[9];
    for ( i = 0; i < tamanho; i++)
    {
        binario_string(numeros[i], binario);
        printf("%s", binario);
    }
}

void manchester (int tamanho, int *numeros, char sinal){
    int i, j, k, clock, digito; 
    char binario[9];
    
    clock = (sinal = 'A') ? 1 : 0;
    
    for ( i = 0; i < tamanho; i++)
    {
        binario_string(numeros[i], binario);
        for ( j = 0; j < 8; j++)
        {
            digito = (binario[j] == 'A')? 1 : 0;
            for ( k = 0 ; k < 2; k++)
            {   
                if ((digito^clock) == 1)
                {
                    printf("A");
                }
                else
                {
                    printf("B");
                }
                clock = (clock + 1) % 2;
            }  
        }
    }
}

void cod_4b5b (int tamanho, int *numeros){

}

void terceira_camada(int tamanho, int *numeros, char *codificacao, char sinal){
    int i;
    
    for (i = 0; i < tamanho; i++)
    {
        numeros[i] = faz_binario(numeros[i], 1);  
    }
    if (strcmp(codificacao, "NRZ")==0)
    {
        printf("%s %d ", codificacao, tamanho*8);
        nrz(tamanho, numeros);
    }
    if (strcmp(codificacao, "Manchester")==0)
    {
        printf("%s %c %d ", codificacao, sinal, tamanho*8*2);
        manchester(tamanho, numeros, sinal);
    }
    if (strcmp(codificacao, "4b5b")==0)
    {
        /* code */
    }
}

void segunda_camada(char *mensagem, char *codificacao, char sinal){

    int tamanho, *decimais, i;

    tamanho = strlen(mensagem);
    decimais = (int*) malloc(tamanho * sizeof(int));
    if (decimais == NULL)
    {
        exit(1);
    }
    for ( i = 0; i < tamanho; i++)
    {
        decimais[i] = mensagem[i];
    }
    terceira_camada(tamanho, decimais, codificacao, sinal);
}

void primeira_camada(){
    char mensagem[80], codificacao[11], sinal;
    scanf("%s", codificacao);
    
    if (strcmp(codificacao, "Manchester")==0)
    {
        scanf(" ");
        scanf("%c", &sinal);
    } 
    scanf(" ");
    scanf("%[^\n]s", mensagem);
    segunda_camada(mensagem, codificacao, sinal);
}


int main(){
    primeira_camada();
    return 0;
}