#ifndef MEMORYMAP_INCLUDED
#define MEMORYMAP_INCLUDED
#include <list>
#include <string>

using namespace std;
class Node
{
    std::string name;
    int base_address;
    int size;
    int final_address;
    public:
    Node(std::string n, int BAddr, int s);
    Node(int BAddr, int s);
    Node(string n,int s);
    std::string get_name();
    int get_base_address();
    int get_size();
    int get_final_address();
    void set_base_address(int BAddr);
    void set_final_address(int f);
    void update_size();
    void set_name(std::string n);
};

class HoleTable
{
  list<Node> table;
  void sort();
  void merge();
public:
  void allocate(int base_address, int size);
  void deallocate(int base_address,int size);
  int get_table_size();
  void print_table();
  Node search(int BAddr);
  int  search_by_size(int s);

};

class ProcessesTable
{
  list<Node> table;
  public:
  void allocate(string n, int BAddr, int size);
  void deallocate(int BAddr);
  void print_table();
  bool search_base_address(int BAddr);


};
class Memory{};  //Under construction :)

void table_sync_add_process(HoleTable &h1, ProcessesTable &t1, Node &n);
void table_sync_delete_process(HoleTable &h1, ProcessesTable &t1, Node n);
void initial_Processes_table_filling(HoleTable h1, ProcessesTable &t1, int memory_size);

#endif // MEMORYMAP_INCLUDED
