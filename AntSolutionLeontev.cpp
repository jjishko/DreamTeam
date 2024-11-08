﻿#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <unordered_set>

#include "Team.h"

using namespace std;

// Параметры муравьиного алгоритма
const int NUM_ANTS = 100;            // Количество муравьев 100
const int MAX_ITERATIONS = 200;      // Количество итераций 200
const double ALPHA = 1.0;            // Влияние феромонов 1.0
const double BETA = 2.0;             // Влияние эвристики 2.0
const double RHO = 0.3;              // Коэффициент испарения феромонов 0.3
const double Q = 100.0;              // Константа для обновления феромонов 100.0

vector<vector<double>> initializePheromones(int numItems, int numBins) {
    return vector<vector<double>>(numItems, vector<double>(numBins, 1.0));
}

double heuristic(int remainingSpace) {
    return remainingSpace > 0 ? 1.0 / remainingSpace : 0.0;
}

int evaluateSolution(const vector<int>& solution, int numBins, const vector<int>& capacities, const vector<int>& weights) {
    vector<int> usedSpace(numBins, 0);
    int binsUsed = 0;

    for (int i = 0; i < solution.size(); ++i) {
        int bin = solution[i];
        if (bin != -1 && bin < numBins) {
            usedSpace[bin] += weights[i];
        }
    }

    for (int i = 0; i < numBins; ++i) {
        if (usedSpace[i] > 0 && usedSpace[i] <= capacities[i]) {
            binsUsed++;
        }
    }

    return binsUsed;
}

void updatePheromones(vector<vector<double>>& pheromones, const vector<int>& bestSolution, int bestSolutionBins) {
    for (int i = 0; i < pheromones.size(); ++i) {
        for (int j = 0; j < pheromones[i].size(); ++j) {
            pheromones[i][j] *= (1 - RHO); // Испарение феромонов
        }
    }

    // Обновление феромонов на лучших путях
    for (int i = 0; i < bestSolution.size(); ++i) {
        int binIdx = bestSolution[i];
        if (binIdx != -1) {
            pheromones[i][binIdx] += Q / bestSolutionBins;
        }
    }
}

vector<int> generateSolution(const vector<int>& weights, const vector<int>& binCapacities, vector<vector<double>>& pheromones) {
    int numItems = weights.size();
    int numBins = binCapacities.size();
    vector<int> solution(numItems, -1);
    vector<int> remainingSpace = binCapacities;

    for (int i = 0; i < numItems; ++i) {
        vector<double> probabilities(numBins, 0.0);
        double totalProbability = 0.0;
        bool validBinExists = false;

        for (int j = 0; j < numBins; ++j) {
            if (remainingSpace[j] >= weights[i]) {
                probabilities[j] = pow(pheromones[i][j], ALPHA) * pow(heuristic(remainingSpace[j]), BETA);
                totalProbability += probabilities[j];
                validBinExists = true;
            }
        }

        if (!validBinExists) {
            continue;
        }

        double randValue = static_cast<double>(rand()) / RAND_MAX * totalProbability;
        double cumulativeProbability = 0.0;
        int chosenBin = -1;
        for (int j = 0; j < numBins; ++j) {
            cumulativeProbability += probabilities[j];
            if (randValue <= cumulativeProbability) {
                chosenBin = j;
                break;
            }
        }

        if (chosenBin != -1) {
            solution[i] = chosenBin;
            remainingSpace[chosenBin] -= weights[i];
        }
    }

    return solution;
}

vector<int> antsolution(const vector<int>& weights, const vector<int>& binCapacities) {
    srand(static_cast<unsigned int>(time(0)));
    int numItems = weights.size();
    int numBins = binCapacities.size();

    vector<vector<double>> pheromones = initializePheromones(numItems, numBins);
    vector<int> bestSolution;
    int bestSolutionBins = numBins + 1;

    for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
        vector<vector<int>> solutions;
        for (int ant = 0; ant < NUM_ANTS; ++ant) {
            vector<int> solution = generateSolution(weights, binCapacities, pheromones);
            solutions.push_back(solution);
            int binsUsed = evaluateSolution(solution, numBins, binCapacities, weights);
            if (binsUsed < bestSolutionBins) {
                bestSolutionBins = binsUsed;
                bestSolution = solution;
            }
        }
        updatePheromones(pheromones, bestSolution, bestSolutionBins);
    }

    return bestSolution;
}


unordered_set<int> AntSolutionLeontev(const vector<int>& objects, const vector<int>& containers) {
    vector<int> c = containers;
    vector<int> o = objects;
    sort(c.begin(), c.end());
    reverse(c.begin(), c.end());
    sort(o.begin(), o.end());
    reverse(o.begin(), o.end());
    vector<int> result = antsolution(o, c);
    unordered_set<int> mySet(result.begin(), result.end());
    if (result.empty() || find(result.begin(), result.end(), -1) != result.end()) {
        mySet = {};
    }
    return mySet;
}