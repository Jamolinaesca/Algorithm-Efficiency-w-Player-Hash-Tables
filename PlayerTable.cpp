#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "PlayerTable.h"
using namespace std;
 
PlayerHashTable::PlayerHashTable()
{
    hashTableChaining = new PlayerNode[tablesize];
    hashTableOpenAddress = new PlayerNode[tablesize];
    countChainingSearch = 0;
    countOpenSearch = 0;
    countChainingCollisions = 0;
    countOpenCollisions = 0;
 
    for(int i=0 ; i < tablesize ; i++)
    {
        hashTableChaining[i] = NULL;
    }
    for(int i=0 ; i < tablesize ; i++)
    {
        hashTableOpenAddress[i] = NULL;
    }
}
 
int PlayerHashTable::hashSum(string value, int tableLen)
{
    int sum = 0;
    for (int i = 0; i < value.length(); i++){
    if(i%2==0)
        sum = sum + value[i];
    }
    sum = sum % tableLen;
    return sum;
}
 
void PlayerHashTable::insertChainingPlayer(int year, string teamID, string leagueID, string playerID, int salary, string firstName, string lastName, int birthYear, string birthCountry, int weight, int height, string bats, string throws)
{
    string player = firstName+lastName;
    PlayerNode* newPlayer = new PlayerNode(firstName,lastName,playerID,birthYear,birthCountry,weight,height,bats,throws);
    int index = hashSum(player, tablesize);
 
    Team v;
    v.leagueID = leagueID;
    v.salary = salary;
    v.teamID = teamID;
    v.year = year;
 
    if(hashTableChaining[index] == NULL)
    {
        hashTableChaining[index] = newPlayer;
        hashTableChaining[index]->team.push_back(v);
        return;
    }
    else
    {
        PlayerNode *temp = hashTableChaining[index];
        while(temp->next != NULL)
        {
            if(temp->playerID == playerID)
            {
                temp->team.push_back(v);
                return;
            }
            temp = temp->next;
        }
 
        PlayerNode *newPlayer2 = newPlayer;
        newPlayer2->previous = temp;
        temp->next = newPlayer2;
        newPlayer2->team.push_back(v);
        countChainingCollisions++;
    }
}
 
void PlayerHashTable::searchChainHashTable(string firstNamel, string lastNamel)
{
    string player = firstNamel+lastNamel;
    int index = hashSum(player, tablesize);
 
    if(hashTableChaining[index] == NULL)
    {
        cout << "Player not found" <<endl;
        return;
    }
 
    while(hashTableChaining[index] != NULL)
    {
        if(hashTableChaining[index]->firstName + hashTableChaining[index]->lastName == player)
        {
            cout << endl;
            cout<<"Chaining Hash Table: " <<endl;
            cout<<"First name: "<<hashTableChaining[index]->firstName<<endl;
            cout<<"Last name: "<<hashTableChaining[index]->lastName<<endl;
            cout<<"Year born: "<<hashTableChaining[index]->birthYear<<endl;
            cout<<"Country born: "<<hashTableChaining[index]->birthCountry<<endl;
            cout<<"Weight: "<<hashTableChaining[index]->weight<<endl;
            cout<<"Height: "<<hashTableChaining[index]->height<<endl;
            cout<<"Bats: "<<hashTableChaining[index]->bats<<endl;
            cout<<"Throws: "<<hashTableChaining[index]->throws<<endl<<endl;
            cout<<"Teams and salary:"<<endl;
 
            for(int i = 0 ; i < hashTableChaining[index]->team.size(); i++)
            {
                cout <<hashTableChaining[index]->team[i].year<< "," << hashTableChaining[index]->team[i].teamID << "," << hashTableChaining[index]->team[i].leagueID << "," << hashTableChaining[index]->team[i].salary << endl;
            }
            cout <<endl;
 
            cout << "Hash table size: " << tablesizechaining << endl;
            cout << "Collisions using chaining: " << countChainingCollisions << endl;
            cout << "Search operations using chaining: " << countChainingSearch << endl << endl;
            return;
        }
        countChainingSearch++;
        hashTableChaining[index] = hashTableChaining[index]->next;
    }
}
 
