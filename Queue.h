#ifndef QUEUE_H
#define QUEUE_H
#pragma once

#include "node.h"
//Go through tree nodes

/**
* A queue class that stores nodes
*/
class Queue
{
  node *data[100]; //

  int Tail,
      Head;


    public:

        /**
        *   Default Queue class constructor initializes the head and tail position to 0.
        */
      Queue(){ //default constructor

        Tail = 0;
        Head = 0;

      }

        /**
        *   checks if the Queue is empty. 1 True
        */
      int empty(){

        if(Tail == Head){

            return 1;

        }else{

            return 0;
        }
      }

    /**
    *   Returns a pointer to the head of the data array which contains nodes
    *   @return node A pointer to the head of the data array which contains nodes
    */
      node *deque(){

        return data[Head++];
      }

      void enque(node *value){

        data[Tail++] = value;
      }

        /**
        * Sets the head and tail to position 0
        */
      void makeEmpty(){

        Tail = 0;
        Head = 0;
      }
}; //END QUEUE CLASS

#endif //QUEUE_H
