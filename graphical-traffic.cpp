/* --------------------------------------------------------
 * TrafficGraphics.cpp
 *     Create an interface to graphically display the output
 * as you solve the traffic puzzle, where you try to get the
 * red car to exit the grid to the right.
 *
 * Class: Program #4 for CS 141, Fall 2017.
 * Lab: Mon 5am,
 * TA Alan Turing
 * System: Mac OS X
 * Author: Dale Reed
 *
 * Running the program gives text for the instructions and prompts for user input,
 * but the output is graphical.
 *
 * To do:
 *    Implement resetting the board
 *
 * When running the program, pasting in the following input takes you directly
 * to a win:
        gr1
        mu1
        ou1
        pl2
        cl3
        bd2
        yd3
        rr3

 */
#include <fstream>
#include <iostream>
#include "gobjects.h"   // For the Stanford graphics library
#include <fstream>      // For file input
#include <cstring>      // For string functions
using namespace std;

// Global constants
#define VALID_COLOR_LETTERS "RBGMCYOP"   // Used to validate user input
#define SUCCESSFUL_MOVE 1                // Move was successful
#define INVALID_VEHICLE_DIRECTION 2      // Signifies attempt was made to move vehicle in invalid direction
#define MOVE_ATTEMPTED_ON_OTHER_VEHICLE 3  // Attempt was made to move ontop of another vehicle
#define MOVE_ATTEMPTED_OFF_BOARD 4       // Attempt was made to move off board
#define PUZZLE_IS_SOLVED 5               // Puzzle has been solved
#define BOARD_SIZE 6                     // How many pieces on a side for the board


//--------------------------------------------------------------------
class Vehicle
{
    public:
        // Constructor
        Vehicle(char color=' ', char orientation='H', int row=1, int col=1, int length=1)
        {
            // Set values
            switch( color) {
                case('R'): this->color = "RED"; break;
                case('B'): this->color = "BLUE"; break;
                case('G'): this->color = "GREEN"; break;
                case('M'): this->color = "MAGENTA"; break;
                case('C'): this->color = "CYAN"; break;
                case('Y'): this->color = "YELLOW"; break;
                case('O'): this->color = "ORANGE"; break;
                case('P'): this->color = "PINK"; break;
                default:   this->color = "GRAY"; break;
            }
            this->orientation = orientation;
            this->row = row; this->col = col; this->length = length;
            vehicleIndex = -1;
        }

        // Copy constructor
        Vehicle( const Vehicle &otherVehicle) {
            this->color = otherVehicle.color;
            this->orientation = otherVehicle.orientation;
            this->row = otherVehicle.row;
            this->col = otherVehicle.col;
            this->length = otherVehicle.length;
            this->vehicleIndex = otherVehicle.vehicleIndex;
        }

        // Accessor (get) member functions
        string getColor() { return color; }
        char getOrientation() { return orientation; }
        int getRow() { return row; }
        int getCol() { return col; }
        int getLength() { return length; }
        int getVehicleIndex() { return vehicleIndex; }

        // Mutator (set) member functions
        void setRow( int theRow) { row = theRow; }
        void setCol( int theCol) { col = theCol; }
        void setVehicleIndex( int theIndex) { vehicleIndex = theIndex; }

        // Utility member functions
        void print() {
            cout << color << " vehicle is at: " << row << "," << col
                 << " with length " << length << " oriented " << orientation << endl;
        }

    private:
        string color;
        char orientation;
        int row,col,length;
        int vehicleIndex;   // Index of vehicle in external Vehicles array
}; // end class Vehicle


//--------------------------------------------------------------------
// Display ID info
void displayIDInfo()
{
    printf("Author:  Dale Reed          \n");
    printf("Lab:     Mon 5am            \n");
    printf("Program: #4, Graphical Traffic \n");
    printf(" \n");
}//end displayIDInfo()


//------------------------------------------------------------------------------------------
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
         << "accepted.  Enter \"reset\" to reset board, or \"exit\" to exit.  " << endl;
}//end displayInstructions()


