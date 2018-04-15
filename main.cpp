#include <iostream>
#include "Tree.h"
using namespace std;


int main() {
    char instruction;
    int key = 0;
    int num_val = 0;
    bool quit = false;
	string usage =
    "Commands\n"
    "------------------------------------------\n"
    "i -- Insert an integer i where i >= 0.\n"
    "d -- Delete key and its associated value.\n"
    "r -- Destroy the whole tree.\n"
    "q -- Quit.\n"
    "? -- Print help message.\n\n";

    cout << "B+ Tree of Order 4\n" 
	     << "By Dhaval Shah, Jinming Wu, and Tim Krato\n"
		 << "-------------------\n"
		 << "This program will build B+ Tree interactively.\n"
		 << "We assume that all input are unique. If the i-\n"
		 << "-nput is not unique and found its existence in\n"
		 << "the tree, operation will still be executed but\n"
		 << "tree will not change.\n\n";
    Tree tree(4);
    cout << "Here, we will initial the B+ Tree.\n\nPlease input number of the values you want to input: \n> ";
    cin >> num_val;
    cout << "\nPlease input values, seperated by space: \n> ";
    while(num_val){
        cin >> key;
        tree.insert(key,key);
        num_val--;
    }
    cout << "\n:: Initialized. Printing current tree...\n\n";
    tree.print();
    cout << "\n:: Entering interactive prompt...\n\n";
    cout << usage;
    while (!quit)
    {
        cout << "> ";
        cin >> instruction;
        switch (instruction) {
            case 'd':
                cout << "[DELETE]> ";
                cin >> key;
                tree.remove(key);
				cout << "\n:: Delete operation complete. Printing current tree...\n\n";
                tree.print();
                break;
            case 'i':
                cout << "[INSERT]> ";
                cin >> key;
                if (key < 0) {
                    cout << "Invalid input.";
                    break;
                }
                tree.insert(key, key);
                cout << "\n:: Insert operation complete. Printing current tree...\n\n";
                tree.print();
                break;
            case 'q':
                quit = true;
                break;
            case 'r':
                tree.destroyTree();
                cout << ":: Tree destoryed.\n";
                tree.print();
                break;
            case '?':
                cout << usage;
                break;
            default:
                cin.ignore(256, '\n');
                cout << "invalid commands. \n\n" << usage;
                break;
        }
    }
    return 0;
}
