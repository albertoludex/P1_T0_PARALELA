#include "funciones.h"

//aqui tenemos el menu con las opciones que tenemos en el ej1
void options(){
    printf("\nImagen cargada\n");
    printf("Ahora ponga una de las siguientes opciones que se le presentan a continuacion\n\n");
    printf("1. MEDIA\n");
    printf("2. MEDIANA\n");
    printf("3. SOBEL\n");
}
void ejec_info(){
    printf("para ejecutar el codigo debera hacerlo de la siguiente manera: name_main + <img_name + Ancho img + Largo img\n");

}
void Error(){
    printf("ERROR PARAMETROS");
    ejec_info();
}

//vemos los parametros

int compara_argumentos(int argc, char* argv[]){
    FILE *f= fopen(argv[1],"r");
    if(argc!=4){
        
        return 1; 
    }
    if(f==NULL){
        return 1;
    }
    fclose(f);
    return 0; //Si todo es correcto devuelve 0
}



void matriz_load(char* fichero, int ancho, int largo, unsigned char** matriz){

    FILE *f = fopen (fichero, "rb");	
    unsigned char linea[ancho];
	int i,j;
	
	for(i=0;i<largo;i++)
	{
	    fread(matriz[i], sizeof(linea), 1, f); //Leemos fichero y almacenamos en matriz
      
    }    
    fclose(f);

    
}

unsigned char** matriz_creacion(int ancho, int largo){
    int i;
    unsigned char** matriz = (unsigned char**) malloc (largo * sizeof(unsigned char*)); //array de puntero para largo
    for(i=0;i<largo;i++){
        matriz[i]= (unsigned char*) malloc (ancho * sizeof(unsigned char)); //aray de puntero para ancho
    }
    return matriz;
}

unsigned char media (unsigned char ** matriz, int x, int y){
    int media=0;
    unsigned char resultado;
    //esquina sup iz
    media+=  matriz[x-1][y-1] ;
    //mitad superior
    media += matriz[x][y-1];
    //esquina sup derecha
    media+= matriz[x+1][y-1] ;
    //mitad izquierda
    media+= matriz[x-1][y] ;
     //elemento
    media+= matriz[x][y] ;
    //mitad derechaecha
    media+= matriz[x+1][y];
    //esquina inf izquierda
    media+= matriz[x-1][y+1] ;
    //centro inf
    media+= matriz[x][y+1] ;
    //esq inf derecha
    media+= matriz[x+1][y-1] ;
    resultado=media/9;
    return resultado;
}

void media_calculate(unsigned char** matriz, unsigned char** matriz_2, int ancho, int largo){
    int i,j;
    memcpy(matriz_2[0],matriz[0], ancho * sizeof(unsigned char)); //pasamos de la fila inicial

    for(i=1;i<largo-1;i++){ //Recorremos filas de la mat, pasando de la primera
        for(j=0;j<ancho;j++){ //elemento a elemento
            if(j==0||j==ancho-1){ //pasamos del primer elemento de cada fila
                matriz_2[i][j]=matriz[i][j];
            }
            else{
                matriz_2[i][j]=media(matriz,i,j);
            }

        }
    }

    memcpy(matriz_2[largo-1],matriz[largo-1], ancho * sizeof(unsigned char)); //obtenemos la ultima fila

   



}
void mediana_calculate(unsigned char** matriz,unsigned char** matriz_2, int ancho, int largo){

    int i,j;
    memcpy(matriz_2[0],matriz[0], ancho * sizeof(unsigned char));

    for(i=1;i<largo-1;i++){
        for(j=0;j<ancho;j++){
            if(j==0||j==ancho-1){
                matriz_2[i][j]=matriz[i][j];
            }
            else{
                matriz_2[i][j]=mediana(matriz,i,j);
            }

        }
    }
     memcpy(matriz_2[largo-1],matriz[largo-1], ancho * sizeof(unsigned char));

   

}

//qs usada en p0
void qs(unsigned char list[],int limite_izquierdauierdo,int limite_drcho){

    int izquierda,derecha;
    unsigned char temp,pivot;
    izquierda=limite_izquierdauierdo;
    derecha = limite_drcho;
    pivot = list[(izquierda+derecha)/2];
 
    do{
        while(list[izquierda]<pivot && izquierda<limite_drcho)izquierda++;
        while(pivot<list[derecha] && derecha > limite_izquierdauierdo)derecha--;
        if(izquierda <=derecha)
        {

            temp= list[izquierda];
            list[izquierda]=list[derecha];
            list[derecha]=temp;
            izquierda++;
            derecha--;


        }
 
    }while(izquierda<=derecha);
    if(limite_izquierdauierdo<derecha){qs(list,limite_izquierdauierdo,derecha);}
    if(limite_drcho>izquierda){qs(list,izquierda,limite_drcho);}

 
}



