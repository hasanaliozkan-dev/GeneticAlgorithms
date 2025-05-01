



"""
Problem: Simple Genetic Algorithm to Write Hello World
Author: @hasanaliozkan-dev

"""

import random
import numpy as np

target = "Hello World"


def create_individual():
    """
    Create a random individual.
    An individual is a string of random characters.
    """
    individual = ""
    for i in range(len(target)):
        individual += random.choice("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ")
    return individual

def create_population(size):
    """
    Create a population of individuals.
    A population is a list of individuals.
    """
    population = []
    for i in range(size):
        population.append(create_individual())
    return population



def fitness_function(individual):
    """
    Calculate the fitness of an individual.
    The fitness is the number of characters that match the target string.
    """
    fitness = 0
    for i in range(len(target)):
        if individual[i] == target[i]:
            fitness += 1
    return fitness


def select_parents(population):

    """
    Select parents from the population.
    The parents are selected based on their fitness.
    The higher the fitness, the higher the chance of being selected.
    """
    fitnesses = [fitness_function(individual) for individual in population]
    total_fitness = sum(fitnesses)
    probabilities = [fitness / total_fitness for fitness in fitnesses]
    parents = np.random.choice(population, size=2, p=probabilities)
    return parents

def crossover(parent1, parent2, crossover_rate):
    """
    Perform crossover between two parents with a given crossover rate.
    Crossover is the process of combining two parents to create a child.
    """
    if random.random() < crossover_rate:
        crossover_point = random.randint(0, len(target) - 1)
        child = parent1[:crossover_point] + parent2[crossover_point:]
    else:
        child = random.choice([parent1, parent2])
    return child

def mutate(individual, mutation_rate):
    """
    Mutate an individual with a given mutation rate.
    Mutation is the process of randomly changing a character in the individual.
    """
    individual = list(individual)
    for i in range(len(individual)):
        if random.random() < mutation_rate:
            mutation_char = random.choice("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ")
            individual[i] = mutation_char
    return "".join(individual)


def genetic_algorithm(population_size, generations, mutation_rate, crossover_rate):
    """
    Run the genetic algorithm.
    The genetic algorithm is a search heuristic that is inspired by Charles Darwin's theory of natural evolution.
    It is a method for solving optimization problems by iteratively selecting the fittest individuals from a population and creating new individuals through crossover and mutation.
    """
    population = create_population(population_size)
    for generation in range(generations):
        temp_population = sorted(population, key=fitness_function, reverse=True)
        print(f"Generation {generation}: {temp_population[0]}")
        new_population = []
        for i in range(population_size):
            parent1, parent2 = select_parents(population)
            child = crossover(parent1, parent2, crossover_rate)
            child = mutate(child, mutation_rate)
            new_population.append(child)
        population = new_population
        if target in population:
            print(f"Target found in generation {generation}: {target}")
            break
    else:
        print("Target not found")

if __name__ == "__main__":
    population_size = 100
    generations = 1000
    mutation_rate = 0.01
    crossover_rate = 0.7
    genetic_algorithm(population_size, generations, mutation_rate, crossover_rate)



