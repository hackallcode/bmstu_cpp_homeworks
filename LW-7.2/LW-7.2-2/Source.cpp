#include <iostream>
#include <fstream>
#include <string>

// Возможные знаки препинания
const char marks[12] = { ' ', '!', '"', '\'', '(', ')', ',', '-', '.', ':', ';', '?' };

// Структура списка
struct Words {
	std::string data;
	Words * prev;
	Words * next;
};

// Функция открытия файла
bool openDialog(std::ifstream & fin, const std::string printed_name = "file")
{
	std::string filename;
	std::cout << "Enter name of " << printed_name << ":" << std::endl << "> ";
	do {
		std::cin >> filename;

		if (filename == "exit") return false;

		fin.open(filename, std::ios_base::in);
		if (fin.is_open()) {
			return true;
		}
		else {
			std::cout << "Impossible to open the file! You can try enter a name of other file (or 'exit' to exit):" << std::endl << "> ";
		}
	} while (true);
}

// Добавление слова в конец списка
void addWord(Words * & words, std::string data)
{
	if (words == nullptr) {
		words = new Words;
		words->data = data;
		words->next = nullptr;
		words->prev = nullptr;
		return;
	}
	Words * lastWord = words;
	while (lastWord->next != nullptr) lastWord = lastWord->next;
	lastWord->next = new Words;
	lastWord->next->data = data;
	lastWord->next->next = nullptr;
	lastWord->next->prev = lastWord;
}

// Удаление списка
void deleteWords(Words * & words) 
{
	while (words != nullptr) {
		Words * next = words->next;
		delete words;
		words = next;
	}
}

// Проверка символа на знак препинания
inline bool isMark(char letter) {
	for (const char & mark : marks) {
		if (mark == letter) 
			return true;
	}
	return false;
}

// Разделение строки на слова
Words * split(std::string & str)
{
	Words * words = nullptr;
	std::string word = "";
	for (size_t i = 0; i < str.size(); i++) {
		if (isMark(str[i])) {
			if (word != "") {
				addWord(words, word);
				word = "";
			}
		}
		else {
			word += str[i];
		}
	}
	if (word != "") addWord(words, word);
	return words;
}

// Функция печати слова с окружением из n слов
void printWords(Words * printedWord, size_t n)
{
	size_t i = 0;
	while (printedWord->prev != nullptr && i < n) {
		printedWord = printedWord->prev;
		i++;
	}
	for (size_t j = 0; j < i + 1 + n; j++) {
		if (printedWord == nullptr) break;
		std::cout << printedWord->data << " ";
		printedWord = printedWord->next;
	}
	std::cout << std::endl;
}

int main() 
{
	std::ifstream fin;
	if (!openDialog(fin)) return 0;

	std::string search_word;
	std::cout << "What do you want to find?" << std::endl << "> ";
	std::cin >> search_word;

	size_t n = 0;
	std::cout << "How many words to show from both sides of word? The number must be non-negative." << std::endl << "> ";
	std::cin >> n;

	std::string buf;
	while (getline(fin, buf)) {
		Words * words = split(buf);
		Words * lastWord = words;
		while (lastWord != nullptr) {
			if (lastWord->data == search_word) printWords(lastWord, n);
			lastWord = lastWord->next;
		}
		deleteWords(words);
	}
	
	fin.close();
	system("pause");
	return 0;
}