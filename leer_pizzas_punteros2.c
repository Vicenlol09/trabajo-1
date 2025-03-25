#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Definición de las funciones
void mostrar_nombres(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    printf("Nombres de las pizzas:\n");

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ",");

        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ",");
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
            token = strtok(NULL, ",");
        }

        if (i >= 12) {
            printf("%s\n", tokens[11]);
        }
    }
    rewind(file);
}

void calcular_promedio(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);

    int pizza_count = 0;
    float total_sum = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ",");

        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ",");
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
            token = strtok(NULL, ",");
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
    rewind(file);
}

typedef void (*funcion_t)(FILE*);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo.csv> [nombre_pizzas] [promedio_pizzas]\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    funcion_t funciones[] = {mostrar_nombres, calcular_promedio};
    char *funciones_nombre[] = {"nombre_pizzas", "promedio_pizzas"};

    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < 2; j++) {
            if (strcmp(argv[i], funciones_nombre[j]) == 0) {
                funciones[j](file);
                break;
            }
        }
    }

    fclose(file);
    return 0;
}
