#include <iostream>
using namespace std;

struct bpt_node{
	int *data;
	int n;
	bool leaf;
	bpt_node *root_node;
	bpt_node *next_node;
	bpt_node *prev_node;
}


