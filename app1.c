#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            printf("La(s) pizza(s) con la mayor cantidad (%d) son:\n", max_cantidad);
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
            printf("La(s) pizza(s) con la menor cantidad (%d) son:\n", min_cantidad);
        }
        for (int i = 0; i < cantidad_minimos; i++) {
            printf("%s\n", nombres_minimos[i]);
        }
    } else {
        printf("No se encontraron pizzas en el archivo.\n");
    }

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
    funcion_t funciones[] = {mostrar_nombres, calcular_promedio, pms, pls};
    char *funciones_nombre[] = {"nombre_pizzas", "promedio_pizzas", "pms", "pls"};

    // Recorrer los argumentos y llamar a las funciones dinámicamente
    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < 4; j++) {
            if (strcmp(argv[i], funciones_nombre[j]) == 0) {
                funciones[j](file);  // Llamada dinámica a la función usando puntero
                break;
            }
        }
    }

    fclose(file);
    return 0;
}
