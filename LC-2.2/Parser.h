#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "Object.h"

#define DEBUG_LEVEL 1

#define DEBUG(message)                      \
{                                           \
    if (DEBUG_LEVEL > 0) {                  \
        std::cout << message << std::endl;  \
    }                                       \
}

class FileIsBusyException
    : public std::exception
{};

class IncorrectFileException
    : public std::exception
{};

class Parser
{
public:
    Parser(std::string filename) // throw(FileIsBusyException, IncorrectFileException)
        : filename_(filename)
        , objs_(0)
        , headerBegin_("\"")
        , headerEnd_("\"={")
        , fieldBegin_("\"")
        , fieldSeparator_(", ")
        , fieldEnd_("\"")
        , isMultiFieldLine_(true)
        , schemeHeader_("Scheme")
    {
        std::ifstream fin(filename_);
        if (fin.is_open()) {
            std::pair<LineType, std::vector<std::string>> line;
            line.first = EmptyLine;

            while (true) {
                line = GetLine(fin);
                if (line.first == HeaderLine) {
                    if (line.second[0] == schemeHeader_) {
                        break;
                    }
                    else {
                        throw IncorrectFileException();
                    }
                }
            }

            while (true) {
                line = GetLine(fin);
                if (line.first == FieldLine) {
                    if (line.second[0] == schemeHeader_) {
                        break;
                    }
                    else {
                        throw IncorrectFileException();
                    }
                }
                else if (line.first == HeaderLine) {
                    break;
                }
            }
            
            do {
                line = GetLine(fin);
                if (line.first == EmptyLine) {
                    DEBUG("EmptyLine");
                }
                else if (line.first == HeaderLine) {
                    DEBUG("Header: " + line.second[0]);
                }
                else if (line.first == FieldLine) {
                    DEBUG("Field: " + line.second[0]);
                }
                else if (line.first == MultiFieldLine) {
                    DEBUG("MultiFieldLine:");
                    for (std::string& str : line.second) {
                        DEBUG("   " + str);
                    }
                }
                else if (line.first == EndLine) {
                    DEBUG("EndLine");
                }
                else if (line.first == UnknownLine) {
                    DEBUG("UnknownLine: " + line.second[0]);
                }
                else {
                    DEBUG("WTF?!");
                }
            } while (line.first != EndLine);

        }
        else {
            SaveAs(filename_);
        }
    }

    void SaveAs(std::string filename) {
        std::ofstream fout(filename);
        if (!fout.is_open()) {
            throw FileIsBusyException();
        }

        // TODO

        fout.close();
    }
private:
    std::string filename_;
    std::vector<std::string> fieldNames_;
    std::vector<Object> objs_;

    std::string schemeHeader_;
    std::string headerBegin_;
    std::string headerEnd_;
    bool isMultiFieldLine_;
    std::string fieldBegin_;
    std::string fieldSeparator_;
    std::string fieldEnd_;

    enum LineType {
        EmptyLine = 0
        , HeaderLine
        , FieldLine
        , MultiFieldLine
        , EndLine
        , UnknownLine
    };

    std::pair<bool, std::string> SubStr(std::string line, std::string begin, std::string end) {
        std::string subLine(line);

        if (line.size() < begin.size() + end.size()) {
            return std::make_pair(false, line);
        }
        if (begin.size() > 0) {
            if (subLine.substr(0, begin.size()) == begin) {
                subLine = subLine.substr(begin.size());
            }
            else {
                return std::make_pair(false, line);
            }
        }
        if (end.size() > 0) {
            size_t endPos = subLine.find(end);
            if (endPos == subLine.npos) {
                return std::make_pair(false, line);
            }
            subLine = subLine.substr(0, endPos);
        }

        return std::make_pair(true, subLine);
    }

    std::pair<LineType, std::vector<std::string>> GetLine(std::ifstream& fin)
    {
        std::string line;
        std::vector<std::string> vec;

        if (std::getline(fin, line)) {
            std::pair<bool, std::string> subLine;

            // Пустая строка
            if (line.size() == 0) {
                return std::make_pair(EmptyLine, vec);
            }

            // Header
            subLine = SubStr(line, headerBegin_, headerEnd_);
            if (subLine.first) {
                vec.push_back(subLine.second);
                return std::make_pair(HeaderLine, vec);
            }

            // Fields
            if (isMultiFieldLine_) {
                do {
                    subLine = SubStr(line, fieldBegin_, fieldSeparator_);
                    if (subLine.first) {
                        vec.push_back(subLine.second);
                        // Удаляем до разделителя
                        line = line.substr(line.find(fieldSeparator_) + 1);
                    }
                    // Если последнее слово в строке
                    else {
                        subLine = SubStr(line, fieldBegin_, fieldEnd_);
                        if (subLine.first) {
                            vec.push_back(subLine.second);
                        }
                        break;
                    }
                } while (subLine.first);
                if (vec.size() > 0) {
                    return std::make_pair(MultiFieldLine, vec);
                }
            }
            else {
                subLine = SubStr(line, fieldBegin_, fieldEnd_);
                if (subLine.first) {
                    vec.push_back(subLine.second);
                    return std::make_pair(FieldLine, vec);
                }
            }

            vec.push_back(line);
            return std::make_pair(UnknownLine, vec);
        }
        else {
            return std::make_pair(EndLine, vec);
        }
    }
};