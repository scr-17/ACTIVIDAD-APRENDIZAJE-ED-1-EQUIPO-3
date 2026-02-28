#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

//declaracion de la estructura de un nodo
struct nodo {
	char valor;
	struct nodo *siguiente;
};

typedef struct nodo nodo ;
typedef nodo *nodoSig;

int descifrarMensaje(char cadena[]);			//funcion que lleva a cabo la logica para descifrar el mensaje
char insertar(nodoSig *pila, char valor);		//funcion empleada para insertar un nuevo nodo en la pila 
char sacar(nodoSig *pila);						//funcion empleada para eliminar el ultimo nodo de la pila
int leerOpcion();								
int validarCadena(char cadena[]);				//funcion que valida la entrada de una cadena cifrada

int main(){
	char cadena[255];
	int opc = 1;
	while(opc == 1){
		system("cls");
		printf("INGRESE UN MENSAJE CIFRADO: ");
		fgets(cadena, sizeof(cadena), stdin);
	    cadena[strcspn(cadena, "\n")] = '\0';
	    if(validarCadena(cadena)){				//verificar que la cadena sea valida
	    	descifrarMensaje(cadena);			//llamar a la funcion para descifrar el mensaje
		}
		else printf("\nla cadena ingresada no es valida\n\n");
		printf("\ndesea ingresar un nuevo  mensaje cifrado\n1- si\n2- no\n-> ");
		opc = leerOpcion();
		system("pause");
	}
}

int descifrarMensaje(char cadena[]){
	nodoSig pila = NULL;					//se declara una pila vacia
	char mensaje[255], auxMsj[255];			//se declara una cadena para el mensaje y una variable auxiliar
	int i = 0;
	while(cadena[i] != '\0'){				//recorre mientras el dato de la cadena no sea un valor nulo
		if(cadena[i] != ')'){               //se insertan todos los elementos en una pila hasta encontrar un parentesis derecho
			insertar(&pila,cadena[i]);
		}
		else{
			int j = 0;
			while(pila != NULL && pila->valor != '('){			//si el dato es un parentesis derecho se recorre la pila 
				auxMsj[j] = pila->valor;						//cada dato de la pila se alamacena en una variable auxiliar
				sacar(&pila);									//se elimina el ultimo dato de la pila
				j++;
			}													//el proceso sigue hasta encontrar un parentesis izquierdo
			sacar(&pila);										//se elimina el parentesis izquierdo
			auxMsj[j] = '\0';									
			j = 0;
			while(auxMsj[j] != '\0'){							//se alamacena cada caracter de la variable auxiliar en la pila
				insertar(&pila,auxMsj[j]);
				j++;
			}
		}
		i++;
	}
	i = 0;
	while(pila != NULL){										//vaciar la pila en una nueva cadena
		mensaje[i] = pila->valor;
		sacar(&pila);
		i++;
	}
	mensaje[i] = '\0';  									
	int len = strlen(mensaje);
	char aux;
	for(i = 0; i < len/2; i++){									//invertir la cadena 
		aux = mensaje[i];
		mensaje[i] = mensaje[len - i -1];
		mensaje[len - i -1] = aux;
	}
	mensaje[len] = '\0';
	printf("\n\nEL MENSADE DECIFRADO DICE: %s\n\n",mensaje);
}

int validarCadena(char cadena[]){								
	int i = 0, balance = 0;
	if(cadena[0] == '\0') return 0;							//retorna 0 si la cadena esta vacia
	while(cadena[i] != '\0'){								//repite mientras el dato no sea un valor nulo
		if(cadena[i] == '('){								//si la cadena es un parentesis izquierdo el balance de parentesis aumenta
			balance++;										
			if(cadena[i + 1] == ')') return 0;				//si el siguiente caracter es un parentesis derecho retorna 0;
		}
		if(cadena[i] == ')'){								//si la cadena es un parentesis derecho el balance de parentesis disminuye
			balance--;
			if(balance < 0) return 0;						// si hay mas parentesis derechos que izquierdos retorna 0
		}
		i++;
	}
	
	if(balance == 0) return 1;
	else return 0;
}

int leerOpcion() 
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
    if(num == 1 || num == 2) return num;
    else{
    	printf("\nINGRESA UNA OPCION VALIDA\n"); return leerOpcion();		//uso de recursion para validar que el numero este entre 1 y 2
	} 
}

char insertar(nodoSig *pila, char valor){
	nodoSig nuevo = malloc(sizeof(nodo));							//Reservar memoria para nuevo nodo
	nuevo->valor = valor;											//Asignar el nuevo valor			
	nuevo->siguiente = NULL;
	if (*pila != NULL){												//si la pila no esta vacia inserta un nuevo nodo y se conecta con el nodo anterior
		nuevo->siguiente = *pila;	
		*pila = nuevo;
	}
	else{															//si la pila esta vacia se agrega el nuevo nodo
		*pila = nuevo;
	}
	return valor;
}

char sacar(nodoSig *pila){
	if(*pila != NULL){												//si la pila no esta vacia elimina el ultimo nodo
		nodoSig temp;
		temp = *pila;
		char valor = temp->valor; 
		*pila = (*pila)->siguiente;
		free(temp);
		return valor;
	}
	else return '\0';
}
