#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PIZZAS 100
// Definición de las funciones
void nombre_pizzas(FILE *file) {
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

void promedio_pizzas(FILE *file) {
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
    rewind(file);
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
    printf("\nFecha con mayor cantidad de pizzas vendidas: %s (%d pizzas)\n", mejor_fecha, max_ventas);
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
    printf("\nFecha con menor cantidad de pizzas vendidas: %s (%d pizzas)\n", peor_fecha, min_ventas);
    rewind(file);
}

void apo(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    int total_ordenes = 0;
    int total_pizzas = 0;
    int current_order = -1;
    int pizzas_in_order = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        // Procesamiento de tokens 
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
            int order_id = atoi(tokens[1]);  // Columna order_id
            int quantity = atoi(tokens[3]);   // Columna quantity

            if (order_id != current_order) {
                // Nueva orden encontrada
                if (current_order != -1) {
                    total_ordenes++;
                    total_pizzas += pizzas_in_order;
                }
                current_order = order_id;
                pizzas_in_order = quantity;
            } else {
                // Misma orden, sumar cantidad
                pizzas_in_order += quantity;
            }
        }
    }

    // Añadir la última orden
    if (current_order != -1) {
        total_ordenes++;
        total_pizzas += pizzas_in_order;
    }

    // Calcular y mostrar el promedio
    if (total_ordenes > 0) {
        float promedio = (float)total_pizzas / total_ordenes;
        printf("El promedio de pizzas por orden es: %.2f\n", promedio);
    } else {
        printf("No se encontraron ordenes en el archivo.\n");
    }

    rewind(file);
}
 
void apd(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    int total_dias = 0;
    int total_pizzas = 0;
    char current_date[MAX_LINE_LENGTH] = "";
    int pizzas_in_day = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ";");

        // Procesamiento de tokens igual que en el código original
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
            char *order_date = tokens[4];  // Columna order_date
            int quantity = atoi(tokens[3]); // Columna quantity

            if (strcmp(order_date, current_date) != 0) {
                // Nuevo día encontrado
                if (strlen(current_date) > 0) {
                    total_dias++;
                    total_pizzas += pizzas_in_day;
                }
                strcpy(current_date, order_date);
                pizzas_in_day = quantity;
            } else {
                // Mismo día, sumar cantidad
                pizzas_in_day += quantity;
            }
        }
    }

    // Añadir el último día
    if (strlen(current_date) > 0) {
        total_dias++;
        total_pizzas += pizzas_in_day;
    }

    // Calcular y mostrar el promedio
    if (total_dias > 0) {
        float promedio = (float)total_pizzas / total_dias;
        printf("El promedio de pizzas por dia es: %.2f\n", promedio);
    } else {
        printf("No se encontraron datos de dias en el archivo.\n");
    }

    rewind(file);
}

#define MAX_INGREDIENTS 100
typedef struct {
    char ingredient[50];
    int count;
} IngredientCount;

void ims(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados
    
    IngredientCount ingredients[MAX_INGREDIENTS];
    int ingredient_count = 0;
    
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *ptr = line;
        char *tokens[12];
        int token_count = 0;
        int in_quotes = 0;
        char *start = ptr;

        while (*ptr && token_count < 12) {
            if (*ptr == '"') {
                in_quotes = !in_quotes;
            } else if (*ptr == ';' && !in_quotes) {
                *ptr = '\0';
                tokens[token_count++] = start;
                start = ptr + 1;
            }
            ptr++;
        }
        if (token_count < 12) {
            tokens[token_count++] = start;
        }

        if (token_count >= 11) {
            int quantity = atoi(tokens[3]);
            char *ingredients_token = tokens[10];
            
            // Limpiar comillas si existen
            if (ingredients_token[0] == '"') {
                ingredients_token++;
                size_t len = strlen(ingredients_token);
                if (len > 0 && ingredients_token[len-1] == '"') {
                    ingredients_token[len-1] = '\0';
                }
            }
            
            // Procesar ingredientes
            char *saveptr;
            char *ingredient = strtok_r(ingredients_token, ";", &saveptr);
            
            while (ingredient != NULL) {
                // Limpiar espacios
                while (*ingredient == ' ') ingredient++;
                size_t len = strlen(ingredient);
                while (len > 0 && ingredient[len-1] == ' ') {
                    ingredient[len-1] = '\0';
                    len--;
                }
                
                if (*ingredient == '\0') {
                    ingredient = strtok_r(NULL, ";", &saveptr);
                    continue;
                }
                
                // Convertir a minúsculas
                for (char *p = ingredient; *p; p++) {
                    *p = tolower(*p);
                }
                
                // Buscar o agregar ingrediente
                int found = 0;
                for (int j = 0; j < ingredient_count; j++) {
                    if (strcmp(ingredients[j].ingredient, ingredient) == 0) {
                        ingredients[j].count += quantity;
                        found = 1;
                        break;
                    }
                }
                
                if (!found && ingredient_count < MAX_INGREDIENTS) {
                    strncpy(ingredients[ingredient_count].ingredient, ingredient, 49);
                    ingredients[ingredient_count].ingredient[49] = '\0';
                    ingredients[ingredient_count].count = quantity;
                    ingredient_count++;
                }
                
                ingredient = strtok_r(NULL, ";", &saveptr);
            }
        }
    }

    // Encontrar el ingrediente con mayor conteo
    if (ingredient_count == 0) {
        printf("No se encontraron ingredientes.\n");
        rewind(file);
        return;
    }

    int max_count = ingredients[0].count;
    char max_ingredient[50];
    strcpy(max_ingredient, ingredients[0].ingredient);

    for (int j = 1; j < ingredient_count; j++) {
        if (ingredients[j].count > max_count) {
            max_count = ingredients[j].count;
            strcpy(max_ingredient, ingredients[j].ingredient);
        }
    }

    printf("El ingrediente mas vendido es: %s (aparece %d veces)\n", max_ingredient, max_count);
    
    rewind(file);
}


void hp(FILE *file) {
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados
    
    int classic_count = 0, veggie_count = 0;
    
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
            int quantity = atoi(tokens[3]);  // Token 4 (índice 3 en array)
            char *categoria = tokens[9];     // Token 9 (índice 8 en array)

            if (strcmp(categoria, "Classic") == 0) {
                classic_count += quantity;
            }

            else if (strcmp(categoria, "Veggie") == 0) {
                veggie_count += quantity;
            }
        }
    }
    printf("Cantidad de pizzas vendidas por categoria:\n");
    printf("Classic: %d\n", classic_count);
    printf("Veggie: %d\n", veggie_count);
    
    rewind(file);  // Volver al inicio para otra función
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
    funcion_t funciones[] = {nombre_pizzas, promedio_pizzas, pms, pls, dms, dls, dmsp, dlsp, apo, apd, ims, hp}; 
    char *funciones_nombre[] = {"nombre_pizzas", "promedio_pizzas", "pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"}; 

    // Recorrer los argumentos y llamar a las funciones dinámicamente
    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < 12; j++) {
            if (strcmp(argv[i], funciones_nombre[j]) == 0) {
                funciones[j](file);  // Llamada dinámica a la función usando puntero
                break;
            }
        }
    }

    fclose(file);
    return 0;
}
