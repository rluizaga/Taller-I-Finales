#include <stdio.h>
#include <netinet/in.h>

int main() {
    // Abrir el archivo en modo binario para lectura
    FILE* archivo = fopen("nros_2bytes_bigendian.dat", "rb");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    // Leer los valores del archivo y mostrarlos en formato de la máquina local
    unsigned short valor;
    while (fread(&valor, sizeof(unsigned short), 1, archivo) == 1) {
        unsigned short valor_local = ntohs(valor);
        printf("Valor leído: %hu\n", valor_local);
    }

    // Cerrar el archivo
    fclose(archivo);

    return 0;
}
