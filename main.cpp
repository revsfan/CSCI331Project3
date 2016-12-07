/**
*   @file main.cpp
*   @date
*   @author
*   This program is a simple B+ Tree program. The program can either read a file that contains strings or ints OR
*   the user can enter strings or ints into the tree manually.
*/


#define MAXSIZE 150 /** < Max number of records */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <stdlib.h>


/**
*   Displays a menu for different options for different operations on the tree.
*   @return void
*/
void menu();

using namespace std;

class node; //class declaration
node *position,*recordPosition; //node variables

std::ofstream mount("out.txt"); /** < Output file */



//leaf that will store the key
/**
*   A struct that is a record. This contains a pointer to a left and right node.
*   There are two fields depending if the keys are strings or integers.
*/
struct record{

  node *left;
  node *right;
  int key; /** < holds a key of type integer */
  string stringKey; /** < holds a key of type string */

};

//node class that will store a pointer to either another node or a record (leaf)
/**
*   Node class that will store a pointer to either another node or a record (leaf).
*/
class node{

public:

  int numberOfKeys; /** < Keeps track of the number of keys */

  record data[MAXSIZE]; /** < Array of records */

  node *parent;
  node *first;
  node *next;

  int isLeaf; /** < 1 = True */ // 1 True 0 False

  /**
  * Default node constructor.
  */
  node();

  //Puts a record in a node
  /**
  * Inserts a record in a node that has a key that is of type int.
  * @param record value A record.
  * @return void
  */
  void nodeInsert(record value);

  /**
  * Inserts a record in a node that has a key that is of type string.
  * @param record value A record.
  * @return void
  */
  void stringNodeInsert(record value);

  //Split nodes when there is no more room
  /**
  * Splits a node when there is no more room to add a record. This is for only keys that are of type int.
  * @param record value A record.
  * @return record Returns the new record that was created as a result of the split.
  */
  record splitNode(record value);

  /**
  * Splits a node when there is no more room to add a record. This is for only keys that are of type string.
  * @param record value A record.
  * @return record Returns the new record that was created as a result of the split.
  */
  record stringSplitNode(record value);

  //split parents nodes
  /**
  * Splits the parent. This is only for keys that are of type int.
  * @param record value A record
  * @return record Returns the new record that was created as a result of the split.
  */
  record splitParent(record value);

  /**
  * Splits the parent. This is only for keys that are of type string.
  * @param record value A record
  * @return record Returns the new record that was created as a result of the split.
  */
  record stringSplitParent(record value);

  node *nextindex(int value);
  node *stringNextindex(string value);

  /**
  * Displays the tree structure visually. This will only display the tree structure for keys of type int.
  */
  void display();

  /**
  * Displays the tree structure visually. This will only display the tree structure for keys of type string.
  */
  void stringDisplay();

  /**
  * Displays the values of the keys. This will only display the values for keys of type int.
  */
  void displayval();

  /**
  * Displays the values of the keys. This will only display the values for keys of type string.
  */
  void stringDisplayval();

}; //END NODE CLASS

//default constructor
node::node()
{


  for(int i = 0; i <= MAXSIZE; i++){

    data[i].left = NULL;
    data[i].right = NULL;

  }

  isLeaf = 1;
  numberOfKeys = 0;

  parent = NULL;
  first = NULL;
  next = NULL;

}

//Go through tree nodes
class Queue
{
  node *data[100]; //

  int Tail,
      Head;


    public:

      Queue(){ //default constructor

        Tail = 0;
        Head = 0;

      }


      int empty(){

        if(Tail == Head){

            return 1;

        }else{

            return 0;
        }
      }


      node *deque(){

        return data[Head++];
      }

      void enque(node *value){

        data[Tail++] = value;
      }

      void makeEmpty(){

        Tail = 0;
        Head = 0;
      }
}; //END QUEUE CLASS


//Main structure of the b+ tree
/**
*   B+ tree class. Contains the whole tree structure including functionalities with respect to the tree.
*/
class bPTree{


  int mkeys; /** < Max number of keys per node */

  node *root;

  int keys[100]; /** Max number of keys of type int*/ //can change this to whatever
  string stringKeys[100]; /** Max number of keys of type string*/
  int totalNumberOfKeys;

    public:

          bPTree(int n){

            mkeys = n;
            root = NULL;
            totalNumberOfKeys = 0;
          }

