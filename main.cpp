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
                case 2:            cout << "\nWhat is the string key you would like to delete: \n\n";
                                    mount << "\nWhat is the string key you would like to delete: \n\n";
                                    //string value;
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








//if(argv[1][1] == 't'){
//
//cout << "Running empty string tree test\n";
//cout << "Making empty tree with keys of type string...\n\n";
//
//
//bPTree testTree(TEST_VALUE);
//
//cout << "Block size is set to " << TEST_VALUE << endl << endl;
//
//cout << "Tree output..." << endl << endl;
//
//testTree.stringShowTree();
//
//cout << "\nAdding values aF, iF, cG, jk, lO, Uh, MM, hF, rq, yH\n\n";
//testTree.stringInsert("aF");
//testTree.stringInsert("iF");
//testTree.stringInsert("cG");
//testTree.stringInsert("jk");
//testTree.stringInsert("lO");
//testTree.stringInsert("Uh");
//testTree.stringInsert("MM");
//testTree.stringInsert("hF");
//testTree.stringInsert("rq");
//testTree.stringInsert("yH");
//
//cout << "Tree output..." << endl << endl;
//mount << "Tree output..." << endl << endl;
//
//testTree.stringShowTree();
//
//cout << "Deleting cG and jk\n\n";
////testTree.stringDelete("lO");
//
//cout << "Tree output..." << endl << endl;
//
//testTree.stringShowTree();
//
////testTree.stringDelete("aF");
//
//cout << "\n\nListing values in tree";
//
//testTree.stringListValues();
//
//cout << "\n\nEND STRING TREE TEST\n\n\n\n";
//
//
//
//
//
//// empty int tree test
//
//cout << "Running empty int test\n";
//cout << "Making empty tree with keys of type int...\n\n";
//
//
//bPTree testTree2(TEST_VALUE);
//
//cout << "Block size is set to " << TEST_VALUE << endl << endl;
//
//cout << "Tree output..." << endl << endl;
//
//testTree.stringShowTree();
//
//cout << "\nAdding values 82, 15, 22, 53, 18, 19, 23, 44, 68, 35 \n\n";
//testTree2.insert(82);
//testTree2.insert(15);
//testTree2.insert(22);
//testTree2.insert(53);
//testTree2.insert(18);
//testTree2.insert(19);
//testTree2.insert(23);
//testTree2.insert(44);
//testTree2.insert(68);
//testTree2.insert(35);
//
//cout << "Tree output..." << endl << endl;
//mount << "Tree output..." << endl << endl;
//
//testTree2.showTree();
//
//cout << "Deleting 19 and 15\n\n";
////testTree2.intDelete(19);
//
//cout << "Tree output..." << endl << endl;
//
//testTree2.showTree();
//
////testTree.intDelete(15);
//
//cout << "Listing values...\n\n";
//
//testTree2.listValues();
//
//cout << "END INT TREE TEST\n\n\n\n";
//
//
//
////STRING FILE TEST TREE
//
//
//
//cout << "Running string tree test with input file...\n\n";
//
//bPTree testTree3(TEST_VALUE);
//
//cout << "Block size is set to " << TEST_VALUE << endl << endl;
//
//    ifstream stringInFile("stringAutoTest.txt");
//
//        cout << "Loading keys into the tree...\n\n";
//        mount << "Loading keys into the tree...\n\n";
//
//        while(stringInFile >> stringValue){
//            testTree3.stringInsert(stringValue); // only need stringValue
//        }
//
//
//        cout << "The B+ tree has been created.\n\n";
//        mount << "The B+ tree has been created.\n\n";
//
//
//
//cout << "Tree output..." << endl << endl;
//
//testTree3.stringShowTree();
//
//
//cout << "Deleting values ji and rb\n\n";
//testTree3.stringDelete("ji");
//
//cout << "\n\nTree output..." << endl << endl;
//
//testTree3.stringShowTree();
//
//testTree3.stringDelete("rb");
//
//
//cout << "\n\nTree output..." << endl << endl;
//
//testTree3.stringShowTree();
//
//cout << "Listing values...\n\n";
//
//testTree3.stringListValues();
//
//cout << "\n\nEND STRING INPUT FILE TEST\n\n\n\n";
//
//
//
//
//
//
//
//
//
////INT FILE TEST TREE
//
//
//
//cout << "Running int tree test with input file...\n\n";
//
//bPTree testTree4(TEST_VALUE);
//
//cout << "Block size is set to " << TEST_VALUE << endl << endl;
//
//    ifstream intInFile("intAutoTest.txt");
//
//        cout << "Loading keys into the tree...\n\n";
//        mount << "Loading keys into the tree...\n\n";
//
//        while(intInFile >> intValue){
//            testTree4.insert(intValue); // only need stringValue
//        }
//
//
//        cout << "The B+ tree has been created.\n\n";
//        mount << "The B+ tree has been created.\n\n";
//
//
//
//cout << "Tree output..." << endl << endl;
//
//testTree4.showTree();
//
//
//cout << "Deleting values 28 and 35\n\n";
//testTree4.intDelete(28);
//
//cout << "\n\nTree output..." << endl << endl;
//
//testTree4.showTree();
//
//testTree4.intDelete(35);
//
//
//cout << "\n\nTree output..." << endl << endl;
//
//testTree4.showTree();
//
//cout << "Listing values...\n\n";
//
//testTree4.listValues();
//
//cout << "\n\nEND INT INPUT FILE TEST\n\n\n\n";
//
//
//
//
//}





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
