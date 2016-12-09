
//node class that will store a pointer to either another node or a record (leaf)
/**
*   Node class that will store a pointer to either another node or a record (leaf).
*/
#ifndef NODE_H
#define NODE_H

#define MAXSIZE 150 /** < Max number of records */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include "shared.h"
//#include "record.h"
using namespace std;

class node;
  node *position, *recordPosition; //node variables

class node{

public:

/**
* Struct that is a record which holds a key (either int or string) and a left and right pointer to the next record.
*/
 struct record{

  node *left;
  node *right;
  int key; /** < holds a key of type integer */
  string stringKey; /** < holds a key of type string */

};

  int numberOfKeys; /** < Keeps track of the number of keys */

  record data[MAXSIZE]; /** < Array of records */

  node *parent;
  node *first;
  node *next;

  int isLeaf; /** < 1 = True */ // 1 True 0 False

  /**
  * Default node constructor.
  */
  node()
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


  //Puts a record in a node
  /**
  * Inserts a record in a node that has a key that is of type int.
  * @param record value A record.
  * @return void
  */
  void nodeInsert(record value)
  {
    int i = numberOfKeys - 1;
    for(i ; i >= 0 && data[i].key > value.key; i--)
        data[i + 1] = data[i];

    data[i + 1] = value;
    data[i + 1].left = value.left;
    data[i + 1].right = value.right;
    numberOfKeys++;
}

  /**
  * Inserts a record in a node that has a key that is of type string.
  * @param record value A record.
  * @return void
  */
  void stringNodeInsert(record value)
  {
    int i = numberOfKeys - 1;
    for(i ; i >= 0 && data[i].stringKey > value.stringKey; i--)
        data[i + 1] = data[i];

    data[i + 1] = value;
    data[i + 1].left = value.left;
    data[i + 1].right = value.right;
    numberOfKeys++;
}


  //Split nodes when there is no more room
  /**
  * Splits a node when there is no more room to add a record. This is for only keys that are of type int.
  * @param record value A record.
  * @return record Returns the new record that was created as a result of the split.
  */
  record splitNode(record value)
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


  /**
  * Splits a node when there is no more room to add a record. This is for only keys that are of type string.
  * @param record value A record.
  * @return record Returns the new record that was created as a result of the split.
  */
  record stringSplitNode(record value)
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


  //split parents nodes
  /**
  * Splits the parent. This is only for keys that are of type int.
  * @param record value A record
  * @return record Returns the new record that was created as a result of the split.
  */
  record splitParent(record value)
  {

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


  /**
  * Splits the parent. This is only for keys that are of type string.
  * @param record value A record
  * @return record Returns the new record that was created as a result of the split.
  */
  record stringSplitParent(record value)
  {

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


  node *nextindex(int value)
  {

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

  node *stringNextindex(string value)
  {

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

  /**
  * Displays the tree structure visually. This will only display the tree structure for keys of type int.
  */
  void display()
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

  /**
  * Displays the tree structure visually. This will only display the tree structure for keys of type string.
  */
  void stringDisplay()
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

  /**
  * Displays the values of the keys. This will only display the values for keys of type int.
  */
  void displayval()
  {

  for(int i = 0; i < numberOfKeys; i++){
    mount << data[i].key << endl;
    cout << data[i].key << endl;
  }
}

  /**
  * Displays the values of the keys. This will only display the values for keys of type string.
  */
  void stringDisplayval()
  {

  for(int i = 0;i < numberOfKeys; i++){
    mount << data[i].stringKey << endl;
    cout << data[i].stringKey << endl;
  }
}

}; //END NODE CLASS


#endif // NODE_H
