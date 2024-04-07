#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_9.3/LAB_9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestAddEmployee)
        {
            map<string, Employee> phoneBook;
            Employee testEmployee;
            testEmployee.lastName = "Doe";
            testEmployee.phoneNumber = "12345";
            testEmployee.roomNumber = "101";

            addEmployee(phoneBook);

            Assert::IsTrue(phoneBook.find("12345") != phoneBook.end());
            Assert::AreEqual("Doe", phoneBook["12345"].lastName.c_str());
            Assert::AreEqual("101", phoneBook["12345"].roomNumber.c_str());
        }
    };
}
