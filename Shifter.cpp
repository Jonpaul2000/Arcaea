#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool contains(string x, string target)
{
	int count = 0;
	for (int i = 0; x[i] != ';'; i++)
	{
		if (x[i] == target[count])
			count++;
		if (count == target.length())
			return true;
	}
	return false;
}

void setn(int num, int& n)
{
	vector<int> c = { 7912, 49120, 126920, 137470 };
	int narr[4];
	narr[0] = 7911;
	narr[1] = narr[0] + 9890 + 329;
	narr[2] = narr[1] + 10550;
	narr[3] = narr[2] + 10549;

	for (int i = 0; i < c.size(); i++)
	{
		if (num >= c[i])
			n = narr[i];
		else
			break;
	}
	
}

int main()
{
	string x = "Hello world 12345\n";
	ifstream readr("temp2.txt");
	string line;
	string res;
	string note;
	int n = 0;

	if (!readr.is_open())
	{
		cout << "Ha!" << endl;
		return 0;
	}

	while (readr.good())
	{
		// get note type
		getline(readr, line, '(');
		res = line + '(';
		note = line;

		// get number and add n
		getline(readr, line, ',');
		setn(stoi(line), n);
		int num = stoi(line) + n;
		res += to_string(num) + ',';

		// gett ending number and add n
		if (note == "hold" || note == "arc")
		{
			getline(readr, line, ',');
			num = stoi(line) + n;
			res += to_string(num) + ',';
		}

		// go to the end
		getline(readr, line, '\n');
		string temp = line;

		// edit arctap value
		if (contains(temp, "["))
		{
			int i = 0;
			while (temp[i] != ']')
			{
				string time;
				for (; temp[i] != '('; i++)
				{
					res += temp[i];
				}

				res += "(";
				i++;

				// edit the arctap value
				for (; temp[i] != ')'; i++)
					time += temp[i];

				num = stoi(time) + n;
				res += to_string(num) + ")";
				i++;
			}

			for (; i != temp.length(); i++)
				res += temp[i];
		}

		else
		{
			res += line;
		}

		cout << res << endl;
	}
}