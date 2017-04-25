#include <iostream>

#include <string>
#include <vector>
#include <map>

#include <algorithm>
#include <numeric>

enum Grade
{
    F = 1,
    D,
    C,
    B,
    A
};

struct Student
{
    std::string FIO;
    std::string Group;
    std::map<std::string, Grade> Grades;
};

std::vector<Student> LoadStudents()
{
    return{
        {
            "Anna", "G7",
            {
                { "math", Grade::A },
                { "cs", Grade::A },
                { "english", Grade::A },
                { "dutch", Grade::B },
            }
        },
        {
            "Petr", "G7",
            {
                { "math", Grade::B },
                { "cs", Grade::A },
                { "dutch", Grade::C },
            }
        },
        {
            "Vova", "G1",
            {
                { "math", Grade::F },
                { "english", Grade::F },
            }
        },
        {
            "Vasya", "G3",
            {
                { "math", Grade::F },
                { "english", Grade::F },
                { "cs", Grade::B },
                { "dutch", Grade::C },
            }
        },
        {
            "Anton", "G4",
            {
                { "math", Grade::F },
                { "english", Grade::F },
                { "dutch", Grade::C },
                { "cs", Grade::C },
            }
        },
        {
            "Masha", "G2",
            {
                { "math", Grade::A },
            }
        },
        {
            "Sasha", "G6",
            {
                { "english", Grade::F },
                { "russian", Grade::F },
                { "dutch", Grade::F },
            }
        },
        {
            "Jeka", "G2",
            {
                { "english", Grade::A },
            }
        },
        {
            "Sveta", "G3",
            {
            }
        }
    };
}

/*/ Вывод
struct PrinterStudent
{
    void operator()(const Student& s) const
    {
        std::cout << s.FIO << " studies in " << s.Group << " has marks: ";
        for (auto it : s.Grades) {
            std::cout << it.first << " - " << it.second << " ";
        }
        std::cout << std::endl;
    }
};
/**/

struct FindBestStudent
{
    Student const* student = nullptr;

    void operator()(Student const& s)
    {
        auto it = s.Grades.find("math");
        if (it == s.Grades.end()) {
            return;
        }

        if (student == nullptr || it->second >= student->Grades.at("math")) {
            student = &s;
        }
    }
};

struct FindWorstStudent
{
public:
    Student const* student = nullptr;
    float worstAvg = 0;

    void operator()(Student const& s)
    {
        if (s.Grades.size() == 0) {
            return;
        }
        float avg = 0;
        for (auto it : s.Grades) {
            avg += it.second;
        }
        avg /= s.Grades.size();

        if (student == nullptr || avg < worstAvg) {
            student = &s;
            worstAvg = avg;
        }
    }
};

struct FindBusiestStudent
{
    Student const* student = nullptr;

    void operator()(Student const& s)
    {
        if (student == nullptr || s.Grades.size() > student->Grades.size()) {
            student = &s;
        }
    }
};

struct FindStudentsInGroup
{
    std::vector<Student const*> students;
    std::string neededGroup;

    FindStudentsInGroup(std::string const& group)
        : neededGroup(group)
    {}

    void operator()(Student const& s)
    {
        if (s.Group == neededGroup) {
            students.push_back(&s);
        }
    }
};

struct FindSomeStudents
{
    std::vector<Student const*> students;

    void operator()(Student const& s)
    {
        auto it = s.Grades.find("math");
        if (it == s.Grades.end() || it->second != Grade::B) {
            return;
        }
        it = s.Grades.find("cs");
        if (it == s.Grades.end() || it->second != Grade::A) {
            return;
        }

        students.push_back(&s);
    }
};

struct AddLiterature
{
    void operator()(Student& s)
    {
        float avg = 0;
        if (s.Grades.size() != 0) {
            for (auto it : s.Grades) {
                avg += it.second;
            }
            avg /= s.Grades.size();
        }
        else {
            avg = Grade::F;
        }

        s.Grades["Russian literature"] = static_cast<Grade>(static_cast<size_t>(ceil(avg)));
    }
};

struct PrintDutch
{
    void operator()(const Student& s) const
    {
        auto it = s.Grades.find("dutch");
        if (it == s.Grades.end()) {
            std::cout << s.FIO << " hasn't mark!" << std::endl;
        }
        else {
            std::cout << s.FIO << " has " << it->second << std::endl;;
        }
    }
};


int main()
{
    std::vector<Student> students = LoadStudents();

    //std::for_each(students.begin(), students.end(), PrinterStudent());

    auto res1 = std::for_each(students.begin(), students.end(), FindBestStudent());
    std::cout << res1.student->FIO << std::endl;

    auto res2 = std::for_each(students.begin(), students.end(), FindWorstStudent());
    std::cout << res2.student->FIO << std::endl;

    auto res3 = std::for_each(students.begin(), students.end(), FindBusiestStudent());
    std::cout << res3.student->FIO << std::endl;

    auto res4 = std::for_each(students.begin(), students.end(), FindStudentsInGroup{ "G7" });
    for (auto& s : res4.students) {
        std::cout << s->FIO << " ";
    }
    std::cout << std::endl;

    auto res5 = std::for_each(students.begin(), students.end(), FindSomeStudents());
    for (auto& s : res5.students) {
        std::cout << s->FIO << " ";
    }
    std::cout << std::endl;
    
    std::for_each(students.begin(), students.end(), AddLiterature());
    std::for_each(students.begin(), students.end(), PrintDutch());
    
    //std::for_each(students.begin(), students.end(), PrinterStudent());

    system("pause");
}