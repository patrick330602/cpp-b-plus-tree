#include "b+-tree.h"

bpt_node::bpt_node(){
	num=NULL;
	leaf=NULL;
	root_node=NULL;
	next_node=NULL;
	prev_node=NULL;
}

bpt_node::bpt_node(bool l, int d, bpt_node *f, bpt_node *n, bpt_node *p){
	leaf=l;
	num=d;
	root_node=f;
	next_node=n;
	prev_node=p;
}

bpt_node::~bpt_node(){
	num=NULL;
	leaf=NULL;
	root_node=NULL;
	next_node=NULL;
	prev_node=NULL;
	delete root_node;
	delete prev_node;
	delete next_node;
}

bpt_node bpt_node::GetNext(){
	return *next_node;
}

bpt_node bpt_node::GetPrev(){
	return *prev_node;
}

bpt_node bpt_node::GetRoot(){
	return *root_node;
}

bool bpt_node::IsLeaf(){
	return leaf;
}

int bpt_node::GetValue(){
	return num;
}
