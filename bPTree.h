#define MAXSIZE 150 /** < Max number of records */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include "node.h"
#include "Queue.h"



//Main structure of the b+ tree
/**
*   B+ tree class. Contains the whole tree structure including functionalities with respect to the tree.
*/
class bPTree
{


  int mkeys; /** < Max number of keys per node */

  node *root;
  node *position,*recordPosition; //node variables
  int keys[100]; /** Max number of keys of type int*/ //can change this to whatever
  string stringKeys[100]; /** Max number of keys of type string*/
  int totalNumberOfKeys;

    public:
    	

          bPTree(int n)
		  {

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

void insert(int value)
{


  node::record newRecord;

  node *currentNode,
       *temp;

  newRecord.key = value;


  newRecord.left = NULL;
  newRecord.right = NULL;
  if(root == NULL)
  {

    root = new node;
    root-> nodeInsert(newRecord);

  }
  else
  {

    currentNode = root;
    while( !(currentNode-> isLeaf) )
      currentNode=currentNode->nextindex(value);

    if(currentNode-> numberOfKeys < mkeys)
      currentNode-> nodeInsert(newRecord);

    else
	{

      if(currentNode-> isLeaf)
	  {

        newRecord = currentNode-> splitNode(newRecord);
        currentNode-> isLeaf = 1;

      }
	  else
	  {

        newRecord = currentNode-> splitParent(newRecord);
        currentNode-> isLeaf = 0;
      }

      while(1)
	  {

        if(currentNode == root)
		{

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

        }
		else
		{

          currentNode = currentNode-> parent;

          if(currentNode-> data[0].left != NULL)
            currentNode-> isLeaf = 0;

          if(currentNode-> numberOfKeys < mkeys)
		  {

            currentNode-> nodeInsert(newRecord);
            return;

          }
		  else
		  {

            if(currentNode-> isLeaf)
			{

              newRecord = currentNode-> splitNode(newRecord);
              currentNode-> isLeaf = 1;

            }
			else
			{

              newRecord = currentNode-> splitParent(newRecord);
              currentNode-> isLeaf = 0;
            }

          }
        }

      }
    }

  }
}


          /**
          * Inserts a key of type string into the tree.
          * @param string value A key.
          * @return void
          */
void stringInsert(string value)
{


  node::record newRecord;

  node *currentNode,
       *temp;

  newRecord.stringKey = value;


  newRecord.left = NULL;
  newRecord.right = NULL;
  if(root == NULL)
  {

    root = new node;
    root-> stringNodeInsert(newRecord); //stringNodeInsert

  }
  else
  {

    currentNode = root;
    while( !(currentNode-> isLeaf) )
      currentNode = currentNode-> stringNextindex(value);

    if(currentNode-> numberOfKeys < mkeys)
      currentNode-> stringNodeInsert(newRecord);

    else
	{

      if(currentNode-> isLeaf)
	  {

        newRecord = currentNode-> stringSplitNode(newRecord);
        currentNode-> isLeaf = 1;

      }
	  else
	  {

        newRecord = currentNode-> stringSplitParent(newRecord);
        currentNode-> isLeaf = 0;
      }

      while(1)
	  {

        if(currentNode == root)
		{

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

        }
		else
		{

          currentNode = currentNode-> parent;

          if(currentNode-> data[0].left != NULL)
            currentNode-> isLeaf = 0;

          if(currentNode-> numberOfKeys < mkeys)
		  {

            currentNode-> stringNodeInsert(newRecord);
            return;

          }
		  else
		  {

            if(currentNode-> isLeaf)
			{

              newRecord = currentNode-> stringSplitNode(newRecord);
              currentNode-> isLeaf = 1;

            }
			else
			{

              newRecord = currentNode-> stringSplitParent(newRecord);
              currentNode-> isLeaf = 0;
            }

          }
        }

      }
    }

  }
}



          //bool checkindex(int value,int choice);

          //display tree
          /**
          * Display the tree structure with keys of type int.
          */
void showTree()
{
  Queue queue1,
        queue2;


  node *currentNode;
  queue1.enque(root);

  while( !queue1.empty() )
  {

     queue2.makeEmpty();
     mount << endl;
     cout << endl;

     while( !queue1.empty() )
	 {

      currentNode = queue1.deque();
      currentNode-> display();
      mount << "  ";
      cout << "  ";

      if( !currentNode-> isLeaf )
	  {

        queue2.enque(currentNode-> data[0].left);

        for(int i = 0; i <currentNode-> numberOfKeys; i++)
            queue2.enque(currentNode-> data[i].right);

      }
    }

    queue1 = queue2;
  }
}


          /**
          * Display the tree structure with keys of type string.
          */
void stringShowTree()
{
  Queue queue1,
        queue2;


  node *currentNode;
  queue1.enque(root);

  while( !queue1.empty() )
  {

     queue2.makeEmpty();
     mount << endl;
     cout << endl;

     while( !queue1.empty() )
	 {

      currentNode = queue1.deque();
      currentNode-> stringDisplay();
      mount << "  ";
      cout << "  ";

      if( !currentNode-> isLeaf )
	  {

        queue2.enque(currentNode-> data[0].left);

        for(int i = 0; i <currentNode-> numberOfKeys; i++)
            queue2.enque(currentNode-> data[i].right);

      }
    }

    queue1 = queue2;
  }
}


          //goes through the tree to display all of the values
          /**
          * Display all of the key values of type int.
          */

void listValues()
{
  Queue q1,
        q2;

  node *currentNode;

  q1.enque(root);

  while(!q1.empty())
  {

    q2.makeEmpty();

    mount << "\n";
    cout << "\n";

    while(!q1.empty())
	{

      currentNode = q1.deque();

      if(currentNode-> isLeaf)
	  {

        currentNode-> displayval();
      }
      if( !currentNode-> isLeaf)
	  {


        q2.enque(currentNode-> data[0].left);

          for(int i = 0;i < currentNode-> numberOfKeys;i++)
            q2.enque(currentNode-> data[i].right);

      }
    }

    q1 = q2;
  }
}


          /**
          * Display all of the key values of type int.
          */
void stringListValues()
{
  Queue q1,
        q2;

  node *currentNode;

  q1.enque(root);

  while(!q1.empty())
  {

    q2.makeEmpty();

    mount << "\n";
    cout << "\n";

    while(!q1.empty())
	{

      currentNode = q1.deque();

      if(currentNode-> isLeaf)
	  {

        currentNode-> stringDisplayval();
      }
      if( !currentNode-> isLeaf)
	  {


        q2.enque(currentNode-> data[0].left);

          for(int i = 0;i < currentNode-> numberOfKeys;i++)
            q2.enque(currentNode-> data[i].right);

      }
    }

    q1 = q2;
  }
}





          // deletes a value from the tree
          /**
          * Removes a key of type int from the tree.
          * @param int value The key to be removed from the tree.
          */
void Delete(int value)
{

  node *left,
       *right;

  node::record *center;

  node *p,
       *q;


  int i,
      j,
      middleIndex;


  for(i = 0; p-> data[i].key != value; i++)
  ;


  if(p-> isLeaf)
  {

    for(i = i + 1; i < p-> numberOfKeys; i++)
      p-> data[i - 1] = p-> data[i];
    p-> numberOfKeys--;


    //delete the value from keys[]
    for(i = 0; i < totalNumberOfKeys; i++)
      if(keys[i] == value)
	  {
        for(j = i; j < totalNumberOfKeys; j++)
        keys[j] = keys[j + 1];
	  }
    totalNumberOfKeys--;
  }


  while(p-> isLeaf)
  {

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if( p == root )
	{

      if(p-> numberOfKeys > 0)
        return;
      else
	  {

        root = p-> data[0].left;
        return;
      }
    }


    q = p-> parent;

    if(q-> data[0].left == p || q-> data[0].right == p)
	{

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }
	else
	{


      for( i = 0; i < q-> numberOfKeys; i++)
        if(q-> data[i].left == p || q-> data[i].right == p)
          break;

      left = q-> data[i].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }

    if(right-> numberOfKeys > mkeys / 2)
	{

      left-> data[left-> numberOfKeys].key = center-> key;
      left-> numberOfKeys++;
      center-> key = right-> data[0].key;

      for(i = 1; i < right-> numberOfKeys; i++)
        right->data[i-1]=right->data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else
	{

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

  while( !q-> isLeaf)
  {

    for( i = 0; i < q-> numberOfKeys; i++)
	{

      if(q-> data[i].key == value)
	  {

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

  while( !p-> isLeaf)
  {

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if(p == root )
	{

      if(p-> numberOfKeys > 0)
        return;
      else
	  {

        root = p-> first;
        return;
      }
    }

    q = p-> parent;
    if(q-> data[0].left == p || q-> data[0].right == p)
	{

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }
	else
	{

      for( i = 1; i < q-> numberOfKeys; i++)
        if(q->data[i].right==p)
          break;

      left = q-> data[i - 1].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }


    //left has an extra key
    if(left-> numberOfKeys > mkeys / 2)
	{

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

    if(right-> numberOfKeys > mkeys / 2)
	{

      left-> data[left-> numberOfKeys].key = center-> key;
      left-> numberOfKeys++;
      center-> key = right-> data[0].key;

      for(i = 1; i < right-> numberOfKeys; i++)
        right-> data[i - 1] = right-> data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else
	{

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


          /**
          * Removes a key of type string from the tree.
          * @param string value The key to be removed from the tree.
          */
void stringDelete(string value)
{

  node *left,
       *right;

  node::record *center;

  node *p,
       *q;


  int i,
      j,
      middleIndex;


  for(i = 0; p-> data[i].stringKey != value; i++)
  ;


  if(p-> isLeaf)
  {

    for(i = i + 1; i < p-> numberOfKeys; i++)
      p-> data[i - 1] = p-> data[i];
    p-> numberOfKeys--;


    //delete the value from keys[]
    for(i = 0; i < totalNumberOfKeys; i++)
      if(stringKeys[i] == value)
	  {
        for(j = i; j < totalNumberOfKeys; j++)
        stringKeys[j] = stringKeys[j + 1];
	  }
    totalNumberOfKeys--;
  }


  while(p-> isLeaf)
  {

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if( p == root )
	{

      if(p-> numberOfKeys > 0)
        return;
      else
	  {

        root = p-> data[0].left;
        return;
      }
    }


    q = p-> parent;

    if(q-> data[0].left == p || q-> data[0].right == p)
	{

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }else
	{


      for( i = 0; i < q-> numberOfKeys; i++)
        if(q-> data[i].left == p || q-> data[i].right == p)
          break;

      left = q-> data[i].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }

    if(right-> numberOfKeys > mkeys / 2)
	{

      left-> data[left-> numberOfKeys].stringKey = center-> stringKey;
      left-> numberOfKeys++;
      center-> stringKey = right-> data[0].stringKey;

      for(i = 1; i < right-> numberOfKeys; i++)
        right-> data[i - 1] = right-> data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else
	{

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

  while( !q-> isLeaf)
  {

    for( i = 0; i < q-> numberOfKeys; i++)
	{

      if(q-> data[i].stringKey == value)
	  {

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

  while( !p-> isLeaf)
  {

    if(p-> numberOfKeys >= mkeys / 2 )
      return;

    if(p == root )
	{

      if(p-> numberOfKeys > 0)
        return;
      else
	  {

        root = p-> first;
        return;
      }
    }

    q = p-> parent;
    if(q-> data[0].left == p || q-> data[0].right == p)
	{

      left = q-> data[0].left;
      right = q-> data[0].right;
      center =& (q-> data[0]);
      middleIndex = 0;

    }
	else
	{

      for( i = 1; i < q-> numberOfKeys; i++)
        if(q-> data[i].right == p)
          break;

      left = q-> data[i - 1].left;
      right = q-> data[i].right;
      center =& (q-> data[i]);
      middleIndex = i;
    }


    //left has an extra key
    if(left-> numberOfKeys > mkeys / 2)
	{

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

    if(right-> numberOfKeys > mkeys / 2)
	{

      left-> data[left-> numberOfKeys].stringKey = center-> stringKey;
      left-> numberOfKeys++;
      center-> stringKey = right-> data[0].stringKey;

      for(i = 1; i < right-> numberOfKeys; i++)
        right-> data[i - 1] = right-> data[i];

      right-> numberOfKeys--;
      return;
    }

    //merge left and right
    else
	{

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


};
