/* --------------------------------------------------------
 * Traffic.cpp
 *     Text-based version of the game RushHour, where the
 *     object is to move the vehicles such that the small
 *     car can exit the right of the board.
 *
 * Class: Program #2 for CS 141, Fall 2017.  
 * Lab: Teusday, 2:00
 * TA ???
 * System: C++ in Cloud9
 * Author: Andrew O'Connell
 */

#include <iostream>
#include <cstdlib>
#include <cctype>      // for toupper()
using namespace std;

// Global variables and constants
// Variables to store the board pieces
char  p1, p2, p3, p4, p5, p6,
      p7, p8, p9,p10,p11,p12,
     p13,p14,p15,p16,p17,p18,
     p19,p20,p21,p22,p23,p24,
     p25,p26,p27,p28,p29,p30,
     p31,p32,p33,p34,p35,p36;


//--------------------------------------------------------------------
// Display ID info
void displayIDInfo()
{
    cout << "Author: Andrew O'Connell" << endl;
    cout << "Lab:    Tues 2pm"         << endl;
    cout << "Program: #2, Traffic"     << endl;
    cout << endl;
}//end displayIDInfo()


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to the traffic game!                          " << endl
         << "                                                      " << endl
         << "Move the vehicles so that the Red car (RR) can exit   " << endl
         << "the board to the right. Each move should be of the    " << endl
         << "of the form:   CDN   where:                           " << endl
         << "   C  is the vehicle to be moved                      " << endl
         << "   D  is the direction (u=up, d=down, l=left or r=right)" << endl
         << "   N  is the number of squares to move it             " << endl
         << "For example GR2  means move the G vehicle to the right" << endl
         << "2 squares.  Lower-case input such as   gr2  is also   " << endl
         << "accepted.  Enter '-' to reset board, or 'x' to exit.  " << endl;
}//end displayInstructions()



//--------------------------------------------------------------------
// Display the board, using the current values in the global variables.
void displayBoard( )
{
    cout << "- - - - - - - -" << endl;
    cout << "| " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << p5 << " " << p6 << " |" << endl;
    cout << "| " << p7 << " " << p8 << " " << p9 << " " << p10 << " " << p11 << " " << p12 << " |" << endl;
    cout << "| " << p13 << " " << p14 << " " << p15 << " " << p16 << " " << p17 << " " << p18 << " " << endl;
    cout << "| " << p19 << " " << p20 << " " << p21 << " " << p22 << " " << p23 << " " << p24 << " |" << endl;
    cout << "| " << p25 << " " << p26 << " " << p27 << " " << p28 << " " << p29 << " " << p30 << " |" << endl;
    cout << "| " << p31 << " " << p32 << " " << p33 << " " << p34 << " " << p35 << " " << p36 << " |" << endl;
    cout << "- - - - - - - -" << endl;

    return;
}//end displayBoard()

