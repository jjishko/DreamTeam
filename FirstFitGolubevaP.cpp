#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <functional>

using namespace std;

unordered_set<int> firstFit(const vector<int>& objects, const vector<int>& containers)
{
	unordered_set<int> filledContainers; 
	vector<int> remainingCapacity(containers); 
	sort(remainingCapacity.begin(), remainingCapacity.end());

	for (int object : objects) {
		bool placed = false; 

		for (size_t i = 0; i < remainingCapacity.size(); ++i)
		{
			if (remainingCapacity[i] >= object) 
			{
				remainingCapacity[i] -= object; 
				filledContainers.insert(i); 
				placed = true; 
				break; 
			}
		}

		if (!placed)
		{
			return {};
		}
	}

	return filledContainers; 
}
