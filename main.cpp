#include <iostream>
#include <sstream>
#include "BPlusTree.h"
#include "Definitions.h"
using namespace std;

string introMessage() {
    ostringstream oss;
    oss << "B+ Tree of Order 4" << endl;
	oss << "By Dhaval, Jinming, and Tim" << endl;
    oss << "-------------------" << endl;
	oss << "Here, we will initial the B+ Tree." << endl;
    return oss.str();
}

string usageMessage() {
    string message =
    "Commands\n"
	"------------------------------------------------------------------\n"
    "i -- Insert an integer i where i >= 0.\n"
    "d -- Delete key and its associated value.\n"
    "r -- Destroy the whole tree.\n"
    "p -- Print the B+ tree.\n"
    "q -- Quit.\n"
    "? -- Print this help message.\n\n";
    return message;
}

int main(int argc, const char * argv[]) {
    char instruction;
    int key = 0;
	int num_val = 0;
    bool quit = false;
    cout << introMessage();
    BPlusTree tree(4);
	cout << "Please input number of the values you want to input: ";
	cin >> num_val;
	cout << "Please input values, seperated by space: " << endl;
	while(num_val){
		cin >> key;
		tree.insert(key,key);
		num_val--;
	}
	cout << "Initialized. Printing current tree..." << endl;
	tree.print(false);
	cout << "Entering interactive prompt..." << endl;
    while (!quit)
    {
        cout << "> ";
        cin >> instruction;
        switch (instruction) {
            case 'd':
				cout << "[DELETE]> ";
                cin >> key;
                tree.remove(key);
                tree.print(false);
                break;
            case 'i':
				cout << "[INSERT]> ";
                cin >> key;
                if (key < 0) {
                    cout << "Invalid input.";
					break;
                }
                tree.insert(key, key);
                tree.print(false);
                break;
            case 'q':
                quit = true;
                break;
            case 'p':
                tree.print(false);
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