void PlayerHashTable::insertOpenPlayer(int year, string teamID, string leagueID, string playerID, int salary, string firstName, string lastName, int birthYear, string birthCountry, int weight, int height, string bats, string throws)
{
    string name = firstName+lastName;
    int index = hashSum(name,tablesizeopen);
 
    Team *v;
    v = new Team;
    v->year=year;
    v->teamID=teamID;
    v->leagueID=leagueID;
    v->salary=salary;
 
    //case1: if a person haven't been added
    if(hashTableOpenAddress[index]==NULL)
    {
        hashTableOpenAddress[index] = new PlayerNode(firstName,lastName,playerID,birthYear,birthCountry,weight,height,bats,throws);
        info[index].push_back(*v);
        //hashTableOpenAddress[index]->team.push_back(*v);
        return;
    }
    int current=index;
    while(hashTableOpenAddress[current]!=NULL)
    {
        //case2: if a person haven been added the same record, return "This record has been added" or if the different record
        if(hashTableOpenAddress[current]->firstName==firstName && hashTableOpenAddress[current]->lastName == lastName)
        {
 
            for(int i=0 ; i<info[current].size() ;i++)//hashTableOpenAddress[current]->team.size()
            {
                if(info[current][i].year==v->year && info[current][i].salary==v->salary && info[current][i].leagueID==v->leagueID && info[current][i].teamID==v->teamID)
                    return;
            }
            info[current].push_back(*v);
            return;
        }
 
        if(current==tablesizeopen)
            current=0;
        current++;
 
        if(current==index)
            break;
 
    }
 
    if(hashTableOpenAddress[current]==NULL)
    {
        countOpenCollisions++;
        hashTableOpenAddress[current] = new PlayerNode(firstName,lastName,playerID,birthYear,birthCountry,weight,height,bats,throws);
        info[current].push_back(*v);
 
        return;
    }
}
 
void PlayerHashTable::searchOpenHashTable(string first,string last)
{
    countOpenSearch=0;
    string name = first+last;
    int index = hashSum(name, tablesizeopen);
    int current = index+1;
 
    if(hashTableOpenAddress[index]==NULL)
    {
        cout<<"Player not found"<<endl;
        return;
    }
 
    if(hashTableOpenAddress[index]->firstName+hashTableOpenAddress[index]->lastName==name)
    {
        cout << endl;
        cout<<"Open Address Hash Table: " <<endl;
        cout<<"First name: "<<hashTableOpenAddress[index]->firstName<<endl;
        cout<<"Last name: "<<hashTableOpenAddress[index]->lastName<<endl;
        cout<<"Year born: "<<hashTableOpenAddress[index]->birthYear<<endl;
        cout<<"Country born: "<<hashTableOpenAddress[index]->birthCountry<<endl;
        cout<<"Weight: "<<hashTableOpenAddress[index]->weight<<endl;
        cout<<"Height: "<<hashTableOpenAddress[index]->height<<endl;
        cout<<"Bats: "<<hashTableOpenAddress[index]->bats<<endl;
        cout<<"Throws: "<<hashTableOpenAddress[index]->throws<<endl<<endl;
        cout<<"Teams and salary:"<<endl;
 
        for(int i=0 ; i<info[index].size(); i++)
        {
            cout<<info[index][i].year<<","<<info[index][i].teamID<<","<<info[index][i].leagueID<<","<<info[index][i].salary<<endl;
        }
        cout <<endl;
 
        cout << "Hash table size: " << tablesizeopen << endl;
        cout << "Collisions using open addressing: " << countOpenCollisions << endl;
        cout << "Search operations using open addressing: " << countOpenSearch << endl;
 
        return;
    }
    else
    {
        while(hashTableOpenAddress[current]!=NULL && current!=index)
        {
 
            if(hashTableOpenAddress[current]->firstName+hashTableOpenAddress[current]->lastName==name)
            {
                cout << endl;
                cout<<"Open Address Hash Table: " <<endl;
                cout<<"First name: "<<hashTableOpenAddress[index]->firstName<<endl;
                cout<<"Last name: "<<hashTableOpenAddress[index]->lastName<<endl;
                cout<<"Year born: "<<hashTableOpenAddress[index]->birthYear<<endl;
                cout<<"Country born: "<<hashTableOpenAddress[index]->birthCountry<<endl;
                cout<<"Weight: "<<hashTableOpenAddress[index]->weight<<endl;
                cout<<"Height: "<<hashTableOpenAddress[index]->height<<endl;
                cout<<"Bats: "<<hashTableOpenAddress[index]->bats<<endl;
                cout<<"Throws: "<<hashTableOpenAddress[index]->throws<<endl<<endl;
                cout<<"Teams and salary:"<<endl;
 
                for(int i=0 ; i<info[index].size(); i++)
                {
                    cout<<info[index][i].year<<","<<info[index][i].teamID<<","<<info[index][i].leagueID<<","<<info[index][i].salary<<endl;
                }
                cout <<endl;
 
                cout << "Hash table size: " << tablesizeopen << endl;
                cout << "Collisions using open addressing: " << countOpenCollisions << endl;
                cout << "Search operations using open addressing: " << countOpenSearch << endl;
                return;
            }
 
            if(current==tablesizeopen)
                current=0;
            current++;
            countOpenSearch++;
        }
    }
}
 
PlayerHashTable::~PlayerHashTable(){
}
