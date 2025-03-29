#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PIZZAS 100
// Definición de las funciones
void mostrar_nombres(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    printf("Nombres de las pizzas:\n");

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ";");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"') {
                    inside_quotes = 0;
                }
            } else {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"') {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ";");
        }

        if (i >= 12) {
            printf("%s\n", tokens[11]);
        }
    }
    rewind(file);  // Volver al inicio para otra función
}

void calcular_promedio(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    int pizza_count = 0;
    float total_sum = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ";");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"') {
                    inside_quotes = 0;
                }
            } else {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"') {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ";");
        }

        if (i >= 12) {
            total_sum += atof(tokens[7]);  // Octava columna (total_price)
            pizza_count++;
            
        }
    }

    if (pizza_count > 0) {
        printf("\nPromedio de los precios de las pizzas: %.2f\n", total_sum / pizza_count);
    } else {
        printf("\nNo se encontraron pizzas en el archivo.\n");
    }
    rewind(file);  // Volver al inicio para otra función
}

void pms(FILE *file){
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    int max_cantidad = -1;  // Inicializamos la cantidad máxima con un valor bajo
    char nombres_maximos[MAX_PIZZAS][MAX_LINE_LENGTH];  // Cadena para almacenar el nombre de la pizza
    int cantidad_maximos = 0;  // Contador de cuántas pizzas tienen la cantidad máxima
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ";");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"') {
                    inside_quotes = 0;
                }
            } else {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"') {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ";");
        }

        if (i >= 12) {  
            int cantidad = atoi(tokens[3]); 

            if (cantidad > max_cantidad) {
                max_cantidad = cantidad;
                cantidad_maximos = 0;  // Reiniciamos el contador de nombres
                strcpy(nombres_maximos[cantidad_maximos], tokens[11]);  // Guardamos el primer nombre
                cantidad_maximos++;
            } else if (cantidad == max_cantidad) {
                // Si encontramos otra pizza con la misma cantidad máxima, la añadimos
                strcpy(nombres_maximos[cantidad_maximos], tokens[11]);
                cantidad_maximos++;
            }
        }
    }

    if (max_cantidad != -1) {
        if (cantidad_maximos == 1) {
            printf("La pizza con la mayor cantidad (%d) es:\n", max_cantidad);
        } else {
            printf("Las pizzas con la mayor cantidad (%d) son:\n", max_cantidad);
        }
        for (int i = 0; i < cantidad_maximos; i++) {
            printf("%s\n", nombres_maximos[i]);
        }
    } else {
        printf("No se encontraron pizzas en el archivo.\n");
    }

    rewind(file);  // Volver al inicio para otra función
}

void pls(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    int min_cantidad = INT_MAX;  // Inicializamos la cantidad mínima con el valor más grande posible
    char nombres_minimos[MAX_PIZZAS][MAX_LINE_LENGTH];  // Cadena para almacenar el nombre de la pizza
    int cantidad_minimos = 0;  // Contador de cuántas pizzas tienen la cantidad mínima

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ";");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"') {
                    inside_quotes = 0;
                }
            } else {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"') {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ";");
        }

        if (i >= 12) {  
            int cantidad = atoi(tokens[3]);  // Extraemos la cantidad de la columna 4

            if (cantidad < min_cantidad) {
                min_cantidad = cantidad;
                cantidad_minimos = 0;  // Reiniciamos el contador de nombres
                strcpy(nombres_minimos[cantidad_minimos], tokens[11]);  // Guardamos el primer nombre
                cantidad_minimos++;
            } else if (cantidad == min_cantidad) {
                // Si encontramos otra pizza con la misma cantidad mínima, la añadimos
                strcpy(nombres_minimos[cantidad_minimos], tokens[11]);
                cantidad_minimos++;
            }
        }
    }
    if (min_cantidad != INT_MAX) {
        if (cantidad_minimos == 1) {
            printf("La pizza con la menor cantidad (%d) es:\n", min_cantidad);
        } else {
            printf("Las pizzas con la menor cantidad (%d) son:\n", min_cantidad);
        }
        for (int i = 0; i < cantidad_minimos; i++) {
            printf("%s\n", nombres_minimos[i]);
        }
    } else {
        printf("No se encontraron pizzas en el archivo.\n");
    }

    rewind(file); 
}

