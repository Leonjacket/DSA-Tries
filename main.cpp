#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <set>
#include <algorithm>
using namespace std;
struct Node
{
	Node *child[26];
	bool flag;
	Node()
	{
		for (int i = 0; i < 26; ++i)
		{
			child[i] = NULL;
		}
		flag = false;
	}
	bool containsKey(char ch)
	{
		return (child[ch - 'a'] != NULL);
	}
	void put(char ch, Node *node)
	{
		child[ch - 'a'] = node;
	}
	Node *get(char ch)
	{
		return (child[ch - 'a']);
	}
	bool setEnd()
	{
		flag = true;
		return flag;
	}
	bool isEnd()
	{
		return flag;
	}
};
struct Trie
{
	Node *root;
	Trie()
	{
		root = new Node();
	}
	void insert(string word)
	{
		Node *node = root;
		for (int i = 0; i < word.length(); ++i)
		{
			if (!node->containsKey(word[i]))
			{
				node->put(word[i], new Node());
			}
			node = node->get(word[i]);
		}
		node->setEnd();
	}

	bool search(string word)
	{
		Node *node = root;
		for (int i = 0; i < word.length(); ++i)
		{
			if (!node->containsKey(word[i]))
			{
				return false;
			}
			node = node->get(word[i]);
		}
		return node->isEnd();
	}

	bool startWith(string prefix)
	{
		Node *node = root;
		for (int i = 0; i < prefix.length(); ++i)
		{
			if (!node->containsKey(prefix[i]))
			{
				return false;
			}
			node = node->get(prefix[i]);
		}
		return true;
	}
};
bool readDic(Trie &dic, string filename)
{
	ifstream input;
	input.open(filename.c_str());
	if (!input.is_open())
	{
		return false;
	}
	string line;
	while (getline(input, line))
	{
		dic.insert(line);
	}
	input.close();
	return true;
}
void permute(string &a, int l, int r, set<string> &permutations)
{
	if (l == r)
	{
		permutations.insert(a);
	}
	else
	{
		for (int i = l; i <= r; ++i)
		{
			swap(a[l], a[i]);
			permute(a, l + 1, r, permutations);
			swap(a[l], a[i]);
		}
	}
}
void getSubsetsAndPermutations(const string &input, int index, string current, set<string> &subsets)
{
	if (index == input.length())
	{
		if (current.length() >= 3)
		{
			subsets.insert(current);
			permute(current, 0, current.length() - 1, subsets);
			subsets.insert(current);
		}
		return;
	}
	getSubsetsAndPermutations(input, index + 1, current + input[index], subsets);
	getSubsetsAndPermutations(input, index + 1, current, subsets);
}

int main()
{
	system("cls");
	Trie dic;
	string filename = "Dic.txt";

	readDic(dic, filename);

	string input;
	getline(cin, input);

	string combined;
	for (char character : input)
	{
		if (character != ' ')
		{
			combined += character;
		}
	}

	set<string> subsets;
	getSubsetsAndPermutations(combined, 0, "", subsets);

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