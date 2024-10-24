#include <vector>
#include <unordered_set>

#include "Team.h"

using std::vector;
using std::unordered_set;

/*
 - На вход подаются векторы размеров объектов и контейнеров
	(подаются константно, если необходимо, создаете копию внутри своей функции)
 - На выход получаем сет индексов НЕПУСТЫХ контейнеров
	(если по данному алгоритму нельзя упаковать все объекты, возвращается пустой вектор)
 - Функцию алгоритма называем со своей фамилией, использовать верблюжий регистр
	(кароч аналогично нижней функции свои называйте)
 - Здесь ничего не делаем, вся реализация в своих cpp файлах в папке репозитория
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