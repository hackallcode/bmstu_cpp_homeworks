#include <iostream>
#include "TBook.h"

char * randName(char str[8]) {
	for (int i = 0; i < 7; i++) {
		str[i] = 65 + rand() % 26;
	}
	str[7] = '\0';
	return str;
}

int main() {
	int n = 0;
	std::cout << "Enter number of books:" << std::endl << "> ";
	std::cin >> n;
	system("cls");

	TBook * books = new TBook[n];

	size_t maxPages = 0;
	size_t numberOfMax = 0;
	std::cout << "List of books:" << std::endl << std::endl;
	for (int i = 0; i < n; i++) {
		char buf[8];
		books[i] = TBook(randName(buf), randName(buf), rand());
		std::cout << books[i] << std::endl;
		if (books[i].GetPages() > maxPages) {
			maxPages = books[i].GetPages();
			numberOfMax = i;
		}
	}
	
	std::cout << "This book has max number of pages:" << std::endl << std::endl << books[numberOfMax] << std::endl;
	
	system("pause");
	return 0;
}