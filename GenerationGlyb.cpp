#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <unordered_set>

#include "Team.h"

using namespace std;

const int POPULATION_SIZE = 400;    // ������ ���������
const int MAX_GENERATIONS = 1000;    // ���������� ���������
const double MUTATION_RATE = 0.05;  // ����������� �������
const int NUM_BEST_SELECTION = 50;  // ���������� ������ ������� ��� �����������

// ��������� ���������� ������� (���������)
vector<int> generateRandomSolution(int numItems, int numBins) {
    vector<int> solution(numItems);
    for (int i = 0; i < numItems; ++i) {
        solution[i] = rand() % numBins;  // ������ ������ ���������� � ��������� ���������
    }
    return solution;
}

// ������ �������: ���������� �������������� �����������
int evaluateSolution(const vector<int>& solution, const vector<int>& weights, const vector<int>& binCapacities) {
    int numBins = binCapacities.size();
    vector<int> binUsage(numBins, 0);  // ������� �������� � ������ ����������

    // ��������� ������������� ������� ����������
    for (int i = 0; i < solution.size(); ++i) {
        binUsage[solution[i]] += weights[i];
    }

    // ���������, �� ��������� �� ������� �����������
    int binsUsed = 0;
    for (int i = 0; i < numBins; ++i) {
        if (binUsage[i] > 0) {
            if (binUsage[i] > binCapacities[i]) {
                return numeric_limits<int>::max();  // ����������� �������, ���� ��������� �����������
            }
            binsUsed++;
        }
    }

    return binsUsed;  // ���������� �������������� �����������
}

// ����������� (������������)
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

// �������
void mutate(vector<int>& solution, int numBins) {
    for (int i = 0; i < solution.size(); ++i) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            solution[i] = rand() % numBins;  // ���������� ������ � ��������� ���������
        }
    }
}

// �������� (���������)
vector<int> tournamentSelection(const vector<vector<int>>& population, const vector<int>& fitnessScores) {
    int bestIndex = rand() % population.size();

    for (int i = 0; i < 3; ++i) {  // ������ �� ���� ��������� ���������
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

    // ������������� ���������
    vector<vector<int>> population(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        population[i] = generateRandomSolution(numItems, numBins);
    }

    // ������������ �������
    vector<int> fitnessScores(POPULATION_SIZE);
    vector<int> bestSolution;
    int bestFitness = numeric_limits<int>::max();

    for (int generation = 0; generation < MAX_GENERATIONS; ++generation) {
        // ������ ������� ���������
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            fitnessScores[i] = evaluateSolution(population[i], weights, binCapacities);
            if (fitnessScores[i] < bestFitness) {
                bestFitness = fitnessScores[i];
                bestSolution = population[i];
            }
        }

        // ����� ���������
        vector<vector<int>> newPopulation;

        // �������� � �����������
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            vector<int> parent1 = tournamentSelection(population, fitnessScores);
            vector<int> parent2 = tournamentSelection(population, fitnessScores);
            vector<int> child = crossover(parent1, parent2);

            // �������
            mutate(child, numBins);

            newPopulation.push_back(child);
        }

        population = newPopulation;  // ��������� ���������

        //cout << "Generation " << generation + 1 << ": best result = " << bestFitness << endl;

        // ���������������, ���� ������� ���������� (�� ���� ��� ������, �� �����)
        if (bestFitness == numBins) {
            break;
        }
    }

    // ����� ������� ���������� �������
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