//--------------------------------------------------------------------
// Move the selected character one space to the right
void movePieceRight(char piece, char &n1, char &n2, char &n3 , char &n4, char &n5, char &n6)
{
    // Begin at the rightmost space to determine if the wall will be hit.
    // If so, print out error statement after moving as far as possible.
    // All pieces to the left check one space to the right for a '.' character
    // to determine if a move is possible.
    // If a move is possible, replace the piece to the right with the one on 
    // the left and put a '.' character in its place. Else print and error statement.
    
    if (n6==toupper(piece)) {
        cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
        return;
    }
    if (n5==toupper(piece)) {
        if (n6 == '.') {
            n6 = n5;
            n5 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n4==toupper(piece)) {
        if (n5 == '.') {
            n5 = n4;
            n4 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n3==toupper(piece)) {
        if (n4 == '.') {
            n4 = n3;
            n3 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n2==toupper(piece)) {
        if (n3 == '.') {
            n3 = n2;
            n2 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n1==toupper(piece)) {
        if (n2 == '.') {
            n2 = n1;
            n1 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
}//end movePieceRight()

//--------------------------------------------------------------------
// Move the selected character one space down
void movePieceDown(char piece, char &n1, char &n2, char &n3 , char &n4, char &n5, char &n6)
{
    // Begin at the bottom space to determine if the wall will be hit.
    // If so, print out error statement after moving as far as possible.
    // All pieces above check one space below for a '.' character
    // to determine if a move is possible.
    // If a move is possible, replace the piece below with the one above
    // and put a '.' character in its place. Else print and error statement
    
    if (n6==toupper(piece)) {
        cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
        return;
    }
    if (n5==toupper(piece)) {
        if (n6 == '.') {
            n6 = n5;
            n5 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n4==toupper(piece)) {
        if (n5 == '.') {
            n5 = n4;
            n4 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n3==toupper(piece)) {
        if (n4 == '.') {
            n4 = n3;
            n3 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n2==toupper(piece)) {
        if (n3 == '.') {
            n3 = n2;
            n2 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n1==toupper(piece)) {
        if (n2 == '.') {
            n2 = n1;
            n1 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
}//end movePieceDown()

//--------------------------------------------------------------------
// Move the selected character one space to the left
void movePieceLeft(char piece, char &n1, char &n2, char &n3 , char &n4, char &n5, char &n6)
{
    // Begin at the leftmost space to determine if the wall will be hit.
    // If so, print out error statement after moving as far as possible.
    // All pieces to the right check one space to the left for a '.' character
    // to determine if a move is possible.
    // If a move is possible, replace the piece to the left with the one on 
    // the right and put a '.' character in its place. Else print an error statement.
    
    if (n1==toupper(piece)) {
        cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
        return;
    }
    if (n2==toupper(piece)) {
        if (n1 == '.') {
            n1 = n2;
            n2 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n3==toupper(piece)) {
        if (n2 == '.') {
            n2 = n3;
            n3 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n4==toupper(piece)) {
        if (n3 == '.') {
            n3 = n4;
            n4 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n5==toupper(piece)) {
        if (n4 == '.') {
            n4 = n5;
            n5 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n6==toupper(piece)) {
        if (n5 == '.') {
            n5 = n6;
            n6 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
}//end movePieceLeft()

//--------------------------------------------------------------------
// Move the selected character one space upwards
void movePieceUp(char piece, char &n1, char &n2, char &n3 , char &n4, char &n5, char &n6)
{
    // Begin at the uppermost space to determine if the wall will be hit.
    // If so, print out error statement after moving as far as possible.
    // All pieces below check one space above for a '.' character
    // to determine if a move is possible.
    // If a move is possible, replace the piece to the above with the one on 
    // the below and put a '.' character in its place. Else print an error statement
    
    if (n1==toupper(piece)) {
        cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
        return;
    }
    if (n2==toupper(piece)) {
        if (n1 == '.') {
            n1 = n2;
            n2 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n3==toupper(piece)) {
        if (n2 == '.') {
            n2 = n3;
            n3 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n4==toupper(piece)) {
        if (n3 == '.') {
            n3 = n4;
            n4 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n5==toupper(piece)) {
        if (n4 == '.') {
            n4 = n5;
            n5 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
    if (n6==toupper(piece)) {
        if (n5 == '.') {
            n5 = n6;
            n6 = '.';
        }
        else {
            cout << "*** Move was attempted, but couldn't be completed. ***" << endl;
            return;
        }
    }
}//end movePieceUp()

//--------------------------------------------------------------------
// Reset the board with the user inputted characters
void reset() 
{
    // Replace p1-p36 with user inputted characters
    cout << "You have chosen to reset the board." << endl;
    cout << "Please choose 36 new characters to fill the board:" << endl;
    cin >> p1; cin >> p2; cin >> p3; cin >> p4; cin >> p5; cin >> p6;
    cin >> p7; cin >> p8; cin >> p9; cin >> p10; cin >> p11; cin >> p12;
    cin >> p13; cin >> p14; cin >> p15; cin >> p16; cin >> p17; cin >> p18;
    cin >> p19; cin >> p20; cin >> p21; cin >> p22; cin >> p23; cin >> p24;
    cin >> p25; cin >> p26; cin >> p27; cin >> p28; cin >> p29; cin >> p30;
    cin >> p31; cin >> p32; cin >> p33; cin >> p34; cin >> p35; cin >> p36;
    
    // Capatalize characters with toupper()
    p1 = toupper(p1); p2 = toupper(p2); p3 = toupper(p3); p4 = toupper(p4); p5 = toupper(p5); p6 = toupper(p6);
    p7 = toupper(p7); p8 = toupper(p8); p9 = toupper(p9); p10 = toupper(p10); p11 = toupper(p11); p12 = toupper(p12);
    p13 = toupper(p13); p14 = toupper(p14); p15 = toupper(p15); p16 = toupper(p16); p17 = toupper(p17); p18 = toupper(p18);
    p19 = toupper(p19); p20 = toupper(p20); p21 = toupper(p21); p22 = toupper(p22); p23 = toupper(p23); p24 = toupper(p24);
    p25 = toupper(p25); p26 = toupper(p26); p27 = toupper(p27); p28 = toupper(p28); p29 = toupper(p29); p30 = toupper(p30);
    p31 = toupper(p31); p32 = toupper(p32); p33 = toupper(p33); p34 = toupper(p34); p35 = toupper(p35); p36 = toupper(p36);
    
}



//--------------------------------------------------------------------
/*  Board and corresponding global variable values are:
           - - - - - - - -
         1 | G G . . . Y |
         7 | P . . B . Y |
        13 | P R R B . Y >
        19 | P . . B . . |
        25 | O . . . T T |
        31 | O . F F F . |
           - - - - - - - -
 */
int main()
{
    char car; // Character the user wants to move
    char direction; // Direction user wants to move the car
    int numMoves; // Number of spaces the user wants to move the car
    int loopCount = 0; // Loop counter for numMoves
    int count = 1; // Count to display turn number
    
    displayIDInfo();        // Display ID info
    displayInstructions();  // Display game instructions
    
    // Set the board values
     p1='G'; p2='G'; p3='.'; p4='.'; p5='.'; p6='Y';
     p7='P'; p8='.'; p9='.';p10='B';p11='.';p12='Y';
    p13='P';p14='R';p15='R';p16='B';p17='.';p18='Y';
    p19='P';p20='.';p21='.';p22='B';p23='.';p24='.';
    p25='O';p26='.';p27='.';p28='.';p29='T';p30='T';
    p31='O';p32='.';p33='F';p34='F';p35='F';p36='.';
    
    // Display the initial board
    displayBoard();    
    
    // Begin the game and continue while the car is not at the exit position
    // and the car doesn't equal 'X'
    while (p18 != 'R' && (toupper(car) != 'X')) {
        // Request the user's move
        cout << count << ". Your move -> ";
        cin >> car;
        // Check for 'X' and '-' toe exit or reset, else continue receiving
        // the direction and number of moves
        if ((toupper(car) == 'X')) {
            direction = 'A';
            numMoves = 1;
        }
        else if (car == '-') {
            direction = 'A';
            numMoves = 1;
            reset();
            count = 1;
        }
        else {
            cin >> direction;
            cin >> numMoves;
        }
        
        // Check for the direction and execute the corresponding function
        // for every row or column to move the selected character one space.
        // Use for loops to execute the functions numMoves number of times
        if (toupper(direction) == 'R') {
            for(loopCount=0; loopCount<numMoves; loopCount++) {
                movePieceRight(car, p1, p2, p3 , p4, p5, p6);
                movePieceRight(car, p7, p8, p9 , p10, p11, p12);
                movePieceRight(car, p13, p14, p15 , p16, p17, p18);
                movePieceRight(car, p19, p20, p21 , p22, p23, p24);
                movePieceRight(car, p25, p26, p27 , p28, p29, p30);
                movePieceRight(car, p31, p32, p33 , p34, p35, p36);
            }
        }
        if (toupper(direction) == 'D' ) {
            for(loopCount=0; loopCount<numMoves; loopCount++) {
                movePieceDown(car, p1, p7, p13 , p19, p25, p31);
                movePieceDown(car, p2, p8, p14 , p20, p26, p32);
                movePieceDown(car, p3, p9, p15 , p21, p27, p33);
                movePieceDown(car, p4, p10, p16 , p22, p28, p34);
                movePieceDown(car, p5, p11, p17 , p23, p29, p35);
                movePieceDown(car, p6, p12, p18 , p24, p30, p36);
            }
        }
        if (toupper(direction) == 'L' ) {
            for(loopCount=0; loopCount<numMoves; loopCount++) {
                movePieceLeft(car, p1, p2, p3 , p4, p5, p6);
                movePieceLeft(car, p7, p8, p9 , p10, p11, p12);
                movePieceLeft(car, p13, p14, p15 , p16, p17, p18);
                movePieceLeft(car, p19, p20, p21 , p22, p23, p24);
                movePieceLeft(car, p25, p26, p27 , p28, p29, p30);
                movePieceLeft(car, p31, p32, p33 , p34, p35, p36);
            }
        }
        if (toupper(direction) == 'U' ) {
            for(loopCount=0; loopCount<numMoves; loopCount++) {
                movePieceUp(car, p1, p7, p13 , p19, p25, p31);
                movePieceUp(car, p2, p8, p14 , p20, p26, p32);
                movePieceUp(car, p3, p9, p15 , p21, p27, p33);
                movePieceUp(car, p4, p10, p16 , p22, p28, p34);
                movePieceUp(car, p5, p11, p17 , p23, p29, p35);
                movePieceUp(car, p6, p12, p18 , p24, p30, p36);
            }
        }
        // Display the updated board at the end of each turn and increase the
        // count by one
        displayBoard();
        count ++;
    }
    
    cout << endl;
    cout << "*** Congratulations, you did it! ***" << endl;
    cout << "Thank you for playing.  Exiting..." << endl;
    
    return 0;
}//end main()



