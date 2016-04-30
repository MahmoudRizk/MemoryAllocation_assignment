#include "MemoryMap.h"
#include <list>
#include <string>
#include <iostream>


Node::Node(string n, int BAddr, int s)
{
   /*USED for NODE of type PROCESS*/
   name=n;
   base_address=BAddr;
   size=s;
   final_address=base_address+size;
}
Node::Node(int BAddr, int s)
{
    /*USED for NODE of type HOLE*/
    name="HOLE";
    base_address=BAddr;
    size=s;
    final_address=base_address+size;
}
string Node::get_name()
{return name;}
int Node::get_base_address()
{return base_address;}
int Node::get_size()
{return size;}
int Node::get_final_address()
{return final_address;}

void Node::set_base_address(int BAddr)
{base_address=BAddr;}
void Node::set_final_address(int f)
{final_address=f;}
void Node::update_size()
{size=final_address-base_address;}
 void Node::set_name(string n)
{name=n;}
//////////////////////////////////////////////////////////////
/*************************************************************/
//////////////////////////////////////////////////////////////

void HoleTable::sort()
{
    list<Node>::iterator i,j,n;
    i=table.begin();
    j=++table.begin();
    n=table.begin();
    Node *temp=new Node(0,0);
    while(n!=table.end())
    {
        while(j!=table.end())
        {
            if(i->get_base_address()>j->get_base_address())
            {
                *temp=*i;
                *i=*j;
                *j=*temp;
            }
           i++;
           j++;
        }
        i=table.begin();
        j=++table.begin();
        n++;
    }
}//sort according to base_address

void HoleTable::merge()
{
   list<Node>::iterator i_merge, j_merge;
   i_merge=table.begin();
   j_merge=++table.begin();
   for(j_merge;j_merge!=(++table.end());j_merge++)
   {
       if(i_merge->get_final_address()==j_merge->get_base_address())
       {
            i_merge->set_final_address(j_merge->get_final_address());
            i_merge->update_size();
            table.erase(j_merge);
            j_merge--;
       }
   }
}//merge two consecutive holes together

void HoleTable::allocate(int base_address, int size)
{
   Node*n=new Node(base_address,size);
   table.push_back(*n);
   sort();
   merge();

} //allocate new hole

void HoleTable::deallocate(int base_address,int size)
{
  list<Node>::iterator i;

   /*Pointing on the desired base_address*/
   for(i=table.begin();i!=table.end();i++)
   {
     if(i->get_base_address()==base_address) break;
   }

   i->set_base_address(base_address+size); /*Setting the new base address after process allocation*/
   i->update_size();            /*updating the hole block new size*/
   if(i->get_size()==0) table.erase(i); /*if size is zero, will be removed from the table*/

} //deallocate part of (or) all the hole for new process

int HoleTable::get_table_size()
{
   return table.size();
}
void HoleTable::print_table()
{
   list<Node>::iterator i;
   for(i=table.begin();i!=table.end();i++)
   {
      cout<<"Process Name:"<<i->get_name()<<endl;
      cout<<"Process begining address:"<<i->get_base_address()<<endl;
      cout<<"Process size:"<<i->get_size()<<endl;
      cout<<"Process end address:"<<i->get_final_address()<<endl;
      cout<<endl;
   }
}
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
void ProcessesTable::allocate(string n, int BAddr, int size)
{
  Node*n1 =new Node(n,BAddr,size);
  table.push_back(*n1);
}//allocate new process
void ProcessesTable::deallocate(int BAddr)
{
   list<Node>::iterator i;
   /*
     search for the base_address and let the iterator i points to the target
   */
    for(i=table.begin();i!=table.end();i++)
    {
      if(i->get_base_address()==BAddr) break;
    }
    table.erase(i);
} //delete the process from the table;
void ProcessesTable::print_table()
{
  list<Node>::iterator i;
  for(i=table.begin();i!=table.end();i++)
  {
     cout<<"Process Name:"<<i->get_name()<<endl;
     cout<<"Process begining address:"<<i->get_base_address()<<endl;
     cout<<"Process size:"<<i->get_size()<<endl;
     cout<<"Process end address:"<<i->get_final_address()<<endl;
     cout<<endl;
  }
}
