#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct nodo_pila
{
    char caracter;
    struct nodo_pila *siguiente;
} NODO_PILA;

typedef struct nodo_lista
{
    char caracter;
    struct nodo_lista *siguiente;
} NODO_LISTA;

char obtener_cadena();
int obtener_opcion();

int verificar_palindromo();

void lista_agregar_final(NODO_LISTA *, char caracter);
char lista_pop_primero(NODO_LISTA **);
void limpiar_lista(NODO_LISTA **);
void imprimir_lista(NODO_LISTA *);

void pila_agregar(NODO_PILA **, char caracter);
char pila_pop(NODO_PILA **);
void limpiar_pila(NODO_PILA **);
void imprimir_pila(NODO_PILA *);

int main()
{
    int opcion;

    do
    {
        system("cls");
        printf("VERIFICADOR DE PALINDROMOS\n\n"
               "1.Verificar una cadena\n"
               "2.Salir\n");
        opcion = obtener_opcion();

        switch (opcion)
        {
        case 1:
            verificar_palindromo();
            break;
        case 2:
            system("cls");
            printf("Saliendo del programa...\n");
            system("pause");
            break;
        default:
            printf("ERROR. Opcion invalida.\n");
            system("pause");
            system("cls");
            break;
        }
    } while (opcion != 2);

    return 0;
}

// POR IMPLEMENTAR
// CAMBIAR DE LECTURA DE CARACTER A LECTURA DE CADENAS
char obtener_cadena()
{
    char Aux[' '];
    do
    {
        printf("\nIntroduzca un caracter: ");
        fflush(stdin);
        scanf(" %s", Aux); // se leen los datos introducidos
        fflush(stdin);

        if (strlen(Aux) == 1 && isalpha(Aux[0]))
        {
            return Aux[0];
        }
        else
        {
            printf("\n\n Error, dato mal introducido\n\n ");
            system("pause");
        }
    } while (1);
}

int obtener_opcion()
{
    char Aux[' '];
    int i, p, y, num;
    do
    {
        printf("\nIntroduzca una opcion: ");
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
                printf("\nERROR. El dato no es un numero entero positivo.\n");
                break;
            }
        }
        if (y == 0)
            p = 0;
    } while (p == 0);

    num = atoi(Aux); /*Regresa la conversion de la cadena introducida a un digito */
    return num;
}

int verificar_palindromo()
{
    NODO_LISTA *cabecera_lista = NULL;
    NODO_PILA *cabecera_pila = NULL;

    limpiar_lista(&cabecera_lista);
    limpiar_pila(&cabecera_pila);
    return 1;
}

void lista_agregar_final(NODO_LISTA *cabecera_lista, char caracter)
{
}

char lista_pop_primero(NODO_LISTA **)
{
}

void limpiar_lista(NODO_LISTA **cabecera_lista)
{
    NODO_LISTA *previo, *actual;
    previo = NULL;
    actual = *cabecera_lista;

    // La lista esta vacia
    if (actual == NULL)
    {
        return;
    }

    // La lista contiene al menos un elemento
    else
    {
        while (actual != NULL)
        {
            previo = actual;
            actual = actual->siguiente;
            free(previo);
        }
        *cabecera_lista = NULL;
        return;
    }
}

void imprimir_lista(NODO_LISTA *)
{
}

// Agrega al inicio de una lista encadenada
void pila_agregar(NODO_PILA **cabecera_pila, char caracter)
{
    NODO_PILA *nuevo = malloc(sizeof(NODO_PILA));

    // Verificar que se halla alocado memoria
    if (nuevo == NULL)
    {
        printf("Error de alocacion de memoria de pila.\n");
        system("pause");
        return;
    }
    else
    {
        nuevo->caracter = caracter;
        nuevo->siguiente = *cabecera_pila;
        *cabecera_pila = nuevo;
        return;
    }
}

// Pop al inicio de una lista encadenada
char pila_pop(NODO_PILA **cabecera_pila)
{
    // la pila esta vacia
    if (*cabecera_pila == NULL)
    {
        printf("ERROR: La pila esta vacia.\n");
        system("pause");
        return '\0';
    }
    else
    {
        NODO_PILA *temporal;
        char caracter;
        temporal = *cabecera_pila;
        *cabecera_pila = temporal->siguiente;
        caracter = temporal->caracter;
        free(temporal);
        return caracter;
    }
}

void limpiar_pila(NODO_PILA **cabecera_pila)
{
    NODO_PILA *previo, *actual;
    previo = NULL;
    actual = *cabecera_pila;

    // La lista esta vacia
    if (actual == NULL)
    {
        return;
    }

    // La lista contiene al menos un elemento
    else
    {
        while (actual != NULL)
        {
            previo = actual;
            actual = actual->siguiente;
            free(previo);
        }
        *cabecera_pila = NULL;
        return;
    }
}

void imprimir_pila(NODO_PILA *)
{
}