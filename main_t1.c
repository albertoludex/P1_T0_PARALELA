#include "funciones.c"
int main(int argc, char* argv[]){
    //revisamos args
    if(compara_argumentos(argc, argv)==1){
        Error();
        return 0;
    }

    //en este apartado lo que estamos haciendo es declarar las variables
    char* fichero = argv[1];
    int apartados, i;
    unsigned char ** matriz1;
    unsigned char ** matriz2;
    int ancho = atoi(argv[2]);
    int largo = atoi(argv[3]);
    char * name;
    double tiempo;



    //funcion crea matriz y introduce la imagen en esta matriz
    matriz1=matriz_creacion(ancho,largo);
    if(matriz1==NULL){
        printf("Error haciendo la matriz");
        return 0;
    }




    //funcion que guarda matriz con filtrado
    matriz2=matriz_creacion(ancho,largo);
    if(matriz2==NULL){
        printf("error haciendo la matriz");
        return 0;
    }


    //cargar imagen en memo
    matriz_load(fichero,ancho,largo,matriz1);

    options();
    scanf("%d",&apartados);

    clock_t Inicializar;
    clock_t Finalizar;



    //tenemos un switch donde hemos metido los tres casos que nos pide la practica, media mediana y sobel y dependiendo de cual queramos
    //ejecutara un caso u otro.
    switch(apartados){ 
        case 1: //nuestro caso para la creacion de la media con su funcion calcular media

            Inicializar= clock();
            media_calculate(matriz1, matriz2,ancho,largo);
            Finalizar = clock();
            img_create_raw(matriz2,"media.raw",ancho,largo);
        break;



        case 2: //nuestro caso para la creacion de la mediana con su funcion calcular mediana
            Inicializar= clock();
            mediana_calculate(matriz1, matriz2,ancho,largo);
            Finalizar = clock();
            img_create_raw(matriz2,"mediana.raw",ancho,largo);
        break;



        case 3: //nuestro caso para el sobel con su funcion calcular sobel
            Inicializar= clock();
            sobel_calculate(matriz1, matriz2,ancho,largo);
            Finalizar = clock();
            img_create_raw(matriz2,"sobel.raw",ancho,largo);
        break;



        //en caso de que no exista un de los tres comandos para cada una de los switch, nos da un error
        default:
            printf("no existe el comando, por favor reintente otro");
            return 0;
        break;
    }





    //tiempo de ejecucion y sacamos resultados de ancho, largo fichero, el caso del switch y el tiempo que tenemos de ejecucion.
    tiempo=(double)(Finalizar-Inicializar)/CLOCKS_PER_SEC;
    print_results(ancho,largo,fichero,apartados,tiempo);
    
}