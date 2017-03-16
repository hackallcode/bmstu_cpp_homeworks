#include "NotCopyable.h"
#include <iostream>

int main()
{
    try
    {
        NotCopyable obj;
        NotCopyableRaii objRaii(&obj);

        obj.OpenToWrite("someFile.txt");

        obj.OpenToRead("someOtherFile.txt");

        obj.Close();
    }
    catch (const std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
    system("pause");
}