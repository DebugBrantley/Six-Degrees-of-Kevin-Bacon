#include <vector> 
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <iomanip>
#include <map>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <string>

using std::unordered_map;
using std::list;
using std::pair;
using std::cout;
using std::endl;
using std::make_pair;
using std::for_each;
using namespace std;




class AdjList
{
private:

    typedef pair<string, string> edge;
    unordered_map<string ,list<edge>> adjList;

  
  
 
//this method is to use BFS to find the shortest path, and corrupt the pred map in order to navigate between the actors traversed and their 
//predecessor actors
void BFS(unordered_map<string , pair<string, string>> &pred, 
         unordered_map<string ,bool> visited, string actor1, string actor2)
{
     list<string> queue; //list based queue
     std::list<edge>::iterator it; //so we can touch the lists in the map
     unordered_map<string, bool>::iterator visited_it;

     pair<string, string> adj_node;
     pair<string, string> pred_pair;

  
      pred_pair.first = actor1;
      pred_pair.second = "a movie";
      pred[actor1] = pred_pair;
      queue.push_back(actor1);
      visited[actor1] = true;
      bool done = false;
// //      // standard BFS algorithm 
      while(!queue.empty()){
//         cout << "queue iteration" << endl;
        string currActor = queue.front();
        queue.pop_front();
        auto v = adjList.find(currActor);
        auto node = v->second;
//         //we must iterate through each node in the linked list in adjacency list
        for (it = node.begin(); it != node.end(); ++it) {

          adj_node = *it; //dereference it so now it holds the actor and the movie    
          visited_it = visited.find(adj_node.first); //go to the actor's location in the visited map 
          
          if(visited_it == visited.end()){ //if we haven't visited the actor yet
            visited[adj_node.first] = true;
            pred_pair.first = currActor;
            pred_pair.second = adj_node.second;
            pred[adj_node.first] = pred_pair;
            queue.push_back(adj_node.first);
          }
             if(adj_node.first == actor2)
                {     
                      done = true;
                      break;
                } 
                
            }
                if(done == true)
                { break; }
         }
            
} 
  
public:
  
void insertActor(string actor1, string actor2, string movie)
    {
      list<edge> A = adjList[actor1];
      A.push_back(make_pair(actor2, movie));
      adjList[actor1] = A;
    }
  
    
void printGraph()
  {
    for(auto i: adjList){
      cout << i.first;
      auto node = i.second; //node will point to the beginning of the linked list 
      std::list<edge>::iterator it; //iterates through each node connected to the actor at vertex i
      pair<string, string> poop;
      
      for (it = node.begin(); it != node.end(); ++it){
          poop = *it;
          string actor = poop.first;
          cout << "->" << actor;
      }    
      cout << "\n";
    }
  }
   
// utility function to print the shortest distance 
// between source vertex and destination vertex 
string findShortestDistance(string actor1, string actor2)
{
    unordered_map<string ,bool> visited; //create the visted map which stores a vertex name and true if it was visited
    unordered_map<string , pair<string, string>> pred; //create the pred map to store an actor, the vertex (currActor) we were at when we found it, 
                                                       //and movie that was paired with the actor stored
  
    //verify that boths entries are valid
    unordered_map<string, list<edge>>::iterator it1;
    unordered_map<string, list<edge>>::iterator it2;
    it1 = adjList.find(actor1);
    it2 = adjList.find(actor2);
    if (it1 == adjList.end()) //make sure the actor1 exists
        return "Not present";
    else if (it2 == adjList.end()) //make sure the actor2 exists
        return "Not present";
     
    //declaration of the variables we will use when creating our output string
    BFS(pred, visited, actor1, actor2); //call the BFS method so we can fill out the pred map
  
    if(pred.find(actor2) == pred.end()){
      return "Not present";
    }
  
    string outString; //this will store the output for the shortest path
    vector<string> path; // vector path stores the shortest path 
      
    string crawl = actor2; //crawl will save string value of the current predecessor actor 
    path.push_back(actor2); // the destination actor will be the first thing in the vector that represents the path
  
    while (crawl != actor1) { //keep going until the predecessor is = to actor1
          auto v = pred.find(crawl); //find the map location of crawl
          auto pred_movie_pair = v->second; //points to the string pair in the pred map
          string movie = pred_movie_pair.second; //the second value of the pair in the node should be the common movie between the actor and its predecessor
          string movie_string = " -(" + movie + ")- "; //create the movie string
          path.push_back(movie_string); //push back the movie
          string nextPredecessor = pred_movie_pair.first; //nextPredecessor = predecessor of the crawl
          path.push_back(nextPredecessor); //push back the previous actor in the shortest path       
          crawl = nextPredecessor; //crawl gets set to it's preceeding actor
    }

    //path.push_back(actor1);

    for (int i = path.size() - 1; i >= 0; i--) {
        outString += path[i];
    }
    return outString;
} 
  


}; 
  
  
  
  
  
int main(int argc, char** argv){
  
    ifstream file;
    string filename = "cleaned_movielist.txt";
    file.open(filename.c_str());
    string command;
    char *com, *valstr, *mov;
    AdjList actorList;
    while (getline(file, command))
    {
      if (command.length() == 0) // command is empty
            continue;
      
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        mov = strtok(com, " \t"); //tokenize command on whitespace to grab the movie title
        command = command.erase(0,strlen(mov)); //parse and save lower range bound    
        vector<string> theseActors;
      //grabs all of the actors
      while(command.length() > 1)
      {
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        valstr = strtok(com, " \t");
        command = command.erase(0,strlen(valstr) + 1);
        theseActors.push_back(valstr);
       
     }
      int length = int(theseActors.size());
      for(int i = 0; i<length; i++)
      {
        for(int j = 0; j<length; j++)
        {  
          if(j == i){ //don't create a edge with an actor pointing to itself
              continue;
            }
          else { //insert a new edge to the list with the actor at i, the actor at j, and the current movie
              string actor1 = theseActors.at(i);
              string actor2 = theseActors.at(j);
              actorList.insertActor(actor1, actor2, mov);
            }
      
        }
      }
    }
  
     file.close(); //close the input stream
  
//     actorList.printGraph();
    cout << "Done inserting!" << endl;
  
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
    }
  
    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
		
    while (getline(input, command))
    {
      if (command.length() == 0) // command is empty
            continue;
      
        com = strdup(command.c_str()); 
        mov = strtok(com, " \t"); // the first actor
        command = command.erase(0,strlen(mov)); //delete first word
        com = strdup(command.c_str()); 
        valstr = strtok(com, " \t"); // the second actor
      
      if(strcmp(valstr,mov) == 0){
        output << mov << "\n";
      }
      else
      {
       output << actorList.findShortestDistance(mov,valstr) << "\n";       
      }
    }
	
    
  
 input.close();
 output.close();

}