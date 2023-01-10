#include "funciones.h"

void ImpInst(){
    printf("para ejecutar el codigo debemos hacerlo del siguiente modo\n");
    printf("nuestro ejecutable  + iteraciones que queremos\n");

}

double ** matrix_create(int N){
 int i;
    double** matriz = (double**) malloc (N * sizeof(double*)); //array de punteros con N de tamaño
    for(i=0;i<N;i++){
        matriz[i]= (double*) malloc (N * sizeof(double)); //reserva de memo
    }

    return matriz;
}


//creamos vectores[N]  y iniciamos  a valor que luego pasaremos por valor
double* vector_create(int N, double ini){
    double* vect;
    int i;
    vect= (double*) malloc (N * sizeof(double)); 
    for(i=0;i<N;i++)
    vect[i]=ini;

    return vect;
}


//matriz*vector y guardamos en otro vector
void matrixxvector(double** matrix, double* vect_origen, double* vect_destino, int N){

    int i,j;
    double var=0;
    for(i=0;i<N;i++){ //bucle para filas
        var=0;
        for(j=0;j<N;j++){//bucle para columnas
        var+=vect_origen[j]*matrix[i][j];
        }
        vect_destino[i]=var; //recorremos la matriz fila a fila
      
    }
    
}

void matrix_rellena(double** matrix, int N){
    int i,j;
    time_t t;
    

    for(i=0;i<N;i++){ //Fila matriz
        for(j=0;j<N;j++){ //recorre filas
            if(i==j){ //diagonal
                matrix[i][j]=1;
            }
            else if(i>j){//Diagonal inferior
                matrix[i][j]= rand() / ((double) RAND_MAX)*50;
            }
            else{//Diagonal superior
                matrix[i][j]= rand() / ((double) RAND_MAX)*-50; 
            }
        }
    }



}

double dividiendo(double* vect, int N){
    int i;
    double temp=0;
    double valor_literal=25.0;
    

    //Recorre el vector y encuentra el máximo valor absoluto
    for(i=0;i<N;i++){
        if(sqrt(pow(vect[i],2))>temp){
            temp=sqrt(pow(vect[i],2));
        }
    }
    //divide el vector por el maximo valor absoluto
    for(i=0;i<N;i++){

        //lo comparamos con el valor literal 
        if (vect[i]>valor_literal)
        {
        vect[i]/temp;
        }
        
    }
    return temp;

}
int comp_fichero (char *fichero){
    FILE *f= fopen(fichero,"r");
    if (f==NULL){
        return 0;
        //Si no es un fichero devuelve 0 
    }
    fclose(f);
    return 1;
        //Si es un fichero devuelve 1
}


void ImpResultados(int itera,double* absolutes, double temp_matrix, double temp_glob, double temp_eje){
    char nombre[50];
    int contador=0;
    FILE *f;
    int i;
    
    sprintf(nombre,"Resultados_iteracion_%d.txt",itera);

     while(comp_fichero(nombre)==1){
        contador++;
        sprintf(nombre,"Resultados_iteracion_%d(%d).txt",itera,contador);
    }
   

    f=fopen(nombre,"w");
    fprintf(f,"Num de iteraciones: %d\n\n",itera);
    fprintf(f,"1º iter no da absoluto\n");
    for(i=0;i<itera-1;i++){
        fprintf(f,"Mayor absoluto iteración %d: ",i+2);
        fprintf(f,"%f  ",absolutes[i]);
        fprintf(f,"\n");
    }

    fprintf(f,"\n\ntiempo de generacion de la matriz: %f\n",temp_matrix);
    fprintf(f,"tiempo ejecucion: %f\n",temp_eje);
    fprintf(f,"Tiempo de todo, computo global: %f\n",temp_glob);

    fclose(f);

 
}
