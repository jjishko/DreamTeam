#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <set>

using namespace std;

// Структура контейнера
struct Container {
    int vmestim;
    int zagr = 0;
    vector<int> items;
};

// Кол - во использованных контейнеров
int usedcontainers(const vector<Container>& containers) {
    int used = 0;
    for (const auto& container : containers) {
        if (!container.items.empty()) ++used;
    }
    return used;
}

// Функция для генерации начального решения
bool first_solution(const vector<int>& weights, vector<Container>& containers) {
    for (int weight : weights) {
        bool placed = false;
        for (auto& container : containers) {
            if (container.zagr + weight <= container.vmestim) {
                container.zagr += weight;
                container.items.push_back(weight);
                placed = true;
                break;
            }
        }
        if (!placed) return false;
    }
    return true;
}

// Функция для выполнения Tabu Search
void tabuSearch(vector<int>& weights, vector<Container>& containers, int max_znach, int tabuTenure) {
    int num_cont = containers.size();
    vector<Container> best = containers;
    int best_cont = usedcontainers(containers);

    list<pair<int, int>> tabuList;

    for (int iteration = 0; iteration < max_znach; ++iteration) {
        bool foundImprovement = false;

        for (size_t i = 0; i < num_cont; ++i) {
            for (size_t j = 0; j < num_cont; ++j) {
                if (i != j) {
                    for (size_t k = 0; k < containers[i].items.size(); ++k) {
                        int item = containers[i].items[k];
                        if (containers[j].zagr + item <= containers[j].vmestim &&
                            find(tabuList.begin(), tabuList.end(), make_pair(i, j)) == tabuList.end()) {

                            containers[i].zagr -= item;
                            containers[j].zagr += item;
                            containers[j].items.push_back(item);
                            containers[i].items.erase(containers[i].items.begin() + k);

                            int isp_cont = usedcontainers(containers);
                            if (isp_cont < best_cont) {
                                best_cont = isp_cont;
                                best = containers;
                                foundImprovement = true;
                            }

                            containers[i].zagr += item;
                            containers[j].zagr -= item;
                            containers[j].items.pop_back();
                            containers[i].items.insert(containers[i].items.begin() + k, item);

                            tabuList.push_back(make_pair(i, j));
                            if (tabuList.size() > tabuTenure) {
                                tabuList.pop_front();
                            }
                        }
                    }
                }
            }
        }
        if (!foundImprovement) break;
    }
    containers = best;
}

//Индексы занятых контейнеров
vector<int> index_cont(const vector<Container>& containers) {
    vector<int> indexes;
    for (size_t i = 0; i < containers.size(); ++i) {
        if (!containers[i].items.empty()) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

// Основная функция, вызывающая Tabu Search и возвращающая результат
unordered_set<int> TabuSearchOsadchenko(const vector<int>& w, const vector<int>& cont) {
    vector<int> weights = w;
    vector<int> vm = cont;
    vector<Container> containers;
    for (int vmestim : vm) {
        containers.push_back({ vmestim });
    }

    int max_znach = 1000;
    int tabuTenure = 5;
    if (!first_solution(weights, containers)) {
        return {};
    }

    tabuSearch(weights, containers, max_znach, tabuTenure);
    vector<int> indexes = index_cont(containers);
    unordered_set<int> used_cont(indexes.begin(), indexes.end());
    return used_cont;
}
