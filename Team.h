#pragma once
#include <vector>
#include <unordered_set>


using method = std::unordered_set<int>(*)
(const std::vector<int>&, const std::vector<int>&);

//Объявляете здесь свою функцию как по примеру
std::unordered_set<int> simplestPackagingGrigorev(const std::vector<int>& objects, const std::vector<int>& containers);
std::unordered_set<int> AntSolutionLeontev(const std::vector<int>& objects, const std::vector<int>& containers);
std::unordered_set<int> TabuSearchOsadchenko(const std::vector<int>& weights, const std::vector<int>& container);
std::unordered_set<int> bestFitAllayarov(const std::vector<int>& objects, const std::vector<int>& containers);
std::unordered_set<int> GenerationsGlyb(const std::vector<int>& weights, const std::vector<int>& binCapacities);
std::unordered_set<int> firstFitGolubeva(const std::vector<int>& objects, const std::vector<int>& containers);

