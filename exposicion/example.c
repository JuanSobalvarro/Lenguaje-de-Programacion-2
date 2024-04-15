#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_EMPLEADOS = 100;

// Definición de la estructura del empleado
typedef struct {
    char nombre[50];
    int edad;
    float salario;
} Empleado;

// Prototipos de funciones
void agregarEmpleado(Empleado *lista, int *numEmpleados);
void eliminarEmpleado(Empleado *lista, int *numEmpleados);
void mostrarEmpleados(Empleado *lista, int *numEmpleados);

// Función para mostrar el menú y obtener la selección del usuario
int mostrarMenu() {
    int opcion;
    printf("\n1. Agregar empleado\n");
    printf("2. Eliminar empleado\n");
    printf("3. Mostrar empleados\n");
    printf("4. Salir\n");
    printf("Selecciona una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

// Función principal
int main() {
    Empleado listaEmpleados[MAX_EMPLEADOS];
    int numEmpleados = 0;
    int opcion;

    // Puntero a función para manejar las opciones del menú
    void (*funcionesMenu[])(Empleado*, int*) = {agregarEmpleado, eliminarEmpleado, mostrarEmpleados};

    do {
        opcion = mostrarMenu();
        if (opcion >= 1 && opcion <= 3) {
            funcionesMenu[opcion - 1](listaEmpleados, &numEmpleados); // Llamada a la función a través del puntero
        } else if (opcion != 4) {
            printf("Opcion no valida. Intentalo de nuevo.\n");
        }
    } while (opcion != 4);

    printf("Saliendo del programa...\n");

    return 0;
}

// Implementación de funciones

void agregarEmpleado(Empleado *lista, int *numEmpleados) {
    if (*numEmpleados < MAX_EMPLEADOS) {
        printf("\nNombre: ");
        scanf("%s", lista[*numEmpleados].nombre);
        printf("Edad: ");
        scanf("%d", &lista[*numEmpleados].edad);
        printf("Salario: ");
        scanf("%f", &lista[*numEmpleados].salario);
        (*numEmpleados)++;
        printf("Empleado agregado con exito.\n");
    } else {
        printf("No se pueden agregar mas empleados. La lista esta llena.\n");
    }
}

void eliminarEmpleado(Empleado *lista, int *numEmpleados) {
    int indice;
    printf("\nIngrese el indice del empleado a eliminar: ");
    scanf("%d", &indice);
    if (indice >= 0 && indice < *numEmpleados) {
        for (int i = indice; i < (*numEmpleados - 1); i++) {
            lista[i] = lista[i + 1];
        }
        (*numEmpleados)--;
        printf("Empleado eliminado con exito.\n");
    } else {
        printf("Indice invalido.\n");
    }
}

void mostrarEmpleados(Empleado *lista, int *numEmpleados) {
    printf("\nLista de empleados:\n");
    for (int i = 0; i < *numEmpleados; i++) {
        printf("Nombre: %s\tEdad: %d\tSalario: %.2f\n", lista[i].nombre, lista[i].edad, lista[i].salario);
    }
}
