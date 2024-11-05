#pragma once
#include <vector>
#include <unordered_set>

using method = std::unordered_set<int>(*)
(const std::vector<int>&, const std::vector<int>&);

//Îáúÿâëÿåòå çäåñü ñâîþ ôóíêöèþ êàê ïî ïðèìåðó
std::unordered_set<int> simplestPackagingGrigorev(const std::vector<int>& objects, const std::vector<int>& containers);
std::unordered_set<int> AntSolutionLeontev(const std::vector<int>& objects, const std::vector<int>& containers);
std::unordered_set<int> TabuSearchOsadchenko(const std::vector<int>& weights, const std::vector<int>& container);
std::unordered_set<int> bestFitAllayarov(const std::vector<int>& objects, const std::vector<int>& containers);
