#include <vector>
#include <random>
#include <fstream>

using std::vector;
using std::pair;

void saveDataset(std::string fileName,
	const vector<int>& objects, const vector<int>& containers)
{
	std::ofstream f(fileName + ".txt");

	for (int obj : objects)
	{
		f << obj << " ";
	}

	f << std::endl;

	for (int cont : containers)
	{
		f << cont << " ";
	}

	f.close();
}

pair<vector<int>, vector<int>> impossibleDataset()
{
	vector<int> obj{ 5, 5, 10, 2, 5, 3, 7 };
	vector<int> cont{ 10, 10, 10 };

	saveDataset("impossibleData", obj, cont);

	return std::make_pair(obj, cont);
}

pair<vector<int>, vector<int>> randomDataset()
{
	pair <vector<int>, vector<int>> result;
	
	int objectSize = rand() % 50 + 5;
	int containersSize = rand() % 95 + 10;

	for (int i = 0; i < objectSize; i++)
	{
		result.first.push_back(rand() % 990 + 10);
	}

	for (int i = 0; i < containersSize; i++)
	{
		result.second.push_back(rand() % 950 + 50);
	}

	saveDataset("randomData", result.first, result.second);

	return result;
}

pair<vector<int>, vector<int>> easyDataset()
{
	vector<int> obj { 5, 5, 10, 2, 5, 3, 7 };
	vector<int> cont{ 10, 10, 10, 10, 7 };

	saveDataset("easyData", obj, cont);

	return std::make_pair(obj, cont);
}

pair<vector<int>, vector<int>> worstDataset()
{
	pair<vector<int>, vector<int>> result;
	std::ifstream f("worstData.txt");

	if (!f.is_open())
	{
		return result;
	}

	int val;

	while (f.peek() != '\n')
	{
		f >> val;
		result.first.push_back(val);
	}

	f.get();

	while (f.peek() != EOF)
	{
		f >> val;
		result.second.push_back(val);
	}

	f.close();

	return result;
}