//------------------------------------------------------------------------------------------
// Draw a rectangle.  Since the rectangle is created here, make it a reference parameter
// so that when the vehicles are made they can later be changed.
void drawRectangle( bool rectangleAlreadyExists,     // if set to false, we need to create the rectangle here
                    GRect *theRectangle, int x, int y, int xSize, int ySize,
                    string theColor, GWindow graphicsWindow)
{
    // Set the display rectangle position and size.
    if( rectangleAlreadyExists) {
        // Set the bounds for the existing rectangle, such as for the Vehicles
        cout << "Setting vehicle rectangle " << endl;
        theRectangle->setBounds( x, y, xSize, ySize);
    }
    else {
        // Create a new rectangle, such as when painting the board background
        theRectangle = new GRect( x, y, xSize, ySize);
    }
    theRectangle->setFilled( true);
    theRectangle->setColor( theColor);
    graphicsWindow.add( theRectangle);
}//end drawRectangle()


//--------------------------------------------------------------------
// Translate the vehicle input file values into pixel dimensions and draw the vehicle.
// Note that each vehicle's private data members used below are available because this
// is a Vehicle class member function.
void drawVehicle(Vehicle *&pTheVehicle,      // Each vehicle, an instance of class Vehicle
                 GRect *vehicleRectangles[], // Array of vehicle rectangles used to draw vehicle
                 GWindow graphicsWindow)     // The drawing window
{
    // Translate grid positions into pixel values.  The first vehicle's position in the
    // upper-left corner is 30,30
    int xStart = 30 + (pTheVehicle->getCol() - 1) * 40;
    int yStart = 30 + (pTheVehicle->getRow() - 1) * 40;

    // Set default size values
    int xSize = 30;
    int ySize = 30;

    // Modify either the x or y size.  From the edge of one square to the edge of the
    // next square it is 40 pixels, with a space of 10 pixels in between them.
    if( pTheVehicle->getOrientation()=='H') {
        xSize = (pTheVehicle->getLength() * 40) - 10;
    }
    else{
        ySize = (pTheVehicle->getLength()) * 40 - 10;
    }

    // Get the index for this vehicle, used to find which display rectangle is used.
    int vehicleIndex = pTheVehicle->getVehicleIndex();

    // Make a new rectangle used to draw this vehicle.
    vehicleRectangles[ vehicleIndex] = new GRect( xStart, yStart, xSize, ySize);
    vehicleRectangles[ vehicleIndex]->setFilled( true);
    // Set the rectangle color from the already-stored vehicle color
    vehicleRectangles[ vehicleIndex]->setColor( pTheVehicle->getColor());
    graphicsWindow.add( vehicleRectangles[ vehicleIndex]);
}//end drawVehicle()


//------------------------------------------------------------------------------------------
// Draw the board background.
void drawBoardBackground( GWindow graphicsWindow)
{
    // Create the outline darkGray square
    GRect *rect = NULL;
    drawRectangle( false, rect, 10,10,270,270, "darkGray", graphicsWindow);

    // Create the inner playing surface gray square
    drawRectangle( false, rect, 20,20,250,250, "gray", graphicsWindow);

    // Draw the exit opening in the border
    drawRectangle( false, rect, 270,100,10,50, "lightGray", graphicsWindow);

    // Draw the vertical lines
    for( int i=0; i<7; i++) {
        drawRectangle( false, rect, 20+(i*40),20,10,250, "lightGray", graphicsWindow);
    }

    // Draw the horizontal lines
    for( int i=0; i<7; i++) {
        drawRectangle( false, rect, 20,20+(i*40),250,10, "lightGray", graphicsWindow);
    }
}//end drawBoardBackground()


//------------------------------------------------------------------------------------------
void ReadVehicleInfoFromFileAndDisplayThem(
        Vehicle *vehicles[],        // Array of Vehicle class instances
        GRect *vehicleRectangles[], // Array of vehicle rectangles used to draw each vehicle
        int &howManyVehicles,       // Number of vehicles, read from top line of date file
        GWindow graphicsWindow)     // Graphics window used for drawing vehicles
{
    ifstream inputFileStream;  // declare the input file stream

    inputFileStream.open("board.txt");
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file board.txt.  Exiting..." << endl;
        exit( -1);
    }

    inputFileStream >> howManyVehicles;
    // cout << "Number of vehicles is: " << howManyVehicles << endl;  // For debugging

    char vehicle, orientation;
    int row, col, length;
    for( int vehicleIndex=0; vehicleIndex<howManyVehicles; vehicleIndex++) {
        inputFileStream >> vehicle >> orientation >> row >> col >> length;
        // Add the information for each vehicle.  First make a new vehicle.
        vehicles[ vehicleIndex] = new Vehicle(vehicle, orientation, row, col, length);
        // Store the index with the vehicle, used to find the rectangle for that vehicle used in drawing.
        vehicles[ vehicleIndex]->setVehicleIndex( vehicleIndex);
        drawVehicle( vehicles[ vehicleIndex], vehicleRectangles, graphicsWindow);
    }
}// end ReadVehicleInformationFromDataFile()


