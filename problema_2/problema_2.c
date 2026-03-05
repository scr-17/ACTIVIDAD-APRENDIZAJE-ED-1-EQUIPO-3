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

char *obtener_palabra();
int obtener_opcion();

int verificar_palindromo();

void lista_agregar_final(NODO_LISTA **, char caracter);
char lista_pop_primero(NODO_LISTA **);
void limpiar_lista(NODO_LISTA **);

void pila_agregar(NODO_PILA **, char caracter);
char pila_pop(NODO_PILA **);
void limpiar_pila(NODO_PILA **);

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

// Validacion para obtener una cadena que solo contenga una palabra con letras del abecedario
char *obtener_palabra()
{
    char temp[256];
    int valida = 0;

    while (!valida)
    {
        valida = 1;
        fflush(stdin);
        getchar(); // obtener el '\n' que hubo anteriormente
        printf("Ingrese una palabra: ");
        fflush(stdin);

        // Obtener TODO lo que haya en stdin
        fgets(temp, sizeof(temp), stdin);

        // Reemplazar '/n' por un '\0'
        temp[strcspn(temp, "\n")] = '\0';

        // Revisar espacios
        char *espacio = strchr(temp, ' ');
        if (espacio != NULL)
        {
            printf("ERROR. Se ingreso mas de una palabra. Oprima cualquier tecla");
            valida = 0;
        }

        // Revisar cadena vacia
        if (strlen(temp) == 0)
        {
            printf("ERROR. No se ingreso ninguna palabra. Oprima cualquier tecla");
            valida = 0;
        }

        // Validar que todas sean letras del abecedario
        // o que sean espacios (aunque no sean validos, el error se atrapa en condicional anterior)
        int i;
        for (i = 0; temp[i] != '\0'; i++)
        {
            if (!isalpha(temp[i]) && temp[i] != ' ')
            {
                valida = 0;
                printf("ERROR. La palabra no contiene solo letras. Oprima cualquier tecla");
                break;
            }
        }
    }
    // Reservar memoria exacta ahora que temp esta limpio
    // y podemos saber su tamaño exacto
    char *palabra = malloc(strlen(temp) + 1); // Se agrega uno para incluir el '\0'

    // Revisar alocacion de memoria
    if (palabra == NULL)
        return NULL;

    // Pasar palabra de variable estatica a string dinamica
    strcpy(palabra, temp);
    return palabra;
}

// Funcion para obtener numeros enteros positivos + 0
int obtener_opcion()
{
    char Aux[' '];
    int i, p, y, num;
    do
    {
        printf("\nIntroduzca una opcion: ");
        fflush(stdin);
        scanf(" %s", Aux); // se lee los datos introducidos
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

// Funcion principal para verificar si una palabra es palindromo
int verificar_palindromo()
{
    NODO_LISTA *cabecera_lista = NULL;
    NODO_PILA *cabecera_pila = NULL;
    char *cadena = obtener_palabra();
    int es_palindromo = 1, i = 0;

    // printf("cadena: %s\nlargo:%d\nprimero: %c\nultimo:%c\n", cadena, strlen(cadena), cadena[0], cadena[strlen(cadena) - 1]);

    // agregar cadena a pila y a lista.
    // En la pila se agrega al reves, de derecha a izquierda
    // En la lista se agrega en orden, de izquiera a derecha
    while (cadena[i] != '\0')
    {
        pila_agregar(&cabecera_pila, cadena[i]);
        lista_agregar_final(&cabecera_lista, cadena[i]);
        i++;
    }

    // Hace pop a lista y a pila simultaneamente, compara los caracteres y cambia la bandera si no son iguales
    for (i = 0; i < strlen(cadena); i++)
    {
        if (pila_pop(&cabecera_pila) != lista_pop_primero(&cabecera_lista))
        {
            es_palindromo = 0;
            break;
        }
    }

    limpiar_lista(&cabecera_lista);
    limpiar_pila(&cabecera_pila);
    free(cadena);

    if (es_palindromo)
        printf("SI ES PALINDROMO\n");
    if (!es_palindromo)
        printf("NO ES PALINDROMO\n");
    system("pause");
    return es_palindromo;
}

// Agrega al final de una lista encadenada
void lista_agregar_final(NODO_LISTA **cabecera_lista, char caracter)
{
    NODO_LISTA *nuevo = malloc(sizeof(NODO_LISTA));

    // Verificar que se haya alocado memoria
    if (nuevo == NULL)
    {
        printf("Error de alocacion de memoria de lista.\n");
        system("pause");
        return;
    }
    else
    {
        NODO_LISTA *actual, *previo;
        previo = NULL;
        actual = *cabecera_lista;
        while (actual != NULL)
        {
            previo = actual;
            actual = actual->siguiente;
        }
        // La lista no tenia nodos
        if (previo == NULL)
        {
            nuevo->caracter = caracter;
            nuevo->siguiente = NULL;
            *cabecera_lista = nuevo;
            return;
            // Tiene uno o mas nodos
        }
        else
        {
            nuevo->caracter = caracter;
            nuevo->siguiente = NULL;
            previo->siguiente = nuevo;
            return;
        }
    }
}

// Pop al inicio de una lista encadenada
char lista_pop_primero(NODO_LISTA **cabecera_lista)
{
    // la lista esta vacia
    if (*cabecera_lista == NULL)
    {
        printf("ERROR: La lista esta vacia.\n");
        system("pause");
        return '\0';
    }
    else
    {
        NODO_LISTA *temporal;
        char caracter;
        temporal = *cabecera_lista;
        *cabecera_lista = temporal->siguiente;
        caracter = temporal->caracter;
        free(temporal);
        return caracter;
    }
}

// Recorrido y limpieza de lista encadenada
void limpiar_lista(NODO_LISTA **cabecera_lista)
{
    NODO_LISTA *previo, *actual;
    previo = NULL;
    actual = *cabecera_lista;

    // La lista esta vacia
    if (actual == NULL)
        return;

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

// Agrega al inicio de una lista encadenada
void pila_agregar(NODO_PILA **cabecera_pila, char caracter)
{
    NODO_PILA *nuevo = malloc(sizeof(NODO_PILA));

    // Verificar que se haya alocado memoria
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

// Recorrido y limpieza de lista encadenada
void limpiar_pila(NODO_PILA **cabecera_pila)
{
    NODO_PILA *previo, *actual;
    previo = NULL;
    actual = *cabecera_pila;

    // La lista esta vacia
    if (actual == NULL)
        return;

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