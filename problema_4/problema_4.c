#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct NODO
{
    char *nombre;
    struct NODO *siguiente;
} NODO;

char *obtener_nombre();
int obtener_opcion();

void lista_agregar_final(NODO **);
void lista_eliminar(NODO **);
void lista_imprimir(NODO *);
void limpiar_lista(NODO **);

void antivirus(int dias);

int main()
{
    int opcion, dias;
    NODO *cabecera = NULL;

    do
    {
        system("cls");
        printf("ANTIVIRUS\n\n"
               "1.Ingresar contacto\n"
               "2.Eliminar contacto\n"
               "3.Imprimir lista de contactos\n"
               "4.Correr antivirus\n"
               "5.Salir\n\n");
        opcion = obtener_opcion();

        switch (opcion)
        {
        case 1:
            lista_agregar_final(&cabecera);
            break;
        case 2:
            lista_eliminar(&cabecera);
            break;
        case 3:
            lista_imprimir(cabecera);
            break;
        case 4:
            printf("\nIngrese el dia en que ocurrio el virus: ");
            dias = obtener_opcion();
            antivirus(dias);
            break;
        case 5:
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
    } while (opcion != 5);

    limpiar_lista(&cabecera);
    return 0;
}

// Validacion para obtener una cadena que solo contenga una palabra con letras del abecedario
char *obtener_nombre()
{
    char temp[256];
    int valida = 0;

    while (!valida)
    {
        valida = 1;
        fflush(stdin);
        printf("Ingrese un nombre: ");
        fflush(stdin);

        // Obtener TODO lo que haya en stdin
        fgets(temp, sizeof(temp), stdin);

        // Reemplazar '\n' por un '\0'
        temp[strcspn(temp, "\n")] = '\0';

        // Revisar espacios
        char *espacio = strchr(temp, ' ');
        if (espacio != NULL)
        {
            printf("ERROR. Se ingreso mas de un nombre. Oprima cualquier tecla");
            getchar();
            fflush(stdin);
            valida = 0;
        }

        // Revisar cadena vacia
        if (strlen(temp) == 0)
        {
            printf("ERROR. No se ingreso ningun nombre. Oprima cualquier tecla");
            getchar();
            fflush(stdin);
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
                printf("ERROR. El nombre no contiene solo letras. Oprima cualquier tecla");
                getchar();
                fflush(stdin);
                break;
            }
        }
    }
    // Reservar memoria exacta ahora que temp esta limpio
    // y podemos saber su tamaño exacto
    char *nombre = malloc(strlen(temp) + 1); // Se agrega uno para incluir el '\0'

    // Revisar alocacion de memoria
    if (nombre == NULL)
        return NULL;

    // Pasar palabra de variable estatica a string dinamica
    strcpy(nombre, temp);
    return nombre;
}

// Funcion para obtener numeros enteros positivos + 0
int obtener_opcion()
{
    char Aux[' '];
    int i, p, y, num;
    do
    {
        fflush(stdin);
        printf("\nIntroduzca una opcion: ");
        // scanf(" %s", Aux); // se lee los datos introducidos
        fgets(Aux, sizeof(Aux), stdin);
        Aux[strcspn(Aux, "\n")] = '\0';

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

// Agrega al final de una lista encadenada
void lista_agregar_final(NODO **cabecera)
{
    NODO *nuevo = malloc(sizeof(NODO));

    // Verificar que se haya alocado memoria
    if (nuevo == NULL)
    {
        printf("Error de alocacion de memoria de lista.\n");
        system("pause");
        return;
    }
    else
    {
        NODO *actual, *previo;
        previo = NULL;
        actual = *cabecera;

        // Recorre hasta llegar al final
        while (actual != NULL)
        {
            previo = actual;
            actual = actual->siguiente;
        }
        // La lista no tenia nodos
        if (previo == NULL)
        {
            nuevo->nombre = obtener_nombre();
            nuevo->siguiente = NULL;
            *cabecera = nuevo;
            printf("Se agrego correctamente el contacto %s\n", nuevo->nombre);
            system("pause");
            return;
        }
        // Tiene uno o mas nodos
        else
        {
            nuevo->nombre = obtener_nombre();
            nuevo->siguiente = NULL;
            previo->siguiente = nuevo;
            printf("Se agrego correctamente el contacto %s\n", nuevo->nombre);
            system("pause");
            return;
        }
    }
}

// Eliminar algun elemento de la lista
void lista_eliminar(NODO **cabecera)
{
    NODO *previo, *actual;
    actual = *cabecera;
    previo = NULL;
    char *nombre_a_buscar;

    // la lista esta vacia
    if (actual == NULL)
    {
        printf("ERROR: La lista esta vacia.\n");
        system("pause");
        return;
    }
    // La lista contiene al menos un elemento
    else
    {
        nombre_a_buscar = obtener_nombre();

        // Recorrer hasta que se acabe la lista o que encuentre le nombre
        while (actual != NULL && strcmp(actual->nombre, nombre_a_buscar) != 0)
        {
            previo = actual;
            actual = actual->siguiente;
        }

        // Caso de que no se hallo el nodo
        if (actual == NULL)
        {
            printf("No se encontro el contacto\n");
            system("pause");
            return;
        }

        // Caso de que el nodo a eliminar sea el unico nodo
        else if (actual->siguiente == NULL && previo == NULL)
        {
            free(actual);
            *cabecera = NULL;
            printf("Se elimino el contacto %s\nY se vacio la lista\n", nombre_a_buscar);
            system("pause");
            return;
        }
        // Caso de que el nodo a eliminar sea el primero
        else if (previo == NULL)
        {
            *cabecera = actual->siguiente;
            free(actual);
            printf("Se elimino el contacto %s\n", nombre_a_buscar);
            system("pause");
            return;
        }
        // Caso de que el nodo a eliminar sea el ultimo de la lista
        else if (actual->siguiente == NULL)
        {
            previo->siguiente = NULL;
            free(actual);
            printf("Se elimino el contacto %s\n", nombre_a_buscar);
            system("pause");
            return;
        }
        // Caso de que el nodo a eliminar este en medio de la lista
        else
        {
            previo->siguiente = actual->siguiente;
            free(actual);
            printf("Se elimino el contacto %s\n", nombre_a_buscar);
            system("pause");
            return;
        }
    }
}

// Funcion para imprimir toda la lista
void lista_imprimir(NODO *cabecera)
{
    NODO *actual = cabecera;
    if (actual == NULL)
    {
        printf("La lista esta vacia.\n");
    }
    else
    {
        while (actual != NULL)
        {
            printf(" %s ->", actual->nombre);
            actual = actual->siguiente;
        }
        printf(" NULL\n");
    }
    system("pause");
    system("cls");
}

// Recorrido y limpieza de lista encadenada
void limpiar_lista(NODO **cabecera)
{
    NODO *previo, *actual;
    previo = NULL;
    actual = *cabecera;

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
        *cabecera = NULL;
        return;
    }
}

void antivirus(int dias)
{
    int n=1;
}