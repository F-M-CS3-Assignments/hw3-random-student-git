#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)
#include <unistd.h> // for sleep delay

// Learnt M_PI at http://stackoverflow.com/questions/1727881/ddg#1727896 
// learnt sleep at https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program


using namespace std;

struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
	int id;
};

TimeCode subtract_time_t(DryingSnapShot dss){
		try {
			return (*dss.timeToDry-TimeCode(0,0,(dss,time(0)-dss.startTime))); // subtract the total time required by how much time has passed
		}
		catch(...){
			return TimeCode(0,0,0); // i.e. exceeded time required
		}
}

double get_sphere_sa(double rad){
	return 4*M_PI*pow(rad,2);; // 4 pi r^2
}

void tests(){
	// standard subtraction of real time
	DryingSnapShot ds1;
	DryingSnapShot ds2;
	TimeCode tc1=TimeCode(1,0,0);
	ds1.timeToDry=&tc1;
	ds1.startTime=time(0);
	sleep(1);
	TimeCode checksubtract = subtract_time_t(ds1);
	//cout<<checksubtract.ToString()<<endl;
	assert(TimeCode(0,59,59)==checksubtract);
	cout<<"Passed standard subtract test!"<<endl;
	// making sure subtracting real time doesn't result in error of negative timecode
	TimeCode tc2=TimeCode(0,0,1);
	ds2.timeToDry=&tc2;
	ds2.startTime=time(0);
	sleep(2);
	TimeCode checksubtract1 = subtract_time_t(ds2);
	//cout<<checksubtract1.ToString()<<endl;
	assert(TimeCode(0,0,0)==checksubtract1);
	cout<<"Passed edge subtract test!"<<endl;

	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
    /* 
 
 
 	note: Since Valgrind is not available on Mac ARM 64 I used this random software called Address Sanitizer, 

	I did:  clang++ -fsanitize=address -g -o paint PaintDryTimer.cpp

	./paint             
	
	
	*/
	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	tests();
	vector<DryingSnapShot> batchtimes; // stores all dss, which contains staringtimes, ids and total time required
	DryingSnapShot dss;
	string choice; // user input for adding or viewing
	double radius;
	cout<<"Enter a radius:";
	while (radius<=0){ // prevent negative radii
		cout << "Radius must be greater than 0:";
		cin >> radius;
   }
	cin>>radius;
	TimeCode tc=TimeCode(0,0,static_cast<unsigned long long int>(get_sphere_sa(radius))); //convert area to TimeCode
	dss.startTime = time(0); //record starting time
	dss.timeToDry=&tc; // referencing tc (total time needed) TimeCode to neatly store in dss and therefore batchtimes
	dss.id=rand(); //random id yay
	cout<<"ID:"<<dss.id<<endl;; 
	batchtimes.push_back(dss); // all three elements have been recorded so we add it onto array
	cout<<"Time remaining:"<<tc.ToString()<<endl;
	while (batchtimes.size()>0){ // while there are still batches needed to dry
		cout<<"Enter 'add' to add a batch or 'view' to view current batches:"; // user interface
		cin>>choice;
		if (choice=="add" || choice == "ADD"){
			// add new batch, same procedure as earlier it's copy pasted code
			cout << "Input radius:"; 
		    cin >> radius;
		    while (radius<=0){
				cout << "Radius must be greater than 0:";
				cin >> radius;
		   }
		   TimeCode tc=TimeCode(0,0,static_cast<int>(get_sphere_sa(radius)));
		   dss.timeToDry=&tc;
		   dss.startTime = time(0);
		   cout<<"Time remaining:"<<tc.ToString()<<endl;
		   dss.id=rand();
		   batchtimes.push_back(dss);
		}

		else if (choice=="view" || choice == "VIEW"){ //to view existing batches times' and ids
			for (int i=0;i<batchtimes.size();i++){ //for every batch in the list
				if (subtract_time_t(dss) <= 0) { // if complete
					batchtimes.erase(batchtimes.begin() + i);  // remove batch because I mean...it's done
				} 
				else{}
				cout<<"ID:"<<batchtimes[i].id<<endl;; //print batch details otherwise
				cout<<"Time left to dry:"<<subtract_time_t(batchtimes[i]).ToString()<<endl; 
				//get value from reference of timeToDry and then we print it out!
				cout<<"(takes "<<batchtimes[i].timeToDry->ToString()<<" seconds in total to dry)"<<endl;
			}
			}
		else{} // else nothing, else ignore
	   

		}		
	
	for (int i = 0; i < batchtimes.size(); ++i) {
		delete[] batchtimes[i].timeToDry;  // deallocate to prevent memory leaks
	 } 
	cout << "All batches have been dried." << endl;
	
	return 0;
}