          //Inserts value into tree
          /**
          * Inserts a key of type int into the tree.
          * @param int value A key.
          * @return void
          */

          void insert(int value);

          /**
          * Inserts a key of type string into the tree.
          * @param string value A key.
          * @return void
          */
          void stringInsert(string value);


          //bool checkindex(int value,int choice);

          //display tree
          /**
          * Display the tree structure with keys of type int.
          */
          void showTree();

          /**
          * Display the tree structure with keys of type string.
          */
          void stringShowTree();

          //goes through the tree to display all of the values
          /**
          * Display all of the key values of type int.
          */
          void listValues();

          /**
          * Display all of the key values of type int.
          */
          void stringListValues();




          // deletes a value from the tree
          /**
          * Removes a key of type int from the tree.
          * @param int value The key to be removed from the tree.
          */
          void Delete(int value);

          /**
          * Removes a key of type string from the tree.
          * @param string value The key to be removed from the tree.
          */
          void stringDelete(string value);
};

void node::display()
{

  mount << "[";
  cout << "[";

  for(int i = 0; i < numberOfKeys; i++){
    mount << data[i].key << " ";
    cout << data[i].key << " ";
  }

  mount << "]";
  cout << "]";
}

void node::stringDisplay()
{

  mount << "[";
  cout << "[";

  for(int i = 0; i < numberOfKeys; i++){
    mount << data[i].stringKey << " ";
    cout << data[i].stringKey << " ";
  }

  mount << "]";
  cout << "]";
}




void node::displayval()
{

  for(int i = 0; i < numberOfKeys; i++){
    mount << data[i].key << endl;
    cout << data[i].key << endl;
  }
}


void node::stringDisplayval()
{

  for(int i = 0;i < numberOfKeys; i++){
    mount << data[i].stringKey << endl;
    cout << data[i].stringKey << endl;
  }
}



node *node::nextindex(int value){

    int i;

  if(this-> data[0].left == NULL && this->data[0].right == NULL)
        return(this);

  else{
    for(i = 0; i < numberOfKeys; i++){

      if(value < data[i].key)
        return data[i].left;
      else if(value == data[i].key)
        return data[i].right;
      else if(value > data[i].key && value < data[i+1].key)
        return data[i].right;
    }
    return data[i-1].right;

  }

}







node *node::stringNextindex(string value){

    int i;

  if(this-> data[0].left == NULL && this->data[0].right == NULL)
        return(this);

  else{
    for(i = 0; i < numberOfKeys; i++){

      if(value < data[i].stringKey)
        return data[i].left;
      else if(value == data[i].stringKey)
        return data[i].right;
      else if(value > data[i].stringKey && value < data[i+1].stringKey)
        return data[i].right;
    }
    return data[i - 1].right;

  }

}














void node::nodeInsert(record value)
{
    int i = numberOfKeys - 1;
    for(i ; i >= 0 && data[i].key > value.key; i--)
        data[i + 1] = data[i];

    data[i + 1] = value;
    data[i + 1].left = value.left;
    data[i + 1].right = value.right;
    numberOfKeys++;
}






void node::stringNodeInsert(record value)
{
    int i = numberOfKeys - 1;
    for(i ; i >= 0 && data[i].stringKey > value.stringKey; i--)
        data[i + 1] = data[i];

    data[i + 1] = value;
    data[i + 1].left = value.left;
    data[i + 1].right = value.right;
    numberOfKeys++;
}














record node::splitNode(record value)
{
  node *newblock;
  record newRecord;

  int i,
      j,
      center;

  center = (numberOfKeys) / 2;
  newblock = new node;

