#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include "bPTree.h"
#include "node.h"
#include "Queue.h"
#include "shared.h"

using namespace std;

int main(){

int number;

  ifstream inputFile;

    string value;

  mount << "Enter number of values per node: " << endl;
  cout << "Enter number of values per node: " << endl;
  cin >> number;




  bPTree bPlusTree(number);



    //OPEN FILE

      inputFile.open("test.txt");


      while(inputFile >> value){
        bPlusTree.stringInsert(value); // only need value
      }


bPlusTree.stringShowTree();

cout << endl << endl << endl;

bPlusTree.stringListValues();

getch();

inputFile.close();


return 0;
}
