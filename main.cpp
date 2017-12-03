//Made by Juan Molina & Jetanat Datephanyawat
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "PlayerTable.h"
using namespace std;
 
int main(int argc, char* argv[])
{
    PlayerHashTable myHash;
    string yearID, teamID, leagueID, playerID, salary, firstName, lastName, birthYear, birthCountry, weight, height, bats, throws;
 
    int hashtablesize = stoi(argv[2]);
    char* filename = argv[1];
    myHash.tablesize = hashtablesize;
 
    ifstream myfile;
    myfile.open(filename);
    string line;
 
    int skipLine;
    if(myfile.is_open())
    {
        while(getline(myfile, line))
        {
            if(skipLine != 0)
            {
                stringstream word(line);
                getline(word, yearID, ',');
                getline(word, teamID, ',');
                getline(word, leagueID, ',');
                getline(word, playerID, ',');
                getline(word, salary, ',');
                getline(word, firstName, ',');
                getline(word, lastName, ',');
                getline(word, birthYear, ',');
                getline(word, birthCountry, ',');
                getline(word, weight, ',');
                getline(word, height, ',');
                getline(word, bats, ',');
                getline(word, throws);
                myHash.insertChainingPlayer(stoi(yearID), teamID, leagueID, playerID, stoi(salary), firstName, lastName, stoi(birthYear), birthCountry, stoi(weight),stoi(height),bats,throws);
                myHash.insertOpenPlayer(stoi(yearID), teamID, leagueID, playerID, stoi(salary), firstName, lastName, stoi(birthYear),birthCountry, stoi(weight),stoi(height),bats,throws);
            }
            skipLine++;
        }
    }
    else
    {
        cout << "Could not open file" <<endl;
    }
 
    string choice;
    while(choice != "2")
    {
        cout <<   "======Main Menu======" << endl;
        cout << "1. Query hash table" << endl;
        cout << "2. Quit program" << endl;
        getline(cin, choice);
        switch(stoi(choice)){
        case 1:
            {
                string firstName, lastName;
                cout << "Please enter first name: " <<endl;
                getline(cin, firstName);
                cout << "Please enter last name: " <<endl;
                getline(cin, lastName);
 
                myHash.searchChainHashTable(firstName, lastName);
                myHash.searchOpenHashTable(firstName, lastName);
;                break;
            }
        case 2:
            {
                cout << "Goodbye!" << endl;
                break;
            }
        }
    }
    return 0;
}
