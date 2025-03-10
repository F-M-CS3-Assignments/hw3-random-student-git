#ifndef TIMECODE_H
#define TIMECODE_H

#include <iostream> 
#include <stdexcept>
#include <climits>

/*

I learnt how to throw here: https://www.geeksforgeeks.org/how-to-throw-an-exception-in-cpp/

I learnt how to intialize constructor here: https://www.geeksforgeeks.org/constructors-c/

I learnt digit to string conversion here https://www.geeksforgeeks.org/cpp-program-to-check-string-is-containing-only-digits/

I learnt how to convert seconds to time here: https://www.inchcalculator.com/seconds-to-time-calculator/

I learnt about UINT_MAX here: https://stackoverflow.com/questions/7152759/what-happens-when-i-assign-a-negative-value-to-an-unsigned-int

*/

using namespace std;

class TimeCode {
    public:
        TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0){
            //test for negative integers, 
            // numbers >= UINT_MAX  is the set of values of negative integers when assigned to unsigned integers
            if ((hr<0) || (hr>=UINT_MAX)){ 
                throw invalid_argument("Invalid argument. Please input an integer.");
            }
            if ((min<0) || (min>=UINT_MAX)){
                throw invalid_argument("Invalid argument. Please input an integer.");
            }
            if ((sec<0) || (sec>=ULLONG_MAX)){
                throw invalid_argument("Invalid argument. Please input an integer.");
            }
            t=(3600*hr)+(60*min)+sec; //calculate hours and minutes seconds and add them up
            
        }
        TimeCode(const TimeCode& tc);
        ~TimeCode(){};
        void SetHours(unsigned int hours){
            //test for negative integers
        if (((hours<0) || (hours>=UINT_MAX))){
            throw invalid_argument("Invalid argument. Please input an unsigned integer.");
        }
            unsigned int hr,min,sec;
            GetComponents(hr,min,sec); //getter function that converts t seconds into time (hour:minutes:seconds)
            t=ComponentsToSeconds(hours,min,sec); //assign new t by setting the hours with new value 'hours'
        }
        void SetMinutes(unsigned int minutes){
            unsigned int hr,min,sec;
            //CheckIfInvalid(minutes);
            if (((minutes<0) || (minutes>=UINT_MAX))){
                throw invalid_argument("Invalid argument. Please input an unsigned integer.");
            }
            if (minutes>=60){
                throw invalid_argument("Invalid minutes. Minutes cannot be above 59.");
                }
            
            GetComponents(hr,min,sec); //getter function that converts t seconds into time (hour/minutes/seconds)
            t=ComponentsToSeconds(hr,minutes,sec); //assign new t by setting minutes with new value 'minutes'
        
        }
        void SetSeconds(unsigned int seconds){
            unsigned int hr,min,sec;
            //CheckIfInvalid(seconds);
            if (((seconds<0) || (seconds>=4294967295))){
                throw invalid_argument("Invalid argument. Please input an unsigned integer.");
            }
            if (seconds>=60){
                throw invalid_argument("Invalid seconds. Seconds cannot be above 59.");
            }
            GetComponents(hr,min,sec); //getter function that converts t seconds into time (hour/minutes/seconds)
            t=ComponentsToSeconds(hr,min,seconds);  //assign new t, setting seconds with new value 'seconds'
        
        }

        void reset(){
            t=0; // resets the TimeCode by assigning t to be equal to 0 seconds
        }
       
       // these three getter functions use getter function GetComponents and return their respective component of time
        unsigned int GetHours() const{
            unsigned int hr,min,sec;
            GetComponents(hr,min,sec); 
            return hr; 
        }
        unsigned int GetMinutes() const{
            unsigned int hr,min,sec;
            GetComponents(hr,min,sec);
            return min;
        }
        unsigned int GetSeconds() const{
            unsigned int hr,min,sec;
            GetComponents(hr,min,sec);
            return sec;
        }

        long long unsigned int GetTimeCodeAsSeconds() const {return t;};

        /*void CheckIfInvalid(int number){
            for (char ch:to_string(number)){
                if (!(int(ch) >= 48 && int(ch) <= 57)) {
                    throw invalid_argument("Invalid argument. Please input an integer.");
                }
            }
        }*/
        
        
        void GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
            /* 
            This method is essentially just divide total seconds by 3600 to get hours,
            divide the remainder by 60 to get minutes, and the remainder of THAT is seconds
            */
            long long unsigned int total=t;
            hr=total/3600;
            total=total%3600;
            min=total/60; 
            sec=total%60;
        }
        static long long unsigned int ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
            if ((hr<0) || (hr>=UINT_MAX)||(min<0) || (min>=UINT_MAX) || (sec<0) || (sec>=UINT_MAX)){ // nothing should be < 0
                throw invalid_argument("Invalid argument. Please input an unsigned integer.");
            }
            //no roll overs here
            if (min>=60){
                throw invalid_argument("Invalid minutes. Minutes cannot be above 59.");
            }
            if (sec>=60){
                throw invalid_argument("Invalid seconds. Seconds cannot be above 59.");
            }
            // one hour is 3600 seconds, one minute is sixty seconds, so we multiply and add them up
            return ((hr*3600)+(min*60)+sec);
            }
        

        string ToString() const{
            // converts seconds to time using the same formula in GetComponents()
            //then converts each component to string and concatenates them into hour/minute/second form
            return to_string(t/3600)+":"+to_string(((t)%3600)/60)+":"+to_string((((t)%3600)%60));
        }

        TimeCode operator+(const TimeCode& other) const{
            // adds the t of both TimeCodes
            long long unsigned int total=t+other.t;
            //converts the sum to time, same formula as in GetComponents()
            unsigned int hr=total/3600;
            total=total%3600;
            unsigned int min=total/60;
            unsigned int sec=total%60;
            //returns the sum as new TimeCode
            return TimeCode(hr,min,sec);
        }
        TimeCode operator-(const TimeCode& other) const{
            // subtracts the t of both TimeCodes
            long long unsigned int total=t-other.t;
            if (t<other.t){
                throw invalid_argument("Fatal. Resultant TimeCode is negative.");
            }
            //converts the difference to time, same formula as in GetComponents()
            unsigned int hr=total/3600;
            total=total%3600;
            unsigned int min=total/60;
            unsigned int sec=total%60;
            //returns the difference as new TimeCode
            return TimeCode(hr,min,sec);
        }
        TimeCode operator*(double a) const{
            if (a<0){
                throw invalid_argument("Negative arguments not allowed.");
            }
            //converts t to double to multiply with a
            double prod=static_cast<double>(t)*a;
            //converts product, stores product into a long long unsigned product in seconds for conversion
            long long unsigned int new_t=static_cast<long long unsigned int>(prod);
            //converts the product to time, same formula as in GetComponents()
            unsigned int hr=new_t/3600;
            new_t=new_t%3600;
            unsigned int min=new_t/60;
            unsigned int sec=new_t%60; 
            //returns the product as new TimeCode
            return TimeCode(hr, min, sec);
        }
        TimeCode operator/(double a) const{
            if (a==0.0){
                throw invalid_argument("Can not divide by zero.");
            }
            if (a<0){
                throw invalid_argument("Negative arguments not allowed.");
            }
            //converts t to double to divide by a
            double quot=static_cast<double>(t)/a;
            if (quot<0){ //I don't think this is possible but just in case
                throw invalid_argument("Fatal. Resultant TimeCode is negative");
            }
            //converts quotient, stores quotient into a long long unsigned quotient in seconds for conversion
            long long unsigned int new_t=static_cast<long long unsigned int>(quot);
            //converts the quotient to time, same formula as in GetComponents()
            unsigned int hr=new_t/3600;
            new_t=new_t%3600;
            unsigned int min=new_t/60;
            unsigned int sec=(new_t%60); 
            //returns the quotient as new TimeCode
            return TimeCode(hr, min, sec);
        }

        
        //The following comparison operators just compare the t of both TimeCodes and return true or false depending
        //on the expression and values of t for both TimeCodes
        
        

        bool operator == (const TimeCode& other) const{
            return t==other.t;
        }
        bool operator != (const TimeCode& other) const{
            return t!=other.t;
        }

        bool operator < (const TimeCode& other) const{
            return t<other.t;
        }
        bool operator <= (const TimeCode& other) const{
            return t<=other.t;
        }

        bool operator > (const TimeCode& other) const{
            return t>other.t;
        }
        bool operator >= (const TimeCode& other) const{
            return t>=other.t;
        }

private:
    long long unsigned int t = 0;
};

#endif