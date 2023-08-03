#include <string.h>
#include <unistd.h>
#include <stdio.h>



int main(){
    FILE* unArchivo = fopen("archivo.txt", "r+");
    if(!unArchivo){
        perror("Error al abrir el archivo\n");
        return 1;
    }
    char* buff;
    long wrPos = 0, rdPos = 0;
    size_t tamanio = 0;
    while( getline(&buff, &tamanio, unArchivo) && !feof(unArchivo)  ){
        int contadorEspacios = 0;
        for(int i = 0 ; i <strlen(buff); i++){
            if( buff[i] == ' ')  contadorEspacios++;
        }
        rdPos = ftell(unArchivo); //Me guardo la posicion donde leo, si encuent
        if( contadorEspacios > 0){
            fseek(unArchivo, wrPos, SEEK_SET );
            fprintf(unArchivo, "%s", buff);
            wrPos = ftell(unArchivo);
        }
        fseek(unArchivo, rdPos, SEEK_SET);
        printf("buff: %s", buff);
    }
    ftruncate(fileno(unArchivo), wrPos);

    return 0;
}

/* archivo.txt:
Hola que onda
hola
como estas?
vos
que onda jajaj
onda

*/

/*Resultado:
Hola que onda
como estas?
que onda jajaj

*/
