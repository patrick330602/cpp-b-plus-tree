#include "b+-tree.h"

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

bpt_node* bpt_node::search(int d){
	int v = this->GetValue();
	if(d < v){
		return (!GetPrev())?GetPrev():GetPrev()->search(d);
	}
	else if(d > v){
		return (!GetNext())?GetNext():GetNext()->search(d);
	}
	else{
		return this;
	}
}
