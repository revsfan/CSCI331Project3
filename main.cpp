#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "bPTree.h"
#include "node.h"

#define TEST_VALUE 3

using namespace std;

/**
* Simple menu for functions on the B+ tree
*/
void menu();

/**
*   Displays different flags for program
*/
void helpMenu();

int main(int argc, char* argv[]){

  int number; /** < Size of a block */ //size of block
  int intValue; /** < A key value of type int */
  string stringValue; /** < A key value of type string */ // key value




//CLI ARGUMENTS

// FOR FILE IMPORT
if(argc == 3){

    if(argv[1][1] == 's'){ //if the input file is of type string

        ifstream stringInFile( argv[2]);
        cout << "String file opened successfully \n\n";
        mount << "String file opened successfully \n\n";

        cout << "Enter the number of values per block: " << endl;
        mount << "Enter the number of values per block: " << endl;

        cin >> number;

        cout << "Number of values per block have been set to: " << number << endl;
        mount << "Number of values per block have been set to: " << number << endl;

        bPTree bPlusTree(number);

        cout << "Loading keys into the tree...\n\n";
        mount << "Loading keys into the tree...\n\n";

        while(stringInFile >> stringValue){
            bPlusTree.stringInsert(stringValue); // only need stringValue
        }

        cout << "The B+ tree has been created.\n\n";
        mount << "The B+ tree has been created.\n\n";


        int choice = 0;
        string value;



        while(choice < 5){

        menu(); //display menu
        cin >> choice;


            switch(choice){

                //adding a record
                case 1:             cout << "What is the string key you would like to add: \n\n";
                                    mount << "What is the string key you would like to add: \n\n";

                                    cin >> value;

                                    bPlusTree.stringInsert(value);
                                    cout << "\nKey has been added\n\n";
                                    mount << "\nKey has been added\n\n";
                                    break;

                //deleting a record
                case 2:            cout << "\nWhat is the string key you would like to delete: \n\n";
                                    mount << "\nWhat is the string key you would like to delete: \n\n";
                                    //string value;
                                    cin >> value;

                                    bPlusTree.stringDelete(value);
                                    cout << "\nKey has been deleted from the tree\n\n";
                                    mount << "\nKey has been deleted from the tree\n\n";
                                    break;


            //show tree
            case 3:               bPlusTree.stringShowTree();
                                    break;

            //list values
            case 4:               bPlusTree.stringListValues();
                                    break;

            //go back to the other menu
            case 5:               exit(EXIT_SUCCESS);
                                    break;

            //ERROR
            default:                cout << "Something went wrong...";
                                    mount << "Something went wrong...";
                                    exit(EXIT_FAILURE);
            }


        }
    }

    //FOR FILE INPUT
    if(argv[1][1] == 'i'){ //if the input file is of type int

        ifstream intIntFile( argv[2]);
        cout << "Integer file opened successfully \n\n";
        mount << "Integer file opened successfully \n\n";

        cout << "Enter the number of values per block: " << endl;
        mount << "Enter the number of values per block: " << endl;

        cin >> number;

        cout << "Number of values per block have been set to: " << number << endl;
        mount << "Number of values per block have been set to: " << number << endl;

        bPTree bPlusTree(number);

        cout << "Loading keys into the tree...\n\n";
        mount << "Loading keys into the tree...\n\n";

        while(intIntFile >> intValue){
            bPlusTree.insert(intValue); // only need intValue
        }

        cout << "The B+ tree has been created.\n\n";
        mount << "The B+ tree has been created.\n\n";



        int choice = 0;
        int value;



        while(choice < 5){

        menu(); //display menu
        cin >> choice;


            switch(choice){

                //adding a record
                case 1:             cout << "What is the int key you would like to add: \n\n";
                                    mount << "What is the int key you would like to add: \n\n";

                                    cin >> value;

                                    bPlusTree.insert(value);
                                    cout << "\nKey has been added\n\n";
                                    mount << "\nKey has been added\n\n";
                                    break;

                //deleting a record
                case 2:            cout << "\nWhat is the int key you would like to delete: \n\n";
                                    mount << "\nWhat is the int key you would like to delete: \n\n";
                                    //int value;
                                    cin >> value;

                                    bPlusTree.intDelete(value);
                                    cout << "\nKey has been deleted from the tree\n\n";
                                    mount << "\nKey has been deleted from the tree\n\n";
                                    break;


            //show tree
            case 3:               bPlusTree.showTree();
                                    break;

            //list values
            case 4:               bPlusTree.listValues();
                                    break;

            //go back to the other menu
            case 5:               exit(EXIT_SUCCESS);
                                    break;

            //ERROR
            default:                cout << "Something went wrong...";
                                    mount << "Something went wrong...";
                                    exit(EXIT_FAILURE);
            }


        }
        }



}


//empty string tree

if (argc == 2){

    if(argv[1][1] == 's'){ //empty int tree

        ifstream stringInFile( argv[2]);
        cout << "String file opened successfully \n\n";
        mount << "String file opened successfully \n\n";

        cout << "Enter the number of values per block: " << endl;
        mount << "Enter the number of values per block: " << endl;

        cin >> number;

        cout << "Number of values per block have been set to: " << number << endl;
        mount << "Number of values per block have been set to: " << number << endl;

        bPTree bPlusTree(number);

        cout << "Loading keys into the tree...\n\n";
        mount << "Loading keys into the tree...\n\n";

        while(stringInFile >> stringValue){
            bPlusTree.stringInsert(stringValue); // only need stringValue
        }

        cout << "The B+ tree has been created.\n\n";
        mount << "The B+ tree has been created.\n\n";


        int choice = 0;
        string value;



        while(choice < 5){

        menu(); //display menu
        cin >> choice;


            switch(choice){

                //adding a record
                case 1:             cout << "What is the string key you would like to add: \n\n";
                                    mount << "What is the string key you would like to add: \n\n";

                                    cin >> value;

                                    bPlusTree.stringInsert(value);
                                    cout << "\nKey has been added\n\n";
                                    mount << "\nKey has been added\n\n";
                                    break;

                //deleting a record
                case 2:            cout << "\nWhat is the string key you would like to delete: \n\n";
                                    mount << "\nWhat is the string key you would like to delete: \n\n";
                                    //string value;
                                    cin >> value;

                                    bPlusTree.stringDelete(value);
                                    cout << "\nKey has been deleted from the tree\n\n";
                                    mount << "\nKey has been deleted from the tree\n\n";
                                    break;


            //show tree
            case 3:               bPlusTree.stringShowTree();
                                    break;

            //list values
            case 4:               bPlusTree.stringListValues();
                                    break;

            //go back to the other menu
            case 5:               exit(EXIT_SUCCESS);
                                    break;

            //ERROR
            default:                cout << "Something went wrong...";
                                    mount << "Something went wrong...";
                                    exit(EXIT_FAILURE);
            }


        }
    }




if(argv[1][1] == 'i'){ //empty int tree



        cout << "Enter the number of values per block: " << endl;
        mount << "Enter the number of values per block: " << endl;

        cin >> number;

        cout << "Number of values per block have been set to: " << number << endl;
        mount << "Number of values per block have been set to: " << number << endl;

        bPTree bPlusTree(number);


        cout << "The B+ tree has been created.\n\n";
        mount << "The B+ tree has been created.\n\n";


        int choice = 0;
        int value;



        while(choice < 5){

        menu(); //display menu
        cin >> choice;


            switch(choice){

                //adding a record
                case 1:             cout << "What is the int key you would like to add: \n\n";
                                    mount << "What is the int key you would like to add: \n\n";

                                    cin >> value;

                                    bPlusTree.insert(value);
                                    cout << "\nKey has been added\n\n";
                                    mount << "\nKey has been added\n\n";
                                    break;

                //deleting a record
                case 2:            cout << "\nWhat is the int key you would like to delete: \n\n";
                                    mount << "\nWhat is the int key you would like to delete: \n\n";
                                    //int value;
                                    cin >> value;

                                    bPlusTree.intDelete(value);
                                    cout << "\nKey has been deleted from the tree\n\n";
                                    mount << "\nKey has been deleted from the tree\n\n";
                                    break;


            //show tree
            case 3:               bPlusTree.showTree();
                                    break;

            //list values
            case 4:               bPlusTree.listValues();
                                    break;

            //go back to the other menu
            case 5:               exit(EXIT_SUCCESS);
                                    break;

            //ERROR
            default:                cout << "Something went wrong...";
                                    mount << "Something went wrong...";
                                    exit(EXIT_FAILURE);
            }


        }
    }


    if(argv[1][1] == 'h'){

        helpMenu();
        exit(EXIT_SUCCESS);
    }



}





return 0;
}


void menu(){


    cout << "\n\nWhat would you like to do?" << endl << endl;
    mount << "\n\nWhat would you like to do?" << endl << endl;

    cout << "1. Add record\n" << "2. Delete record\n" << "3. Show tree\n" << "4. List values\n" << "5. Quit the program\n";
    mount << "1. Add record\n" << "2. Delete record\n" << "3. Show tree\n" << "4. List values\n" << "5. Quit the program\n";


}

void helpMenu(){

    cout << "-i <FILENAME>                    integers with file";

    cout << "\n-s <FILENAME>                  strings with file";

    cout << "\n-i                                 empty tree with integer keys";

    cout << "\n-s                                  empty tree with string keys\n";
}
