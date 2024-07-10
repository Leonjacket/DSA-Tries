#include "generator.h"
int main()
{
	system("cls");
	Trie dic;
	string filename = "Dic.txt";

	if (readDic(dic, filename))
	{
		cout << "Dictionary read successfully !" << endl;
	}
	else
	{
		cerr << "Error: Cannot read dictionary file" << endl;
		return 0;
	}
	cout << "\n-> Enter letter(s): ";

	string input;
	getline(cin, input);

	cout << endl;

	string combined;
	for (char character : input)
	{
		if (character != ' ')
		{
			combined += character;
		}
	}

	set<string> subsets;
	getSubsets(combined, 0, "", subsets);

	set<string> validWords;
	for (const string &subset : subsets)
	{
		if (dic.search(subset))
		{
			validWords.insert(subset);
		}
	}
	cout << validWords.size() << endl;

	for (const string &word : validWords)
	{
		cout << word << endl;
	}

	return 0;
}