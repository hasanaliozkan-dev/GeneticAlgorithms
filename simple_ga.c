#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TARGET "Hello World"
#define TARGET_LENGTH 11
#define POPULATION_SIZE 100
#define GENERATIONS 1000
#define MUTATION_RATE 0.01
#define CROSSOVER_RATE 0.7
#define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "
#define CHARSET_SIZE 53

typedef struct {
    char genes[TARGET_LENGTH + 1];
    int fitness;
} Individual;

// Function prototypes
Individual create_individual();
void create_population(Individual population[]);
int fitness_function(Individual individual);
void select_parents(Individual population[], Individual *parent1, Individual *parent2);
Individual crossover(Individual parent1, Individual parent2);
void mutate(Individual *individual);
void genetic_algorithm();

int main() {
    // Seed the random number generator
    srand(time(NULL));

    genetic_algorithm();

    return 0;
}

Individual create_individual() {
    Individual individual;
    for (int i = 0; i < TARGET_LENGTH; i++) {
        individual.genes[i] = CHARSET[rand() % CHARSET_SIZE];
    }
    individual.genes[TARGET_LENGTH] = '\0'; // Null-terminate the string
    individual.fitness = 0; // Initialize fitness
    return individual;
}

void create_population(Individual population[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = create_individual();
    }
}

int fitness_function(Individual individual) {
    int fitness = 0;
    for (int i = 0; i < TARGET_LENGTH; i++) {
        if (individual.genes[i] == TARGET[i]) {
            fitness++;
        }
    }
    return fitness;
}

void select_parents(Individual population[], Individual *parent1, Individual *parent2) {
    // Calculate fitness for each individual
    int fitnesses[POPULATION_SIZE];
    int total_fitness = 0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitnesses[i] = fitness_function(population[i]);
        total_fitness += fitnesses[i];
    }

    // Calculate selection probabilities
    float probabilities[POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++) {
        probabilities[i] = (float)fitnesses[i] / total_fitness;
    }

    // Select two parents based on probabilities
    float rand1 = (float)rand() / RAND_MAX;
    float rand2 = (float)rand() / RAND_MAX;
    int index1 = 0, index2 = 0;
    float cumulative_probability = 0.0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        cumulative_probability += probabilities[i];
        if (rand1 < cumulative_probability) {
            index1 = i;
            break;
        }
    }

    cumulative_probability = 0.0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        cumulative_probability += probabilities[i];
        if (rand2 < cumulative_probability) {
            index2 = i;
            break;
        }
    }

    *parent1 = population[index1];
    *parent2 = population[index2];
}

Individual crossover(Individual parent1, Individual parent2) {
    Individual child;
    if ((float)rand() / RAND_MAX < CROSSOVER_RATE) {
        int crossover_point = rand() % TARGET_LENGTH;
        for (int i = 0; i < TARGET_LENGTH; i++) {
            if (i < crossover_point) {
                child.genes[i] = parent1.genes[i];
            } else {
                child.genes[i] = parent2.genes[i];
            }
        }
        child.genes[TARGET_LENGTH] = '\0';
    } else {
        // No crossover, just copy one of the parents
        if (rand() % 2 == 0) {
            strcpy(child.genes, parent1.genes);
        } else {
            strcpy(child.genes, parent2.genes);
        }
    }
    return child;
}

void mutate(Individual *individual) {
    for (int i = 0; i < TARGET_LENGTH; i++) {
        if ((float)rand() / RAND_MAX < MUTATION_RATE) {
            individual->genes[i] = CHARSET[rand() % CHARSET_SIZE];
        }
    }
}

void genetic_algorithm() {
    Individual population[POPULATION_SIZE];
    create_population(population);

    for (int generation = 0; generation < GENERATIONS; generation++) {
        // Sort the population (simple bubble sort for demonstration)
        for (int i = 0; i < POPULATION_SIZE - 1; i++) {
            for (int j = 0; j < POPULATION_SIZE - i - 1; j++) {
                if (fitness_function(population[j]) < fitness_function(population[j + 1])) {
                    Individual temp = population[j];
                    population[j] = population[j + 1];
                    population[j + 1] = temp;
                }
            }
        }

        printf("Generation %d: %s (Fitness: %d)\n", generation, population[0].genes, fitness_function(population[0]));

        // Create a new population
        Individual new_population[POPULATION_SIZE];
        for (int i = 0; i < POPULATION_SIZE; i++) {
            Individual parent1, parent2;
            select_parents(population, &parent1, &parent2);
            new_population[i] = crossover(parent1, parent2);
            mutate(&new_population[i]);
        }

        // Replace the old population with the new population
        memcpy(population, new_population, sizeof(population));

        // Check if target is found
        for (int i = 0; i < POPULATION_SIZE; i++) {
            if (strcmp(population[i].genes, TARGET) == 0) {
                printf("Target found in generation %d: %s\n", generation, TARGET);
                return;
            }
        }
    }

    printf("Target not found in %d generations.\n", GENERATIONS);
}