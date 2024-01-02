#include <iostream> 
#include <cstdlib> 
#include <ctime>     
#include <cstddef>  
#include <iostream>
#include "ui.cpp"

using namespace std;

const int water = 0;
const int boat = 1;
const int hit = 2;
const int miss = 3;

const int carrier = 5;
const int battleship = 4;
const int destroyer = 3;
const int submarine = 3;
const int patrolBoat = 2;

int playerGrid[10][10];
int aiGrid[10][10];
int trackerGrid[10][10];

void startGrid(){
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            playerGrid[i][j] = water;
            aiGrid[i][j] = water;
            trackerGrid[i][j] = water;
            cout << playerGrid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printGrid(int grid[10][10]){
    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= 10; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkShip(char direction, int row, int column, int size, int grid[10][10]){
    if(direction == 'H'){
        if(column + size > 11){
            cout  << "ship out of bounds" << endl;
            return false;
        }
        for(int i = 1; i <= size; i++){
            if(grid[row][column - 1 + i] != water){
                cout << "ship already placed here" << endl;
                return false;
            }
        }
    } 

    else if(direction == 'V'){
        if(row + size > 11) {
            cout  << "ship out of bounds" << endl;
            return false;
        }
        for(int i = 1; i <= size; i++) {
            if(grid[row - 1 + i][column] != water){
                cout << "ship already placed here" << endl;
                return false;
            }
        }
    }

    else if(direction != 'H' || direction != 'V'){
        cout << "incorrect direction" << endl;
        return false;
    }
    return true;
}

bool checkAIShip(char direction, int row, int column, int size, int grid[10][10]){
    if(direction == 'H'){
        if(column + size > 11){
            return false;
        }
        for(int i = 1; i <= size; i++){
            if(grid[row][column - 1 + i] != water){
                return false;
            }
        }
    } 

    else if(direction == 'V'){
        if(row + size > 11) {
            return false;
        }
        for(int i = 1; i <= size; i++) {
            if(grid[row - 1 + i][column] != water){
                return false;
            }
        }
    }

    else if(direction != 'H' && direction != 'V'){
        return false;
    }
    return true;
}

void addShip(char direction, int row, int column, int size, int grid[10][10]){
    if (direction == 'H'){
        for (int i = 1; i <= size; ++i)
            grid[row][column + i - 1] = boat;
    } else{
        for (int i = 1; i <= size; ++i)
            grid[row + i - 1][column] = boat;
    }
}

bool isAttackValid(int row, int column, int grid[10][10]){
    return grid[row][column] != hit && grid[row][column] != miss;
}

void destroy(int row, int column, int grid[10][10]){
    //if attack hits a ship
    if(grid[row][column] == boat) {
        grid[row][column] = hit;
        trackerGrid[row][column] = hit;
        cout << endl;
        cout << "tracker grid" << endl;
        printGrid(trackerGrid);
        cout << "you: ship has been hit!" << endl;
        cout << endl;
        return;
    }

    //if attack hits the water
    if(grid[row][column] == water) {
        grid[row][column] = miss;
        trackerGrid[row][column] = miss;
        cout << endl;
        cout << "tracker grid" << endl;
        printGrid(trackerGrid);
        cout << "you: attack has missed" << endl;
        cout << endl;
        return;
    }

    //if the attack is at the same coordinate
    cout << "attack repeated" << endl;
    return;
}

bool win(int grid[10][10]){
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            if(grid[i][j] != boat){
                continue;
            }
            else
                return false;
        }
    }
    return true;
} 

