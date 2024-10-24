#include <vector>
#include <unordered_set>

#include "Team.h"

using std::vector;
using std::unordered_set;

/*
 - �� ���� �������� ������� �������� �������� � �����������
	(�������� ����������, ���� ����������, �������� ����� ������ ����� �������)
 - �� ����� �������� ��� �������� �������� �����������
	(���� �� ������� ��������� ������ ��������� ��� �������, ������������ ������ ������)
 - ������� ��������� �������� �� ����� ��������, ������������ ��������� �������
	(����� ���������� ������ ������� ���� ���������)
 - ����� ������ �� ������, ��� ���������� � ����� cpp ������ � ����� �����������
*/

unordered_set<int> simplestPackagingGrigorev(const vector<int>& objects,
	const vector<int>& containers)
{
	int thisContainer;
	int posOfObject = 0;
	int posOfContainer = 0;
	unordered_set<int> filledContainers;

	while (posOfContainer < containers.size())
	{
		thisContainer = containers.at(posOfContainer);

		while (thisContainer - objects.at(posOfObject) >= 0)
		{
			thisContainer -= objects.at(posOfObject++);

			if (posOfObject == objects.size())
			{
				filledContainers.insert(posOfContainer);
				return filledContainers;
			}
		}

		filledContainers.insert(posOfContainer++);

	}

	filledContainers.clear();
	return filledContainers;
}