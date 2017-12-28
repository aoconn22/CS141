/* prog5Boggle.cpp

    Running this program looks like:
        Program: #5, Boggle
        TA: Grace Hopper, Tues 5-6
        Nov 5, 2017

        Welcome to the game of Boggle, where you play against the clock
        to see how many words you can find using adjacent letters on the
        board.  Each letter can be used only once for a given word.
 
 
        The dictionary total number of words is: 263533
        Number of words of the right length is:  259709

        Some random characters are: a c r l n e a p p u

        Do word lookups for 10 seconds.

        Enter a word: fish
        fish is in the dictionary.
        There are 3 seconds left.

        Enter a word: cat
        cat is in the dictionary.
        There are 3 seconds left.

        Enter a word: dog
        dog is in the dictionary.
        There are 1 seconds left.

        Enter a word: entropy
        entropy is in the dictionary.
        There are -3 seconds left.
        I let you finish your last move. Time is up!
 
*/
#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // Allows using the tolower() function
#include <ctime>      // Timer functions
#include <cstring>    // For strlen
using namespace std;

// Global constants
const char DictionaryFileName[] = "dictionary.txt";
const int MaxNumberOfWords = 263533; // Number of dictionary words
const int MinWordLength = 3;         // Minimum dictionary word size to be stored
const int MaxWordLength = 16;	     // Max word size.  Add 1 for null
const int MaxUserInputLength = 81;   // Max user input length
const int NumberOfLetters = 26;      // Letters in the alphabet
const int TotalSecondsToPlay = 60;   // Total number of seconds to play per board
const int boardSize = 36;            // Size of the 4x4 board array


//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    printf("\n");
    printf("Author: Andrew O'Connell          \n");
    printf("Program: #5, Boggle        \n");
    printf("TA: Grace Hopper, Tues 5-6  \n");
    printf("Nov 20, 2017                \n");
    printf("\n");
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------
// Display instructions
void displayInstructions()
{
    printf("Welcome to the game of Boggle, where you play against the clock   \n");
    printf("to see how many words you can find using adjacent letters on the  \n");
    printf("board.  Each letter can be used only once for a given word.       \n");
    printf("  \n");
    printf("When prompted to provide input you may also:                      \n");
    printf("     Enter 'r' to reset the board to user-defined values.         \n");
    printf("     Enter 's' to solve the board and display all possible words. \n");
    printf("     Enter 't' to toggle the timer on/off.                        \n");
    printf("     Enter 'x' to exit the program.                               \n");
    printf("  \n");
}//end displayInstructions()


//---------------------------------------------------------------------------
// Read in dictionary
//    First dynamically allocate space for the dictionary.  Then read in words
// from file.  Note that the '&' is needed so that the new array address is
// passed back as a reference parameter.
void readInDictionary(
          char ** &dictionary,                      // dictionary words
          long int &numberOfWords)                  // number of words stored
{
    // Allocate space for large array of C-style strings
    dictionary = new char*[ MaxNumberOfWords];
    
    // For each array entry, allocate space for the word (C-string) to be stored there
    for (int i=0; i < MaxNumberOfWords; i++) {
        dictionary[i] = new char[ MaxWordLength+1];
        // just to be safe, initialize C-strings to all null characters
        for (int j=0; j < MaxWordLength; j++) {
            dictionary[i][j] = '\0';
        }//end for (int j=0...
    }//end for (int i...
    
    // Now read in the words from the file
    ifstream inStream;                 // declare an input stream for my use
    numberOfWords = 0;                   // Row for the current word
    inStream.open( DictionaryFileName);
    assert( ! inStream.fail() );       // make sure file open was OK
    
    // Keep repeating while input from the file yields a word
    char theWord[ 81];    // declare input space to be clearly larger than largest word
    while( inStream >> theWord) {
        int wordLength = (int)strlen( theWord);
        if( wordLength >= MinWordLength && wordLength <= MaxWordLength) {
            strcpy( dictionary[ numberOfWords], theWord);
            // increment number of words
            numberOfWords++;
        }
    }//end while( inStream...
    
    cout << "The dictionary total number of words is: " << MaxNumberOfWords << endl;
    cout << "Number of words of the right length is:  " << numberOfWords << endl;
    
    // close the file
    inStream.close();
}//end readInDictionary()


