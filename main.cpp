#include <iostream>
#include "BPlusTree.h"
using namespace std;


string introMessage() {
    string message =
    "B+ Tree of Order 4\n"
	"By Dhaval Shah, Jinming Wu, and Tim Krato\n"
    "-------------------\n";
	return message;
}

string usageMessage() {
    string message =
    "Commands\n"
	"------------------------------------------\n"
    "i -- Insert an integer i where i >= 0.\n"
    "d -- Delete key and its associated value.\n"
    "r -- Destroy the whole tree.\n"
    "q -- Quit.\n"
    "? -- Print help message.\n\n";
    return message;
}

int main() {
    char instruction;
    int key = 0;
	int num_val = 0;
    bool quit = false;
    cout << introMessage();
    BPlusTree tree(4);
	cout << "Here, we will initial the B+ Tree.\n\nPlease input number of the values you want to input: ";
	cin >> num_val;
	cout << "Please input values, seperated by space: \n";
	while(num_val){
		cin >> key;
		tree.insert(key,key);
		num_val--;
	}
	cout << ":: Initialized. Printing current tree...\n\n";
	tree.print();
	cout << "\n:: Entering interactive prompt...\n\n";
	cout << usageMessage();
    while (!quit)
    {
        cout << "> ";
        cin >> instruction;
        switch (instruction) {
            case 'd':
				cout << "[DELETE]> ";
                cin >> key;
                tree.remove(key);
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
                tree.print();
                break;
            case 'q':
                quit = true;
                break;
            case 'r':
                tree.destroyTree();
                tree.print();
                break;
            case '?':
                cout << usageMessage();
                break;
            default:
                cin.ignore(256, '\n');
                cout << "invalid commands. \n\n" << usageMessage();
                break;
        }
    }
    return 0;
}
