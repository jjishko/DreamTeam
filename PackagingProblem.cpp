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

	float share = 0;

	for (int ind : result)
	{
		share += data.second[ind];
	}

	share = share * 100 / std::accumulate(data.second.begin(), data.second.end(), 0);

	cout << "�������� ���������: " << methodName << endl;
	cout << "����� ������: " << time << " ���" << endl;
	cout << "���-�� ������� �����������: " << result.size() << endl;
	printf("���� �������� ������������: %.1f %%\n\n", share);
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL) + rand());

	pair<vector<int>, vector<int>> easyData = easyDataset();
	pair<vector<int>, vector<int>> rndData = randomDataset();
	pair<vector<int>, vector<int>> worstData = worstDataset();

	// �� ������� ���������� ���� �������� � main � ������� ������� run:
	// methodName - �������� ���������, 
	// foo - ��������� �� ������� ��������� (��� �������)
	// data - easyData
	{
		cout << "=========== ������ ������" << endl;
		cout << "���-�� �����������: " << easyData.second.size() << endl << endl;

		run("���������� ��������", simplestPackagingGrigorev, easyData);
		run("FirstFit ��������", firstFitGolubeva, easyData);
		run("���������� ��������", AntSolutionLeontev, easyData);

	}

	//�� �� �����, �� data = rndData
	{
		cout << "=========== ��������� ������" << endl;
		cout << "���-�� �����������: " << rndData.second.size() << endl << endl;

		run("���������� ��������", simplestPackagingGrigorev, rndData);
		run("FirstFit ��������", firstFitGolubeva, rndData);
		run("���������� ��������", AntSolutionLeontev, rndData);
	}

	//��������� ������ ������� ������� ������ - worstData
	{
		cout << "=========== ������ ������" << endl;
		cout << "���-�� �����������: " << worstData.second.size() << endl << endl;

		run("���������� ��������", simplestPackagingGrigorev, worstData);
		run("FirstFit ��������", firstFitGolubeva, worstData);
		run("���������� ��������", AntSolutionLeontev, worstData);
	}

	return 0;
}