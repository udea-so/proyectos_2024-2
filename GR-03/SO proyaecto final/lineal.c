#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Estructura para almacenar métricas generales
typedef struct {
    int total_reviews;
    int positive_reviews;
    int negative_reviews;
    int neutral_reviews;
    int total_positive_words;
    int total_negative_words;
} ReviewStats;

int max_reviews = 500;  // Tamaño inicial del arreglo de reseñas
int review_count = 0;   // Contador de reseñas
char **reviews = NULL;  // Arreglo de reseñas

// Estructura para almacenar las palabras clave y su frecuencia
typedef struct {
    char *word;
    int count;
} WordCount;

#define MAX_WORDS 100

// Variables globales para almacenar estadísticas y frecuencias de palabras
ReviewStats stats = {0, 0, 0, 0, 0, 0};
WordCount word_counts[MAX_WORDS];
int word_count_size = 0;

// Lista de palabras positivas y negativas
const char *positive_words[] = {
    "good", "better", "quality", "finicky", "appreciates", "healthy", "delightful", "yummy",
    "amazing", "satisfying", "fresh", "delicious", "great", "loved", "recommend", "excellent",
    "superb", "guilt free", "fantastic", "best", "incredible", "magic", "ecstatic", "love",
    "blown away", "personal", "great deal", "perfect", "tasty", "fun", "easy", "convenient",
    "fantastic", "best", NULL};

const char *negative_words[] = {
    "error", "bummed", "not", "disappointed", "stale", "don't", "chewy", "hard",
    "boring", "plain", "medicinal", "poor", "soggy", "gluey", "bad", "lacks", "cheap", "unpleasant",
    "too sweet", "lackluster", "horrible", "terrible", "low quality", "worst", "too much", "overpriced", NULL};

void measure_performance(void (*program)()) {
    struct rusage usage;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    program();
    end = clock();
    getrusage(RUSAGE_SELF, &usage);

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tiempo de CPU usado: %f segundos\n", cpu_time_used);
    printf("Memoria máxima utilizada: %ld KB\n", usage.ru_maxrss);
}

// Función para contar las palabras positivas y negativas en una reseña
void update_word_frequency(const char *review, const char **words, WordCount *word_counts, int *word_count_size) {
    for (int i = 0; words[i] != NULL; i++) {
        if (strstr(review, words[i])) {
            int found = 0;
            for (int j = 0; j < *word_count_size; j++) {
                if (strcmp(word_counts[j].word, words[i]) == 0) {
                    word_counts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && *word_count_size < MAX_WORDS) {
                word_counts[*word_count_size].word = strdup(words[i]);
                word_counts[*word_count_size].count = 1;
                (*word_count_size)++;
            }
        }
    }
}

// Función para actualizar las estadísticas generales (reseñas positivas, negativas, neutrales)
void update_review_stats(const char *review, const char **positive_words, const char **negative_words) {
    int positive_count = 0;
    int negative_count = 0;

    // Contar palabras positivas
    for (int i = 0; positive_words[i] != NULL; i++) {
        if (strstr(review, positive_words[i])) {
            positive_count++;
        }
    }

    // Contar palabras negativas
    for (int i = 0; negative_words[i] != NULL; i++) {
        if (strstr(review, negative_words[i])) {
            negative_count++;
        }
    }

    // Actualizar estadísticas generales
    stats.total_reviews++;
    stats.total_positive_words += positive_count;
    stats.total_negative_words += negative_count;

    if (positive_count > negative_count) {
        stats.positive_reviews++;
    } else if (negative_count > positive_count) {
        stats.negative_reviews++;
    } else {
        stats.neutral_reviews++;
    }
}

// Función para calcular la puntuación general de una reseña
int calculate_overall_score(const char *review, const char **positive_words, const char **negative_words) {
    int positive_count = 0;
    int negative_count = 0;

    // Contar las palabras positivas
    for (int i = 0; positive_words[i] != NULL; i++) {
        if (strstr(review, positive_words[i])) {
            positive_count++;
        }
    }

    // Contar las palabras negativas
    for (int i = 0; negative_words[i] != NULL; i++) {
        if (strstr(review, negative_words[i])) {
            negative_count++;
        }
    }

    // Retornar la puntuación
    return positive_count - negative_count;
}

// Función para procesar una reseña
void process_review(const char *review) {
    // Actualizar las estadísticas generales
    update_review_stats(review, positive_words, negative_words);

    // Actualizar la frecuencia de palabras clave
    update_word_frequency(review, positive_words, word_counts, &word_count_size);
    update_word_frequency(review, negative_words, word_counts, &word_count_size);

    // Calcular y mostrar la puntuación general de la reseña
    int score = calculate_overall_score(review, positive_words, negative_words);
    // printf("Puntuación de la reseña: %d\n", score);
}

// Función para imprimir las métricas finales
void print_final_results() {
    printf("Total de Reseñas Procesadas: %d\n", stats.total_reviews);
    printf("Reseñas Positivas: %d (%.2f%%)\n", stats.positive_reviews, (stats.positive_reviews / (float)stats.total_reviews) * 100);
    printf("Reseñas Negativas: %d (%.2f%%)\n", stats.negative_reviews, (stats.negative_reviews / (float)stats.total_reviews) * 100);
    printf("Reseñas Neutrales: %d (%.2f%%)\n", stats.neutral_reviews, (stats.neutral_reviews / (float)stats.total_reviews) * 100);
    printf("Palabras Positivas Encontradas: %d\n", stats.total_positive_words);
    printf("Palabras Negativas Encontradas: %d\n", stats.total_negative_words);

    // printf("\nFrecuencia de Palabras Clave:\n");
    // for (int i = 0; i < word_count_size; i++) {
    //     printf("%s: %d veces\n", word_counts[i].word, word_counts[i].count);
    // }
}

void run_program() {
    FILE *file = fopen("reviews_output_1000.txt", "r");
    if (file == NULL) {
        perror("Error abriendo el archivo");
        exit(1);
    }

    // Leer todo el contenido del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_content = malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    fclose(file);

    file_content[file_size] = '\0';

    // Dividir el contenido del archivo en reseñas
    char *token = strtok(file_content, "\n");
    reviews = malloc(max_reviews * sizeof(char *));

    while (token != NULL) {
        if (review_count >= max_reviews) {
            max_reviews *= 2;
            reviews = realloc(reviews, max_reviews * sizeof(char *));
        }
        reviews[review_count] = strdup(token);
        review_count++;
        token = strtok(NULL, "\n");
    }

    free(file_content);

    // Procesar cada reseña secuencialmente
    for (int i = 0; i < review_count; i++) {
        process_review(reviews[i]);
    }

    // Imprimir resultados finales
    print_final_results();
}

int main() {
    measure_performance(run_program);
    return 0;
}