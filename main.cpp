#include "xorLL.hpp"
#include <iostream>

int main() {
    XORLinkedList<int> list;
	for (int i : {5, 6, 7, 8, 9}) list.push_back(i);
	for (int i : {4, 3, 2, 1}) list.push_front(i);

	std::cout << list << std::endl;

	for (int i : list) std::cout << i << " ";
	std::cout << std::endl;
	
    std::cout << "Print wiht rbegin() and rend()\n";
	for (auto it = list.rbegin();it != list.rend(); --it) {
		*it += 10;
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	auto l = [](int val) {
		std::cout << val << " ";
	};
    
    std::cout <<"\nPrint wiht for_each\n";
	std::for_each(list.begin(), list.end(), l);

	std::cout<< "\nMove\n";
	XORLinkedList<int> mvList{};
	mvList = std::move(list);
	std::cout << mvList << "\n" << std::endl;
	std::cout << list << "\n" << std::endl;

    std::cout << "Modifier functions\n";

    mvList.pop_back();
    mvList.pop_front();
    mvList.insert(1, 4);
    mvList.insert(2, 4);
    mvList.erase(2);
    std::cout << mvList << std::endl;
    std::cout << "Size = " << mvList.getSize()<< std::endl;

    return 0;
}