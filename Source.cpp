/*
Jackson Esco
CS-210 SNHU
April 18th, 2022
*/

#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
To call this function, pass the name of the Python funciton as an argument.
*/
void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}


/*
To call this funciton, pass the name of the Pythonfunciton and the string parameter to be used in that function
*/
int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;


    return _PyLong_AsInt(presult);
}


/*
To call this funciton, pass the name of the Python function and the string parameter to be used in that funciton
*/
int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;

    return _PyLong_AsInt(presult);
}


/*
This function creates the user menu with options for creating an inventory list, searching for a specific item in the inventory, creating a historgram of the inventory, and exitting the program
*/
void DrawMenu() {

    //Initialize method-specific variables
    int menuLoop = 0;                                      //Track the number of menu loops
    int wordCount = 0;                                     //Track the number of times a specific searched word was found
    int itemQuantity = 0;                                  //Variable to contain an item quantity from frequency.dat
    string searchTerm;                                     //Collect user input for a search term
    string itemName;                                       //Variable to contain an item name from frequency.dat
    string greenColor = "\033[32;1m";                      //Set font color green for the histogram asterisks
    string defaultColor = "\033[0m";                       //Set default font color for the console
    ifstream fileInput;                                    //Open ifstream for file

    while (menuLoop != 4) {

        //Prompt and collect user input
        std::cout << "[1] Calculate the number of times each item appears" << std::endl;
        std::cout << "[2] Calculate the frequency of a specific item" << std::endl;
        std::cout << "[3] Create a histogram based on the number of appearances of each item" << std::endl;
        std::cout << "[4] Quit" << std::endl;

        std::cin >> menuLoop;

        //Check if user input is valid. If not, prompt correct input.
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please input a valid selection: ";
            std::cin >> menuLoop;
        }


        //Switch statement: Execute the proper command for user input
        switch (menuLoop) {

            //
            //Case 1: Calculate the number of times each item appears, then print a list
            //
        case 1:
            system("CLS");                                          //Clear the screen to tidy things up
            CallProcedure("CountAll");                      //Call the Python function "CountAll"
            std::cout << std::endl;                           //Add a bit of space in between the printed list and menu
            break;

            //
            //Case 2: Calculate the number of times a specific item appears, then print the result.
            //
        case 2:
            //Clear the screen, then collect user input for search
            system("CLS");
            std::cout << "What item would you like to search for?" << std::endl;
            std::cin >> searchTerm;

            //Call Python function with the search term, then return an integer word count value.
            wordCount = callIntFunc("CountInstances", searchTerm);

            //Print statement with returned word count.
            std::cout << std::endl << searchTerm << " : " << wordCount << std::endl << std::endl;

            break;

            //
            //Case 3: Print a histogram based on how many times each item appears. Like case 1, but with stars.
            //
        case 3:
            system("CLS");                                          //Clear the screen to tidy things up
            CallProcedure("CollectData");           //Call the Python function "CollectData"

            fileInput.open("frequency.dat");        //Open frequency.dat

            fileInput >> itemName;                            //Collect first item on list
            fileInput >> itemQuantity;                        //Collect first quantity on list

            //For each line in the file, print a histogram. After every line has been parsed, break.
            while (!fileInput.fail()) {
                //Set text color to the default white
                std::cout << defaultColor;

                //Print the item name, then prepare for the histogram
                std::cout << std::setw(14) << std::left << itemName << std::setw(6);

                //Set histogram color (for fun)
                std::cout << greenColor;

                //Print itemQuantity number of asterisks
                for (int i = 0; i < itemQuantity; i++) {

                    //Print green asterisks in line.
                    std::cout << std::right << "*";
                }
                //Prepare for the next line, then set the next item's name and quantity.
                std::cout << std::endl;
                fileInput >> itemName;
                fileInput >> itemQuantity;
            }

            //Close frequency.dat, reset font color, then break
            fileInput.close();
            std::cout << defaultColor << endl;
            break;

            //
            //Case 4: Quit the program.
            //
        case 4:
            return;

            //Default case: Invalid input
        default:
            std::cout << "Please input a valid selection.";
            std::cout << std::endl;
            break;
        }
    }
}

//Main method. Calls the DrawMenu method to collect user input.
void main()
{
    //Draw the user menu.
    DrawMenu();

}
