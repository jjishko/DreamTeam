#include <vector>
#include <unordered_set>
#include <limits>
#include <algorithm>

#include "Team.h"

using std::vector;
using std::unordered_set;

unordered_set<int> bestFitAllayarov(const vector<int>& objects, const vector<int>& containers) {
    vector<int> OBJECTS = objects;
    sort(OBJECTS.begin(), OBJECTS.end());
    reverse(OBJECTS.begin(), OBJECTS.end());
    vector<int> remainingCapacity = containers;
    sort(remainingCapacity.begin(), remainingCapacity.end());
    reverse(remainingCapacity.begin(), remainingCapacity.end());
    unordered_set<int> filledContainers;

    // Проходим по каждому объекту
    for (int i = 0; i < OBJECTS.size(); ++i) {
        int objectSize = OBJECTS[i];
        int bestIndex = -1;
        int minRemaining = std::numeric_limits<int>::max();

        // Ищем контейнер с минимально возможным оставшимся пространством после добавления объекта
        for (int j = 0; j < remainingCapacity.size(); ++j) {
            if (remainingCapacity[j] >= objectSize && remainingCapacity[j] - objectSize < minRemaining) {
                minRemaining = remainingCapacity[j] - objectSize;
                bestIndex = j;
            }
        }

        // Если подходящего контейнера нет, возвращаем пустой результат
        if (bestIndex == -1) {
            filledContainers.clear();
            return filledContainers;
        }

        // Размещаем объект в найденный контейнер и обновляем его оставшуюся вместимость
        remainingCapacity[bestIndex] -= objectSize;
        filledContainers.insert(bestIndex);
    }

    return filledContainers;
}
