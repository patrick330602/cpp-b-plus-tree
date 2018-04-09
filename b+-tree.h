#include <iostream>
using namespace std;

class bpt_node
{
	private:
		int num;
		bool leaf;
		bpt_node *root_node;
		bpt_node *next_node;
		bpt_node *prev_node;
	public:
		bpt_node(): num(-1), leaf(NULL), root_node(NULL), next_node(NULL), prev_node(NULL) {}
		bpt_node(bool l, int d, bpt_node *f, bpt_node *n, bpt_node *p):num(d), leaf(l), root_node(f),next_node(n), prev_node(p) {}
		~bpt_node();

		bpt_node* GetNext(){return next_node;}
		bpt_node* GetPrev(){return prev_node;}
		bpt_node* GetRoot(){return root_node;}
		bool IsLeaf(){return leaf;}
		int GetValue(){return num;}

		bpt_node* search(int d);
		bpt_node ins(int d);
		bpt_node del(int d);
		void print(bpt_node top_node);
};



