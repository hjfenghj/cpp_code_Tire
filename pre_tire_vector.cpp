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
	Node() { pass = 0; end = 0; nexts =vector<Node*>(26); }
};

struct returntype
{
	bool B;
	int N;
	returntype() { B = true; N = 0; }
};

Node get_Tire(vector<string> IN_STR)
{
	Node root;
	Node* cur_node = &root;
	for (int i = 0; i < IN_STR.size(); i++)
	{
		
		string cur_str = IN_STR[i];
		for (char c : cur_str)
		{
			int idx = c - 'a';
			if (cur_node->nexts[idx] == NULL)
			{
				cur_node->nexts[idx] = new Node();
			}
			cur_node = cur_node->nexts[idx];
			cur_node-> pass++;
		}
		cur_node->end++;
		cur_node = &root;
	}
	return root;
}

returntype node_query(Node& Tire,string s)
{
	returntype res;
	Node* cur_node_ptr = &Tire;
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

void delete_node(Node& Tire, string s)
{
	Node cur = Tire;
	if (node_query(Tire, s).N)
	{
		Node* root =&cur;
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

int main()
{
	vector<string> IN_STR = {"abcd" ,"abc","bck","abd","bce","arf" ,"abcef","abc"};
	string Q = "ab";
	string D = "abc";
	Node ROOT = get_Tire(IN_STR);
	returntype res = node_query(ROOT, Q);
	cout << res.B << " " << res.N << endl;
	delete_node(ROOT, D);
	delete_node(ROOT, D);
	delete_node(ROOT, D);
	returntype res1 = node_query(ROOT, "abc");
	cout << res1.B << " " << res1.N << endl;
	return 0;
}