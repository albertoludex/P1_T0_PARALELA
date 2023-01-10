#include "funciones.c"
int main(int argc, char* argv[]){
    clock_t IG = clock();// Inicio global

    //Comprobamos los argumetnos
    if(argc==1){
        ImpInst();
        return 0;
    }
    if(atoi(argv[1])<1){
        printf("El numero de iteraciones no puede ser menor que 1\n");
        ImpInst();
        return 0;
    }
    

    
    //Establecemos la semilla para rellenar la matriz  con numeros pseudoaleatorios en funcion del reloj 
    srand(time(NULL));
    

    //DECLARACION DE VARIABLES
    //Vectores
    double* V0 = vector_create(TAMANO,1);
    double* V1 = vector_create(TAMANO,0);
    //Variables auxiliares e iteradores
    double abs;
    int i,j;
    int itera=atoi(argv[1]);
    //Resultados
    double t_matriz;
    double t_global;
    double t_ejecucion;
    double matrix;
    double* absolutos= vector_create(itera-1,0);

    clock_t IM = clock(); //Incio crear matiz
    double** M = matrix_create(TAMANO);
        matrix_rellena(M,TAMANO);
    clock_t FM = clock();  //Final crear matriz

    clock_t IE = clock();//Inicio ejecucion

    matrixxvector(M,V0,V1,TAMANO);//La iteración 1 no genera valor absoluto

    for(i=2;i<=itera;i++){
        if((i%2)==1){

            matrixxvector(M,V0,V1,TAMANO);
            abs= dividiendo(V1,TAMANO);
        }else{
            matrixxvector(M,V1,V0,TAMANO);
            abs= dividiendo(V0,TAMANO);
        }

        absolutos[i-2]=abs;
       
    }
    clock_t FE = clock(); //Fin ejecucion
    clock_t FG = clock(); //Fin global

t_matriz=(double)(FM-IM)/CLOCKS_PER_SEC;
t_ejecucion=(double)(FE-IE)/CLOCKS_PER_SEC;
t_global=(double)(FG-IG)/CLOCKS_PER_SEC;

ImpResultados(itera,absolutos,t_matriz,t_global,t_ejecucion);


}

