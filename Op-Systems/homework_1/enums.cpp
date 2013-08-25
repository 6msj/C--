#include <iostream>
using namespace std;

int main()
{
   enum ingredient {paper = 1, match, tobacco} table;

   table  = paper;

   if (table == paper)
       cout << "Paper is on the table";
   if (table == match)
       cout << "A match is on the table";
   if (table == tobacco)
       cout << "Tobacco is on the table";

 return 0;

}

