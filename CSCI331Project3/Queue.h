#include "node.h"
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