void dms(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    // Usamos un arreglo de estructuras para guardar fechas y ventas totales
    typedef struct {
        char fecha[MAX_LINE_LENGTH];
        float total_venta;
    } VentaPorFecha;

    VentaPorFecha ventas[MAX_PIZZAS];  // Arreglo para almacenar las fechas y sus ventas
    int num_fechas = 0;  // Contador de fechas registradas

    // Leemos todas las líneas del archivo
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        // Procesamos cada línea
        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ";");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"') {
                    inside_quotes = 0;
                }
            } else {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"') {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ";");
        }

        if (i >= 12) {
            char *fecha = tokens[4];  // Fecha en la columna 5
            float total_venta = atof(tokens[7]);  // Precio total en la columna 8

            // Buscamos si ya tenemos esa fecha registrada
            int encontrado = 0;
            for (int j = 0; j < num_fechas; j++) {
                if (strcmp(ventas[j].fecha, fecha) == 0) {
                    ventas[j].total_venta += total_venta;  // Sumamos el total de ventas
                    encontrado = 1;
                    break;
                }
            }

            // Si la fecha no está registrada, la añadimos
            if (!encontrado) {
                strcpy(ventas[num_fechas].fecha, fecha);
                ventas[num_fechas].total_venta = total_venta;
                num_fechas++;
            }
        }
    }

    // Encontrar la mayor venta
    float max_venta = 0;
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_venta > max_venta) {
            max_venta = ventas[i].total_venta;
        }
    }
    // Contamos cuántas fechas tienen la venta máxima
    int count_max = 0;
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_venta == max_venta) {
            count_max++;
        }
    }
    if (count_max == 1) {
        printf("La fecha con la mayor venta es:\n", max_venta);
    } else {
        printf("Las fechas con mayor venta son:\n", max_venta);
    }

    // Mostrar las fechas y ventas
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_venta == max_venta) {
            printf("Fecha: %s, Dinero recaudado: %.2f\n", ventas[i].fecha, ventas[i].total_venta);
        }
    }
}

void dls(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    // Usamos un arreglo de estructuras para guardar fechas y ventas totales
    typedef struct {
        char fecha[MAX_LINE_LENGTH];
        float total_venta;
    } VentaPorFecha;

    VentaPorFecha ventas[MAX_PIZZAS];  // Arreglo para almacenar las fechas y sus ventas
    int num_fechas = 0;  // Contador de fechas registradas

    // Leemos todas las líneas del archivo
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        // Procesamos cada línea
        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ";");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"') {
                    inside_quotes = 0;
                }
            } else {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"') {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ";");
        }

        if (i >= 12) {
            char *fecha = tokens[4];  // Fecha en la columna 5
            float total_venta = atof(tokens[7]);  // Precio total en la columna 8

            // Buscamos si ya tenemos esa fecha registrada
            int encontrado = 0;
            for (int j = 0; j < num_fechas; j++) {
                if (strcmp(ventas[j].fecha, fecha) == 0) {
                    ventas[j].total_venta += total_venta;  // Sumamos el total de ventas
                    encontrado = 1;
                    break;
                }
            }

            // Si la fecha no está registrada, la añadimos
            if (!encontrado) {
                strcpy(ventas[num_fechas].fecha, fecha);
                ventas[num_fechas].total_venta = total_venta;
                num_fechas++;
            }
        }
    }

    // Encontrar la menor venta
    float min_venta = FLT_MAX;  // Usamos el valor máximo de un float como referencia
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_venta < min_venta) {
            min_venta = ventas[i].total_venta;
        }
    }

    // Contamos cuántas fechas tienen la venta mínima
    int count_min = 0;
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_venta == min_venta) {
            count_min++;
        }
    }

    // Imprimir las fechas con la menor venta
    if (count_min == 1) {
        printf("La fecha con la menor venta es:\n");
    } else {
        printf("Las fechas con menor venta son:\n");
    }

    // Mostrar las fechas y ventas
    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_venta == min_venta) {
            printf("Fecha: %s, Dinero recaudado: %.2f\n", ventas[i].fecha, ventas[i].total_venta);
        }
    }

    rewind(file);  // Volver al inicio para otra función
}