//--------------------------------------------------------------------------------------
// Use binary search to look up the search word in the dictionary array, returning index
// if found, -1 otherwise
int binarySearch( const char searchWord[ MaxWordLength+1], // word to be looked up
                  char **dictionary)               // the dictionary of words
{
    int low, mid, high;     // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = MaxNumberOfWords - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // searchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = strcmp( searchWord, dictionary[ mid]);
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located prior to mid location
        }
        else  {
            low = mid + 1; // word should be located after mid location
        }
    }
    
    // Word was not found
    return -1;
}//end binarySearch()


//---------------------------------------------------------------------------
// Get random character
//    Find random character using a table of letter frequency counts.
// Iterate through the array and find the first position where the random number is
// less than the value stored.  The resulting index position corresponds to the
// letter to be generated (0='a', 1='b', etc.)
char getRandomCharacter()
{
    
    // The following table of values came from the frequency distribution of letters in the dictionary
    float letterPercentTotals[ NumberOfLetters] = {
                0.07680,  //  a
                0.09485,  //  b
                0.13527,  //  c
                0.16824,  //  d
                0.28129,  //  e
                0.29299,  //  f
                0.32033,  //  g
                0.34499,  //  h
                0.43625,  //  i
                0.43783,  //  j
                0.44627,  //  k
                0.49865,  //  l
                0.52743,  //  m
                0.59567,  //  n
                0.66222,  //  o
                0.69246,  //  p
                0.69246,  //  q
                0.76380,  //  r
                0.86042,  //  s
                0.92666,  //  t
                0.95963,  //  u
                0.96892,  //  v
                0.97616,  //  w
                0.97892,  //  x
                0.99510,  //  y
                1.00000}; //  z
    
    // generate a random number between 0..1
    // Multiply by 1.0 otherwise integer division truncates remainders
    float randomNumber = 1.0 * rand() / RAND_MAX;
    
    // Find the first position where our random number is less than the
    // value stored.  The index corresponds to the letter to be returned,
    // where 'a' is 0, 'b' is 1, and so on.
    for( int i=0; i<NumberOfLetters; i++) {
        if( randomNumber < letterPercentTotals[ i]) {
            // we found the spot.  Return the corresponding letter
            return (char) 'a' + i;
        }
    }
    
    // Sanity check
    cout << "No alphabetic character generated.  This should not have happened. Exiting program.\n";
    exit( -1);
    return ' ';   // should never get this
}//end getRandomCharacter

//---------------------------------------------------------------------------
void displayBoard( char boardArray[ boardSize])
{
    // keep track of the row number
    int rowNumber;
    
    // fill the inner 4x4 board with random characters
    for ( rowNumber=1; rowNumber<5; rowNumber++) {
        // use row number to allow for looping through i= 7-10, 13-16, 19-22 etc. 
        for ( int i=((6*rowNumber)+1); i<((6*rowNumber)+5); i++) {
            cout << boardArray[i] << " ";
        }
        cout << endl;
    }

    return;
}//end displayBoard

//---------------------------------------------------------------------------
void resetBoard( char boardArray[ boardSize], int &count)
{
    char c;  // stores a single board input character, to be handled one at a time
    int rowNumber; // keep track of row number
    
    cout << "You have chosen to reset the board.    " << endl
         << "Enter 16 characters for the new board: " << endl;
    // fill the inner 4x4 board with selected characters
    for ( rowNumber=1; rowNumber<5; rowNumber++) {
        // use row number to allow for looping through i= 7-10, 13-16, 19-22 etc. 
        for ( int i=((6*rowNumber)+1); i<((6*rowNumber)+5); i++) {
            cin >> c;
            boardArray[ i] = c;
        }
    }
    count = 1;
    return;
}//end resetBoard 