//------------------------------------------------------------------------------------------
// Read input from the console to reset the board
void resetBoard(
        Vehicle *vehicles[],        // Array of Vehicle class instances
        GRect *vehicleRectangles[], // Array of vehicle rectangles used to draw each vehicle
        int &howManyVehicles,       // Number of vehicles, read from top line of date file
        GWindow graphicsWindow)     // Graphics window used for drawing vehicles
{
    // Dispose of all the old vehicles and all the old rectangles, as new ones will be created.
    for( int i=0; i<howManyVehicles; i++) {
        vehicleRectangles[i]->setVisible( false);
        delete vehicleRectangles[i];
        delete vehicles[ i];
    }

    cout << "Enter the information for the new board, in the same format as the board.txt file" << endl;
    cin >> howManyVehicles;

    char vehicle, orientation;
    int row, col, length;
    for( int vehicleIndex=0; vehicleIndex<howManyVehicles; vehicleIndex++) {
        cin >> vehicle >> orientation >> row >> col >> length;
        // Add the information for each vehicle.  First make a new vehicle.
        vehicles[ vehicleIndex] = new Vehicle(vehicle, orientation, row, col, length);
        // Store the index with the vehicle, used to find the rectangle for that vehicle used in drawing.
        vehicles[ vehicleIndex]->setVehicleIndex( vehicleIndex);
        drawVehicle( vehicles[ vehicleIndex], vehicleRectangles, graphicsWindow);
    }

    // Read the last return character from the input, so that the program doesn't think the user already
    // typed in a move.
    char c;
    c = getchar();
}//end resetBoard()


//------------------------------------------------------------------------------------------
// Given the direction and distance, calculate the x,y board block offsets to move the vehicle rectangle.
void calculateXYdifferences(
        int &xDifference,    // Calculated x,y board block differences
        int &yDifference,
        char direction)      // One of the letters: L, R, U, D for left, right, up, or down
{
    // Find the horizontal difference
    if( direction == 'L' || direction == 'R') {
        xDifference = 1;
        if( direction == 'L') {
            xDifference = xDifference * -1;   // Negative change to x movement
        }
    }
    // Find the vertical difference
    if( direction == 'D' || direction == 'U') {
        yDifference = 1;
        if( direction == 'U') {
            yDifference = yDifference * -1;   // Negative change to y movement
        }
    }
}


//------------------------------------------------------------------------------------------
Vehicle * findWhichVehicle( char vehicleLetter, Vehicle *vehicles[], int howManyVehicles)
{
    for( int i=0; i < howManyVehicles; i++) {
        if( vehicleLetter == vehicles[ i]->getColor()[0]) {
            return vehicles[ i];
        }
    }

    cout << "*** Vehicle " << vehicleLetter << " not found. " << endl;
    return vehicles[ 0];
}// end findWhichVehicle()


//--------------------------------------------------------------------
// Place a vehicle's letters on a textual model of the board.  This is used to check for overlap errors.
// Set the overlapError reference parameter to true if there is an overlap error.
void placeVehicleOnBoard(
            Vehicle *pTheVehicle,       // The vehicle to be placed
            char board[][ BOARD_SIZE],  // The character array board onto which the vehicle is placed
            bool &overlapError)         // Gets set to true if there is an overlap error
{
    // Extract values of vehicle to be placed
    int theRow = pTheVehicle->getRow() - 1;
    int theCol = pTheVehicle->getCol() - 1;
    int theLength = pTheVehicle->getLength();
    string theColor = pTheVehicle->getColor();

    // Step through and place each vehicle's letter onto the board
    for( int counter=0; counter < theLength; counter++) {
        // Check for overlap error
        if( board[ theRow][ theCol] != '.') {
            overlapError = true;
        }
        board[ theRow][ theCol] = theColor[0];  // Store only first letter of the color string

        // Depending on the orientation, now change either the row or column to advance to next position.
        if( pTheVehicle->getOrientation() == 'H') {
            // Horizontal orientation, so next position is to the right.
            theCol++;
        } else {
            // Vertical orientation, so next position is below.
            theRow++;
        }
    }//end for( int counter...

}//end placeVehicleOnBoard()


