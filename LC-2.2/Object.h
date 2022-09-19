#pragma once

#include <map>
#include <string>
#include <vector>

class Object
{
public:
    Object()
        : fields_()
    {}

    Object(Object const& rhs) 
        : fields_(rhs.fields_)
    {}

    Object& operator=(Object const& rhs)
    {
        fields_ = rhs.fields_;
    }

    std::string const& operator[](std::string const& key) const
    {
        return fields_.at(key);
    }

    std::string& operator[](std::string const& key)
    {
        return fields_[key];
    }

    std::vector<std::string> Fields()
    {
        std::vector<std::string> result;
        for (auto it = fields_.begin(); it != fields_.end(); ++it) {
            result.push_back(it->first);
        }
        return result;
    }
private:
    std::map<std::string, std::string> fields_;
};
