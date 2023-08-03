#include <stdio.h>
#include <malloc.h>
#include <string.h>


char* replicar(char* unaCadena, unsigned int I1, unsigned int I2, int cantDupl){
    if(I1 > I2 || cantDupl < 0){
        return "\0";
    }
    char* nuevoBuff = malloc(sizeof(char) * (strlen(unaCadena)* (I2-I1+1)*cantDupl) +1 ); // +1 por el \0.
    memset(nuevoBuff, '\0', strlen(nuevoBuff));
    int indiceActNB= 0;
    for(int i = 0 ; i < I1; i++){
        nuevoBuff[i] = unaCadena[i];
        indiceActNB++;
     }

    int cantVecesDuplico = 0;
    while(cantVecesDuplico < cantDupl){
        for(int i = I1; i <= I2; i++){
            nuevoBuff[indiceActNB] = unaCadena[i];
            indiceActNB++;
        }
        cantVecesDuplico++;
    }
    for(int i = I2+1 ; i < strlen(unaCadena); i++){
        nuevoBuff[indiceActNB] = unaCadena[i];
    }
    return nuevoBuff;

}


int main(){
    char* unaReplica = replicar("hola",1,2,3);
    printf("unaReplica: %s", unaReplica);
    free(unaReplica);
    return 0;
}