unsigned char mediana(unsigned char ** matriz,int x, int y){
    unsigned char elements[9];


    //esquina sup iz
    elements[0]= matriz[x-1][y-1];
    //mitad superior
    elements[1]= matriz[x][y-1];
    //esquina sup derecha
    elements[2]= matriz[x+1][y-1];
    //mitad izquierda
    elements[3]= matriz[x-1][y];
     //elemento
    elements[4]= matriz[x][y];
    //mitad derechaecha
    elements[5]= matriz[x+1][y];
    //esquina inf izquierda
    elements[6]= matriz[x-1][y+1];
    //centro inf
    elements[7]= matriz[x][y+1];
    //esq inf derecha
    elements[8]= matriz[x+1][y-1];

    qs(elements,0,8);//qs organiza los elements del array

    return elements[4];//cogemos el elemento de en medio
   

}
void sobel_calculate (unsigned char** matriz, unsigned char** matrix2, int ancho, int largo){
    int i,j;

    memcpy(matrix2[0],matriz[0], ancho * sizeof(unsigned char));

    for(i=1;i<largo-1;i++){
        for(j=0;j<ancho;j++){
            if(j==0||j==ancho-1){
                matrix2[i][j]=matriz[i][j];
            }
            else{

                matrix2[i][j]=sobel(matriz,i,j);
            }

        }
    }
     memcpy(matrix2[largo-1],matriz[largo-1], ancho * sizeof(unsigned char));

}

unsigned char sobel(unsigned char** matriz,int x, int y){
     int c=0;
     int f=0;
     unsigned char j;
     //esquina sup iz
    f= matriz[x-1][y-1]*-1;
    c= matriz[x-1][y-1]*-1;
    //mitad superior
    f= f+ matriz[x][y-1]*0;
    c= c+ matriz[x][y-1]*-2;
    //esquina sup derecha
    f= f+ matriz[x+1][y-1]*1;
    c= c+ matriz[x+1][y-1]*-1;
    //mitad izquierda
    f= f+ matriz[x-1][y]*-2;
    c= c+ matriz[x-1][y]*0;
     //elemento
    f= f+ matriz[x][y]*0;
    c= c+ matriz[x][y]*0;
    //mitad derecha
    f= f+ matriz[x+1][y]*2;
    c= c+ matriz[x+1][y]*0;
    //esquina inf izquierda
    f= f+ matriz[x-1][y+1]*-1;
    c= c+ matriz[x-1][y+1]*1;
    //centro inf
    f= f+ matriz[x][y+1]*0;
    c= c+ matriz[x][y+1]*2;
    //esq inf derecha
    f= f+ matriz[x+1][y-1]*1;
    c= c+ matriz[x+1][y-1]*1;

    c= pow(c,2);
    f= pow(f,2);

    j=sqrt(c+f);

    return j;

}




int comp_fichero (char *fichero){
    FILE *f= fopen(fichero,"r");
    if (f==NULL){
        return 0;//no fichero    
        }
    fclose(f);
    return 1;
        //si fichero
}
//guardamos nueva matriz
void img_create_raw (unsigned char** matrix, char* fichero,int ancho,int largo){
	int i,j;
    char nombre[50];
    int contador=0;
	FILE *f = fopen (fichero,"wb");
	if (f==NULL){ //vemos si existe fichero creado
		printf("Error en nuevo fichero");
		exit;
	}
	
	for (j = 0; j < largo; j++){
		fwrite(matrix[j],sizeof(unsigned char),ancho,f);
	}
	
	fclose(f);
   
}
//printeamos los resultados
void print_results(int ancho, int largo, char* fichero, int filt, double temp){
char nombre[50];
    int contador=0;
    FILE *f;
    int i;
    
    sprintf(nombre,"Resultados_%dx%d.txt",ancho,largo);
     while(comp_fichero(nombre)==1){
        contador++;
        sprintf(nombre,"Resultados_%dx%d(%d).txt",ancho, largo,contador);
    }
   

    f=fopen(nombre,"w");
    fprintf(f,"Parametros de ejecucion\n\nancho: %d\n",ancho);
    fprintf(f,"largo: %d\n\n",largo);

    fprintf(f,"fichero de entrada: %s\n",fichero);
   
    

    if(filt==1){
        fprintf(f,"fichero de salida: media.raw\n");
        fprintf(f,"Tipo de filtrado: media\n");
       
    }
    if(filt==2){
        fprintf(f,"fichero de salida: mediana.raw\n");
        fprintf(f,"Tipo de filtrado:  mediana\n");
        
    }
    if(filt==3){
        fprintf(f,"fichero de salida: sobel.raw\n");
        fprintf(f,"Tipo de filtrado: sobel\n");
        
    }
    
    fprintf(f,"Tiempo  de ejecucion: %f\n",temp);
   fclose(f);




    


}