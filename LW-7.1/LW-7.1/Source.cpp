#include <string>
#include <iostream>

bool isPalindrome(std::string & str) 
{
	size_t len = str.size();
	for (size_t i = 0; i < len / 2; i++) {
		if (str[i] != str[len - 1 - i]) return false;
	}
	return true;
}

int main() 
{
	std::string buf;
	std::cout << "To stop calculation enter 'exit'" << std::endl << std::endl;
	do {
		std::cout << "Enter a string:" << std::endl << "> ";
		std::cin >> buf;
		if (buf == "exit") return 0;
		if (isPalindrome(buf))
			std::cout << "It's palindrome!" << std::endl << std::endl;
		else
			std::cout << "It's NOT palindrome!" << std::endl << std::endl;
	} while (true);
	return 0;
}