//---------------------------------------------------------------------------
char generateBoard( char boardArray[ boardSize])
{
    // keep track of the row number
    int rowNumber;
    
    // fill the board with asterisks for searching purposes
    for ( int i=0; i<boardSize; i++) {
       boardArray[i] = '*';
    }
    // fill the inner 4x4 board with random characters
    for ( rowNumber=1; rowNumber<5; rowNumber++) {
        // use row number to allow for looping through i= 7-10, 13-16, 19-22 etc. 
        for ( int i=((6*rowNumber)+1); i<((6*rowNumber)+5); i++) {
            boardArray[i] = getRandomCharacter();
        }
    }
    
}//end generateBoard

//---------------------------------------------------------------------------
void findLetter( char boardArray[ boardSize], char inputLetter[ MaxUserInputLength], char storeChar[MaxUserInputLength],
                       int currentBoardIndex, int indexOfLetterToFind, int storeCharIndex, int inputLength, bool &wordFound) //
{
    // array of search locations for adjacent characters beginning on the left, and moving clockwise
    int searchLocation[8] = {-1, -7, -6, -5, 1, 7, 6, 5}; 
    
    // save the letter found and replace it with ' ' so it isn't reused
    storeChar[ storeCharIndex] = boardArray[ currentBoardIndex];
    //cout << storeCharIndex << " ";
    boardArray[ currentBoardIndex] = ' ';
    
    // base case:
    // if the stored characters are equal to the user input, set wordFound
    // equal to true and end function to begin dictionary lookup
    if (strcmp(storeChar, inputLetter) == 0 && strlen(storeChar) == inputLength) {
        wordFound = true;
    }
    
    // new board index for the new search location
    int newBoardIndex;
    
    // loop through the searchLocation array to search all adjacent board positions   
    for( int i=0; i<8; i++) {
        newBoardIndex = (currentBoardIndex + searchLocation[i]);
        
        // check if the searched character is equal to the next user entered character
        // and that the word has not already been found
        if ( boardArray[newBoardIndex] == inputLetter[indexOfLetterToFind]
            && !wordFound) {
                
            // recursive call with the new board index, index of character to be searched,
            // and index to store found characters
            findLetter( boardArray, inputLetter, storeChar,
                              newBoardIndex, indexOfLetterToFind + 1, storeCharIndex + 1, inputLength, wordFound); 
        }// end if(boardArray...
    }// end for(int i...
    
    // restore the board with saved character if match not found
    boardArray[ currentBoardIndex] = storeChar[storeCharIndex];
    
    // decrement the array of stored characters by one each time 
    // the recursion steps back
    storeChar[storeCharIndex] = char ( 0 );
}//end findLetter

//---------------------------------------------------------------------------
int score(char wordToScore[MaxUserInputLength], int &score) 
{
    // point value int to allow for the point value of each word to be returned
    int pointValue;
    // check for words less than 3 letters long and award no points if so
    if (strlen(wordToScore) < 3) {
        score += 0;
        pointValue = 0;
        return pointValue;
    }
    // check for words 3 letters long and award 1 point if so
    else if (strlen(wordToScore) < 4) {
        score += 1;
        pointValue = 1;
        cout << "   Worth " << pointValue << " points." << endl;
    }
    // check for words 4 letters long and award 2 points if so
    else if (strlen(wordToScore) < 5) {
        score += 2;
        pointValue = 2;
        cout << "   Worth " << pointValue << " points." << endl;
    }
    // check for words 5 letters long and award 4 points if so
    else if (strlen(wordToScore) < 6) {
        score += 4;
        pointValue = 4;
        cout << "   Worth " << pointValue << " points." << endl;
    }
    // check for words 6 letters or longer and award 1 point per letter
    else{
        for( int i=6; i<=16; i++) {
            if ( i == strlen(wordToScore)) {
                score += strlen(wordToScore);
                pointValue = strlen(wordToScore);
                cout << "   Worth " << pointValue << " points." << endl;
            }
        }
    }
}//end score

