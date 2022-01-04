/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"
// #include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS
   
     
     
   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }
	 //================================
   // When working on Checkpoint 3, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
  
   result = maze_search(mymaze, rows, cols); // <--- TASK: CHANGE THIS
	
	
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

	 //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated

  for(int i = 0; i < rows; i++){
    delete []mymaze[i];
  }
  delete []mymaze;
  
  
  
  
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  // *** You complete *** 

  int scount = 0; 
  int fcount = 0; 
  bool solved = true;
  
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(maze[i][j] == 'S'){
        scount++;
       }
     }
   }
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(maze[i][j] == 'F'){
         fcount++; 
      }
    }
  }
  if(scount !=1 || fcount !=1){
    return -1; 
  }
  Queue q(rows*cols);
  Location s; 
  Location e;
 
  
  for(int i = 0;i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(maze[i][j] == 'S'){
        int row1_inital = i;
        int col1_inital = j;
      }
    }
  }
  s.row = row1_inital;
  s.col = col1_inital;
  
   for(int i = 0;i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(maze[i][j] == 'F'){
        int row1_end = i;
        int col1_end = j;
      }
    }
  } 
  e.row = row1_end;
  e.col = col1_end;
  
  q.add_to_back(s);
  
  bool** isMaze = new bool*[rows];
  for(int i = 0; i <rows; i++ ){
    isMaze[i] = new bool[cols];
  }
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      isMaze[i][j] = true; 
    }
  }
  
  isMaze[row1_inital][col1_inital] = false;
  
  Location** track = new Location* [rows];
  for(int i = 0; i < rows; i++){
    track[i] = new Location[cols];
  }
  
  
  Location instantiate;
  instantiate.row = 0;
  instantiate.col = 0;
  
  
  for(int i = 0; i< rows; i++){
    for(int j = 0; j < cols; j++){
      track[i][j] = instantiate;
    }
  }

  while(!(q.is_empty()) && solved){
    Location loc = q.remove_from_front();
    
    //cout<<loc.row<<","<<loc.col<<endl;
    Location current;
    
    if(((loc.row)==e.row) && ((loc.col)==e.col)){
      solved = false;
      break;
    } 
    
    if((loc.row +1) < rows && maze[loc.row+1][loc.col] != '#' && isMaze[loc.row +1][loc.col] == true){ //South
         current.row = loc.row + 1; 
         current.col = loc.col; 
         q.add_to_back(current);
         track[current.row][current.col] = loc;
         isMaze[current.row][current.col] = false;
         
    }
    if((loc.row -1) >= 0 && maze[loc.row-1][loc.col]!= '#' && isMaze[loc.row -1][loc.col] == true){//North  
        current.row = loc.row - 1; 
        current.col = loc.col; 
        q.add_to_back(current);
        track[current.row][current.col] = loc;
        isMaze[current.row][current.col] = false;
    
    }   
    if((loc.col +1) < cols && isMaze[loc.row][loc.col+1] == true && maze[loc.row][loc.col+1]!= '#' ){ //East
      
      current.row = loc.row; 
      current.col = loc.col + 1; 
      q.add_to_back(current);
      track[current.row][current.col] = loc;
      isMaze[current.row][current.col] = false;
      
    }
    if((loc.col -1) >= 0 && isMaze[loc.row][loc.col-1] == true && maze[loc.row][loc.col-1]!= '#' ){ //West
      current.row = loc.row; 
      current.col = loc.col - 1;
      q.add_to_back(current);
      track[current.row][current.col] = loc;
      isMaze[current.row][current.col] = false;
      
    }
 }
  
    if(solved == true){
      return 0;
     }
 
  Location flag; 
  flag = e;
  while(maze[flag.row][flag.col] != maze[s.row][s.col]){
    flag = track[flag.row][flag.col];
    maze[flag.row][flag.col] = '*';  
    if(flag.row == s.row && flag.col == s.col){
      maze[flag.row][flag.col]='S';
    }
  }
  
  //while((flag.row!=s.row) && (flag.col!=s.col))
  
  for(int i = 0; i < rows; i++){
    delete []isMaze[i];
  }
  for(int i = 0; i < rows; i++){
    delete []track[i];
  }
  delete []isMaze;
  delete []track; 
  
  
  
  return 1;
  
}
       
       
       
