#include "TBook.h"

#define EMPTY_STRING "(Unknown)"

TBook::~TBook() {

}

TBook::TBook()
{
	Author = EMPTY_STRING;
	Name = EMPTY_STRING;
	Pages = NULL;
}

TBook::TBook(const std::string & author = EMPTY_STRING, const std::string & name = EMPTY_STRING, size_t pages = NULL)
{
	Author = author;
	Name = name;
	Pages = pages;
}

std::string TBook::GetAuthor() {
	return Author;
}

std::string TBook::GetName() {
	return Name;
}

size_t TBook::GetPages() {
	return Pages;
}

std::ostream& operator<<(std::ostream & out, TBook & book)
{
	out << "Author: " << book.GetAuthor() << std::endl;
	out << "Name:   " << book.GetName() << std::endl;
	out << "Pages:  " << book.GetPages() << std::endl;
	return out;
}