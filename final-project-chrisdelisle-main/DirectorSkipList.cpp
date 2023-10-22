/**
 DirectorSkipList.cpp
 .cpp file for the DirectorSkipList class
 **/

#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

/**DirectorSkipList - default constructor for a DirectorSkipList Object
 * sets values to default
 */

DirectorSkipList::DirectorSkipList() {
    // TODO
    head = new DirectorSLNode();
    head->next = vector<DirectorSLNode*>(levels, nullptr);
    head->director = "";
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
}

// DirectorSkipList - constructor for DirectorSkipList object 
// defaults values to desired input valuts
// @param _cap, _levels

DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    // TODO
    capacity = _cap;
    levels = _levels;
    head = new DirectorSLNode();
    head->director = "";
    head->next = vector<DirectorSLNode*>(levels, nullptr);
}

// ~DirectorSkipList - destructor 
// deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)

DirectorSkipList::~DirectorSkipList() {
    // TODO
    for(int i = 0; i < size; i++)
    {
        DirectorSLNode * tmp = head; //starts at head
        head = head->next.at(i); //moves head to next index in vector
        delete tmp; //deletes previous index
    }
}

// insert - Inserts a movie node into the skip list with the specified director
// @param director, _movie
// @return void
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    // TODO

    //points to head to start at start of skiplist
    DirectorSLNode *tmp = search(director);
    if(tmp != NULL && tmp->director == director) //if movie / director are not in list already
    {
        tmp->addMovie(_movie); //adds movie
        return;
    }

    int n_levels = 1;
    while(n_levels < levels && rand() % 2 ==0) //decide how many levels this node will appear in/height (keeps general balance)
    {
        n_levels++;
    }

    DirectorSLNode * d = new DirectorSLNode(director, n_levels);
    d->addMovie(_movie);

    DirectorSLNode *curr = head;

    vector <DirectorSLNode*> prev = vector <DirectorSLNode*>(levels + 1, nullptr); //creating vector to store data in front of insertion

    

    for(int i = levels - 1; i >= 0; i--) //accounts for all levels, starting at upper
    {
        //goes across each node in the current level
        //if current list director name is less (alphabetically) than desired, continue to traverse
        while(curr->next[i] != nullptr && curr->next[i]->director < director) 
        {
            curr = curr->next[i];
        }
        prev[i] = curr; //after finding location of desired director, set the new "prev" list to the current
    }

    curr = curr->next[0]; //sets current to the next lists level 0 (director)

    if(curr != nullptr && curr->director == director) //if it is not null, and at the right director
    {
       curr->addMovie(_movie); //add movie
    }
    else{ //if the next is null (essentially adding new director to end) or the director is not already in the list
       
        //creates new list to be added(director)

        
        for(int i = n_levels - 1; i >= 0; i--)
        {
            d->next[i] = prev[i]->next[i]; //adds everything before the added director, before the added director
            prev[i]->next[i] = d; //makes everything before the new director (prev)'s ->next (what will come after) to the new node
        }

        //n->addMovie(_movie); // adds movie to newly added node
       // size++; //increases size as new node is added
    }

}

// DirectorSkipList - Searches for a node in the skip list with the specified director
// @param director
// @ return DirectorSLNode
DirectorSLNode *DirectorSkipList::search(string director) {
    // TODO

    DirectorSLNode * curr = head; //sets a current point to the start

    for(int i = levels -1; i >= 0; i--) //accounts for all levels, going down
    {
        while(curr->next[i] != nullptr && curr->next[i]->director < director) //goes while alphabetically less than the desired director
        {
            curr = curr->next[i];
        }
    }

    curr = curr->next[0]; //once found, sets curr pointer to index/level 0 (the director)

    if(curr != nullptr && curr->director == director) //checks to make sure it found the director
    {
        return curr; //returns desired director node
    }
    else{
        return nullptr;
    }

   
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() {
    // TODO

    DirectorSLNode *curr = head;
    for(int i = levels -1; i >= 0; i--) //goes through each level
    {
        cout << "Level " << i << ": ";
        while(curr->next[i] != nullptr) //goes though each node in a level
        {
            cout << curr->director << " ";
            curr = curr->next[i];
        }
        cout << endl;
    }

    
}
