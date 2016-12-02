#define MAXSIZE 150 //number of duplicate records in a node
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <conio.h>


using namespace std;

class node; //class declaration
node *position,*recordPosition; //node variables


//leaf that will store the key
struct record{

  node *left;
  node *right;
  int key;

};

//node class that will store a pointer to either another node or a record (leaf)
class node{

public:

  int numberOfKeys;

  record data[MAXSIZE];

  node *parent;
  node *first;
  node *next;

  int isLeaf; // 1 True 0 False

  node();

  //Puts a record in a node
  void nodeInsert(record value);

  //Split nodes when there is no more room
  record splitNode(record value);

  //split parents nodes
  record splitParent(record value);

  node *nextindex(int value);

  void display();
  void displayval();

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
class bPTree{


  int mkeys;

  node *root;

  int keys[100];//can change this to whatever
  int totalNumberOfKeys;

    public:

          bPTree(int n){

            mkeys = n;
            root = NULL;
            totalNumberOfKeys = 0;
          }

          //Inserts value into tree
          void insert(int value);


          //bool checkindex(int value,int choice);

          //display tree
          void showTree();

          //goes through the tree to display all of the values
          void listValues();




          // deletes a value from the tree
          void Delete(int value);
};

void node::display()
{

  cout << "[";

  for(int i = 0; i < numberOfKeys; i++)
    cout<<data[i].key<<" ";

  cout<<"]";
}
void node::displayval()
{

  for(int i = 0;i < numberOfKeys; i++)
  cout << data[i].key << endl;
}

node *node::nextindex(int value)
{

  if(this->data[0].left==NULL && this->data[0].right==NULL)
  return(this);
  else{
    for(int i = 0; i < numberOfKeys; i++)
    {
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

void node::nodeInsert(record value)
{

    for(int i = numberOfKeys-1; i >= 0 && data[i].key > value.key; i--)
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



void bPTree::showTree()
{
  Queue queue1,
        queue2;


  node *currentNode;
  queue1.enque(root);

  while( !queue1.empty() ){

     queue2.makeEmpty();
     cout << endl;
     while( !queue1.empty() ){

      currentNode = queue1.deque();
      currentNode-> display();
      cout << "  ";

      if( !currentNode-> isLeaf ){

        queue2.enque(currentNode-> data[0].left);

        for(int i = 0; i <currentNode-> numberOfKeys; i++)
            queue2.enque(currentNode->data[i].right);

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



int main(int argc, char **argv){

    //freopen("out.txt","w",stdout); //steals cout stream and writes it to file. This will cause the console to not display anything but will function correctly

  int number, //size of block
      value; // key value





  ifstream inputFile;


  cout << "Enter number of values per node: " << endl;
  cin >> number;




  bPTree bPlusTree(number);



    //OPEN FILE

      inputFile.open("test.txt");


      while(inputFile >> value){
        bPlusTree.insert(value); // only need value
      }


bPlusTree.showTree();

cout << endl << endl << endl;

bPlusTree.listValues();

getch();

inputFile.close();

  return 0;
}
