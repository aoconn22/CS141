
 /* ------------------------------------------------ 
  * Guess it Program 
  *
  * Class: CS 141, Fall 2017.  Tues 2pm lab
  * System: C++ in Cloud 9
  * Author: Andrew O'Connell
  *
  * -------------------------------------------------
  */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

    // program header
    cout << "Program #1: Guess It" << endl;
    cout << "Author: Andrew O'Connell" << endl;
    cout << "Lab: Tues 2pm" << endl;
    cout << "Date: Sep 11, 2017" << endl;
    cout << "System:  C++ in Cloud 9" << endl << endl;

    int loopCounter;  // initializes counter variable
    char specialChar, randomChar; // initializes the special character and random character
    char userResponse; // initialize the character used to reveal the users secret character
    srand(time(0)); // seed for random number generator
    
    // if statement to set the special charcter
    if (rand() % 2 == 0) {
        specialChar = (rand() % 26) + 65;
    }
    else {
        specialChar = (rand() % 26) + 97;
    }

    // loop to iterate through the places 99-0 on the board
    for (loopCounter=99; loopCounter>=0; loopCounter--) {
        
        // if statement to decide if the random character is upper 
        // or lower case and to assign an ASCII value to it
        if (rand() % 2 == 0) {
            randomChar = (rand() % 26) + 65;
        }
        else {
            randomChar = (rand() % 26) + 97;
        }
        
        // placees a special or random character on each
        // place on the board above 10
        if ((loopCounter % 9 == 0) && (loopCounter >= 10)) {
            cout << loopCounter << ":" << specialChar << " ";
        }
        else if ((loopCounter % 9 != 0) && (loopCounter >= 10)) {
            cout << loopCounter << ":" << randomChar << " ";
        }
        // second if statement with extra spacing for single digit characters
        if ((loopCounter % 9 == 0) && (loopCounter <= 9)) {
            cout << " " << loopCounter << ":" << specialChar << " ";
        }
        else if ((loopCounter % 9 != 0) && (loopCounter <= 9)) {
            cout << " " << loopCounter << ":" << randomChar << " ";
        }
        
        // if statement to begin a new line every 10 characters
        if (loopCounter % 10 == 0) {
            cout << endl;
        }
    }
    
    cout << endl << endl;
    
    // closing text
    cout << "1. Choose any two-digit number in the table above (e.g. 73)." << endl;
    cout << "2. Subtract its two digits from itself (e.g. 73 - 7 - 3 = 63)" << endl;
    cout << "3. Find this new number (e.g. 63) and remember the letter next to it." << endl;
    cout << "4. Now press r and I'll read your mind..." << endl;
    cin >> userResponse;
    
    // initiates response after user input
    while (userResponse != 'r') {
        cout << "Please enter r" << endl;
        cin >> userResponse;
    }
    
    cout << endl << endl << "You selected the character: " << specialChar;
    
    return 0;
}