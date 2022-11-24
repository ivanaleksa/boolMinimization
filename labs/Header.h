#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int bin_to_dec(string bin_number, const int& lenght) {
	int res = 0;
	for (int i = lenght - 1; i >= 0; i--) {
		res += (int(bin_number[i]) - 48) * pow(2, lenght - i - 1);
	}
	return res;
}

string dec_to_bin(int number, const int& n) {
	string bin = "", res = "";
	while (number != 0) {
		bin += char(number % 2 + 48);
		number /= 2;
	}
	for (int i = n - 1; i >= 0; i--)
		if (i >= bin.size()) res += "0";
		else res += bin[i];
	return res;
}

vector<string> return_single_set(string bin_number, const int& lenght, const int& n) {
	vector<string> res;
	for (int i = 0; i < lenght; i++)
		if (int(bin_number[i]) == 49) res.push_back(dec_to_bin(i, n));
	return res;
}

vector<string> return_zero_set(string bin_number, const int& lenght, const int& n) {
	vector<string> res;
	for (int i = 0; i < lenght; i++)
		if (int(bin_number[i]) == 48) res.push_back(dec_to_bin(i, n));
	return res;
}

vector<string> return_AlphabetSingle_set(string bin_number, const int& lenght, const int& n) {
	vector<string> res;
	string alphabet = "";

	for (int i = 0; i < n; i++) alphabet += char(97 + i);
	for (int i = 0; i < n; i++) alphabet += char(65 + i);

	for (int i = 0; i < lenght; i++)
		if (int(bin_number[i]) == 49) {
			 string bin_def = dec_to_bin(i, n), alp_def = "";
			 for (int j = 0; j < bin_def.size(); j++) {
				 if (int(bin_def[j]) == 49) alp_def += alphabet[j];
				 else alp_def += alphabet[j + n];
			 }
			 res.push_back(alp_def);
		}
	return res;
}

void func_number(string bin_number, const int& lenght) {
	cout << bin_to_dec(bin_number, lenght) << endl;
}

void single_set(string bin_number, const int& lenght, const int& n) {
	vector<string> res = return_single_set(bin_number, lenght, n);
	for (string s : res) cout << s << endl;
}

void SDNF(string bin_number, const int& lenght, const int& n) {
	vector<string> needed_sets = return_single_set(bin_number, lenght, n);
	string result = "", alphabet = "";

	for (int i = 0; i < n; i++) alphabet += char(97 + i);
	for (int i = 0; i < n; i++) alphabet += char(65 + i);

	for (int j = 0; j < needed_sets.size(); j++) {
		for (int i = 0; i < needed_sets[j].size(); i++) {
			if (int(needed_sets[j][i]) == 49) result += alphabet[i];
			else result += alphabet[i + n];
		}
		if (j != needed_sets.size() - 1)
			result += " v ";
	}
	cout << result << endl;
}

void SKNF(string bin_number, const int& lenght, const int& n) {
	vector<string> needed_sets = return_zero_set(bin_number, lenght, n);
	string result = "", alphabet = "";

	for (int i = 0; i < n; i++) alphabet += char(97 + i);
	for (int i = 0; i < n; i++) alphabet += char(65 + i);

	for (int j = 0; j < needed_sets.size(); j++) {
		result += "(";
		for (int i = 0; i < needed_sets[j].size(); i++) {
			if (int(needed_sets[j][i]) == 49) result += alphabet[i];
			else result += alphabet[i + n];
			if (i != needed_sets[j].size() - 1)
				result += " v ";
		}
		result += ")";
	}
	cout << result << endl;
}

