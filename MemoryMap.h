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
    Node();
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

public:
  void merge();
  void allocate(int base_address, int size);
  void deallocate(int base_address,int size);
  int get_table_size();
  void print_table();
  Node search(int BAddr);
  int  get_available_size(int s);
  int  search_first_fit(int s);
  int  search_worst_fit(int s);
  int  search_best_fit(int s);
  friend class Memory;

};

class ProcessesTable
{
  list<Node> table;
  public:
  void allocate(string n, int BAddr, int size);
  void deallocate(int BAddr);
  void print_table();
  bool search_base_address(int BAddr);
  Node search_base_address_2(int BAddr);
  int  get_table_size();
  friend class Memory;



};
class Memory
{
  Node *memory=new Node[10];
  public:
 void update_memory(HoleTable h1, ProcessesTable t1);
 void print_memory_by_name();
 void print_memory_in_detail();

};  //Under construction :)

int table_sync_add_process(HoleTable &h1, ProcessesTable &t1, Node &n);
void table_sync_delete_process(HoleTable &h1, ProcessesTable &t1, Node n);
void table_sync_delete_process(HoleTable &h1, ProcessesTable &t1, int BAddr);
void initial_Processes_table_filling(HoleTable h1, ProcessesTable &t1, int memory_size);
void holes_initialize(HoleTable &h1);
void input_processes(list<Node> &list_processes);
void process_processes(list<Node> &list_processes, HoleTable &h1, ProcessesTable &t1);
void tables_handler(list<Node> &list_processes, HoleTable &h1, ProcessesTable &t1, Memory &memory);
#endif // MEMORYMAP_INCLUDED