//---------------------------------------------------------------------------
void findPossibleWords( char boardArray[ boardSize], char inputLetter[ MaxUserInputLength], char storeChar[MaxUserInputLength],
                         char **dictionary, int numberOfDictionaryWords)
{
    // min and max letter counts, and variable to track the current letter count of words being searched
    int min, max, letterCount;
    // index position in userInput for easier readability
    int indexOfLetterToFind = 1;                
    // store c so the board can be restored while searching  
    int storeCharIndex = 0;
    // starting board index to search when calling the recursive findLetter function
    int startingIndex;
    // boolean word found value to pass into the recursive function
    bool wordFound = false;
    // user input length for easier readability(rather than pass strlen(userInput) into the recursive function
    int userInputLength;
    // index in the dictionary array of the found word
    int wordIndex;
    // parallel array to the dictionary array to track which words have been found on the board that are also in the dictionary
    bool trackWordsFound[numberOfDictionaryWords];
    // set all elements in the array to false
    for (int i=0; i<numberOfDictionaryWords; i++) {
            trackWordsFound[i] = false;
    }
    
    // set the minimum and maximum word lengths to search for on the board
    cout << "Enter min and max word lengths to display: ";
    
    cin >> min >> max;
    
    // loop through every word in the dictionary between the min and max letter count
    // values and begin a recursive search of every location on the board for the selected
    // word in the dictionary
    for( int letterCount=min; letterCount<=max; letterCount++ ) {
        for( int i=0; i<numberOfDictionaryWords; i++) {
            // check that the word is the right length and set it equal to the user input value
            // which is passed into the recursive search function
            if ( strlen(dictionary[i]) == letterCount) {
                inputLetter = dictionary[i];
                userInputLength = strlen(inputLetter);
                // loop through every board position and recursively search for the current dictionary word           
                for( int j=0; j<36; j++) {
                    // set the starting index equal to the board position
                    startingIndex = j;
                    findLetter( boardArray, inputLetter, storeChar,
                              startingIndex, indexOfLetterToFind, storeCharIndex, userInputLength, wordFound);
                    // check if findLetter returns true and adjusts the words found array accordingly       
                    if ( wordFound == true) {
                        // set the word index equal to the index value returned by the binary search
                        wordIndex = binarySearch( inputLetter, dictionary);
                        // set the element at the returned index to true
                        trackWordsFound[wordIndex] = true;
                        // set word found equal to false so the next board position can be searched
                        wordFound = false;
                    }// end if( wordFound...)
                }// end for( int j...)
            }// end if(strlen...)
        }// end for( int i...)
    }//end for( int letterCount...)
      
    cout << "Words between " << min << " and " << max << " are:" << endl;
    // display all of the words found in order by word size and alphabetically
    for( letterCount=min; letterCount<=max; letterCount++ ) {
        for( int i=0; i<numberOfDictionaryWords; i++) {
            if ( trackWordsFound[i] == true && strlen(dictionary[i]) == letterCount) {
                cout << dictionary[i] << " ";
            }
        } 
    }
    cout << endl;
    
}//end findPossibleWords
   
