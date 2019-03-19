#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
    char letra;
    struct lista *prox;
}TLSE;

TLSE *insere(char caracter, TLSE *inicio){
    TLSE *novo = (TLSE *) malloc(sizeof(TLSE));
    novo->letra = caracter;//Acho que tem q usar strcpy
    novo->prox = NULL;

    if(!inicio){
        inicio = novo;
        return inicio;
    }

    else if(!inicio->prox){
        inicio->prox = novo;
        return inicio;
    }

    TLSE*aux = inicio;
    while(aux->prox)
        aux = aux->prox;

    aux->prox = novo;
    return inicio;
}

void libera(TLSE *inicio){
    if(inicio->prox)
        libera(inicio->prox);
    free(inicio);
}

int compara(TLSE *inicio, char *palavra){
    int tam = strlen(palavra);
    TLSE*aux = inicio;
    int i = 0;
    while(i<tam && aux){
        if(aux->letra == palavra[i]){
            aux= aux->prox;
            i++;
        }
        else
            return 0;
    }
    return 1;
}

void imprimeLista(TLSE *inicio){
    if(!inicio)
        return;
    printf("%c->", inicio->letra);
    imprimeLista(inicio->prox);
}

TLSE* separador(char*palavra, TLSE *inicio){
    int tam = strlen(palavra);
    for(int i = 0; i<tam;i++)
        inicio = insere(palavra[i], inicio);

    return inicio;
}

int contador(TLSE *inicio, char *modelo){
    FILE *fp = fopen("biblia","r");
    if(!fp){
        printf("Deu Ruim!");
        exit(1);
    }

    char palavra[32];
    char ch;
    int aux, i = 0, resultado = 0;

    while((ch = fgetc(fp)) != EOF){

        aux = (int) ch;

        if((aux >64 && aux < 91) || (aux>96 && aux < 122)){
            printf("%c", ch);
            palavra[i] = ch;
            i++;
            }
        else{
            inicio = separador(palavra, inicio);
            if(inicio){
                resultado += compara(inicio, modelo);
                strcpy(palavra,"");
                i = 0;
                libera(inicio);
                inicio = NULL;
                }
            printf("\n\n");
            }
        }
    fclose(fp);
    return resultado;
}

int main()
{
    TLSE *inicio = NULL;
    char modelo[] = "Jesus";
    printf("\nInforme a palavra: ");
    //scanf("%s", modelo);
    //getchar();
    printf("%s aparece %d vezes!", modelo, contador(inicio, modelo));
    return 0;
}