//--------------------------------------------------------------------
// Check for attempt to move on top of another vehicle.
// Make a text model with all the vehicles on the board.  Copy the
// vehicle to be moved, and change its values to be the ones reflecting
// the proposed move.  Attempt to place it on the board that currently
// has all the other pieces.  An error is set if this attempt tries to
// place a piece on the board onto a square that is not already blank.
//
bool attemptMadeToMoveOnTopOfAnotherVehicle(
        Vehicle *pTheVehicleToMove, // The vehicle being moved
        Vehicle *vehicles[],        // Array of all the vehicles
        int vehicleIndex,           // Index of vehicle being moved
        int howManyVehicles,        // How many vehicles there are
        char direction)             // One of: R,L,U,D
{
    bool overlapError = false;  // Gets set to true when there is an overlap error

    // Create a text model containing letters for the vehicles and '.' for spaces
    char board[ BOARD_SIZE][ BOARD_SIZE];
    // Initialize to all '.'
    for( int row=0; row<BOARD_SIZE; row++) {
        for( int col=0; col<BOARD_SIZE; col++) {
            board[ row][ col] = '.';
        }
    }

    // Place all vehicle characters on the board.
    for( int i=0; i<howManyVehicles; i++) {
        if( i != vehicleIndex) {
           placeVehicleOnBoard( vehicles[ i], board, overlapError);
        }
    }

    // See if placing current vehicle in new position would create conflict.
    // Create a new vehicle in the position where it would be after the move, and attempt to place it
    // on the board.
    Vehicle newVehicle( *pTheVehicleToMove);   // Use copy constructor to clone the existing vehicle
    // Modify its row,col location to reflect the move.

    // Update the internal vehicle's position.
    int xDifference = 0;  // Change in x blocks for a move
    int yDifference = 0;  // Change in y blocks for a move
    // Set the xDifference and yDifference values according to the move direction
    calculateXYdifferences( xDifference, yDifference, direction);
    // Update the piece to reflect a single block movement in the indicated direction
    newVehicle.setRow( pTheVehicleToMove->getRow() + yDifference);
    newVehicle.setCol( pTheVehicleToMove->getCol() + xDifference);

    // Attempt to place it in its new location, setting overlapError if there is an overlap
    placeVehicleOnBoard( &newVehicle, board, overlapError);

    if( overlapError) {
        return true;
    } else {
        return false;
    }
}//end attemptMadeToMoveOnTopOfAnotherVehicle()


//--------------------------------------------------------------------
// Return true if an attempt is made to move off the board
bool attemptMadeToMoveOffBoard(
        Vehicle *pTheVehicleToMove,
        char direction)
{
    // Check all four directions for attempts to move out of bounds
    if( ( direction=='R' && (pTheVehicleToMove->getCol() + pTheVehicleToMove->getLength()) > BOARD_SIZE) ||
        ( direction=='L' && (pTheVehicleToMove->getCol() == 1) ) ||
        ( direction=='D' && (pTheVehicleToMove->getRow() + pTheVehicleToMove->getLength()) > BOARD_SIZE) ||
        ( direction=='U' && (pTheVehicleToMove->getRow() == 1) )
      ) {
        return true;
    }

    return false;
}//end attemptMadeToMoveOffBoard()


//--------------------------------------------------------------------
// Reset the vehicle row,col values as well as the rectangle display position.
// This is done when a prospective move caused a rectangle overlap or went off the board.
void resetVehicle(
        Vehicle *pTheVehicleToMove,
        int originalRow,
        int originalCol,
        GRect *pTheRectangle,
        int originalX,
        int originalY)
{
    pTheVehicleToMove->setRow( originalRow);
    pTheVehicleToMove->setCol( originalCol);
    pTheRectangle->setLocation( originalX, originalY);
}


