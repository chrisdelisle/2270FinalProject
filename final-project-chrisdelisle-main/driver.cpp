/**
 driver.cpp
 Chris Delisle
 includes main function
 **/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu(MovieHashTable &movieTable, DirectorSkipList &list);


//./a.out IMDB-Movie-Data.csv 100 100
// Main function
int main(int argc, char* argv[]) {
    // TODO

    //if invalid arguments
    if(argc != 4)
    {
        cout << "Invalid Number of Arguments!"  << endl;
        return 0;
    }

    //recieves command line arguments
    string filename = argv[1];
    int hashSize = atoi(argv[2]);
    int skipSize = atoi(argv[3]);

    MovieHashTable table = MovieHashTable(hashSize); //creates table
    DirectorSkipList directorList = DirectorSkipList(skipSize, DEFAULT_LEVELS); //creates list

    
    //fills in table and list from file
    readMovieCSV(filename, table, directorList);

    //calls display menu
    display_menu(table, directorList);


    //calls destructor once quit
    table.~MovieHashTable();
    
    //calls destructor once quit
    directorList.~DirectorSkipList();

    
    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// readMovieCSV - Function to read a CSV file into a vector of MovieNode objects
// @ param filename, movieTable, directorList
// @return void
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // TODO

    ifstream file;
    string line;
     file.open(filename);
     if(!file.is_open()) //checks if file is open
     {
        return;
     }


    getline(file, line);

    while(getline(file, line)) //goes through every line of file
    {
       
        MovieNode *curr = parseMovieLine(line); //uses parseMovieLine to create a movie node with each line
        if(curr != nullptr)
        {
            movieTable.insert(curr->title, curr); //inserts into table
            directorList.insert(curr->director, curr); //insearts into list
        }
    }

    file.close(); //closes file

}

// diplsay_menu - displays menu and loops with options until closed
// Function to display the menu options
//@ param table, list
// return void
void display_menu(MovieHashTable &table, DirectorSkipList &list) {
    // TODO
    string option;

    //inital menu
    cout << "Number of collisions: " << table.getCollisions() << endl;

    cout << "Please select an option:" << endl;
    cout << "1). Find the director of a movie" << endl;
    cout << "2). Find the number of movies by a director" << endl;
    cout << "3). Find the description of a movie" << endl;
    cout << "4). List the movies by a director" << endl;
    cout << "5). Quit" << endl;
    cout << "" << endl;
    cout << "Enter an option:" << endl;

    getline(cin, option); //recieves user input

    bool run = true;

    while(run) //runs until run is set to false
    {
    
    //find director
    if(option == "1")
    {
        string name;
        cout << "Enter movie name: ";
        getline(cin, name);
        cout << endl;
        MovieNode *n = table.search(name); //searches for director by movie name

        if(n == nullptr) //if not found
        {
            cout << "That movie does not exist in the data file." << endl;
        }

        else //if found
        {
            cout << "The director of " << name << " is " << n->director << endl;
        }
        cout << endl;

        //shows menu again
        cout << "Please select an option:" << endl;
        cout << "1). Find the director of a movie" << endl;
        cout << "2). Find the number of movies by a director" << endl;
        cout << "3). Find the description of a movie" << endl;
        cout << "4). List the movies by a director" << endl;
        cout << "5). Quit" << endl;
        cout << "" << endl;
        cout << "Enter an option:" << endl;

        getline(cin, option);
        
    }

    //find movies by director
    else if(option == "2")
    {
        cout << "Enter director name: ";
        string name;
        getline(cin, name);

        cout << endl;

        if(list.search(name) != nullptr) //if director is found
        {
            int num = list.search(name)->movies.size();
            cout << name << " has directed " << num << " movies" << endl;
        }
        else{ //if director is not found in list
            cout << name << " has not directed any movies in the list." << endl;
        }

        cout << endl;
        //shows menu
        cout << "Please select an option:" << endl;
        cout << "1). Find the director of a movie" << endl;
        cout << "2). Find the number of movies by a director" << endl;
        cout << "3). Find the description of a movie" << endl;
        cout << "4). List the movies by a director" << endl;
        cout << "5). Quit" << endl;
        cout << "" << endl;
        cout << "Enter an option:" << endl;

        getline(cin, option);
    }

    else if(option == "3")
    {
        //find movie description by movie name
        cout << "Enter movie name: ";
        string name;
        getline(cin, name);
        MovieNode *movie = table.search(name);
        if(movie != nullptr) //if movie is found
        {
        cout << movie->description << endl; //prints desc.
        }
        else{ //if movie is not found
            cout << name << " does not exist in the list." << endl;
        }

        cout << endl;

        //shows menu
        cout << "Please select an option:" << endl;
        cout << "1). Find the director of a movie" << endl;
        cout << "2). Find the number of movies by a director" << endl;
        cout << "3). Find the description of a movie" << endl;
        cout << "4). List the movies by a director" << endl;
        cout << "5). Quit" << endl;
        cout << "" << endl;
        cout << "Enter an option:" << endl;

        getline(cin, option);

    }


    else if(option == "4")
    {
        //find all movies directed by a director
        cout << "Enter director name: ";
        string name;
        getline(cin, name);
        cout << endl;

        if(list.search(name) == NULL) //if name is not in list
        {
            cout << "The director does not exist in the list" << endl;
        }
        else{ //if name is found
        cout << name << " directed the following movies:" << endl;
        for(int i = 0; i < list.search(name)->movies.size(); i++) //loops through director's movie size
        {
            cout << i + 1 << ": " << list.search(name)->movies[i]->title << endl;
        }
        }

        cout << endl;

        //shows menu
        cout << "Please select an option:" << endl;
        cout << "1). Find the director of a movie" << endl;
        cout << "2). Find the number of movies by a director" << endl;
        cout << "3). Find the description of a movie" << endl;
        cout << "4). List the movies by a director" << endl;
        cout << "5). Quit" << endl;
        cout << "" << endl;
        cout << "Enter an option:" << endl;

        getline(cin, option);

    }

    //if user wants to quit
    else if(option == "5") 
    {
        cout << "Quitting... Goodbye." << endl;
        run = false; //ends loop

        break; //ends loop
    }

    //if 1-5 are not entered
    else
    {
        cout << "Enter a valid option (1-5):" << endl;
        getline(cin, option);
    }


    }


    return; //ends function


}
