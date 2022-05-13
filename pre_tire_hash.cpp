#include<vector>
#include<iostream>
#include<string>
#include<map>

using namespace std;

class Node
{
public:
	int pass;
	int end;
	map<char,Node*> nexts;
	Node() { pass = 0; end = 0; }
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
			if (cur_node->nexts.find(c) == cur_node->nexts.end())
			{
				cur_node->nexts.emplace(c, new Node());
			}
			cur_node = cur_node->nexts.find(c)->second;
			cur_node->pass++;
		}
		cur_node->end++;
		cur_node = &root;
	}
	return root;
}

returntype node_query(Node& Tire, string s)
{
	returntype res;
	Node* cur_node_ptr = &Tire;
	for (char c : s)
	{
		if (cur_node_ptr->nexts.find(c) == cur_node_ptr->nexts.end())
		{
			res.B = false;
		}
		else
		{
			cur_node_ptr = cur_node_ptr->nexts.find(c)->second;
		}
	}
	res.N = cur_node_ptr->pass;
	if (res.B && cur_node_ptr->end == 0)
	{
		res.B = false;
	}
	return res;
}



int main()
{
	vector<string> IN_STR = { "abc","bck","abd","bce","arf" };
	string Q = "abcd";
	Node ROOT = get_Tire(IN_STR);
	returntype res = node_query(ROOT, Q);
	cout << res.B << " " << res.N << endl;
	return 0;

}