#include <iostream>
#include <fstream>
#include <string>

struct Strings {
	std::string data;
	Strings * prev;
	Strings * next;
};

bool openDialog(std::ifstream & fin, const std::string printed_name = "file")
{
	std::string filename;
	std::cout << "Enter name of " << printed_name << ":" << std::endl << "> ";
	do {
		std::cin >> filename;

		if (filename == "stop") return false;

		fin.open(filename, std::ios_base::in);
		if (fin.is_open()) {
			return true;
		}
		else {
			std::cout << "Impossible to open the file! You can try enter a name of other file (or 'stop' to exit):" << std::endl << "> ";
		}
	} while (true);
}

void newStrings(Strings * & str, std::string data, Strings * prev, Strings * next = nullptr)
{
	if (str != nullptr) delete str;
	str = new Strings;
	str->data = data;
	str->prev = prev;
	str->next = next;
}

Strings * split(std::string str, std::string delim)
{
	Strings * res = nullptr;
	Strings * last = nullptr;
	
	size_t prev = 0;
	size_t next;
	size_t delta = delim.length();

	while ((next = str.find(delim, prev)) != std::string::npos) {
		if (next - prev == 0) {
			prev = next + delta;
			continue;
		}
		if (res == nullptr) {
			newStrings(res, str.substr(prev, next - prev), nullptr);
			last = res;
		}
		else {
			newStrings(last->next, str.substr(prev, next - prev), last);
			last = last->next;
		}		
		prev = next + delta;
	}
	if (res == nullptr)
		newStrings(res, str.substr(prev), nullptr);
	else
		newStrings(last->next, str.substr(prev), last);

	return res;
}

int main() 
{
	std::ifstream fin;
	if (!openDialog(fin)) return 0;

	std::string word;
	do {
		std::cout << "What do you want to find?" << std::endl << "> ";
		std::cin >> word;
	} while (word == "");

	size_t n = 0;
	do {
		std::cout << "How many words to show from both sides of word?" << std::endl << "> ";
		std::cin >> n;
	} while (n < 0);	

	std::string buf;
	while (getline(fin, buf)) {
		for (size_t i = 0; i < buf.size(); i++) {
			if (buf[i] == '.' || buf[i] == ',' || buf[i] == '-' || buf[i] == '!' || buf[i] == '?' || buf[i] == '"' ||
				buf[i] == '(' || buf[i] == ')' || buf[i] == '\'' || buf[i] == ':' || buf[i] == ';') {
				buf[i] = ' ';
			}
		}
		Strings * first = split(buf, " ");
		Strings * words = first;
		while (words != nullptr) {
			if (words->data == word) {
				size_t i = n;
				Strings * current = words;
				while (current->prev != nullptr && i > 0) {
					current = current->prev;
					i--;
				}
				while (i < n) {
					std::cout << current->data << " ";
					current = current->next;
					i++;
				}
				std::cout << words->data << " ";
				i = n;
				current = words;
				while (current->next != nullptr && i > 0) {
					current = current->next;
					i--;
					std::cout << current->data << " ";
				}
				std::cout << std::endl;
			}
			words = words->next;
		}
		words = first;
		while (words != nullptr) {
			Strings * next = words->next;
			delete words;
			words = next;
		}
	}
	
	fin.close();
	system("pause");
	return 0;
}