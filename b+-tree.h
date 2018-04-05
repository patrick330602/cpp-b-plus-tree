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
		bpt_node();
		bpt_node(bool l, int d, bpt_node *f, bpt_node *n, bpt_node *p);
		~bpt_node();

		bpt_node GetNext();
		bpt_node GetPrev();
		bpt_node GetRoot();
		bool IsLeaf();
		int GetValue();

		bpt_node search(int d);
		bpt_node ins(int d);
		bpt_node del(int d);
		void print(bpt_node top_node);
};



