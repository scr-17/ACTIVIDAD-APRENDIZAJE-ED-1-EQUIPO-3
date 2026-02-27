#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/*
EJEMPLOS ENTRADAS VALIDAS:
	Olimpia(am(nfor)I ed (da))tica
	pro(gar)macion
	la (mi se (p(ali)s) sal ed acigol)portante  
	ethan es un (o(a(ai(eyt)red)n)c) ejemplar
	y(f(z(rp (an(je(el m) y)or )m)o)a)e
*/

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
	int opc = 1;
	while(opc == 1){
		system("cls");
		printf("INGRESE UN MENSAJE CIFRADO: ");
		fgets(cadena, sizeof(cadena), stdin);
	    cadena[strcspn(cadena, "\n")] = '\0';
	    if(validarCadena(cadena)){
	    	desifrarMensaje(cadena);
		}
		else printf("\nla cadena ingresada no es valida\n\n");
		printf("\ndesea ingresar un nuevo  mensaje cifrado\n1- si\n2- no\n-> ");
		opc = leer_opcion();
		system("pause");
	}
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
	printf("\n\nEL MENSADE DECIFRADO DICE: %s\n\n",mensaje);
}

int validarCadena(char cadena[]){
	int i = 0, balance = 0;
	if(cadena[0] == '\0') return 0;
	while(cadena[i] != '\0'){
		if(cadena[i] == '('){
			balance++;
			if(cadena[i + 1] == ')') return 0;
		}
		if(cadena[i] == ')'){
			balance--;
			if(balance < 0) return 0;
		}
		i++;
	}
	
	if(balance == 0) return 1;
	else return 0;
}

int leer_opcion()
{
	int valor;
	int valido = 0;

	do
	{
		if (scanf("%d", &valor) == 1 && (valor == 2 || valor == 1))
			valido = 1;
		else
		{
			printf("\nIngrese una opcion valida\n-> ");
			valido = 0;
		}
		while (getchar() != '\n')
			;
	} while (!valido);

	return valor;
}

