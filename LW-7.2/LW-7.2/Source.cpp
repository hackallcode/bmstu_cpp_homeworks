#include <iostream>
#include <fstream>
#include <string>

// Возможные знаки препинания
const char marks[12] = { ' ', '!', '"', '\'', '(', ')', ',', '-', '.', ':', ';', '?' };

// Проверка символа на знак препинания
inline bool isMark(char letter) {
	for (const char& mark : marks) {
		if (mark == letter) 
			return true;
	}
	return false;
}

// Класс для работы со списком
class WordsList 
{
private:
	// Структура списка
	struct WordsElement	{
		std::string data;
		WordsElement * prev;
		WordsElement * next;
	} * Word;
public:
	// Деструктор
	~WordsList()
	{
		while (Word != nullptr) {
			WordsElement * next = Word->next;
			delete Word;
			Word = next;
		}
	}

	// Конструктор по умолчанию
	WordsList() : Word(nullptr)
	{}

	// Добавление слова в конец списка
	void Add(const std::string data)
	{
		if (Word == nullptr) {
			Word = new WordsElement;
			Word->data = data;
			Word->next = nullptr;
			Word->prev = nullptr;
			return;
		}
		WordsElement * lastWord = Word;
		while (lastWord->next != nullptr) lastWord = lastWord->next;
		lastWord->next = new WordsElement;
		lastWord->next->data = data;
		lastWord->next->next = nullptr;
		lastWord->next->prev = lastWord;
	}

	// Функция печати слова с окружением из n слов
	void Print(std::ostream & stream, const std::string & search_word, size_t count)
	{
		WordsElement * lastWord = Word;
		while (lastWord != nullptr) {
			if (lastWord->data == search_word) {

				WordsElement * printedWord = lastWord;
				size_t i = 0;
				while (printedWord->prev != nullptr && i < count) {
					printedWord = printedWord->prev;
					i++;
				}
				for (size_t j = 0; j < i + 1 + count; j++) {
					if (printedWord == nullptr) break;
					stream << printedWord->data << " ";
					printedWord = printedWord->next;
				}
				stream << std::endl;

			}
			lastWord = lastWord->next;
		}
	}
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

// Разделение строки на слова
WordsList * split(std::string & str)
{
	WordsList * words = new WordsList;
	std::string word = "";
	for (size_t i = 0; i < str.size(); i++) {
		if (isMark(str[i])) {
			if (word != "") {
				words->Add(word);
				word = "";
			}
		}
		else {
			word += str[i];
		}
	}
	if (word != "") words->Add(word);
	return words;
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
		WordsList * words = split(buf);
		words->Print(std::cout, search_word, n);
		delete words;
	}
	
	fin.close();
	system("pause");
	return 0;
}