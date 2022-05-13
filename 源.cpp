#include<vector>
#include<iostream>
#include<string>

using namespace std;

class Node
{
public:
	int pass;
	int end;
	vector<Node*> nexts;
	Node() { pass = 0; end = 0; nexts = vector<Node*>(26); }
};

struct returntype
{
	bool B;
	int N;
	returntype() { B = true; N = 0; }
};

class Trie
{
private:
	Node* root;
public:
	Trie()
	{
		root = new Node();
	}
	void insert(string cur_str)
	{
		Node* cur_node = root;
		for (char c : cur_str)
		{
			int idx = c - 'a';
			if (cur_node->nexts[idx] == NULL)
			{
				cur_node->nexts[idx] = new Node();
			}
			cur_node = cur_node->nexts[idx];
			cur_node->pass++;
		}
		cur_node->end++;
	return;
	}

	returntype node_query(string s)
	{
		returntype res;
		Node* cur_node_ptr = root;
		for (char c : s)
		{
			int idx = c - 'a';
			if (cur_node_ptr->nexts[idx] == NULL)
			{
				res.B = false;
				res.N = 0;
				return res;
			}
			else
			{
				cur_node_ptr = cur_node_ptr->nexts[idx];
			}
		}
		res.N = cur_node_ptr->pass;
		if (res.B && cur_node_ptr->end == 0)
		{
			res.B = false;
		}
		return res;
	}

	void delete_node(string s)
	{
		if (node_query(s).N)
		{
			for (char c : s)
			{
				if (--(root->nexts[c - 'a']->pass) == 0)
				{
					root->nexts[c - 'a'] = NULL;
					return;
				}
				root = root->nexts[c - 'a'];
			}
			root->end--;
		}
		return;
	}


};


int main()
{
	Trie root;
	vector<string> IN_STR = { "abcd" ,"abc","bck","abd","bce","arf" ,"abcef","abc" };
	for (int i = 0; i < IN_STR.size(); i++)
	{
		root.insert(IN_STR[i]);
	}

	string Q = "ab";
	string D = "abc";
	returntype res = root.node_query(Q);
	cout << res.B << " " << res.N << endl;
	root.delete_node(D);
	root.delete_node(D);
	root.delete_node(D);
	returntype res1 = root.node_query("abc");
	cout << res1.B << " " << res1.N << endl;
	return 0;
}