string dummy_var(string bin_number, const int& lenght, const int& n) {
	string alphabet = "", res = "";

	for (int i = 0; i < n; i++) alphabet += char(97 + i);

	for (int i = 0; i < n; i++) {
		int step = pow(2, n - i - 1), last_div = 0;
		string vec1 = "", vec2 = "";
		for (int j = 0; j < lenght; j++) {
			if (last_div == int(j / step)) {
				vec1 += bin_number[j];
				if (int((j + 1) / step) != int(j / step))
					last_div = j / step;
			}
			else {
				vec2 += bin_number[j];
				if (int((j + 1) / step) != int(j / step))
					last_div = (j + 1) / step;
			}
		}
		if (vec1 == vec2) res += alphabet[i];
	}
	if (res.size() == 0) return "There's no dummy vars :(";
	return res;
}

int countUnit(string set) {
	int res = 0;
	for (int i = 0; i < set.size(); i++) if (int(set[i]) >= 97 && int(set[i]) <= 122) res++;
	return res;
}

bool checkValuableGlue(string set1, string set2, int k) {
	int countSame = 0, checkNotSameChar = 0;
	for (int c = 0; c < k; c++) {
		if (set1[c] == set2[c]) countSame++;
		else
			if (abs(int(set1[c]) - int(set2[c])) == 32) checkNotSameChar++;
	}
	return countSame == k - 1 && checkNotSameChar == 1;
}

bool check_exit(vector<string> sets, int n) {
	for (int i = 0; i < sets.size() - 1; i++) {
		for (int j = i + 1; j < sets.size(); j++) {
			if (checkValuableGlue(sets[i], sets[j], n)) return true;
		}
	}
	return false;
}

string gluing(string set1, string set2, int k) {
	string res = "";
	for (int i = 0; i < k; i++) {
		if (set1[i] == set2[i]) res += set1[i];
	}
	return res;
}

bool hasThisImpInSet(string imp, string set){
	int count = 0;
	for (int i = 0; i < imp.size(); i++) {
		for (int j = 0; j < set.size(); j++) {
			if (imp[i] == set[j]) count++;
		}
	}
	return count == imp.size();
}

vector<string> findMin(vector<string> allSets) {
	vector<string> res;
	vector<int> lenght_string;
	for (int i = 0; i < allSets.size(); i++) {
		int k = 0;
		for (int j = 0; j < allSets[i].size(); j++) {
			if ((allSets[i][j] >= 65 && allSets[i][j] <= 90) || (allSets[i][j] >= 97 && allSets[i][j] <= 122))
				k++;
		}
		lenght_string.push_back(k);
	}
	int min = 10000000;
	for (int i = 0; i < lenght_string.size(); i++)
		if (lenght_string[i] < min) min = lenght_string[i];

	for (int i = 0; i < lenght_string.size(); i++) {
		if (lenght_string[i] == min)
			res.push_back(allSets[i]);
	}
	return res;
}