//--------------------------------------------------------------------
// Given the desired move information, vehicle information, and
//    drawing rectangles, move the appropriate drawing rectangle.
//
// Return error condition values use the following global constants:
//   SUCCESSFUL_MOVE 1                 // Move was successful
//   INVALID_VEHICLE_DIRECTION 2       // Signifies attempt was made to move vehicle in invalid direction
//   MOVE_ATTEMPTED_ON_OTHER_VEHICLE 3 // Attempt was made to move ontop of another vehicle
//   MOVE_ATTEMPTED_OFF_BOARD 4        // Attempt was made to move off board
//   PUZZLE_IS_SOLVED 5                // Puzzle has been solved
//
int makeTheMove(
        char vehicleLetter,         // Letter of vehicle to be moved
        Vehicle *vehicles[],        // Array of all vehicles information
        int howManyVehicles,        // How many vehicles there are total
        GRect *vehicleRectangles[], // Array of drawing rectangles for all the vehicles
        char direction,             // Direction letter: L, R, U, D
        char distance)              // Board block distance to be moved
{
    int xDifference = 0;  // Change in x blocks for a move
    int yDifference = 0;  // Change in y blocks for a move
    Vehicle *pTheVehicleToMove;  // The vehicle to move, on any given move
    int returnValue = SUCCESSFUL_MOVE;  // Assume success.  This gets reset if there is an error

    // Find the vehicle to be moved
    pTheVehicleToMove = findWhichVehicle( vehicleLetter, vehicles, howManyVehicles);

    // Check for mismatch between desired move direction and vehicle orientation
    char theVehicleOrientation = pTheVehicleToMove->getOrientation();
    if( ( (theVehicleOrientation == 'H') && (direction != 'L' && direction != 'R') ) ||
        ( (theVehicleOrientation == 'V') && (direction != 'U' && direction != 'D') )
      ) {
      returnValue = INVALID_VEHICLE_DIRECTION;
    }

    // If no errors were found so far, move the rectangle using the computed x,y offsets.
    // Moves are made one square at a time. Do error checking along the way to see if we
    // attempt to move on top of another piece, or off the board.
    if( returnValue == SUCCESSFUL_MOVE) {
        // Calculate x,y block difference for the move.
        calculateXYdifferences( xDifference, yDifference, direction);

        // Move the vehicle by the calculated x,y offsets
        // First get the index of the current vehicle, used to determine which drawing rectangle to use
        int vehicleIndex = pTheVehicleToMove->getVehicleIndex();
        GRect *pTheRectangle = vehicleRectangles[ vehicleIndex];

        // Make multiple square moves one at a time, to allow checking for win and errors.
        // First store the original position values, so that the vehicle can be reset if the move ends up
        // overwriting another piece or attempting to go off the board.
        int originalRow = pTheVehicleToMove->getRow();
        int originalCol = pTheVehicleToMove->getCol();
        int originalX = pTheRectangle->getX();
        int originalY = pTheRectangle->getY();
        for( int i=0; i<distance; i++) {
            // Check for attempt to move on top of another vehicle
            if( attemptMadeToMoveOnTopOfAnotherVehicle( pTheVehicleToMove, vehicles, vehicleIndex,
                                                        howManyVehicles, direction)) {
                returnValue = MOVE_ATTEMPTED_ON_OTHER_VEHICLE;
                resetVehicle( pTheVehicleToMove, originalRow, originalCol, pTheRectangle, originalX, originalY);
                break;
            }
            // Check for attempt to move off the board
            if( attemptMadeToMoveOffBoard( pTheVehicleToMove, direction)) {
                returnValue = MOVE_ATTEMPTED_OFF_BOARD;
                resetVehicle( pTheVehicleToMove, originalRow, originalCol, pTheRectangle, originalX, originalY);
                break;
            }

            // Move the rectangle
            pTheRectangle->move( xDifference*40, yDifference*40);

            // Update the internal vehicle's position.
            pTheVehicleToMove->setRow( pTheVehicleToMove->getRow() + yDifference);
            pTheVehicleToMove->setCol( pTheVehicleToMove->getCol() + xDifference);
            pause( 120);  // Let individual block moves show up (not required)

            // Check for win, which is when red car is in the exit position
            if( pTheVehicleToMove->getColor().compare("RED") == 0  &&
                pTheVehicleToMove->getRow() == 3 &&
                pTheVehicleToMove->getCol() == 5
               ) {
                returnValue = PUZZLE_IS_SOLVED;   // signifies a win
                break;
            }

        }//end for( int i...
    }//end if( returnValue == 1...

    return returnValue;
}//end makeTheMove()


//--------------------------------------------------------------------
// We are done when the red car is at the exit position row 2, column 5
bool done(Vehicle *vehicles[], int howManyVehicles)
{
   bool returnValue = false;   // default is we are not done

   Vehicle *theVehicle = findWhichVehicle( 'R', vehicles, howManyVehicles);
   if( theVehicle->getRow() == 2 && theVehicle->getCol() == 5) {
       returnValue = true;
   }

   return returnValue;   // true if theVehicle is at row 2, column 5
}//end done()


