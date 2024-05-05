#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
Tarea T;
struct Nodo *Siguiente;
}Nodo;

Nodo *crearListaVacia();
Nodo *crearTareas(int *id);
void insertarNodo(Nodo **pendientes, Nodo *nuevoNodo);
//void tareasRealizadas(Nodo **pendientes, Nodo **realizadas); sustitui por mover nodo
void mostrarTareas(Nodo *pendientes, Nodo *realizadas);
void mostarTareaEspecifica(Nodo *pendientes, Nodo *realizadas);
//void eliminarNodo(Nodo **pendientes, int id);
void moverNodo(Nodo **pendientes, Nodo **realizadas);

//**************INICIO DEL MAIN****************


int main(int argc, char const *argv[])
{ 
srand(time(NULL));    
    int control, id=1000;
    Nodo *nuevoNodo;
    Nodo *realizadas;
    Nodo *pendientes;

realizadas=crearListaVacia();
pendientes=crearListaVacia();

do
{
nuevoNodo= crearTareas(&id);
insertarNodo(&pendientes, nuevoNodo);
printf("\n Desea ingresar otra tarea 0: NO \n OTRO NUMERO: SI: \n");
scanf("%d", &control);
} while (control !=0);

//tareasRealizadas(&pendientes, &realizadas);
moverNodo(&pendientes, &realizadas);
mostrarTareas(pendientes, realizadas);
mostarTareaEspecifica(pendientes, realizadas);

    return 0;
}


//***************FIN DE MAIN*****************


Nodo *crearTareas(int *id){

char *buff= (char*)malloc(100 * sizeof(char));
Nodo *nuevoNodo= (Nodo *)malloc(sizeof(Nodo));
fflush(stdin);
printf("\n ingrese una descripcion de la tarea: ");
gets(buff);
fflush(stdin);
nuevoNodo->T.Descripcion=(char*)malloc((strlen(buff)+1)* sizeof(char));
strcpy(nuevoNodo->T.Descripcion,buff);
free(buff);
nuevoNodo->T.TareaID= (*id)++;
nuevoNodo->T.Duracion= rand()%50+1;
nuevoNodo->Siguiente = NULL;
return nuevoNodo;

}

Nodo *crearListaVacia(){

    return NULL;
}

void insertarNodo(Nodo **pendientes, Nodo *nuevoNodo){

nuevoNodo->Siguiente= *pendientes;
*pendientes= nuevoNodo;

}

void mostrarTareas(Nodo *pendientes, Nodo *realizadas){
    Nodo *auxP= pendientes;
    Nodo *auxR=realizadas;

    printf("\n *****TAREAS PENDIENTES***** \n"); 

    while (auxP != NULL)
    {
        printf("\n id Tarea: %d", auxP->T.TareaID);
        printf("\n Descripcion Tarea: %s", auxP->T.Descripcion);
        printf("\n Duracion Tarea: %d dias\n", auxP->T.Duracion);
        printf("\n***********\n");       
        auxP = auxP->Siguiente;
    }

    printf("\n *****TAREAS REALIZADAS***** \n");   

    while (auxR != NULL)
    {
        printf("\n id Tarea: %d", auxR->T.TareaID);
        printf("\n Descripcion Tarea: %s", auxR->T.Descripcion);
        printf("\n Duracion Tarea: %d dias\n", auxR->T.Duracion);
        printf("\n***********\n");       
        auxR = auxR->Siguiente;
    }

}

/*void tareasRealizadas(Nodo **pendientes, Nodo **realizadas){

    int id, ok;

    do
    {

            printf("\n Ingrese el id de la tarea realizada: ");
            scanf("%d", &id);

            Nodo *Aux = *pendientes;
            while(Aux && Aux->T.TareaID != id) 
            {
            Aux = Aux->Siguiente;
            }

            insertarNodo(realizadas, Aux);
            eliminarNodo(pendientes, id);

printf("\n desea agregar otra tarea 1-si\n 0-no ");
scanf("%d", &ok);
    } while (ok != 0);


}*/


void mostarTareaEspecifica(Nodo *pendientes, Nodo *realizadas) {
    int id;
    printf("\n Ingrese el id de la tarea deseada: ");
    scanf("%d", &id);

    Nodo *AuxP = pendientes;
    Nodo *AuxR = realizadas;

    // Buscar la tarea con el ID especificado en la lista de pendientes
    while (AuxP != NULL && AuxP->T.TareaID != id) {
        AuxP = AuxP->Siguiente;
    }

    // Buscar la tarea con el ID especificado en la lista de realizadas
    while (AuxR != NULL && AuxR->T.TareaID != id) {
        AuxR = AuxR->Siguiente;
    }

    if (AuxP != NULL && AuxP->T.TareaID == id) {
        printf("\n La tarea solicitada es una tarea PENDIENTE");
        printf("\n id Tarea: %d", AuxP->T.TareaID);
        printf("\n Descripcion Tarea: %s", AuxP->T.Descripcion);
        printf("\n Duracion Tarea: %d dias\n", AuxP->T.Duracion);
    } else if (AuxR != NULL && AuxR->T.TareaID == id) {
        printf("\n La tarea solicitada es una tarea REALIZADA");
        printf("\n id Tarea: %d", AuxR->T.TareaID);
        printf("\n Descripcion Tarea: %s", AuxR->T.Descripcion);
        printf("\n Duracion Tarea: %d dias\n", AuxR->T.Duracion);
    } else {
        printf("\n No se encontró una tarea con el ID especificado.\n");
    }
}




/*void eliminarNodo(Nodo **pendientes, int id){
    Nodo **aux = pendientes;

    while (*aux != NULL && (*aux)->T.TareaID != id)
    {
        aux = &(*aux)->Siguiente;
    }
    
    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;

        free(temp);
    }
    
}*/




void moverNodo(Nodo **pendientes, Nodo **realizadas) {
    int id, otra;
    do {
        printf("\nIngrese el ID de la tarea a mover a realizadas: ");
        scanf("%d", &id);

        Nodo *actual = *pendientes;
        Nodo *previo = NULL;

        // Buscar el nodo con el ID dado en la lista de pendientes
        while (actual != NULL && actual->T.TareaID != id) {
            previo = actual;
            actual = actual->Siguiente;
        }

        if (actual != NULL) {
            // Desenlazo el nodo de la lista de pendientes
            if (previo != NULL) {
                previo->Siguiente = actual->Siguiente;
            } else {
                *pendientes = actual->Siguiente;
            }

            // creo un nodo y copio los datos
            Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
            nuevoNodo->T.TareaID = actual->T.TareaID;
            nuevoNodo->T.Duracion = actual->T.Duracion;
            nuevoNodo->T.Descripcion = strdup(actual->T.Descripcion); // lafuncion hace la reserva de memora
            nuevoNodo->Siguiente = *realizadas;
            *realizadas = nuevoNodo;

           

            // Libero la memoria del nodo de pendientes
            free(actual->T.Descripcion);
            free(actual);
        } else {
            printf("\nNo se encontró una tarea con el ID especificado en la lista de pendientes.\n");
        }

        printf("\n¿Desea agregar otra tarea? (1: Sí, 0: No): ");
        scanf("%d", &otra);
    } while (otra != 0);
}



