#ifndef PLAYERTABLE_H
#define PLAYERTABLE_H
#include<vector>
#include<iostream>
#include<queue>
#include <string>
using namespace std;
 
struct Team
{
    int year;
    string teamID;
    string leagueID;
    int salary;
};
 
struct PlayerNode
{
    string firstName;
    string lastName;
    string playerID;
    int birthYear;
    string birthCountry;
    int weight;
    int height;
    string bats;
    string throws;
 
    vector<Team> team;
 
    PlayerNode *next;
    PlayerNode *previous;
 
    PlayerNode(){};
    PlayerNode(string firstNamel,string lastNamel, string playerIDl, int birthYearl, string birthCountryl, int weightl, int heightl, string batsl, string throwsl)
    {
        firstName=firstNamel;
        lastName=lastNamel;
        playerID=playerIDl;
        birthYear=birthYearl;
        birthCountry=birthCountryl;
        weight=weightl;
        height=heightl;
        bats=batsl;
        throws=throwsl;
        next = NULL;
        previous = NULL;
    }
};
 
class PlayerHashTable
{
public:
    PlayerHashTable();
    ~PlayerHashTable();
    int hashSum(string value, int tableSize);
    void searchChainHashTable(string firstName, string lastName);
    void searchOpenHashTable(string firstName, string lastName);
    void insertChainingPlayer(int yearID, string teamID, string leagueID, string playerID, int salary, string firstName, string lastName, int birthYear, string birthCountry, int weight, int height, string bats, string throws);
    void insertOpenPlayer(int yearID, string teamID, string leagueID, string playerID, int salary, string firstName, string lastName, int birthYear, string birthCountry, int weight, int height, string bats, string throws);
    int countChainingSearch;
    int countOpenSearch;
    int countChainingCollisions;
    int countOpenCollisions;
    int tablesize;
 
private:
    PlayerNode *hashTableChaining;
    PlayerNode *hashTableOpenAddress;
    vector<Team> info[20000];
};
#endif