  //divide the leaf into two parts
  if(value.key > data[center].key){


    for(i = center + 1, j = 0; i <= numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center - 1;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    newblock-> nodeInsert(value);
    newblock-> first = newblock;
    newblock-> parent = parent;
    newRecord.key = newblock-> data[0].key;
    newRecord.right = newblock;
    newRecord.left = this;
    this-> next = newblock;
  }
  else{

    for(i = center, j = 0; i < numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    nodeInsert(value);
    newblock-> parent = parent;
    newRecord.key = newblock-> data[0].key;
    newRecord.right = newblock;
    newRecord.left = this;
    this-> next = newblock;

  }
  return(newRecord);
}






record node::stringSplitNode(record value)
{
  node *newblock;
  record newRecord;

  int i,
      j,
      center;

  center = (numberOfKeys) / 2;
  newblock = new node;

  //divide the leaf into two parts
  if(value.stringKey > data[center].stringKey){


    for(i = center + 1, j = 0; i <= numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center - 1;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    newblock-> stringNodeInsert(value);
    newblock-> first = newblock;
    newblock-> parent = parent;
    newRecord.stringKey = newblock-> data[0].stringKey;
    newRecord.right = newblock;
    newRecord.left = this;
    this-> next = newblock;
  }
  else{

    for(i = center, j = 0; i < numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    stringNodeInsert(value);
    newblock-> parent = parent;
    newRecord.stringKey = newblock-> data[0].stringKey;
    newRecord.right = newblock;
    newRecord.left = this;
    this-> next = newblock;

  }
  return(newRecord);
}
















record node::splitParent(record value){

  node *newblock;
  record newRecord;

  int i,
      j,
      center;

  center = (numberOfKeys - 2) / 2;
  newblock = new node;

  //divide the parent into two parts
  if(value.key > data[center].key){

    for( i = center + 1, j = 0; i <= numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center - 1;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    newblock-> nodeInsert(value);
    newblock-> first = newblock;
    newblock-> parent = parent;
    this-> data[this-> numberOfKeys].right = newblock-> data[0].left;
    newblock-> data[1].left = newblock-> data[0].right;
    newRecord.key = newblock-> data[0].key;
    newRecord.right = newblock;
    newRecord.left = this;
    this-> isLeaf = 0;
    newblock-> isLeaf = 0;


    //deleting the first key
    for( i = 1; i < newblock-> numberOfKeys; i++)
      newblock-> data[i - 1] = newblock-> data[i];

    newblock-> numberOfKeys--;

    //applying parent
    for( i = 0; i < newblock-> numberOfKeys; i++){

      newblock-> data[i].right-> parent = newblock;
    }
  }else{

    for( i = center, j = 0; i < numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    nodeInsert(value);
    newblock-> parent = parent;
    this-> data[this-> numberOfKeys].right = newblock-> data[0].left;
    newblock-> data[1].left = newblock-> data[0].right;
    newRecord.key = newblock-> data[0].key;
    newRecord.right = newblock;
    newRecord.left = this;


    //delete first key from node
    for( i = 1; i < newblock-> numberOfKeys; i++)
      newblock-> data[i - 1] = newblock-> data[i];

    newblock-> numberOfKeys--;


    //applying the parent
    for( i = 0; i < newblock-> numberOfKeys; i++){

      newblock-> data[i].right-> parent = newblock;
    }
  }//END ELSE

  return(newRecord);
}






record node::stringSplitParent(record value){

  node *newblock;
  record newRecord;

  int i,
      j,
      center;

  center = (numberOfKeys - 2) / 2;
  newblock = new node;

  //divide the parent into two parts
  if(value.stringKey > data[center].stringKey){

    for( i = center + 1, j = 0; i <= numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center - 1;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    newblock-> stringNodeInsert(value);
    newblock-> first = newblock;
    newblock-> parent = parent;
    this-> data[this-> numberOfKeys].right = newblock-> data[0].left;
    newblock-> data[1].left = newblock-> data[0].right;
    newRecord.stringKey = newblock-> data[0].stringKey;
    newRecord.right = newblock;
    newRecord.left = this;
    this-> isLeaf = 0;
    newblock-> isLeaf = 0;


    //deleting the first key
    for( i = 1; i < newblock-> numberOfKeys; i++)
      newblock-> data[i - 1] = newblock-> data[i];

    newblock-> numberOfKeys--;

    //applying parent
    for( i = 0; i < newblock-> numberOfKeys; i++){

      newblock-> data[i].right-> parent = newblock;
    }
  }else{

    for( i = center, j = 0; i < numberOfKeys; i++, j++)
      newblock-> data[j] = data[i];

    newblock-> numberOfKeys = numberOfKeys - center;
    numberOfKeys = numberOfKeys - newblock-> numberOfKeys;
    stringNodeInsert(value);
    newblock-> parent = parent;
    this-> data[this-> numberOfKeys].right = newblock-> data[0].left;
    newblock-> data[1].left = newblock-> data[0].right;
    newRecord.stringKey = newblock-> data[0].stringKey;
    newRecord.right = newblock;
    newRecord.left = this;


    //delete first key from node
    for( i = 1; i < newblock-> numberOfKeys; i++)
      newblock-> data[i - 1] = newblock-> data[i];

    newblock-> numberOfKeys--;


    //applying the parent
    for( i = 0; i < newblock-> numberOfKeys; i++){

      newblock-> data[i].right-> parent = newblock;
    }
  }//END ELSE

  return(newRecord);
}













void bPTree::showTree()
{
  Queue queue1,
        queue2;


  node *currentNode;
  queue1.enque(root);

  while( !queue1.empty() ){

     queue2.makeEmpty();
     mount << endl;
     cout << endl;

     while( !queue1.empty() ){

      currentNode = queue1.deque();
      currentNode-> display();
      mount << "  ";
      cout << "  ";

      if( !currentNode-> isLeaf ){

        queue2.enque(currentNode-> data[0].left);

        for(int i = 0; i <currentNode-> numberOfKeys; i++)
            queue2.enque(currentNode-> data[i].right);

      }
    }

    queue1 = queue2;
  }
}








void bPTree::stringShowTree()
{
  Queue queue1,
        queue2;


  node *currentNode;
  queue1.enque(root);

  while( !queue1.empty() ){

     queue2.makeEmpty();
     mount << endl;
     cout << endl;

     while( !queue1.empty() ){

      currentNode = queue1.deque();
      currentNode-> stringDisplay();
      mount << "  ";
      cout << "  ";

      if( !currentNode-> isLeaf ){

        queue2.enque(currentNode-> data[0].left);

        for(int i = 0; i <currentNode-> numberOfKeys; i++)
            queue2.enque(currentNode-> data[i].right);

      }
    }

    queue1 = queue2;
  }
}








void bPTree::listValues()
{
  Queue q1,
        q2;

  node *currentNode;

  q1.enque(root);

  while(!q1.empty()){

    q2.makeEmpty();

    mount << "\n";
    cout << "\n";

    while(!q1.empty()){

      currentNode = q1.deque();

      if(currentNode-> isLeaf){

        currentNode-> displayval();
      }
      if( !currentNode-> isLeaf){


        q2.enque(currentNode-> data[0].left);

          for(int i = 0;i < currentNode-> numberOfKeys;i++)
            q2.enque(currentNode-> data[i].right);

      }
    }

    q1 = q2;
  }
}




void bPTree::stringListValues()
{
  Queue q1,
        q2;

  node *currentNode;

  q1.enque(root);

  while(!q1.empty()){

    q2.makeEmpty();

    mount << "\n";
    cout << "\n";

    while(!q1.empty()){

      currentNode = q1.deque();

      if(currentNode-> isLeaf){

        currentNode-> stringDisplayval();
      }
      if( !currentNode-> isLeaf){


        q2.enque(currentNode-> data[0].left);

          for(int i = 0;i < currentNode-> numberOfKeys;i++)
            q2.enque(currentNode-> data[i].right);

      }
    }

    q1 = q2;
  }
}












//insert value into the tree
void bPTree::insert(int value) // only need value
{


  record newRecord;

  node *currentNode,
       *temp;

  newRecord.key = value;


  newRecord.left = NULL;
  newRecord.right = NULL;
  if(root == NULL){

    root = new node;
    root-> nodeInsert(newRecord);

  }else{

    currentNode = root;
    while( !(currentNode-> isLeaf) )
      currentNode=currentNode->nextindex(value);

    if(currentNode-> numberOfKeys < mkeys)
      currentNode-> nodeInsert(newRecord);

    else{

      if(currentNode-> isLeaf){

        newRecord = currentNode-> splitNode(newRecord);
        currentNode-> isLeaf = 1;

      }else{

        newRecord = currentNode-> splitParent(newRecord);
        currentNode-> isLeaf = 0;
      }

      while(1){

        if(currentNode == root){

          temp = new node;
          temp-> data[0] = newRecord;
          temp-> first = root;
          temp-> parent = NULL;
          temp-> data[0].left = newRecord.left;
          temp-> data[0].right = newRecord.right;
          temp-> numberOfKeys = 1;
          root = temp;
          root-> isLeaf = 0;
          temp-> first-> parent = temp;
          temp-> data[0].right-> parent = temp;
          temp-> data[0].left-> parent = temp;
          return;

        }else{

          currentNode = currentNode-> parent;

          if(currentNode-> data[0].left != NULL)
            currentNode-> isLeaf = 0;

          if(currentNode-> numberOfKeys < mkeys){

            currentNode-> nodeInsert(newRecord);
            return;

          }else{

            if(currentNode-> isLeaf){

              newRecord = currentNode-> splitNode(newRecord);
              currentNode-> isLeaf = 1;

            }else{

              newRecord = currentNode-> splitParent(newRecord);
              currentNode-> isLeaf = 0;
            }

          }
        }

      }
    }

  }
}








//insert value into the tree
void bPTree::stringInsert(string value) // only need value
{


  record newRecord;

  node *currentNode,
       *temp;

  newRecord.stringKey = value;


  newRecord.left = NULL;
  newRecord.right = NULL;
  if(root == NULL){

    root = new node;
    root-> stringNodeInsert(newRecord); //stringNodeInsert

  }else{

    currentNode = root;
    while( !(currentNode-> isLeaf) )
      currentNode = currentNode-> stringNextindex(value);

    if(currentNode-> numberOfKeys < mkeys)
      currentNode-> stringNodeInsert(newRecord);

    else{

      if(currentNode-> isLeaf){

        newRecord = currentNode-> stringSplitNode(newRecord);
        currentNode-> isLeaf = 1;

      }else{

        newRecord = currentNode-> stringSplitParent(newRecord);
        currentNode-> isLeaf = 0;
      }

      while(1){

        if(currentNode == root){

          temp = new node;
          temp-> data[0] = newRecord;
          temp-> first = root;
          temp-> parent = NULL;
          temp-> data[0].left = newRecord.left;
          temp-> data[0].right = newRecord.right;
          temp-> numberOfKeys = 1;
          root = temp;
          root-> isLeaf = 0;
          temp-> first-> parent = temp;
          temp-> data[0].right-> parent = temp;
          temp-> data[0].left-> parent = temp;
          return;

        }else{

          currentNode = currentNode-> parent;

          if(currentNode-> data[0].left != NULL)
            currentNode-> isLeaf = 0;

          if(currentNode-> numberOfKeys < mkeys){

            currentNode-> stringNodeInsert(newRecord);
            return;

          }else{

            if(currentNode-> isLeaf){

              newRecord = currentNode-> stringSplitNode(newRecord);
              currentNode-> isLeaf = 1;

            }else{

              newRecord = currentNode-> stringSplitParent(newRecord);
              currentNode-> isLeaf = 0;
            }

          }
        }

      }
    }

  }
}











void bPTree::Delete(int value){

  node *left,
       *right;

  record *center;

  node *p,
       *q;


  int i,
      j,
      middleIndex;


  for(i = 0; p-> data[i].key != value; i++)
  ;


  if(p-> isLeaf){

    for(i = i + 1; i < p-> numberOfKeys; i++)
      p-> data[i - 1] = p-> data[i];
    p-> numberOfKeys--;


    //delete the value from keys[]
    for(i = 0; i < totalNumberOfKeys; i++)
      if(keys[i] == value){
        for(j = i; j < totalNumberOfKeys; j++)
        keys[j] = keys[j + 1];
    }
    totalNumberOfKeys--;
  }


  while(p-> isLeaf){

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if( p == root ){

      if(p-> numberOfKeys > 0)
        return;
      else{

        root = p-> data[0].left;
        return;
      }
    }


    q = p-> parent;

    if(q-> data[0].left == p || q-> data[0].right == p){

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }else{


      for( i = 0; i < q-> numberOfKeys; i++)
        if(q-> data[i].left == p || q-> data[i].right == p)
          break;

      left = q-> data[i].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }

    if(right-> numberOfKeys > mkeys / 2){

      left-> data[left-> numberOfKeys].key = center-> key;
      left-> numberOfKeys++;
      center-> key = right-> data[0].key;

      for(i = 1; i < right-> numberOfKeys; i++)
        right->data[i-1]=right->data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else{

      left-> data[left-> numberOfKeys].key = center-> key;
      left -> numberOfKeys++;

      for(j = 0; j < right-> numberOfKeys; j++)
        left-> data[left-> numberOfKeys + j] = right-> data[j];

      left-> numberOfKeys += right-> numberOfKeys;

      //delete record from parent
      for(i = middleIndex + 1; i < q-> numberOfKeys; i++)
        q-> data[i - 1] = q-> data[i];

      q-> numberOfKeys--;
      p = q;
    }


  }

  q = recordPosition;

  while( !q-> isLeaf){

    for( i = 0; i < q-> numberOfKeys; i++){

      if(q-> data[i].key == value){

        for( i = i + 1; i < q-> numberOfKeys; i++)
          q-> data[i - 1] = q-> data[i];
        q-> numberOfKeys--;
        break;
      }

    }
    if(i == q-> numberOfKeys)
    break;
  }

  p = q;

  while( !p-> isLeaf){

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if(p == root ){

      if(p-> numberOfKeys > 0)
        return;
      else{

        root = p-> first;
        return;
      }
    }

    q = p-> parent;
    if(q-> data[0].left == p || q-> data[0].right == p){

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }else{

      for( i = 1; i < q-> numberOfKeys; i++)
        if(q->data[i].right==p)
          break;

      left = q-> data[i - 1].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }


    //left has an extra key
    if(left-> numberOfKeys > mkeys / 2){

      for(i = right-> numberOfKeys - 1; i >= 0; i--)
        right-> data[i + 1] = right-> data[i];

      right-> numberOfKeys++;
      right-> data[0].key = center-> key;
      center-> key = left-> data[left-> numberOfKeys - 1].key;
      left-> numberOfKeys--;
      return;
    }

    //right has an extra key
    else

    if(right-> numberOfKeys > mkeys / 2){

      left-> data[left-> numberOfKeys].key = center-> key;
      left-> numberOfKeys++;
      center-> key = right-> data[0].key;

      for(i = 1; i < right-> numberOfKeys; i++)
        right-> data[i - 1] = right-> data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else{

      left-> data[left-> numberOfKeys].key = center-> key;
      left-> numberOfKeys++;

      for(j = 0; j < right-> numberOfKeys; j++)
        left-> data[left-> numberOfKeys + j] = right-> data[j];

      left-> numberOfKeys += right-> numberOfKeys;

      //delete the record from the parent
      for(i = middleIndex + 1; i < q-> numberOfKeys ; i++)
      q-> data[i - 1] = q-> data[i];
      q-> numberOfKeys--;
      p = q;
    }

  }


}




void bPTree::stringDelete(string value){

  node *left,
       *right;

  record *center;

  node *p,
       *q;


  int i,
      j,
      middleIndex;


  for(i = 0; p-> data[i].stringKey != value; i++)
  ;


  if(p-> isLeaf){

    for(i = i + 1; i < p-> numberOfKeys; i++)
      p-> data[i - 1] = p-> data[i];
    p-> numberOfKeys--;


    //delete the value from keys[]
    for(i = 0; i < totalNumberOfKeys; i++)
      if(stringKeys[i] == value){
        for(j = i; j < totalNumberOfKeys; j++)
        stringKeys[j] = stringKeys[j + 1];
    }
    totalNumberOfKeys--;
  }


  while(p-> isLeaf){

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if( p == root ){

      if(p-> numberOfKeys > 0)
        return;
      else{

        root = p-> data[0].left;
        return;
      }
    }


    q = p-> parent;

    if(q-> data[0].left == p || q-> data[0].right == p){

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }else{


      for( i = 0; i < q-> numberOfKeys; i++)
        if(q-> data[i].left == p || q-> data[i].right == p)
          break;

      left = q-> data[i].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }

    if(right-> numberOfKeys > mkeys / 2){

      left-> data[left-> numberOfKeys].stringKey = center-> stringKey;
      left-> numberOfKeys++;
      center-> stringKey = right-> data[0].stringKey;

      for(i = 1; i < right-> numberOfKeys; i++)
        right-> data[i - 1] = right-> data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else{

      left-> data[left-> numberOfKeys].stringKey = center-> stringKey;
      left -> numberOfKeys++;

      for(j = 0; j < right-> numberOfKeys; j++)
        left-> data[left-> numberOfKeys + j] = right-> data[j];

      left-> numberOfKeys += right-> numberOfKeys;

      //delete record from parent
      for(i = middleIndex + 1; i < q-> numberOfKeys; i++)
        q-> data[i - 1] = q-> data[i];

      q-> numberOfKeys--;
      p = q;
    }


  }

  q = recordPosition; //record position is a node

  while( !q-> isLeaf){

    for( i = 0; i < q-> numberOfKeys; i++){

      if(q-> data[i].stringKey == value){

        for( i = i + 1; i < q-> numberOfKeys; i++)
          q-> data[i - 1] = q-> data[i];
        q-> numberOfKeys--;
        break;
      }

    }
    if(i == q-> numberOfKeys)
    break;
  }

  p = q;

  while( !p-> isLeaf){

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if(p == root ){

      if(p-> numberOfKeys > 0)
        return;
      else{

        root = p-> first;
        return;
      }
    }

    q = p-> parent;
    if(q-> data[0].left == p || q-> data[0].right == p){

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }else{

      for( i = 1; i < q-> numberOfKeys; i++)
        if(q-> data[i].right == p)
          break;

      left = q-> data[i - 1].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }


    //left has an extra key
    if(left-> numberOfKeys > mkeys / 2){

      for(i = right-> numberOfKeys - 1; i >= 0; i--)
        right-> data[i + 1] = right-> data[i];

      right-> numberOfKeys++;
      right-> data[0].stringKey = center-> stringKey;
      center-> stringKey = left-> data[left-> numberOfKeys - 1].stringKey;
      left-> numberOfKeys--;
      return;
    }

    //right has an extra key
    else

    if(right-> numberOfKeys > mkeys / 2){

      left-> data[left-> numberOfKeys].stringKey = center-> stringKey;
      left-> numberOfKeys++;
      center-> stringKey = right-> data[0].stringKey;

      for(i = 1; i < right-> numberOfKeys; i++)
        right-> data[i - 1] = right-> data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else{

      left-> data[left-> numberOfKeys].stringKey = center-> stringKey;
      left-> numberOfKeys++;

      for(j = 0; j < right-> numberOfKeys; j++)
        left-> data[left-> numberOfKeys + j] = right-> data[j];

      left-> numberOfKeys += right-> numberOfKeys;

      //delete the record from the parent
      for(i = middleIndex + 1; i < q-> numberOfKeys ; i++)
      q-> data[i - 1] = q-> data[i];
      q-> numberOfKeys--;
      p = q;
    }

  }


}











int main(int argc, char* argv[]){


  int number; /** < Size of a block */ //size of block
  int intValue; /** < A key value of type int */
  string stringValue; /** < A key value of type string */ // key value

//  char intInFile[16];
//  char stringInFile[16];



//ARG EXECUTION AREA

//string with input file
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

        while(inputFile >> stringValue){
            bPlusTree.stringInsert(stringValue); // only need stringValue
        }

        cout << "The B+ tree has been created.\n\n";
        mount << "The B+ tree has been created.\n\n";
    }


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

        while(inputFile >> intValue){
            bPlusTree.insert(intValue); // only need intValue
        }

        cout << "The B+ tree has been created.\n\n";
        mount << "The B+ tree has been created.\n\n";


        }



}



if(argc == 5){ //load 2 files one of type string other of type int. This is for testing mostly. The key types cant mix into one tree.


        //load 2 files

        ifstream stringInFile( argv[2]); //string file
        cout << "String file opened successfully \n\n";
        mount << "String file opened successfully \n\n";

        ifstream intIntFile( argv[4]); //int file
        cout << "Integer file opened successfully \n\n";
        mount<< "Integer file opened successfully \n\n";



        //make and load the values for a string tree
        bPTree bPlusTreeString(number);

        cout << "Loading string keys into the tree...\n\n";
        mount << "Loading string keys into the tree...\n\n";

        while(inputFile >> stringValue){
            bPlusTreeString.stringInsert(stringValue); // only need stringValue
        }

        cout << "The B+ tree has been created using keys of type string.\n\n";
        mount << "The B+ tree has been created using keys of type string.\n\n";




        //make and load the values for a int tree

        bPTree bPlusTreeInt(number);

        cout << "Loading integer keys into the tree...\n\n";
        mount << "Loading integer keys into the tree...\n\n";

        while(inputFile >> intValue){
            bPlusTreeInt.insert(intValue); // only need intValue
        }

        cout << "The B+ tree has been created using keys of type int.\n\n";
        mount << "The B+ tree has been created using keys of type int.\n\n";

        char choice = '0';
        int treeChoice = -1;

        while (treeChoice < 3){



        cout << "Which tree (string/integer) would you like to edit?\n";
        mount << "Which tree (string/integer) would you like to edit?\n";

        cout << "1. String tree\n2. Integer tree\n3. Exit program\n";
        mount << "1. String tree\n2. Integer tree\n3. Exit program\n";

        cin >> treeChoice;

        if(treeChoice == 3){ //quit the program

            exit(EXIT_SUCCESS);
        }


            if(treeChoice == 1){ //string tree

                while(choice < '5'){

                menu(); //displays the menu

                cin >> choice;

                    switch(choice){

                        //adding a record
                        case '1':   cout << "What is the string key you would like to add: \n";
                                    mount << "What is the string key you would like to add: \n";
                                    string value;
                                    cin >> value;

                                    bPlusTreeString.stringInsert(value);
                                    cout << "Key has been added\n\n";
                                    mount << "Key has been added\n\n";
                                    break;

                        //deleting a record
                        case '2':   cout << "What is the string key you would like to delete: \n";
                                    mount << "What is the string key you would like to delete: \n";
                                    string value;
                                    cin >> value;

                                    bPlusTreeString.stringDelete(value);
                                    cout << "Key has been deleted from the tree\n\n";
                                    mount << "Key has been deleted from the tree\n\n";
                                    break;

                        //show tree
                        case '3':   bPlusTreeString.stringShowTree();
                                    break;

                        //list values
                        case '4':   bPlusTreeString.stringListValues();
                                    break;

                        //go back to the other menu
                        case '5':   //exit(EXIT_SUCCESS);
                                    break;

                        //ERROR
                        default:    cout << "Something went wrong...";
                                    mount << "Something went wrong...";
                                    exit(EXIT_FAILURE);
                    }


                }

             //END IF TREECHOICE == 1

            }else{ //else TREECHOICE == 2 (ints)

                while(choice < '5'){

                menu(); //displays the menu

                cin >> choice;

                    switch(choice){

                        //adding a record
                        case '1':   cout << "What is the int key you would like to add: \n";
                                    mount << "What is the int key you would like to add: \n";
                                    int value;
                                    cin >> value;

                                    bPlusTreeInt.insert(value);
                                    cout << "Key has been added\n\n";
                                    mount << "Key has been added\n\n";
                                    break;

                        //deleting a record
                        case '2':   cout << "What is the int key you would like to delete: \n";
                                    mount << "What is the int key you would like to delete: \n";
                                    int value;
                                    cin >> value;

                                    bPlusTreeInt.Delete(value);
                                    cout << "Key has been deleted from the tree\n\n";
                                    mount << "Key has been deleted from the tree\n\n";
                                    break;

                        //show tree
                        case '3':   bPlusTreeInt.showTree();
                                    break;

                        //list values
                        case '4':   bPlusTreeInt.listValues();
                                    break;

                        //go back to the other menu
                        case '5':   //exit(EXIT_SUCCESS);
                                    break;

                        //ERROR
                        default:    cout << "Something went wrong...";
                                    mount << "Something went wrong...";
                                    exit(EXIT_FAILURE);
                    }


                }

            }//END ELSE




        }//END WHILE

}//END ARGC == 5


if(argc == 2){



}

//
//
//  ifstream inputFile;
//
//
//  mount << "Enter number of values per node: " << endl;
//  cout << "Enter number of values per node: " << endl;
//  cin >> number;
//
//
//
//
//  bPTree bPlusTree(number);
//
//
//
//    //OPEN FILE
//
//      inputFile.open("test.txt");
//
//
//      while(inputFile >> value){
//        bPlusTree.stringInsert(value); // only need value
//      }
//
//
//bPlusTree.stringShowTree();
//
//cout << endl << endl << endl;
//
//bPlusTree.stringListValues();
//
//getch();
//
//inputFile.close();

  return 0;
}


void menu(){


    cout << "What would you like to do?" << endl << endl;
    mount << "What would you like to do?" << endl << endl;

    cout << "1. Add record\n" << "2. Delete record\n" << "3. Show tree\n" << "4. List values\n" << "5. Go back to the previous menu\n";
    mount << "1. Add record\n" << "2. Delete record\n" << "3. Show tree\n" << "4. List values\n" << "5. Go back to the previous menu\n";


}

void helpMenu(){

    cout << "List of different arguments: \n\n";
    cout << "-s <filename> Loads a file  "
}
