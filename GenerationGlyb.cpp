#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <unordered_set>

#include "Team.h"

using namespace std;

const int POPULATION_SIZE = 400;    // Размер популяции
const int MAX_GENERATIONS = 1000;    // Количество поколений
const double MUTATION_RATE = 0.05;  // Вероятность мутации
const int NUM_BEST_SELECTION = 50;  // Количество лучших решений для скрещивания

// Генерация случайного решения (хромосомы)
vector<int> generateRandomSolution(int numItems, int numBins) {
    vector<int> solution(numItems);
    for (int i = 0; i < numItems; ++i) {
        solution[i] = rand() % numBins;  // Каждый объект помещается в случайный контейнер
    }
    return solution;
}

// Оценка решения: количество использованных контейнеров
int evaluateSolution(const vector<int>& solution, const vector<int>& weights, const vector<int>& binCapacities) {
    int numBins = binCapacities.size();
    vector<int> binUsage(numBins, 0);  // Сколько объектов в каждом контейнере

    // Вычисляем использование каждого контейнера
    for (int i = 0; i < solution.size(); ++i) {
        binUsage[solution[i]] += weights[i];
    }

    // Проверяем, не превышены ли размеры контейнеров
    int binsUsed = 0;
    for (int i = 0; i < numBins; ++i) {
        if (binUsage[i] > 0) {
            if (binUsage[i] > binCapacities[i]) {
                return numeric_limits<int>::max();  // Невозможное решение, если превышена вместимость
            }
            binsUsed++;
        }
    }

    return binsUsed;  // Количество использованных контейнеров
}

// Скрещивание (одноточечное)
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int size = parent1.size();
    vector<int> child(size);
    int crossoverPoint = rand() % size;

    for (int i = 0; i < size; ++i) {
        if (i < crossoverPoint) {
            child[i] = parent1[i];
        }
        else {
            child[i] = parent2[i];
        }
    }

    return child;
}

// Мутация
void mutate(vector<int>& solution, int numBins) {
    for (int i = 0; i < solution.size(); ++i) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            solution[i] = rand() % numBins;  // Перемещаем объект в случайный контейнер
        }
    }
}

// Селекция (турнирная)
vector<int> tournamentSelection(const vector<vector<int>>& population, const vector<int>& fitnessScores) {
    int bestIndex = rand() % population.size();

    for (int i = 0; i < 3; ++i) {  // Турнир из трех случайных индивидов
        int randomIndex = rand() % population.size();
        if (fitnessScores[randomIndex] < fitnessScores[bestIndex]) {
            bestIndex = randomIndex;
        }
    }

    return population[bestIndex];
}

unordered_set<int> GenerationsGlyb(const vector<int>& weights, const vector<int>& binCapacities) {
    unordered_set<int> filledContainers;
    srand(time(0));

    int numItems = weights.size();
    int numBins = binCapacities.size();

    // Инициализация популяции
    vector<vector<int>> population(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        population[i] = generateRandomSolution(numItems, numBins);
    }

    // Эволюционный процесс
    vector<int> fitnessScores(POPULATION_SIZE);
    vector<int> bestSolution;
    int bestFitness = numeric_limits<int>::max();

    for (int generation = 0; generation < MAX_GENERATIONS; ++generation) {
        // Оценка текущей популяции
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            fitnessScores[i] = evaluateSolution(population[i], weights, binCapacities);
            if (fitnessScores[i] < bestFitness) {
                bestFitness = fitnessScores[i];
                bestSolution = population[i];
            }
        }

        // Новая популяция
        vector<vector<int>> newPopulation;

        // Селекция и скрещивание
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            vector<int> parent1 = tournamentSelection(population, fitnessScores);
            vector<int> parent2 = tournamentSelection(population, fitnessScores);
            vector<int> child = crossover(parent1, parent2);

            // Мутация
            mutate(child, numBins);

            newPopulation.push_back(child);
        }

        population = newPopulation;  // Обновляем популяцию

        //cout << "Generation " << generation + 1 << ": best result = " << bestFitness << endl;

        // Останавливаемся, если решение оптимально (не надо так делать, но можно)
        if (bestFitness == numBins) {
            break;
        }
    }

    // Вывод лучшего найденного решения
    if (bestSolution.size() != 0) {
        /*cout << "best result: " << endl;
        for (int i = 0; i < bestSolution.size(); ++i) {
            cout << "Object " << i + 1 << " in container " << bestSolution[i] + 1 << endl;
        }*/
        //cout << "Amount of used containers: " << bestFitness << endl;
    }
    else {
        //cout << "Solution doesn't exist " << endl;
    }

    move(bestSolution.begin(), bestSolution.end(), std::inserter(filledContainers, filledContainers.end()));
    return filledContainers;
}