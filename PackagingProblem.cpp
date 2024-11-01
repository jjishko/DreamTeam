//КОММЕНТАРИИ И КОД КАРКАСА НЕ МЕНЯТЬ!
/*
1) Написать алгоритм в отдельном cpp файле 
	(пример и инструкции в SimplestPackagingGrigorev.cpp)
2) Создать объявление функции в Team.h
3) Вызвать функцию алгоритма в main
4) Проверить работоспособность кода, чтобы не положить проект
5) Выложить в репозиторий GitHub (в отдельную ветку!)
6) Идем тусить
*/

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <numeric>
#include <format>
#include <unordered_set>

#include "DatasetGeneration.h"
#include "Team.h"

using std::vector;
using std::string;
using std::pair;
using std::unordered_set;
using std::cin;
using std::cout;
using std::endl;

void run(string methodName, method foo, pair<const vector<int>&, const vector<int>&> data)
{
	auto start = std::chrono::system_clock::now();
	unordered_set<int> result = foo(data.first, data.second);
	auto end = std::chrono::system_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	float share = 0;

	for (int ind : result)
	{
		share += data.second[ind];
	}

	share = share * 100 / std::accumulate(data.second.begin(), data.second.end(), 0);

	cout << "Название алгоритма: " << methodName << endl;
	cout << "Время работы: " << time << " мкс" << endl;
	cout << "Кол-во занятых контейнеров: " << result.size() << endl;
	printf("Доля занятого пространства: %.1f %%\n\n", share);
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL) + rand());

	pair<vector<int>, vector<int>> easyData = easyDataset();
	pair<vector<int>, vector<int>> rndData = randomDataset();
	pair<vector<int>, vector<int>> worstData = worstDataset();

	// По образцу добавляете свой алгоритм в main с помощью функции run:
	// methodName - название алгоритма, 
	// foo - указатель на функцию алгоритма (имя функции)
	// data - easyData
	{
		cout << "=========== ЛУЧШИЕ ДАННЫЕ" << endl;
		cout << "Кол-во контейнеров: " << easyData.second.size() << endl << endl;

		run("Простейшая упаковка", simplestPackagingGrigorev, easyData);
		run("FirstFit алгоритм", firstFitGolubeva, easyData);
		run("Муравьиный алгоритм", AntSolutionLeontev, easyData);

	}

	//То же самое, но data = rndData
	{
		cout << "=========== СЛУЧАЙНЫЕ ДАННЫЕ" << endl;
		cout << "Кол-во контейнеров: " << rndData.second.size() << endl << endl;

		run("Простейшая упаковка", simplestPackagingGrigorev, rndData);
		run("FirstFit алгоритм", firstFitGolubeva, rndData);
		run("Муравьиный алгоритм", AntSolutionLeontev, rndData);
	}

	//Передаете худший вариант входных данных - worstData
	{
		cout << "=========== ХУДШИЕ ДАННЫЕ" << endl;
		cout << "Кол-во контейнеров: " << worstData.second.size() << endl << endl;

		run("Простейшая упаковка", simplestPackagingGrigorev, worstData);
		run("FirstFit алгоритм", firstFitGolubeva, worstData);
		run("Муравьиный алгоритм", AntSolutionLeontev, worstData);
	}

	return 0;
}