#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define TAMANIO 100

typedef struct nodo {
    int dato;
    struct nodo *siguiente;
}nodo;
typedef nodo *nodosig;

int solicitar_entero();
nodosig cola_aleatoria();
int insertar_cola(nodosig *cola, int dato);
void sub_cola(nodosig cola, nodosig *cola_destino);
void imprimir_cola(nodosig cola);
void vaciar_cola(nodosig *cola);

int main() {

    int op;
    nodosig cola_principal = cola_aleatoria();
    nodosig cola_negativos = NULL;

    do{
        printf("\n\t\tCREACION Y EXTRACCION, COLAS ALEATORIAS");
        printf("\n\t1. Imprimir elementos de la cola principal");
        printf("\n\t2. Formar una segunda cola con los numeros negativos");
        printf("\n\t3. Imprimir elementos de la sub-cola");
        printf("\n\t4. Salir\n\t>");
        op = solicitar_entero();

        switch(op) 
        {
            case 1: 
                imprimir_cola(cola_principal);
                break;
            case 2: 
                vaciar_cola(&cola_negativos);
                sub_cola(cola_principal, &cola_negativos);
                printf("\nSub-cola generada exitosamente\n");
                imprimir_cola(cola_negativos);
                break;
            case 3:
                imprimir_cola(cola_negativos);
                break;
            case 4:
                printf("\nFinalizando programa...\n");
                vaciar_cola(&cola_principal);
                vaciar_cola(&cola_negativos);
                break;
            default:
                printf("\nOpcion no valida\n");
        }
        system("pause");
        system("cls");
    }while(op != 4);

    return 0;
}

/*Funcion que inserta elementos por la cola(el final)*/
int insertar_cola(nodosig *cola, int dato){
    nodosig nuevo;
    nuevo = malloc(sizeof(nodo));

    if(nuevo == NULL) return 0;
    nuevo->dato = dato;
    nuevo->siguiente = NULL;

    if( *cola == NULL) {
        *cola = nuevo;
    }else{
        nodosig actual = *cola;
        while(actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    return 1;
}


void sub_cola(nodosig cola, nodosig *cola_destino){
    nodosig actual = cola   ;
    while(actual != NULL) {
        if(actual->dato < 0) {
            insertar_cola(cola_destino, actual->dato);
        }
        actual = actual->siguiente;
    }
}

void vaciar_cola(nodosig *cola) {
    nodosig temporal;
    while(*cola != NULL) {
        temporal = *cola;
        *cola = (*cola)->siguiente;
        free(temporal);
    }
}


nodosig cola_aleatoria() {

    nodosig cola = NULL;
    int i, min = -25, max = 25;

    srand(time(NULL));
    for(i = 0; i < TAMANIO; i++) {
        int num = (rand() % (max - min + 1)) + min; 
        insertar_cola(&cola, num);
    }
    return cola;
}

void imprimir_cola(nodosig cola){

    if(cola == NULL){
        printf("La cola se encuentra vacia");
        return;
    }

    nodosig actual = cola;
    while(actual != NULL) {
        printf("[%d] ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

int solicitar_entero()
{
    char Aux[' '];
    int i, p, y, num;
    do
    {
        fflush(stdin);
        scanf(" %s", Aux); // se lee los datos introducidos
        fflush(stdin);
        y = strlen(Aux);

        for (i = 0; i < y; i++)
        {
            if (isdigit(Aux[i])) /*Con una bandera valida que el caracter leido de una cadena sea un digito*/
                p = 1;
            else
                p = 0;

            if (p == 0)
            {
                printf("\nError de lectura\nFavor de introducir un numero correcto: ");
                break;
            }
        }
        if (y == 0)
            p = 0;
    } while (p == 0);

    num = atoi(Aux); /*Regresa la conversion de la cadena introducida a un digito */
    return num;
}
