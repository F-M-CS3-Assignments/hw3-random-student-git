
#include <iostream>
#include <assert.h>

using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);

	try{
		// negative input
		long long unsigned int t_1 = TimeCode::ComponentsToSeconds(-3, 17, 42);
		//cout<<t_1<<endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}
	
	
	
	try{
		//roll over input
		long long unsigned int t_3 = TimeCode::ComponentsToSeconds(3, 60, 1);
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;

	//make sure intitial values when not defined are 0
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}

void TestReset(){
	cout << "Testing Reset" << endl;
	TimeCode tc;
	tc.reset();
	//make sure resetted values are 0
	assert(tc.ToString() == "0:0:0");
	cout << "PASSED!" << endl << endl;
}



void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	assert(tc.ToString() == "0:0:0");
	

	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	try {
        TimeCode tc3(3, -60, 42);
        assert(false); 
    } catch (const invalid_argument& e) {
        // just leave this empty
		// and keep doing more tests
    }
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	//roll over inputs
	TimeCode tc2(0, 60, 60);
    tc2.GetComponents(h, m, s);
    assert(h == 1 && m == 1 && s == 0);
	cout << "PASSED!" << endl << endl;
}


void TestSubtraction(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	//regular input
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	// what if big number is subtracted from small number? 
	//what if result is negative
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc9 = TimeCode(8, 5, 9);
	tc9.SetMinutes(15); // test valid change
	cout<<tc9.ToString()<<endl;
	assert(tc9.ToString() == "8:15:9");

	try
	{
		tc9.SetMinutes(80);  // test roll over input
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	try
	{
		tc9.SetMinutes(-8);  // test negative integer
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc9.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}

void TestSetSeconds()
{
	cout << "Testing SetSeconds" << endl;

	TimeCode tc6 = TimeCode(8, 5, 9);
	tc6.SetSeconds(15); // test valid change
	assert(tc6.ToString() == "8:5:15");

	try
	{
		tc6.SetSeconds(80);  //test roll over input
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	try
	{
		tc6.SetSeconds(-8);  // test neagtive integer
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc6.ToString() == "8:5:15");

	cout << "PASSED!" << endl << endl;
}

void TestSetHours()
{
	cout << "Testing TestSetHours" << endl;

	TimeCode tc7 = TimeCode(8, 5, 9);
	tc7.SetHours(1); // test valid change
	cout<<tc7.ToString()<<endl;
	assert(tc7.ToString() == "1:5:9");
	try
	{
		tc7.SetHours(-80); 
		assert(false); // test negative integer		
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc7.ToString() == "1:5:9");
	cout << "PASSED!" << endl << endl;
}

void TestAddition() {
    cout << "Testing Addition" << endl;
	//regular addition
    TimeCode tc1(1, 1, 1);
    TimeCode tc2(2, 2, 2);
    TimeCode tc3 = tc1 + tc2;
    assert(tc3.ToString() == "3:3:3");

    cout << "PASSED!" << endl << endl;
}


void TestMultiplication() {
    cout << "Testing Multiplication" << endl;
	// regular multiplying
    TimeCode tc(1, 1, 1);
    TimeCode tc2 = tc * 2;
    assert(tc2.ToString() == "2:2:2");
    TimeCode tc3 = tc * 0;
    assert(tc3.ToString() == "0:0:0");
	// multiplying by negative
    try {
        TimeCode tc4 = tc * -1;
        assert(false); 
    } 
	catch (const invalid_argument& e) {
        // just leave this empty
		// and keep doing more tests
    }

    cout << "PASSED!" << endl << endl;
}

void TestCompare() {
    cout << "Testing Comparison" << endl;
    TimeCode tc(1, 0, 0);
    TimeCode tc2(1, 0, 0);
	TimeCode tc3(2, 0, 0);
    TimeCode tc4(1, 0, 0);
	// regular comparisons
    assert(tc2.ToString() == tc.ToString());
	assert(tc2.ToString() >= tc.ToString());
	assert(tc2.ToString() <= tc.ToString());
	assert(tc3.ToString() >= tc.ToString());
	assert(tc3.ToString() > tc.ToString());
	assert(tc.ToString() <= tc3.ToString());
	assert(tc.ToString() < tc3.ToString());
    cout<<"PASSED!"<<endl;
}

void TestDivision() {
    cout << "Testing Division" << endl;
	// regular division
    TimeCode tc(4, 0, 0);
    TimeCode tc2 = tc / 4;
    assert(tc2.ToString() == "1:0:0");

    try {
		//divide by zero
        TimeCode tc3 = tc / 0;
        assert(false); 
    } 
	catch (const invalid_argument& e) {
		// just leave this empty
		// and keep doing more tests
        
    }

    try {
		//divide by negative integer
        TimeCode tc4 = tc / -1;
        assert(false); 
    } 
	catch (const invalid_argument& e) {
		// just leave this empty
		// and keep doing more tests
    }



	
}
int main(){
	TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestGetComponents();
    TestSubtraction();
    TestSetMinutes();
    TestSetSeconds();
    TestSetHours();
    TestAddition();
    TestMultiplication();
    TestDivision();
    cout << "PASSED ALL TESTS!!!" << endl;
    return 0;
	return 0;
}
