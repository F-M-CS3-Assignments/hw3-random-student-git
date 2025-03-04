#include <iostream>
#include <fstream>
#include "TimeCode.h"
#include <vector>
using namespace std;


// I've read the notes! :P

int main() {
   ifstream inFS;   // input file stream
   string eachline;     // get each line of file as string
   vector<TimeCode*> alltimes; // points to a vector containing TimeCodes to store for computing averages

   inFS.open("Space_Corrected.csv"); // open the CSV file

   if (!inFS.is_open()) { // if it can't open, print 'unable to open' (this block is copied from zybook)
      cout << "Could not open file" << endl;
      return 1;
   }


   inFS >> eachline; //get line of file as input 
   while (!inFS.fail()){ // as long as there is new lines
   int first=0; // this is for getting the first colon ":" only, as any secondary/tertiary colons etc. will not be about time display
      for (int i = 0; i < eachline.length(); ++i) { //for every character in line, 
        if (first==0 && int(eachline[i])==58){ // value of colon in ASCII is 58
            string hrs;
            hrs.push_back(eachline[i-2]); // the two characters before the colon represent the hours
            hrs.push_back(eachline[i-1]);

            string min;
            min.push_back(eachline[i+1]); // the two characters after the colon represent the minutes
            min.push_back(eachline[i+2]);
            
            try{ // if we can convert the characters into integers, then the line contains time, otherwise line doesn't contain time
            TimeCode* newtime=new TimeCode(stoi(hrs),stoi(min),0);
            alltimes.push_back(newtime); // add TimeCode to array
            }
            catch(...){} // ignore otherwise
            first=1; // prevent extra colons as the next ones won't be about time
        }
      }
        inFS >> eachline; // input the next line again
   }
   TimeCode sum=TimeCode(0,0,1); // base TimeCode which we will add all other TimeCodes onto
   for (int i = 0; i < alltimes.size(); ++i) {
      sum=sum+*alltimes[i];  // get the sum of the existing sum plus the new TimeCode that is pointed to
   }
   sum=sum/alltimes.size(); //divide by the number of TimeCodes
   cout << "Average time:" << sum.ToString() << endl;
   
   inFS.close(); //close file
   for (int i = 0; i < alltimes.size(); ++i) {
      delete[] alltimes[i];  // deallocate to prevent MEMORY LEAKS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   }
   return 0;
}