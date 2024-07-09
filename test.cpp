#include "generator.h"
int main()
{
	Trie dic;
	string filename = "Dic.txt";
	bool flag = readFile(dic, filename);
	if(flag)
	{
		cout << "success!";
	}
	else
	{
		cout << "fail!";
	}
	cout << "print the dictionary: \n";
	//printTrie(dic);
	if(writeFile(dic))
	{
		cout << "1" << endl;
	}
	else
	{
		cout << "0" << endl;
	}
	cout << "enter letter(s): ";
	char n;
	string tmp = "";
	int y = 4;
	while(y)
	{
		cin >> n;
		tmp += n;
		--y;
	}
	cout << "string: " << tmp;
	set<string> permutations;
	int count = 0;
	set<string> list;
	permute(tmp, 0, tmp.length() - 1, permutations);
	for(set<string>::iterator it = permutations.begin(); it != permutations.end(); ++it)
	{
		if(dic.startWith(*it))
		{
			++count;
			list.insert(*it);
		}
	}
	cout << count << endl;
	cout << count << endl;
	for(set<string>::iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}