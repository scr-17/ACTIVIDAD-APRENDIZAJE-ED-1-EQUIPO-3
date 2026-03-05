#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct nodo
{
    int dato;
    struct nodo *siguiente;
} NODO;

/*Funcion para solicitar y validar la entrada de enteros*/
int solicitarEntero();

/*Funcion para imprimir una lista enlazada*/
void mostrarLista(NODO *);

/*Funcion para ingresar un elemento a la lista enlazada,
    estos se insertan por el final y son aleatorios*/
void insertarAleatorio(NODO **);

/*Funcion para eliminar todos los elementos superiores
    a un valor ingresado por el usuario*/
void eliminarSuperiores(NODO **);

/*Funcion para vaciar la lista al finalizar el programa,
    evitando fugas de memoria*/
void vaciarLista(NODO **);

int main()
{
    NODO *lista = NULL;
    int op;
    /*Se inicializa una semilla para los numeros aleatorios,
    determinando su orden de aparicion*/
    srand(time(NULL));

    do
    {
        printf("\t\tLISTAS ENLAZADAS CON NUMEROS ALEATORIOS (1-100)\n\n");
        printf("Ingrese una opcion del menu\n\n1) Ingresar un numero aleatorio\n");
        printf("2) Eliminar elementos mayores a un numero dado\n");
        printf("3) Imprimir la lista\n4) Salir del programa\n\n>");
        op = solicitarEntero();
        switch (op)
        {
        case 1:
            insertarAleatorio(&lista);
            break;
        case 2:
            eliminarSuperiores(&lista);
            break;
        case 3:
            mostrarLista(lista);
            break;
        case 4:
            printf("\nFinalizando programa...\n\n");
            break;
        default:
            printf("\n\nOpcion invalida, favor de ingresar una valida por favor\n");
        }
        system("pause");
        system("cls");
    } while (op != 4);

    vaciarLista(&lista);

    return 0;
}

/*En esta funcion, solicitamos que el usuario ingrese un numero entero.
    Si no se puede leer de forma correcta, se repite el flujo hasta que
    el usuario ingrese uno correcto*/
int solicitarEntero()
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

/*Recorremos la lista con un ciclo hasta encontrar el nodo final,
    mientras se imprime cada nodo que vayamos encontrando*/
void mostrarLista(NODO *lista)
{
    if (lista == NULL)
    {
        printf("\nLista vacia\n\n");
        return;
    }
    NODO *ptr = NULL;
    ptr = lista;

    printf("\n");
    while (ptr != NULL)
    {
        printf("%d --> ", ptr->dato);
        ptr = ptr->siguiente;
    }
    printf("NULL\n\n");
}

/*Insertamos por el final un nodo en la lista enlazada, aqui
    tambien le asignamos el numero aleatorio a este*/
void insertarAleatorio(NODO **lista)
{
    int valor;

    NODO *nuevo, *previo, *actual;
    nuevo = malloc(sizeof(NODO));
    if (nuevo != NULL)
    {
        /*Generamos un numero aleatorio que le daremos de valor*/
        valor = (rand() % 99) + 1;
        nuevo->dato = valor;
        nuevo->siguiente = NULL;
        previo = NULL;
        actual = *lista;
        /*Recorremos la lista hasta encontrar el ultimo nodo*/
        while (actual != NULL)
        {
            previo = actual;
            actual = actual->siguiente;
        }
        /*Si no recorrio nada, osea, si es el primer elemento*/
        if (previo == NULL)
        {
            *lista = nuevo;
        }
        /*Si es cualquier otro elemento*/
        else
        {
            previo->siguiente = nuevo;
            nuevo->siguiente = NULL;
        }

        printf("\nLista actualizada:\n");
        mostrarLista(*lista);
    }
}

void eliminarSuperiores(NODO **lista)
{
    int limite, bandera = 0;
    NODO *temporal = NULL, *previo = NULL, *actual = NULL, *posterior = NULL;

    /*En caso de lista vacia*/
    if (*lista == NULL)
    {
        printf("\nError. La lista esta vacia\n\n");
        return;
    }

    /*Solicitamos un limite para borrar los nodos con menor valor*/
    printf("Ingrese un numero: ");
    limite = solicitarEntero();

    /*Por medio de tres punteros de trabajo, recorremos la lista*/
    previo = NULL;                   /*El puntero del nodo directamente atras del que borraremos*/
    actual = *lista;                 /*El puntero del nodo que borraremos*/
    posterior = (*lista)->siguiente; /*El puntero del nodo despues del que borraremos*/

    /*Recorremos mientras el nodo a borrar no sea NULL*/
    while (actual != NULL)
    {
        /*En caso de que el numero caiga en las condiciones requeridas*/
        if (actual->dato > limite)
        {
            bandera = 1;       /*Utilizamos una bandera para ver si se elimino algun numero*/
            temporal = actual; /*Utilizamos un puntero de apoyo para eliminarlo sin perder el puntero de actual*/
            /*En caso de que sea el primer elemento*/
            if (previo == NULL)
            {
                *lista = posterior;
            }
            /*Caso contrario*/
            else
            {
                previo->siguiente = posterior;
            }
            /*Movemos los punteros para adelante*/
            actual = posterior;
            if (posterior != NULL) /*Verificamos que el puntero posterior no sea null para evitar errores*/
                posterior = posterior->siguiente;

            /*Liberamos memoria del puntero a eliminar*/
            free(temporal);
        }
        /*Caso contrario*/
        else
        {
            /*Recorremos los punteros al siguiente*/
            previo = actual;
            actual = posterior;
            if (posterior != NULL)
                posterior = posterior->siguiente;
        }
    }

    /*En caso de que se eliminara al menos un elemento*/
    if (bandera)
    {
        printf("\nNumeros eliminados con exito, lista actualizada:\n");
        mostrarLista(*lista);
    }
    /*Caso contrario*/
    else
    {
        printf("\nNo se encontraron numeros a eliminar, la lista se mantiene igual\n\n");
    }
}

/*Utilizamos esta funcion para vaciar la lista evitando fugas de memoria*/
void vaciarLista(NODO **lista)
{
    /*Si la lista esta vacia, no hacemos nada*/
    if (*lista == NULL)
        return;

    /*Puntero de trabajo para eliminar nodos*/
    NODO *temporal = NULL;

    /*Recorremos hasta encontrar el ultimo elemento*/
    while (*lista != NULL)
    {
        temporal = *lista;
        *lista = (*lista)->siguiente;
        free(temporal);
    }
}