//---------------------------------------------------------------------------
int main()
{
    // declare variables
    char **dictionary;                  // 2d array of dictionary words, dynamically allocated
    long int numberOfWords;             // how many words actually found in dictionary
    int wordIndex;                      // index in the dictionary of the searched word
    int letterCount;                    // letter count of the word being searched for
    
    char userInput[ MaxUserInputLength];// user input of word to search for
    char board[ boardSize];             // array of chars to make up the board
    char storeCharacter[MaxUserInputLength];    // store the user input so the board can be restored while searching
    
    int startingIndex;                  // index position on board to begin searching
    int theIndexOfLetterToFind = 1;     // index position in userInput for easier readability                
    int firstCharIndex = 0;             // index position to store found letters
    bool found = false;                 // boolean the is true if the word is found on the board
    
    int elapsedSeconds = 0;             // amount of time that has passed since the start of the game
    int totalScore = 0;                 // the total score to be displayed every turn
    int turnCount = 1;                  // the current turn number
    bool timerEnabled = true;           // boolean timer enabled to toggle the timer display
    
    srand(time(0));                     // seed for rand()
    
    
    
    // Declare a variable to hold a time, and get the current time
    time_t startTime = time( NULL);

    displayIdentifyingInformation();
    displayInstructions();
    
    // read in dictionary.  numberOfWords returns the actual number of words found
    readInDictionary( dictionary, numberOfWords);
    
    bool trackWordsFound[numberOfWords];// boolean array parallel to dictionary array to track found words
    
    // set each index in trackWordsFound[] to false
    for (int i=0; i<numberOfWords; i++) {
            trackWordsFound[i] = false;
    }
    
    // generate randomized board
    generateBoard( board);
    
    // game loop -- continue playing while either the timer is disabled or the
    // elapsed seconds are less than the total seconds allowed to play for
    while( timerEnabled == false || elapsedSeconds < TotalSecondsToPlay) {
        // calculate how many seconds have elapsed since we started the timer.
        elapsedSeconds = difftime( time( NULL), startTime);
        // check if the timer is enabled, and display the seconds remaining if true
        if (timerEnabled == true) {
            cout << "   " << TotalSecondsToPlay - elapsedSeconds << " seconds remaining" << endl;
        }
        // display the board
        displayBoard( board);
        // display the score
        cout << "   Score: " << totalScore << endl;
        // Prompt for and get user input
        cout << turnCount << ". Enter a word: ";
        cin >> userInput;
        for ( int i=0; i<strlen(userInput); i++) {
            userInput[i] = tolower( userInput[i]);
        }

        // check for user input 'r' to reset the board
        if ( *userInput == 'r' && strlen(userInput) == 1) {
            resetBoard( board, turnCount);
            continue;
        }
        // check for user input 's' to display all possible words on the board
        if ( *userInput == 's' && strlen(userInput) == 1) {
            findPossibleWords( board, userInput, storeCharacter, dictionary, numberOfWords);
            cout << "Exiting the program";
            return 0;
        }
        // check for user input 't' to toggle the time
        if ( *userInput == 't' && strlen(userInput) == 1) {
            timerEnabled = ! timerEnabled;
            cout << endl;
            continue;
        }
        // check for user input 'x' to exit the game
        if ( *userInput == 'x' && strlen(userInput) == 1) {
            cout << "Thanks for playing!" << endl;
            return 0;
        }
        
        // set inputValue equal to the first letter in the user input                                             
        char inputValue = userInput[0]; 
        // set the userInputLength equal to the length of the string in userInput
        int userInputLength = strlen(userInput);  
        // loop through the board positions for the first letter in userInput
        for( int i=0; i< 36; i++) {
            // if the character on the board is equal to the first letter in userInput,
            // then begin the recursive function findLetter the the index of the found letter
            if ( board[ i] == inputValue) {
                startingIndex = i;
                findLetter( board, userInput, storeCharacter,
                startingIndex, theIndexOfLetterToFind, firstCharIndex, userInputLength, found);
                
            }
               
        }
        // if found is true, then findLetter found the word on the board
        // so begin the dictionary search for the found word
        if ( found == true) {
            if( binarySearch( userInput, dictionary) != -1) {
                wordIndex = binarySearch( userInput, dictionary);
                // check if the word has already been found in previous turns
                if ( trackWordsFound[wordIndex] == true) {
                    cout << "Sorry, that word was already previously found." << endl;
                }
                // else set the word found equal to true and update the score
                else {
                    trackWordsFound[wordIndex] = true;
                    score(userInput, totalScore);
                }
                // list the words found so far
                cout << "Words so far are: ";
                // loop through the whole dictionary and print the found words alphabetically
                // beginning with three letter words and moving up through to 16 letter words
                for( letterCount=3; letterCount<=16; letterCount++ ) {
                    for( int i=0; i<numberOfWords; i++) {
                        if ( trackWordsFound[i] == true && strlen(dictionary[i]) == letterCount) {
                            cout << dictionary[i] << " ";
                        }
                    }
                }
                cout << endl;
            }
        }
        
        if( found == false && userInputLength != 1) {
            cout << " Cannot be formed on the board." << endl;
        }
        else if (binarySearch( userInput, dictionary) == -1 && userInputLength != 1){
                cout << " Was not found in the dictionary." << endl;
        }
        // incrememnt the turn count by 1
        turnCount++;
        
        cout << endl;
        elapsedSeconds = difftime( time( NULL), startTime);
    }// end while

    cout << "I let you finish your last move. Time is up!" << endl;
    
    return 0;   
}//end main()
