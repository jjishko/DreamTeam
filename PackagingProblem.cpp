//ÊÎÌÌÅÍÒÀÐÈÈ È ÊÎÄ ÊÀÐÊÀÑÀ ÍÅ ÌÅÍßÒÜ!
/*
1) Íàïèñàòü àëãîðèòì â îòäåëüíîì cpp ôàéëå 
	(ïðèìåð è èíñòðóêöèè â SimplestPackagingGrigorev.cpp)
2) Ñîçäàòü îáúÿâëåíèå ôóíêöèè â Team.h
3) Âûçâàòü ôóíêöèþ àëãîðèòìà â main
4) Ïðîâåðèòü ðàáîòîñïîñîáíîñòü êîäà, ÷òîáû íå ïîëîæèòü ïðîåêò
5) Âûëîæèòü â ðåïîçèòîðèé GitHub (â îòäåëüíóþ âåòêó!)
6) Èäåì òóñèòü
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

	cout << "Íàçâàíèå àëãîðèòìà: " << methodName << endl;
	cout << "Âðåìÿ ðàáîòû: " << time << " ìêñ" << endl;
	cout << "Êîë-âî çàíÿòûõ êîíòåéíåðîâ: " << result.size() << endl;
	printf("Äîëÿ çàíÿòîãî ïðîñòðàíñòâà: %.1f %%\n\n", share);
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL) + rand());

	pair<vector<int>, vector<int>> easyData = easyDataset();
	pair<vector<int>, vector<int>> rndData = randomDataset();
	pair<vector<int>, vector<int>> worstData = worstDataset();

	// Ïî îáðàçöó äîáàâëÿåòå ñâîé àëãîðèòì â main ñ ïîìîùüþ ôóíêöèè run:
	// methodName - íàçâàíèå àëãîðèòìà, 
	// foo - óêàçàòåëü íà ôóíêöèþ àëãîðèòìà (èìÿ ôóíêöèè)
	// data - easyData
	{
		cout << "=========== ËÓ×ØÈÅ ÄÀÍÍÛÅ" << endl;
		cout << "Êîë-âî êîíòåéíåðîâ: " << easyData.second.size() << endl << endl;

		run("Ïðîñòåéøàÿ óïàêîâêà", simplestPackagingGrigorev, easyData);
		run("Ìóðàâüèíûé àëãîðèòì", AntSolutionLeontev, easyData);
		run("Tabu Search", TabuSearchOsadchenko, easyData);
		run("Àëãîðèòì Best Fit", bestFitAllayarov, easyData);

	}

	//Òî æå ñàìîå, íî data = rndData
	{
		cout << "=========== ÑËÓ×ÀÉÍÛÅ ÄÀÍÍÛÅ" << endl;
		cout << "Êîë-âî êîíòåéíåðîâ: " << rndData.second.size() << endl << endl;

		run("Ïðîñòåéøàÿ óïàêîâêà", simplestPackagingGrigorev, rndData);
		run("Ìóðàâüèíûé àëãîðèòì", AntSolutionLeontev, rndData);
		run("Tabu Search", TabuSearchOsadchenko, rndData);
		run("Àëãîðèòì Best Fit", bestFitAllayarov, rndData);
	}

	//Ïåðåäàåòå õóäøèé âàðèàíò âõîäíûõ äàííûõ - worstData
	{
		cout << "=========== ÕÓÄØÈÅ ÄÀÍÍÛÅ" << endl;
		cout << "Êîë-âî êîíòåéíåðîâ: " << worstData.second.size() << endl << endl;

		run("Ïðîñòåéøàÿ óïàêîâêà", simplestPackagingGrigorev, worstData);
		run("Ìóðàâüèíûé àëãîðèòì", AntSolutionLeontev, worstData);
		run("Tabu Search", TabuSearchOsadchenko, worstData);
		run("Àëãîðèòì Best Fit", bestFitAllayarov, worstData);
	}

	return 0;
}