#define MAX_DATES 100
void dmsp(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezado

    typedef struct {
        char fecha[20];  // Fecha (formato DD-MM-YYYY)
        int total_vendido;  // Total de pizzas vendidas en esa fecha
    } Venta;

    Venta ventas[MAX_DATES];  
    int num_fechas = 0;

    // Leer las líneas y procesar las fechas y cantidades
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 12) {
            tokens[i++] = token;
            token = strtok(NULL, ";");
        }

        if (i >= 12) {
            char *fecha = tokens[4];  // Fecha en formato DD-MM-YYYY
            int cantidad = atoi(tokens[3]);  // La cantidad de pizzas vendidas

            // Comprobar si la fecha ya existe en el arreglo de ventas
            int found = 0;
            for (int j = 0; j < num_fechas; j++) {
                if (strcmp(ventas[j].fecha, fecha) == 0) {
                    ventas[j].total_vendido += cantidad;  // Acumular cantidad de ventas
                    found = 1;
                    break;
                }
            }

            // Si la fecha no existe, agregarla al arreglo
            if (!found && num_fechas < MAX_DATES) {
                strcpy(ventas[num_fechas].fecha, fecha);
                ventas[num_fechas].total_vendido = cantidad;
                num_fechas++;
            }
        }
    }

    // Buscar la fecha con más pizzas vendidas
    int max_ventas = 0;
    char mejor_fecha[20];

    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_vendido > max_ventas) {
            max_ventas = ventas[i].total_vendido;
            strcpy(mejor_fecha, ventas[i].fecha);
        }
    }

    // Mostrar la fecha con más pizzas vendidas y la cantidad
    printf("\nFecha con más pizzas vendidas: %s (%d pizzas)\n", mejor_fecha, max_ventas);
    rewind(file);
}

#define MAX_DATES 100
void dlsp(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezado

    typedef struct {
        char fecha[20];  // Fecha (formato DD-MM-YYYY)
        int total_vendido;  // Total de pizzas vendidas en esa fecha
    } Venta;

    Venta ventas[MAX_DATES];  
    int num_fechas = 0;

    // Leer las líneas y procesar las fechas y cantidades
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0;
        char *token = strtok(line, ";");

        while (token != NULL && i < 12) {
            tokens[i++] = token;
            token = strtok(NULL, ";");
        }

        if (i >= 12) {
            char *fecha = tokens[4];  // Fecha en formato DD-MM-YYYY
            int cantidad = atoi(tokens[3]);  // La cantidad de pizzas vendidas

            // Comprobar si la fecha ya existe en el arreglo de ventas
            int found = 0;
            for (int j = 0; j < num_fechas; j++) {
                if (strcmp(ventas[j].fecha, fecha) == 0) {
                    ventas[j].total_vendido += cantidad;  // Acumular cantidad de ventas
                    found = 1;
                    break;
                }
            }

            // Si la fecha no existe, agregarla al arreglo
            if (!found && num_fechas < MAX_DATES) {
                strcpy(ventas[num_fechas].fecha, fecha);
                ventas[num_fechas].total_vendido = cantidad;
                num_fechas++;
            }
        }
    }

    // Buscar la fecha con menos pizzas vendidas
    int min_ventas = __INT_MAX__;
    char peor_fecha[20];

    for (int i = 0; i < num_fechas; i++) {
        if (ventas[i].total_vendido < min_ventas) {
            min_ventas = ventas[i].total_vendido;
            strcpy(peor_fecha, ventas[i].fecha);
        }
    }

    // Mostrar la fecha con menos pizzas vendidas y la cantidad
    printf("\nFecha con menos pizzas vendidas: %s (%d pizzas)\n", peor_fecha, min_ventas);
    rewind(file);
}

// Definimos un tipo de puntero a función que toma un FILE* como parámetro
typedef void (*funcion_t)(FILE*);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: ./app1 [nombre del archivo csv] [funciones]\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Definir un arreglo de punteros a funciones
    funcion_t funciones[] = {mostrar_nombres, calcular_promedio, pms, pls, dms, dls, dmsp, dlsp};
    char *funciones_nombre[] = {"nombre_pizzas", "promedio_pizzas", "pms", "pls", "dms", "dls", "dmsp", "dlsp"};

    // Recorrer los argumentos y llamar a las funciones dinámicamente
    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < 8; j++) {
            if (strcmp(argv[i], funciones_nombre[j]) == 0) {
                funciones[j](file);  // Llamada dinámica a la función usando puntero
                break;
            }
        }
    }

    fclose(file);
    return 0;
}
