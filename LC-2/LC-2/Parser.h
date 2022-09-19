#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
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

class AlreadyExistsException
    : public std::exception
{};

class Parser
{
public:
    Parser(const std::string& filename) // throw(FileIsBusyException, IncorrectFileException)
        : filename_(filename)
        , objs_(0)
        , headerBegin_("\"")
        , headerEnd_("\"={")
        , fieldSeparator_(",")
        , lineEnd_("}")
        , schemeHeader_("Scheme")
    {
        std::ifstream fin(filename_);
        if (fin.is_open()) {
            std::pair<LineType, std::vector<std::string>> line;
            
            if ((line = GetLine(fin)).first == MultiFieldLine) {
                if (line.second[0] == schemeHeader_) {
                    for (size_t i = 1; i < line.second.size(); ++i) {
                        if (line.second[i].front() != '\"' || line.second[i].back() != '\"') {
                            throw IncorrectFileException();
                        }
                        line.second[i] = line.second[i].substr(1, line.second[i].size() - 2);
                        fieldNames_.push_back(line.second[i]);
                    }

                    while ((line = GetLine(fin)).first != EndLine) {
                        if (line.first == MultiFieldLine) {
                            if (line.second.size() != fieldNames_.size() + 1) {
                                throw IncorrectFileException();
                            }
                            if (objs_.count(line.second[0]) > 0) {
                                throw AlreadyExistsException();
                            }
                            for (size_t i = 1; i < line.second.size(); ++i) {
                                objs_[line.second[0]][fieldNames_[i - 1]] = line.second[i];
                            }
                        }
                    }
                }
                else {
                    throw IncorrectFileException();
                }
            }
            else {
                throw IncorrectFileException();
            }

        }
        else {
            SaveAs(filename_);
        }
    }

    Object& GetObject(const std::string& key) 
    {
        return objs_.at(key);
    }

    std::vector<std::string> GetObjsNames()
    {
        std::vector<std::string> result;
        for (auto it = objs_.begin(); it != objs_.end(); ++it) {
            result.push_back(it->first);
        }
        return result;
    }

    void SaveAs(const std::string& filename) {
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
    std::unordered_map<std::string, Object> objs_;

    std::string schemeHeader_;
    std::string headerBegin_;
    std::string headerEnd_;
    std::string fieldSeparator_;
    std::string lineEnd_;

    enum LineType {
        EmptyLine = 0
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
            std::string lineCopy(line);
            std::pair<bool, std::string> subLine;

            // Пустая строка
            if (line.size() == 0) {
                return std::make_pair(EmptyLine, vec);
            }

            // MultiField
            subLine = SubStr(line, headerBegin_, headerEnd_);
            if (subLine.first) {
                vec.push_back(subLine.second);

                // Удаляем до полей
                line = line.substr(headerBegin_.size() + subLine.second.size() + headerEnd_.size());
                while (line.front() == ' ') {
                    line = line.substr(1);
                }

                while(true) {
                    size_t endPos = line.find(fieldSeparator_);
                    if (endPos != line.npos) {
                        vec.push_back(line.substr(0, endPos));
                        
                        line = line.substr(endPos + fieldSeparator_.size());
                        while (line.front() == ' ') {
                            line = line.substr(1);
                        }
                    }
                    else {
                        size_t endPos = line.find(lineEnd_);
                        if (endPos != line.npos) {
                            vec.push_back(line.substr(0, endPos));

                            line = line.substr(endPos + lineEnd_.size());
                            while (line.size() > 0 && line.front() == ' ') {
                                line = line.substr(1);
                            }

                            if (line.size() == 0) {
                                return std::make_pair(MultiFieldLine, vec);
                            }
                        }
                        return std::make_pair(UnknownLine, std::vector<std::string>(1, lineCopy));
                    }
                };
            }

            vec.push_back(line);
            return std::make_pair(UnknownLine, std::vector<std::string>(1, lineCopy));
        }
        else {
            return std::make_pair(EndLine, vec);
        }
    }
};