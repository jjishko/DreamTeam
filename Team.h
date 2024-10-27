#pragma once
#include <vector>
#include <unordered_set>

using method = std::unordered_set<int>(*)
(const std::vector<int>&, const std::vector<int>&);

//ќбъ€вл€ете здесь свою функцию как по примеру
std::unordered_set<int> simplestPackagingGrigorev(const std::vector<int>& objects,
	const std::vector<int>& containers);

std::unordered_set<int> AntSolutionLeontev(const std::vector<int>& objects, const std::vector<int>& containers);