//����������� � ��� ������� �� ������!
/*
1) �������� �������� � ��������� cpp �����
	(������ � ���������� � SimplestPackagingGrigorev.cpp)
2) ������� ���������� ������� � Team.h
3) ������� ������� ��������� � main
4) ��������� ����������������� ����, ����� �� �������� ������
5) �������� � ����������� GitHub (� ��������� �����!)
6) ���� ������
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

	int sumOfFilledContainers = 0;

	for (int ind : result)
	{
		sumOfFilledContainers += data.second[ind];
	}

	//share = share * 100 / std::accumulate(data.second.begin(), data.second.end(), 0);

	cout << "�������� ���������: " << methodName << endl;
	cout << "����� ������: " << time << " ���" << endl;
	cout << "���-�� ������� �����������: " << result.size() << endl;
	cout << "����� �������� ������� �����������: " << sumOfFilledContainers << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL) + rand());

	pair<vector<int>, vector<int>> easyData = easyDataset();
	pair<vector<int>, vector<int>> rndData = randomDataset();
	pair<vector<int>, vector<int>> worstData = worstDataset();
	pair<vector<int>, vector<int>> impossibleData = impossibleDataset();

	// �� ������� ���������� ���� �������� � main � ������� ������� run:
	// methodName - �������� ���������, 
	// foo - ��������� �� ������� ��������� (��� �������)
	// data - easyData
	{
		cout << "=========== ������ ������" << endl;
		cout << "���-�� ��������: " << easyData.first.size() << endl;
		cout << "���-�� �����������: " << easyData.second.size() << endl << endl;

		run("���������� ��������", simplestPackagingGrigorev, easyData);
		run("First Fit", firstFitGolubeva, easyData);
		run("Best Fit", bestFitAllayarov, easyData);
		run("Tabu Search", TabuSearchOsadchenko, easyData);
		run("������������ ��������", GenerationsGlyb, easyData);
		run("���������� ��������", AntSolutionLeontev, easyData);
	}

	//�� �� �����, �� data = rndData
	{
		cout << "=========== ��������� ������" << endl;
		cout << "���-�� ��������: " << rndData.first.size() << endl;
		cout << "���-�� �����������: " << rndData.second.size() << endl << endl;

		run("���������� ��������", simplestPackagingGrigorev, rndData);
		run("First Fit", firstFitGolubeva, rndData);
		run("Best Fit", bestFitAllayarov, rndData);
		run("Tabu Search", TabuSearchOsadchenko, rndData);
		run("������������ ��������", GenerationsGlyb, rndData);
		run("���������� ��������", AntSolutionLeontev, rndData);
	}

	//��������� ������ ������� ������� ������ - worstData
	{
		cout << "=========== ������ ������" << endl;
		cout << "���-�� ��������: " << worstData.first.size() << endl;
		cout << "���-�� �����������: " << worstData.second.size() << endl << endl;

		run("���������� ��������", simplestPackagingGrigorev, worstData);
		run("First Fit", firstFitGolubeva, worstData);
		run("Best Fit", bestFitAllayarov, worstData);
		run("Tabu Search", TabuSearchOsadchenko, worstData);
		run("������������ ��������", GenerationsGlyb, worstData);
		run("���������� ��������", AntSolutionLeontev, worstData);
	}

	{
		cout << "=========== ����������� ������" << endl;
		cout << "���-�� ��������: " << impossibleData.first.size() << endl;
		cout << "���-�� �����������: " << impossibleData.second.size() << endl << endl;

		run("���������� ��������", simplestPackagingGrigorev, impossibleData);
		run("First Fit", firstFitGolubeva, impossibleData);
		run("Best Fit", bestFitAllayarov, impossibleData);
		run("Tabu Search", TabuSearchOsadchenko, impossibleData);
		run("������������ ��������", GenerationsGlyb, impossibleData);
		run("���������� ��������", AntSolutionLeontev, impossibleData);
	}

	return 0;
}