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
