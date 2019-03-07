#include <iostream>
#include <string>
#include <fstream>
 
using namespace std;
 
class customers
{
  public:
    customers(); // constructor
    string FirstName, LastName, number;
};
 
struct nodeType
{
  customers info;
  nodeType* next;
};
 
class sortedListType
{
  public:
    nodeType* firstptr;
    sortedListType(); // constructor
    void InsertInOrder(customers);
    void printList();
    ~sortedListType(); // destructor
};
 
customers::customers()
{
  FirstName = "";
  LastName = "";
  number = "";
}
 
sortedListType::sortedListType()
{
  firstptr = NULL;
}
 
void sortedListType::InsertInOrder(customers customer)
{
  nodeType* tmpNode = new nodeType;
  tmpNode->info = customer;
  tmpNode->next = NULL;
 
  if (!firstptr)
  {
    firstptr = tmpNode;
  }
  else if (tmpNode->info.LastName < firstptr->info.LastName)
  {
    tmpNode->next = firstptr;
    firstptr = tmpNode;
  }
  else{
    nodeType* current = firstptr->next;
    nodeType* prev = firstptr;
    bool cursor = false;
    while (current)
    {
      if(tmpNode->info.LastName < current->info.LastName)
      {
        tmpNode->next = current;
        prev->next = tmpNode;
        cursor = true;
        break;
      }
      prev = current;
      current = current->next;
    }
 
    if(!cursor)
    {
      prev->next = tmpNode;
      tmpNode->next = NULL;
    }
  }
}
 
/*
If I put the list in order first and then separate that sorted into
two different customer lists and print those then merge the two sorted lists
that should technically make things easier
*/
 
void sortedListType::printList()
{
  nodeType* customer = firstptr;
 
  while(customer)
  {
    cout << "          " << customer->info.FirstName<< "          " << customer->info.LastName<< "          " << customer->info.number << endl;
    customer = customer->next;
  }
}
 
sortedListType::~sortedListType()
{
  nodeType* temp;
 
  while(firstptr)
  {
    temp = firstptr->next;
    delete firstptr;
    firstptr = temp;
  }
}
 
int main()
{
  sortedListType customer1, customer2, final;
  customers temp;
  ifstream myfile;
  myfile.open("infile.txt");
 
  // loop to insert the first 7 entries of infile.txt for customer 1
  for (int i = 0; i < 7; i++)
  {
    myfile >> temp.FirstName >> temp.LastName >> temp.number;
    customer1.InsertInOrder(temp);
  }
 
  // loop for the next batch of 7 entries for customer 2
  for (int i = 0; i < 7; i++)
  {
    myfile >> temp.FirstName >> temp.LastName >> temp.number;
    customer2.InsertInOrder(temp);
  }
  nodeType* current1 = customer1.firstptr;
  nodeType* current2 = customer2.firstptr;
 
  while (current1 || current2)
  {
    if (current1->info.LastName < current2->info.LastName)
    {
      final.InsertInOrder(current1->info);
      current1 = current1->next;
    }
    else
    {
      final.InsertInOrder(current2->info);
      current2 = current2->next;
    }
    if (current1)
    {
      final.InsertInOrder(current1->info);
      current1 = current1->next;
    }
    if (current2)
    {
      final.InsertInOrder(current2->info);
      current2 = current2->next;
    }
  }
 
  cout << "\t\t" << "Customer 1 Phone Book" << endl;
  customer1.printList();
  cout << endl;
  cout << "\t\t" << "Customer 2 Phone Book" << endl;
  customer2.printList();
  cout << endl;
  cout << "\t\t" << "Final Phone Book" << endl;
  final.printList();
 
  return 0;
}
 
/*
               PROGRAM OUTPUT
  Customer 1 Phone Book
          Adegboyega          Akinsiku          (202)234-5678
          Jonnetta          Bratcher          (345)444-6738
          Dhuel          Fisher          (410)878-5503
          Remington          Holt          (310)567-2349
          Kendall          Keeling          (202)694-0090
          Joanna          Phillip          (304)550-1236
          Ranjay          Salmon          (410)555-6666
 
                Customer 2 Phone Book
          Charles          Brown          (201)223-0021
          Kerisha          Burke          (310)445-2939
          Allee          Clark          (410)778-3848
          Brionna          Huskey          (921)858-2348
          Brittany          Jackson          (410)120-4502
          Kourtnei          Langley          (202)880-6729
          Michael          Phillips          (404)567-2345
 
                Final Phone Book
          Adegboyega          Akinsiku          (202)234-5678
          Jonnetta          Bratcher          (345)444-6738
          Charles          Brown          (201)223-0021
          Kerisha          Burke          (310)445-2939
          Allee          Clark          (410)778-3848
          Dhuel          Fisher          (410)878-5503
          Remington          Holt          (310)567-2349
          Brionna          Huskey          (921)858-2348
          Brittany          Jackson          (410)120-4502
          Kendall          Keeling          (202)694-0090
          Kourtnei          Langley          (202)880-6729
          Joanna          Phillip          (304)550-1236
          Michael          Phillips          (404)567-2345
          Ranjay          Salmon          (410)555-6666
*/
