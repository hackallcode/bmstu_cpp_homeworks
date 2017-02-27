#include <cstdlib>
#include <locale>
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

struct Line
{
	std::string data;
	size_t hash;
	size_t * count;
	size_t ** numbers;
	Line * next;
};

void initLine(Line * & lines, size_t file_id, const std::string & line, size_t line_number)
{
	if (lines == nullptr) delete lines;
	lines = new Line;
	lines->data = line;
	std::hash<std::string> hash_fn;
	lines->hash = hash_fn(line);
	lines->count = new size_t [2];
	lines->count[file_id != 1] = 0;
	lines->count[file_id] = 1;
	lines->numbers = new size_t * [2];
	lines->numbers[file_id != 1] = nullptr;
	lines->numbers[file_id] = new size_t[1];
	lines->numbers[file_id][0] = line_number;
	lines->next = nullptr;
}

void addNumbers(Line * & lines, size_t file_id, size_t line_number)
{
	lines->count[file_id]++;
	size_t * new_numbers = new size_t[lines->count[file_id]];
	memcpy(new_numbers, lines->numbers[file_id], (lines->count[file_id] - 1) * sizeof(size_t));
	new_numbers[lines->count[file_id] - 1] = line_number;
	delete[] lines->numbers[file_id];
	lines->numbers[file_id] = new_numbers;
}

void addLine(Line * & lines, size_t file_id, const std::string & line, size_t line_number)
{
	if (lines == nullptr) {
		initLine(lines, file_id, line, line_number);
		return;
	}
	
	std::hash<std::string> hash_fn;
	size_t hash = hash_fn(line);

	Line * last_line = lines;
	while (last_line->next != NULL) {
		if (last_line->hash == hash) {
			addNumbers(last_line, file_id, line_number);
			return;
		}
		last_line = last_line->next;
	}
	if (last_line->hash == hash) {
		addNumbers(last_line, file_id, line_number);
		return;
	}
	initLine(last_line->next, file_id, line, line_number);
}

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

bool readFile(Line * & lines, size_t file_id = 0, const std::string printed_name = "file")
{
	std::ifstream fin;
	if (!openDialog(fin, printed_name)) return false;

	size_t number = 0;
	std::string buf;
	while (getline(fin, buf)) {
		number++;
		addLine(lines, file_id, buf, number);
	}
	fin.close();
	return true;
}

int main()
{
	setlocale(LC_ALL, "rus");

	Line * lines = nullptr;
	readFile(lines, 0, "first file");
	readFile(lines, 1, "second file");

	system("cls");
	std::cout << "Differents:" << std::endl;
	size_t j = 0;
	while (lines != nullptr) {
		if (lines->count[1] == 0) {
			for (size_t i = 0; i < lines->count[0]; i++) {
				std::cout << "File 1. Line " << lines->numbers[0][i] << ": " << lines->data << std::endl;
			}	
			j++;
		} else if (lines->count[0] == 0) {
			for (size_t i = 0; i < lines->count[1]; i++) {
				std::cout << "File 2. Line " << lines->numbers[1][i] << ": " << lines->data << std::endl;
			}
			j++;
		}
		lines = lines->next;
	}
	if (j == 0) std::cout << "No differents!" << std::endl;

	system("pause");
	return 0;
}