void playerStart(){
    bool valid;
    char position;
    int row;
    int column;
    
    //carrier
    do{
        cout << "enter 'H' or 'V' for carrier's position (size 5)" << endl;
        cin >> position;
        cout << "enter location of carrier (row column)" << endl;
        cin >> row >> column;

        valid = checkShip(position, row, column, carrier, playerGrid);
        if(!valid){
            cout << "invalid input, try a different input" << endl;
        }
    }while (!valid);

    addShip(position,row,column,carrier,playerGrid);
    printGrid(playerGrid);
    
    //battleship
    do{
        cout << "enter 'H' or 'V' for battleship's position (size 4)" << endl;
        cin >> position;
        cout << "enter location of battleship (row column)" << endl;
        cin >> row >> column;

        valid = checkShip(position, row, column, battleship,playerGrid);
        if(!valid){
            cout << "invalid input, try a different input" << endl;
        }
    }while (!valid);

    addShip(position,row,column,battleship,playerGrid);
    printGrid(playerGrid);

    //destroyer
    do{
        cout << "enter 'H' or 'V' for destroyer's position (size 3)" << endl;
        cin >> position;
        cout << "enter location of destroyer (row column)" << endl;
        cin >> row >> column;   

        valid = checkShip(position, row, column, destroyer,playerGrid);
        if(!valid){
            cout << "invalid input, try a different input" << endl;
        }
    }
    while (!valid);

    addShip(position,row,column,destroyer,playerGrid);
    printGrid(playerGrid);

    //submarine
    do{
        cout << "enter 'H' or 'V' for submarine's position (size 3)" << endl;
        cin >> position;
        cout << "enter location of submarine (row column)" << endl;
        cin >> row >> column;

        valid = checkShip(position, row, column, submarine,playerGrid);
        if(!valid){
            cout << "invalid input, try a different input" << endl;
        }
    }
    while (!valid);

    addShip(position,row,column,submarine,playerGrid);
    printGrid(playerGrid);    
    
    //patrolboat
    do{
        cout << "enter 'H' or 'V' for patrolboat's position (size 2)" << endl;
        cin >> position;
        cout << "enter location of patrolboat (row column)" << endl;
        cin >> row >> column;

        valid = checkShip(position, row, column, patrolBoat,playerGrid);
        if(!valid){
            cout << "invalid input, try a different input" << endl;
        }
    }
    while (!valid);

    addShip(position,row,column,patrolBoat,playerGrid);
    printGrid(playerGrid);
}

void playerTurn(int grid[10][10]){
    int row, col;
    bool validShot = false;

    while (!validShot) {
        cout << "enter coordinates to attack enemy(row column): ";
        cin >> row >> col;

        if (!isAttackValid(row, col, grid)){
            cout << "you have already attacked these coordinates. please try again." << endl;
            continue; // This will prompt the user for input again
        }

        // If the attack is valid, then execute the destroy function and exit the loop
        destroy(row, col, grid);
        validShot = true;
    }
}

void placeAIShips() {
    srand((unsigned) time(NULL)); // Seed the random number generator
    char positions[2] = {'H', 'V'};
    int shipSizes[] = {carrier, battleship, destroyer, submarine, patrolBoat};
    int numShips = sizeof(shipSizes) / sizeof(shipSizes[0]);

    for(int i = 0; i < numShips; i++){
        int shipSize = shipSizes[i];
        bool placed = false;
        while(!placed) {
            char direction = positions[rand() % 2];
            int row, column;
            if (direction == 'H') {
                row = rand() % 10 + 1; // For horizontal placement, row can be any valid row
                column = rand() % (11 - shipSize) + 1; // Column must accommodate the full length of the ship
            } else {
                row = rand() % (11 - shipSize) + 1; // Row must accommodate the full height of the ship
                column = rand() % 10 + 1; // For vertical placement, column can be any valid column
            }

            if(checkAIShip(direction, row, column, shipSize, aiGrid)){
                addShip(direction, row, column, shipSize, aiGrid);
                placed = true;
            }
        }
    }
}

void aiDestroy(int row, int column, int grid[10][10]){
    //if attack hits a ship
    if(grid[row][column] == boat) {
        grid[row][column] = hit;
        cout << "your grid" << endl;
        printGrid(playerGrid);
        cout << "enemy: ship has been hit!" << endl;
        cout << endl;
        return;
    }

    //if attack hits the water
    if(grid[row][column] == water) {
        grid[row][column] = miss;
        cout << "your grid" << endl;
        printGrid(playerGrid);
        cout << "enemy: attack has missed" << endl;
        cout << endl;
        return;
    }

    //if the attack is at the same coordinate
    cout << "attack repeated" << endl;
    return;
}

void aiTurn(int grid[10][10]) {
    int row, col;
    bool validShot = false;

    while (!validShot) {
        row = rand() % 10;
        col = rand() % 10;

        // Check if the AI has already shot here
        if (isAttackValid(row, col, grid)) {
            validShot = true;
            aiDestroy(row, col, playerGrid);
        }
    }
}

int main() {
    logo();
    startGrid();
    playerStart();
    placeAIShips();

    while (!win(playerGrid) && !win(aiGrid)) {
        playerTurn(aiGrid);

        if (win(aiGrid)){
            displayWin();
            cout << "congratulations! you win!" << endl;
            break;
        }
        aiTurn(playerGrid); 
        if (win(playerGrid)){
            displayLose();
            cout << "ai has won the game. try again." << endl;
            break;
        }
    }
    return 0;
}
