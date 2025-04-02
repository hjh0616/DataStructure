#include<string>
#include"LinkedList.h"
using namespace std;

void printData(const string& data) {
    cout << "Data:" << data << '\n';
}

int main() {
    LinkedList<string> list;
    list.push_front("AAA");
    list.push_front("BBB");
    list.push_back("CCC");

    list.find("AAA");
    list.print();

    list.remove("AAA");
    list.find("AAA");
    list.print();

	list.traverse(printData);
    return 0;
}