//------------------------------------------------------------------------------------------
void convertToUpperCase( string &userInput)
{
    for( int i=0; i<userInput.length(); i++) {
        userInput[i] = toupper( userInput[i]);
    }
}


//------------------------------------------------------------------------------------------
int main()
{
   // Create the enclosing window and the background
    GWindow graphicsWindow(300,300);
    graphicsWindow.setWindowTitle("CS 141: Prog 4 Graphical Traffic");
    graphicsWindow.setExitOnClose( true);
    drawBoardBackground( graphicsWindow);

    displayIDInfo();        // Display ID info
    displayInstructions();  // Display game instructions

    int howManyVehicles = 0;
    Vehicle *vehicles[ 8];          // Array of vehicle information, where 8 is maximum
    GRect *vehicleRectangles[ 8];   // Array of the rectangles used to draw the vehicles
    ReadVehicleInfoFromFileAndDisplayThem( vehicles, vehicleRectangles, howManyVehicles, graphicsWindow);

    char vehicleLetter; // Extracted from user input
    char direction;     // Extracted from user input (u,d,l,r)
    int  distance;      // Extracted from user input
    int moveNumber = 1; // Counts and displays number of moves
    int moveResult = 0; // Error conditions for move results
    string userInput;   // Stores user input

    // Main loop to play program
    do {
        // Prompt for and get user input, including checking for 'x' to exit
        cout << moveNumber << ". Your move -> ";
        getline(cin, userInput);

        // Convert user input to all upper case, to simplify comparisons
        convertToUpperCase( userInput);
        if( userInput[0]=='X' || userInput.compare( "EXIT") == 0) {
            break;   // break out of main playing loop to exit the game
        }
        else if( userInput.compare( "RESET") == 0) {
            // Reset the board and restart loop
            resetBoard( vehicles, vehicleRectangles, howManyVehicles, graphicsWindow);
            moveNumber = 1;
            continue;
        }

        // Get the vehicle letter, direction ('l','r','u','d') and distance (1..4)
        // User input would be something like: gr2  which would move green right by 2.
        vehicleLetter = userInput[0];
        // Convert the direction and distance numerical characters to their corresponding values.
        direction = userInput[1];
        distance = userInput[2] - '0';

        // Ensure vehicle letter is one of the valid color letters
        if( strchr( VALID_COLOR_LETTERS, vehicleLetter) == NULL) {
            // Vehicle letter input is not a valid color.
            cout << "*** User input is not one of the valid color or action items.  Please retry." << endl;
            continue;
        }

        // Make the move, storing the move result success/error condition.
        moveResult = makeTheMove( vehicleLetter, vehicles, howManyVehicles, vehicleRectangles,
                                  direction, distance);
        if( moveResult == PUZZLE_IS_SOLVED) {
            cout << "Congratulations! " << endl;
            pause(2000);   // Pause to let user see solved board
            break;
        }
        else if( moveResult != SUCCESSFUL_MOVE) {
            // There was an error
            switch( moveResult) {
                case INVALID_VEHICLE_DIRECTION:
                        cout << "*** Attempt was made to move a piece in the wrong direction. "; break;
                case MOVE_ATTEMPTED_ON_OTHER_VEHICLE:
                        cout << "*** Attempt is made to move a piece on top of another piece. "; break;
                case MOVE_ATTEMPTED_OFF_BOARD:
                        cout << "*** Attempt is made to move a piece off the board. "; break;
            }
            cout << "Please retry. " << endl;
            // Loop back up to retry move if there was an error.
            continue;
        }

        moveNumber++;  // Increment the move number.
    } while( moveResult != PUZZLE_IS_SOLVED);   // Red car 'R' is at the exit point for a win

    // Display appropriate ending message.
    if( moveResult == PUZZLE_IS_SOLVED ) {
        cout << endl << "*** You solved it! ***" << endl;
    }
    else {
        cout << "Better luck next time. " << endl;
    }
    cout << endl;
    cout << "Thank you for playing.  Exiting..." << endl;

    // Close the windows, first the graphics window, then the console window.
    graphicsWindow.requestFocus();
    graphicsWindow.close();
    exitGraphics();

    return 0;
}//end main()