vector<string> minimization(vector<string> single_sets, const int& n) {
	// методом Квайна
	string core = "";
	vector<string> res;
	bool f = true;
	int k = n;
	vector<string> sets, tmp_res, s_sets = single_sets;

	// определение первичных импликант
	while (f) {
		if (n == 1) {
			sets.push_back(single_sets[0]);
		}
		else if (n == 2) {
			if (checkValuableGlue(single_sets[0], single_sets[1], k))
			{
				sets.push_back(gluing(single_sets[0], single_sets[1], k));

				// отмечает склеенные наборы
				if (single_sets[0].size() == k)
					single_sets[0] += "*";
				if (single_sets[1].size() == k)
					single_sets[1] += "*";
			}
		}
		else {
			for (int i = 0; i < single_sets.size() - 1; i++) { // проходимся по всем наборам
				for (int j = i + 1; j < single_sets.size(); j++) {
					// если одинаковых символов ровно на один меньше чем длина наборов, то склеиваем
					if (checkValuableGlue(single_sets[i], single_sets[j], k))
					{
						sets.push_back(gluing(single_sets[i], single_sets[j], k));

						// отмечает склеенные наборы
						if (single_sets[i].size() == k)
							single_sets[i] += "*";
						if (single_sets[j].size() == k)
							single_sets[j] += "*";
					}
				}
			}
		}

		// проверяем склеиваемые наборы на их склейку, если не был склеен, то добавляем его в промежуточный  результат
		for (int i = 0; i < single_sets.size(); i++)
			if (single_sets[i].size() == k) {
				bool fl = false;
				int j = 0;
				if (tmp_res.size() == 0) tmp_res.push_back(single_sets[i]);
				else {
					while (j < tmp_res.size() && !fl) {
						if (tmp_res[j] == single_sets[i]) fl = true;
						j++;
					}
					if (!fl) tmp_res.push_back(single_sets[i]);
				}
			}

		k--;

		if (!check_exit(sets, k)) {// проверка на возможность склейки хотя бы одной пары
			f = false;
			for (int i = 0; i < sets.size(); i++) {
				bool fl = false;
				int j = 0;
				if (tmp_res.size() == 0) tmp_res.push_back(sets[i]);
				else {
					while (j < tmp_res.size() && !fl) {
						if (tmp_res[j] == sets[i]) fl = true;
						j++;
					}
					if (!fl) tmp_res.push_back(sets[i]);
				}
			}
		}

		single_sets = sets;
		sets = {};
	}

	//cout << "Первичные импликанты: ";
	//for (int i = 0; i < tmp_res.size(); i++) cout << tmp_res[i] << " ";
	//cout << endl;

	// расстановка меток и составление минимальной формы

	// начальная инициализация таблицы меток
	vector<vector<string>> table, table_without_core;
	for (int i = 0; i < s_sets.size() + 1; i++) {
		vector<string> tmp;
		for (int j = 0; j < tmp_res.size() + 1; j++) {
			if (i == 0 && j == 0) tmp.push_back("0");
			else tmp.push_back("");
		}
		table.push_back(tmp);
	}

	// заполнение ед.наборов и полученных первичных импликант
	for (int i = 0; i < s_sets.size() + 1; i++) {
		for (int j = 0; j < tmp_res.size() + 1; j++) {
			if (j == 0 && i != 0) 
				table[i][j] = s_sets[i - 1];
			else if (i == 0 && j != 0)
				table[i][j] = tmp_res[j - 1];
			if (i != 0 && j != 0) {
				if (hasThisImpInSet(table[0][j], table[i][0])) table[i][j] = "1";
			}
		}
	}

	//cout << "Таблица меток:\n";
	//for (int i = 0; i < s_sets.size() + 1; i++) {
	//	for (int j = 0; j < tmp_res.size() + 1; j++) {
	//		cout << setw(n) << table[i][j] << " ";
	//	}
	//	cout << "\n";
	//}
	
	int k_sets = 0;
	// формирование ядра и отметка покрываемых им наборов
	for (int i = 1; i < table.size(); i++) {
		int count = 0, j_n = 0;
		for (int j = 1; j < table[i].size(); j++) {
			if (table[i][j] == "1") {
				count++;
				j_n = j;
			}
		}

		if (count == 1 && table[0][j_n][table[0][j_n].size() - 1] != '*') {
			core += table[0][j_n] + " V ";
			table[0][j_n] += '*';

			for (int j = 0; j < table.size(); j++) {
				if (table[j][j_n] == "1" && table[j][0].size() == n) {
					table[j][0] += "*";
					k_sets++;
				}
			}
		}
	}

	// если ядро уже покрывает все наборы
	if (k_sets == table.size() - 1) {
		res.push_back(core.substr(0, core.size() - 2));
		return res;
	}

	// отбрасывание ядра и уже покрытых наборов
	for (int i = 0; i < s_sets.size() + 1; i++) {
		vector<string> tmp;
		if (i == 0) {
			for (int j = 0; j < tmp_res.size() + 1; j++)
				if (table[i][j][table[i][j].size() - 1] != '*' || table[i][j] == "0")
					tmp.push_back(table[i][j]);
			table_without_core.push_back(tmp);
		}
		else if (table[i][0].size() == n) {
			for (int j = 0; j < tmp_res.size() + 1; j++)
				if (table[0][j][table[0][j].size() - 1] != '*')
					tmp.push_back(table[i][j]);
			table_without_core.push_back(tmp);
		}
	}

	vector<string> all_forms; // будет хранить все формы (вместе с ядром), которые покрывают все наборы. Потом уже из них будем выбирать мин. формы
	for (int j = 0; j < table_without_core[0].size(); j++) { // перебор кол-ва наборов, которые мы берем (0-8)
		string need_sets = ""; // будем перебирать все перестановки (все комбинаций). Если 1, то берём набора под этим индексов, если 0, то не берем
		for (int i = 0; i < table_without_core[0].size() - j - 1; i++) need_sets += "0";
		for (int i = 0; i < j; i++) need_sets += "1";

		// перебор всех сочетаний первичных импликант и формирование формул, которые покрывают все единичные наборы
		while (1) {
			//cout << need_sets << "\n";
			string tmp = core;
			vector<vector<string>> tmp_table_without_core = table_without_core;
			// работаем с перестановками, их анализиуем тут
			for (int i = 0; i < need_sets.size(); i++) {
				if (need_sets[i] == '1') {
					for (int q = 1; q < tmp_table_without_core.size(); q++) {
						if (tmp_table_without_core[q][i + 1] == "1") tmp_table_without_core[q][0] += "*";
					}
					tmp += tmp_table_without_core[0][i + 1] + " V ";
				}
			}
			// если, данное выражение не покрывает все наборы, то его добавлять не нужно ЭТО НУЖНО ПРОВЕРИТЬ
			bool isItFill = true;
			for (int i = 1; i < tmp_table_without_core.size(); i++) {
				if (tmp_table_without_core[i][0][tmp_table_without_core[i][0].size() - 1] != '*') isItFill = false;
			}

			if (isItFill) all_forms.push_back(tmp.substr(0, tmp.size() - 2));

			if (!next_permutation(begin(need_sets), end(need_sets))) break;
		}
	}
	//for (int i = 0; i < all_forms.size(); i++) cout << all_forms[i] << "\n";

	res = findMin(all_forms);

	//for (int i = 0; i < table_without_core.size(); i++) {
	//	for (int j = 0; j < table_without_core[i].size(); j++)
	//		cout << setw(n) << table_without_core[i][j] << " ";
	//	cout << endl;
	//}

	return res;
}

