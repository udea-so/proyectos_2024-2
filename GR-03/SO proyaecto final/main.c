#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

// Estructura para almacenar una tarea de procesamiento de reseña
typedef struct Task {
    char *review;
    struct Task *next;
} Task;

// Cola de tareas
typedef struct {
    Task *front;
    Task *rear;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool stop;  // Indicador para detener los hilos
} TaskQueue;

// Inicialización global de la cola de tareas
TaskQueue task_queue = {NULL, NULL, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, false};

// Variables globales para estadísticas
typedef struct {
    int total_reviews;
    int positive_reviews;
    int negative_reviews;
    int neutral_reviews;
    int total_positive_words;
    int total_negative_words;
} ReviewStats;

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


ReviewStats stats = {0, 0, 0, 0, 0, 0};
pthread_mutex_t stats_mutex = PTHREAD_MUTEX_INITIALIZER;

// Lista de palabras positivas y negativas
const char *positive_words[] = {"good", "amazing", "excellent", "fantastic", "love", "perfect", NULL};
const char *negative_words[] = {"bad", "horrible", "terrible", "poor", "worst", "hate", NULL};

// Función para procesar las estadísticas de una reseña
void update_review_stats(const char *review) {
    int positive_count = 0, negative_count = 0;

    for (int i = 0; positive_words[i] != NULL; i++) {
        if (strstr(review, positive_words[i])) {
            positive_count++;
        }
    }
    for (int i = 0; negative_words[i] != NULL; i++) {
        if (strstr(review, negative_words[i])) {
            negative_count++;
        }
    }

    pthread_mutex_lock(&stats_mutex);
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
    pthread_mutex_unlock(&stats_mutex);
}

// Función para inicializar la cola de tareas
void enqueue_task(TaskQueue *queue, const char *review) {
    Task *new_task = malloc(sizeof(Task));
    new_task->review = strdup(review);
    new_task->next = NULL;

    pthread_mutex_lock(&queue->mutex);
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_task;
    } else {
        queue->rear->next = new_task;
        queue->rear = new_task;
    }
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

// Función para detener la cola y notificar a todos los hilos
void stop_task_queue(TaskQueue *queue) {
    pthread_mutex_lock(&queue->mutex);
    queue->stop = true;
    pthread_cond_broadcast(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

// Función para obtener una tarea de la cola
Task *dequeue_task(TaskQueue *queue) {
    pthread_mutex_lock(&queue->mutex);
    while (queue->front == NULL && !queue->stop) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    if (queue->stop && queue->front == NULL) {
        pthread_mutex_unlock(&queue->mutex);
        return NULL;
    }

    Task *task = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    pthread_mutex_unlock(&queue->mutex);
    return task;
}

// Función que ejecuta cada hilo del pool
void *thread_function(void *arg) {
    while (1) {
        Task *task = dequeue_task(&task_queue);
        if (task == NULL) break;
        update_review_stats(task->review);
        free(task->review);
        free(task);
    }
    return NULL;
}

// Función para leer reseñas de un archivo
void load_reviews(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Eliminar salto de línea
        enqueue_task(&task_queue, buffer);
    }

    fclose(file);
}

// Función para imprimir estadísticas finales
void print_stats() {
    printf("Total de reseñas: %d\n", stats.total_reviews);
    printf("Reseñas positivas: %d\n", stats.positive_reviews);
    printf("Reseñas negativas: %d\n", stats.negative_reviews);
    printf("Reseñas neutrales: %d\n", stats.neutral_reviews);
    printf("Palabras positivas encontradas: %d\n", stats.total_positive_words);
    printf("Palabras negativas encontradas: %d\n", stats.total_negative_words);
}

// Función principal
void run_program() {
    const int thread_pool_size = 4;  // Tamaño del pool de hilos
    pthread_t threads[thread_pool_size];

    // Cargar reseñas en la cola de tareas
    load_reviews("reviews_output_1000.txt");

    // Crear el pool de hilos
    for (int i = 0; i < thread_pool_size; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    // Una vez que todas las tareas estén encoladas, detener la cola
    stop_task_queue(&task_queue);

    // Unir los hilos
    for (int i = 0; i < thread_pool_size; i++) {
        pthread_join(threads[i], NULL);
    }

    print_stats();
    // return 0;
}

// Función principal que utiliza measure_performance
int main() {
    measure_performance(run_program);
    return 0;
}