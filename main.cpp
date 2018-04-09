#include <iostream>
#include <sstream>
#include "BPlusTree.h"
#include "Definitions.h"
using namespace std;

string introMessage(int aOrder) {
    ostringstream oss;
    oss << "B+ Tree of Order " << aOrder << endl;
    oss << "Following Silberschatz, Korth, Sidarshan, Database Concepts, 5th ed." << endl;
    oss << "To build a B+ tree of a different order, start again and enter the order" << endl;
    oss << "as an integer argument:  bpt <order>  " << endl;
    oss << "(" << MIN_ORDER << " <= order <= " << MAX_ORDER << ")." << endl;
    oss << "To start with input from a file of newline-delimited integers," << endl;
    oss << "start again and enter the order followed by the filename:" << endl;
    oss << "bpt <order> <inputfile> ." << endl << endl;
    return oss.str();
}

string usageMessage() {
    string message =
    "Enter any of the following commands after the prompt > :\n"
    "\ti <k>  -- Insert <k> (an integer, <k> >= 0) as both key and value).\n"
    "\tf <k>  -- Find the value under key <k>.\n"
    "\tp <k> -- Print the path from the root to key k and its associated value.\n"
    "\tr <k1> <k2> -- Print the keys and values found in the range [<k1>, <k2>]\n"
    "\td <k>  -- Delete key <k> and its associated value.\n"
    "\tx -- Destroy the whole tree.  Start again with an empty tree of the same order.\n"
    "\tt -- Print the B+ tree.\n"
    "\tl -- Print the keys of the leaves (bottom row of the tree).\n"
    "\tv -- Toggle output of pointer addresses (\"verbose\") in tree and leaves.\n"
    "\tq -- Quit. (Or use Ctl-D.)\n"
    "\t? -- Print this help message.\n\n";
    return message;
}

int getOrder(int argc, const char * argv[]) {
    if (argc > 1) {
        int order = 0;
        istringstream iss(argv[1]);
        if ((iss >> order) && iss.eof() &&
            order >= MIN_ORDER && order <= MAX_ORDER) {
            return order;
        } else {
            cerr << "Invalid order specification: "
            << argv[1] << endl;
            cerr << "Order must be an integer such that " << MIN_ORDER
            << " <= <order> <= " << MAX_ORDER << endl;
            cerr << "Proceeding with order " << DEFAULT_ORDER << endl;
        }
    }
    return DEFAULT_ORDER;
}



int main(int argc, const char * argv[]) {
    char instruction;
    int key = 0;
    bool quit = false;
    bool verbose = false;
    int order = getOrder(argc, argv);
    cout << introMessage(order);
    cout << usageMessage();
    BPlusTree tree(order);
    if (argc > 2) {
        tree.readInputFromFile(argv[2]);
        cout << "Input from file " << argv[2] << ":" << endl;
        tree.print();
    }
    while (!quit)
    {
        cout << "> ";
        cin >> instruction;
        switch (instruction) {
            case 'd':
                cin >> key;
                tree.remove(key);
                tree.print(verbose);
                break;
            case 'i':
                cin >> key;
                if (key < 0) {
                    cout << usageMessage();
                }
                tree.insert(key, key);
                tree.print(verbose);
                break;
            case 'f':
                cin >> key;
                tree.printValue(key);
                break;
            case 'l':
                tree.printLeaves(verbose);
                break;
            case 'p':
                cin >> key;
                tree.printPathTo(key, verbose);
                break;
            case 'q':
                quit = true;
                break;
            case 'r':
                int key2;
                cin >> key;
                cin >> key2;
                tree.printRange(key, key2);
                break;
            case 't':
                tree.print(verbose);
                break;
            case 'v':
                verbose = !verbose;
                tree.print(verbose);
                break;
            case 'x':
                tree.destroyTree();
                tree.print();
                break;
            case '?':
                cout << usageMessage();
                break;
            default:
                cin.ignore(256, '\n');
                cout << usageMessage();
                break;
        }
    }
    return 0;
}