void fromFirstTillFifthTask() {
	int n;
	string bin_number;
	cin >> n;
	cin >> bin_number;
	int lenght = bin_number.size();
	if (lenght != pow(2, n)) cout << "Error! Invalid vector.";
	else {
		cout << "----Номера функции" << endl;
		func_number(bin_number, lenght);

		cout << endl << "----#Единичные наборы" << endl;
		single_set(bin_number, lenght, n);

		cout << endl << "----#СДНФ" << endl;
		if (return_single_set(bin_number, lenght, n).size() == 0) cout << "There is none of single sets";
		else SDNF(bin_number, lenght, n);

		cout << endl << "----#СКНФ" << endl;
		if (return_zero_set(bin_number, lenght, n).size() == 0) cout << "There is none of zero sets";
		else
			SKNF(bin_number, lenght, n);

		cout << endl << "----#Фиктивные переменные" << endl;
		cout << dummy_var(bin_number, lenght, n) << "\n\n";

		cout << endl << "----#Минимизация" << endl;
		if (return_zero_set(bin_number, lenght, n).size() == 0) cout << "1\n";
		else if (return_single_set(bin_number, lenght, n).size() == 0) cout << "0\n";
		else {
			vector<string> res = minimization(return_AlphabetSingle_set(bin_number, lenght, n), n);
			for (int i = 0; i < res.size(); i++) cout << res[i] << "\n";
			cout << res.size();
		}
	}
}