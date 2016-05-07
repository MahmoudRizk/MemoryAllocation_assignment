#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "MemoryMap.h"



using namespace std;

int algorithm_mode;

int main()
{

   cout<<"Enter the algorithm number:"<<endl;
   cout<<"                           1) first_fit"<<endl;
   cout<<"                           2) best_fit"<<endl;
   cout<<"                           3) worst_fit"<<endl;
   cin>>algorithm_mode;

    HoleTable h1;
    ProcessesTable t1;
    Memory memory;
    list<Node> list_processes;
    holes_initialize(h1);   //User Enter the holes (number of holes and the size of each one) all are handeled inside the function

/*
    //Hard coded test case for holes input, make it easy in Debuging

    h1.allocate(0,1);
    h1.allocate(2,1);
    h1.allocate(3,1);
    h1.allocate(5,1);
    h1.allocate(8,1);
    h1.allocate(9,1);
*/
   initial_Processes_table_filling(h1, t1, 10);  //Automated function for entering initial processes, the name of these process is Px
   memory.update_memory(h1,t1);                  //update the memory array
   memory.print_memory_in_detail();             //Print the memory array in detail(name,base_address, size, final_addess)
   input_processes(list_processes);             //User enter the processes which he wants to allocate
   tables_handler(list_processes,h1,t1,memory); //Handling algorithms after the user enters the processe,(for more details open the function)
   cout<<endl<<"***************"<<" FINAL MEMORY "<<"*************"<<endl;
   memory.update_memory(h1,t1);                 //final update for the memory array
   memory.print_memory_in_detail();             //Print the memory array in detail
   return 0;
}
