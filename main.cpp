#include "b+-tree.h"
#include <iostream>
using namespace std;

int main(){
	int i=0;
	int opt=0;
	string a,b,c;
	cout << "Please initialize the tree(N for empty):"<< endl;
	cin >> a >> b >> c;
	cout << "the initial b+-tree will be:" << endl
	     << a << " " << b << " " << c << endl << endl
		 << "please select options:" << endl
		 << "1) insert node" << endl
		 << "2) delete node" << endl
		 << "3) print node" << endl
		 << "0) exit " << endl;
	while(true){
		cout << "> ";
		cin >> opt;
		switch((int)opt){
			case 1:
			cout << "input the number you want to insert: ";
			cin >> i;
			cout << "inserted." << endl;
			break;
			case 2:
			cout << "input the number you want to delete: ";
			cin >> i;
			cout << "deleted." << endl;
			break;
			case 3:
			cout << "printed." << endl;
			break;
			case 0:
			return 0;
			default:
			cout << "unknown option." << endl;
			break;
		}
	}
	return 0;
}