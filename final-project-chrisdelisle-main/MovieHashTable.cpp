/**
 MovieHashTable.cpp
 .cpp file for the MovieHashTable and MovieNode class
 **/

#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// MovieHashTable - Default Constructor for MovieHashTable with default size
// sets private variables of a MovieHashTable to default sizes
MovieHashTable::MovieHashTable() {
    // TODO
   
    //default values
    table_size = DEFAULT_HTABLE_CAPACITY;

    table = new MovieNode *[table_size];
    for(int i = 0; i < table_size; i++)
    {
        table[i] == nullptr; //sets each index value to null
    }

    n_collisions = 0; //sets initial collisions to 0

}

// MovieHashTable - Constructor for MovieHashTable with given inpu size
// sets private variables of a MovieHashTable to input and default sizes
// @param s
MovieHashTable::MovieHashTable(int s) {
    // TODO
    //sets to default values, with the exception of a desired number s of the table size
    table_size = s;
    
    n_collisions = 0;

    table = new MovieNode *[table_size];

    for(int i = 0; i < s; i++)
    {
        table[i] = nullptr;
    }

}


// ~MovieHashTable - Destructor for MovieHashTable that deletes all nodes in the hash table
MovieHashTable::~MovieHashTable() {
    // TODO

//traverses through table deleting memory
    for(int i = 0; i < table_size; i++)
    {
        MovieNode *curr = table[i];
        while(curr != nullptr)
        {
            MovieNode * tmp = curr; //deletes each node at the index
            curr = curr->next;
            delete tmp;
        }
        table[i] = nullptr;
    }


}

// Hash - function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
//@ param title
//@return int sum
int MovieHashTable::hash(string title) {
    // TODO

    int sum = 0;

    for(int i = 0; i < title.length(); i++)
    {
        sum += title[i]; //converts each char to an int, added to a sum
    }

    //create key
    sum = sum % 110483520; //modded by identikey
    sum = sum % table_size; //modded by table_size

    return sum;
}

// insert - Inserts a movie node into the hash table with the specified title
// @param title, movie
// @ return void
void MovieHashTable::insert(string title, MovieNode* movie) {
    // TODO

    MovieNode *mov = search(title); //checks to see if movie exists already
    
    if(mov != nullptr) //if it does exist
    {
        return;
    }

    int index = hash(title); //creates index using hash function


    if(table[index] == nullptr) //if the location is empty
    {
        table[index] = movie; //adds movie
    }
    else{ //if it is not empty/collision occurs
        
        //chaining for collision
        MovieNode * curr = table[index];
        while(curr->next != nullptr)//traverse the linked list at the index, until it is null/empty
        {
            curr = curr->next;
        }
        curr->next = movie; //adds the movie to the empty spot
        setCollisions(); //calls setCollsions, to increase collisions
    }

}

// Search - Searches for a node in the hash table with the specified title
// @param title
// @return MovieNode
MovieNode* MovieHashTable::search(string title) {
    // TODO
    int ind = hash(title); //finds the index title would be at

    if(table[ind] == NULL) //if the key is null (poor input)
    {
        return NULL;
    }

    if(table[ind]->title == title) //if the index's first movie is the desired movie
    {
        return table[ind];
    }

    //if the index's initial movie is not the desired, taverse the index's linked list
    MovieNode* curr = table[ind];
    while(curr != nullptr) //goes through the linked list in that index until it reaches end/nullptr
    {
        if(curr->title == title) //if current node in LL has the same title
        {
            return curr; //returns that MovieNode
        }
        curr = curr->next;
    }
    //if never found, return nullptr
    return nullptr;
}

// getCollisions - Returns the number of collisions that have occurred during insertion into the hash table
// @return int
int MovieHashTable::getCollisions() {
    // TODO
    return n_collisions;
}

// setCollisions - Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() {
    // TODO
    n_collisions++; //increases by one
}
