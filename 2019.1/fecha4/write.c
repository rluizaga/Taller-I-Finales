#include <stdio.h>
#include <netinet/in.h>

int main()
{
    // Valores de ejemplo a escribir en el archivo
    unsigned short valores[] = {1, 7, 14, 20};

    // Abrir el archivo en modo binario para escritura
    FILE *archivo = fopen("nros_2bytes_bigendian.dat", "wb");

    if (archivo == NULL)
    {
        printf("No se pudo crear el archivo.\n");
        return 1;
    }

    // Obtener el número de elementos en el arreglo
    int num_elementos = sizeof(valores) / sizeof(valores[0]);

    // Escribir los valores en el archivo en formato big-endian
    for (int i = 0; i < num_elementos; i++)
    {
        unsigned short valor_a_escribir = htons(valores[i]);
        fwrite(&valor_a_escribir, sizeof(unsigned short), 1, archivo);
    }

    // Cerrar el archivo
    fclose(archivo);

    printf("Archivo creado y valores escritos correctamente.\n");
    return 0;
}