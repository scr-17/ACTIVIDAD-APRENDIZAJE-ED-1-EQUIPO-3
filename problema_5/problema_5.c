#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

struct NODO {
	char valor;
	struct NODO *siguiente;
};

typedef struct NODO NODO ;
typedef NODO *nodosig;

int desifrarMensaje(char cadena[]);

char insertar(nodosig *pila, char valor){
	nodosig nuevo = malloc(sizeof(NODO));
	nuevo->valor = valor;
	nuevo->siguiente = NULL;
	if (*pila != NULL){
		nuevo->siguiente = *pila;
		*pila = nuevo;
	}
	else{
		*pila = nuevo;
	}
}

char sacar(nodosig *pila){
	if(*pila != NULL){
		nodosig temp;
		temp = *pila;
		*pila = (*pila)->siguiente;
		free(temp);
	}
	else return 0;
}

int main(){
	char cadena[255];
	printf("INGRESA UN MENSAJE CIFRADO: ");
	fgets(cadena, sizeof(cadena), stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
	desifrarMensaje(cadena);
	system("pause");
}

int desifrarMensaje(char cadena[]){
	nodosig pila = NULL;
	char mensaje[255], auxMsj[255];
	int i = 0;
	while(cadena[i] != '\0'){
		if(cadena[i] != ')'){
			insertar(&pila,cadena[i]);
		}
		else{
			int j = 0;
			while(pila != NULL && pila->valor != '('){
				auxMsj[j] = pila->valor;
				sacar(&pila);
				j++;
			}
			sacar(&pila);
			auxMsj[j] = '\0';
			j = 0;
			while(auxMsj[j] != '\0'){
				insertar(&pila,auxMsj[j]);
				j++;
			}
		}
		i++;
	}
	i = 0;
	while(pila != NULL){
		mensaje[i] = pila->valor;
		sacar(&pila);
		i++;
	}
	mensaje[i] = '\0';  
	int len = strlen(mensaje);
	char aux;
	for(i = 0; i < len/2; i++){
		aux = mensaje[i];
		mensaje[i] = mensaje[len - i -1];
		mensaje[len - i -1] = aux;
	}
	mensaje[len] = '\0';
	printf("\n%s\n",mensaje);
}

