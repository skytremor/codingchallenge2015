#include <iostream>   //Used for obvious reasons
#include <string>    //Used for manipulating strings
#include <cmath>    //Used for absolute value function.
#include <regex>   //Used for sanitizing input

using namespace std; //Used for obvious reasons, this a simple program, no real ambiguity.

string int_to_word(int n)
{
    string result     = "";                 //Initialization for the variable in which the result will be stored
    string nstring    = to_string(abs(n)); //Variable that stores the positive string representation of number.
    int nstringlen    = nstring.length(); //Variable that stores the length of the number (in this case, string format)

    if (n <  0) {   result += "minus "; n = abs(n);    } //Check if input is negative, if so, add minus word to string and make num positive.

    const string ones[] = //String array for teens (2 digit numbers) and kids (1 digit numbers).
    {
    "",        "one",     "two",       "three",    "four",
    "five",    "six",     "seven",     "eight",    "nine",
    "ten",     "eleven",  "twelve",    "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    const string tens[] = //String array for double digits that are multiples of 10.
    {
    "",        "twenty",    "thirty",   "fourty",   "fifty",   
    "sixty",   "seventy",   "eighty",   "ninety"
    };
    
    const string powers[] = //String array for powers.
    {
    "", "hundred", "thousand", "million"
    };

    //Processing begins here, in all cases, it goes through each character(s) of string and fetches match in the string array.
    if (n < 20)
    {
        result += ones[n];
    }else 
    if (nstringlen < 3) //Less than 3 digits (10's)
    {
        result += tens[(nstring[0]) - '0'-1] + " " + ones[(nstring[1]) - '0']; 
    }else
    if (nstringlen < 4) //Less than 4 digits (100's)
    {
        result += ones[(nstring[0]) - '0'] + " " + powers[1] + " " + int_to_word(stoi(nstring.substr(1,2))); //mmm some tasty recursion
    }else
    if (nstringlen < 5) //Less than 5 digits (1000's)
    {
        result += ones[(nstring[0]) - '0'] + " " + powers[2] + " " + int_to_word(stoi(nstring.substr(1,3))); //mmm some more tasty recursion!
    }else
    if (nstringlen < 6) //Less than 6 digits (10k's)
    {
        result += int_to_word(stoi(nstring.substr(0,2))) + " " + powers[2] + " " + int_to_word(stoi(nstring.substr(2,5))); //Newsflash, it's not gonna stop with recursion.
    }else
    if (nstringlen < 7) //Less than 7 digits (100k's)
    {
        result += int_to_word(stoi(nstring.substr(0,3))) + " " + powers[2] + " " + int_to_word(stoi(nstring.substr(3,6))); //Okay...
    }else
    if (nstringlen < 8) //Less than 8 digits (1m's)
    {
        result += ones[(nstring[0]) - '0'] + " " + powers[3] + " " + int_to_word(stoi(nstring.substr(1,7))); //A little bit less recursion
    }else
    if (nstringlen < 9) //Less than 9 digits (10m's)
    {
        result += int_to_word(stoi(nstring.substr(0,2))) + " " + powers[3] + " " + int_to_word(stoi(nstring.substr(2,8))); //More recursion again!
    }else
    if (nstringlen < 10) //Less than 10 digits (100m's)
    {
        result += int_to_word(stoi(nstring.substr(0,3))) + " " + powers[3] + " " + int_to_word(stoi(nstring.substr(3,8))); //Done with recursion!
    }else{ //Over 100m's
        result += "\nI'm afraid you have exceeded the programs capacity.";
    }

    return result;
}

int main() 
{
    string num = ""; //Variable Initialization
    cout << "Welcome to the interger to word converter!" << endl; 
    label: cout << "Please enter a number ranging from -999,999,999 to 999,999,999 : " << endl;
    getline(cin, num); //Input Capture
    if (regex_match(num, regex("\\-?[0-9]{1,9}"))) //You need some regex to filter out the dirty input.
    {
        if (num != "0" && num != "-0"){ cout << int_to_word(stoi(num)) << endl; }else{ cout << "zero" << endl;}
    }else{
        cout << "Make sure you input a number lower in the specified range." << endl;
        goto label; //Jumping around the code. Some clever stuff I learnt in Theory of Computation Class (little late, I know).
    }

    return 0;
}
