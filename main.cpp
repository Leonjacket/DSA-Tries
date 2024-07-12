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
};
bool buildTrie(Trie &dic, string filename)
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
string getInput()
{
	string raw_input;
	getline(cin, raw_input);
	string lowercaseInput;
	for (char character : raw_input)
	{
		lowercaseInput += tolower(character);
	}
	sort(lowercaseInput.begin(), lowercaseInput.end());
	string combined;
	for (char character : lowercaseInput)
	{
		if (character != ' ')
		{
			combined += character;
		}
	}
	return combined;
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

// Reference resources :
// https://www.youtube.com/watch?v=-urNrIAQnNo - Trie Data Structure
// https://youtu.be/dBGUmUQhjaM?si=KqC_w4d7CwmdSf93 - Trie Data Structure
// https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/amp/ ( Permutations function )
// https://www.geeksforgeeks.org/find-all-unique-subsets-of-a-given-set-using-c-stl/ ( Subsets function )
// ChatGPT for the idea of combining Subset with Permutations.

int main()
{
	system("cls");

	Trie dic; // Create a Trie

	string filename = "Dic.txt";

	buildTrie(dic, filename); // Build the Trie from the Dic.txt

	string input = getInput(); // Get the input which meets requirements in the Proj.pdf

	set<string> subsets;
	getSubsetsAndPermutations(input, 0, "", subsets); // From the combined, generate all the subsets and permutations

	set<string> validWords;
	for (const string &subset : subsets)
	{
		if (dic.search(subset))
		{
			validWords.insert(subset);
		}
	} // Check if the word is available in the Trie

	cout << validWords.size() << endl;
	for (const string &word : validWords)
	{
		cout << word << endl;
	} // Print out the result

	return 0;
}