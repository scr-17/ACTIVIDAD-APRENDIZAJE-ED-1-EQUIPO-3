#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo
{
    int dato;
    struct nodo *siguiente;
} NODO;

//int solicitar_entero();

void mostrar_lista(NODO *);

void insertar_aleatorio(NODO **);

void eliminar_superiores(NODO **);

//void vaciar_lista(NODO **);

int main()
{
    NODO *lista = NULL;
    int op;
    srand(time(NULL));

    do
    {
        printf("\t\tLISTAS ENLAZADAS CON NUMEROS ALEATORIOS (1-256)\n\n");
        printf("Ingrese una opcion del menu\n\n1) Ingresar un numero aleatorio\n");
        printf("2) Eliminar elementos mayores a un numero dado\n");
        printf("3) Imprimir la lista\n4) Salir del programa\n\n>");
        //op = solicitar_entero();
        scanf(" %d", &op);
        switch (op)
        {
        case 1:
            insertar_aleatorio(&lista);
            break;
        case 2:
            eliminar_superiores(&lista);
            break;
        case 3:
            mostrar_lista(lista);
            break;
        case 4:
            printf("\n\nFinalizando programa...\n");
            break;
        default:
            printf("\n\nOpcion invalida, favor de ingresar una valida por favor\n");
        }
        system("pause");
        system("cls");
    } while (op != 4);

    //vaciar_lista(&lista);

    return 0;
}

void mostrar_lista(NODO *lista)
{
    NODO *ptr = NULL;
    ptr = lista;
    while(ptr != NULL){
        printf("%d -->", ptr->dato);
        ptr = ptr->siguiente;
    }
}

void insertar_aleatorio(NODO **lista)
{
    int valor;
    valor = (rand() % 255) + 1;

    NODO *nuevo, *previo, *actual;
    nuevo = malloc(sizeof(NODO));
    if (nuevo != NULL)
    {
        nuevo->dato = valor;
        nuevo->siguiente = NULL;
        previo = NULL;
        actual = *lista;
        while (actual != NULL)
        {
            previo = actual;
            actual = actual->siguiente;
        }
        if (previo == NULL)
        {
            nuevo->siguiente = *lista;
            *lista = nuevo;
        }
        else
        {
            previo->siguiente = nuevo;
            nuevo->siguiente = actual;
        }
    }
}

void eliminar_superiores(NODO **lista)
{
    NODO *temporal = NULL, *previo = NULL, *actual = NULL, *posterior = NULL;

    previo = NULL;
    actual = *lista;
    posterior = (*lista)->siguiente;

    if (*lista == NULL)
    {
        printf("\nError. La lista esta vacia\n");
        return;
    }

    while (actual != NULL)
    {
        if (actual->dato < 67)
        {
            temporal = actual;
            if (previo == NULL)
            {
                *lista = posterior;
            }
            else
            {
                previo->siguiente = posterior;
            }
            actual = posterior;
            if (posterior != NULL)
                posterior = posterior->siguiente;

            free(temporal);
            continue;
        }

        previo = actual;
        actual = posterior;
        posterior = posterior->siguiente;
    }
}
