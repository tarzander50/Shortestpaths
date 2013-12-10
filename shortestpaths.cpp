#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
using namespace std;

const char COMMENT = '#';
const string DIRECTED = "D";
const string UNDIRECTED = "UD";

int main(int argc, char* argv[])
{
  ifstream input;
  char tmpstr[80];
  string gtype;
  map<char, map<char, int> > adj; // <from <to, weight> >
  
  if (argc != 1)
  {
    printf("Must include .txt file as command line arg!");
    exit(1);
  }
  input.open(argv[1]);
  while (input.peek() == COMMENT)	// removing comment lines
    input.getline(tmpstr, 80);
  input >> gtype;
  
  printf("Shortest paths program!\n");

  while (!input.eof())
  {
    char f, t;
    int w;
    input >> f;
    input >> t;
    input >> w;
    
    adj[f][t] = w;
    if (gtype == UNDIRECTED)
    {
      adj[t][f] = w;
    }
  }

  input.close();
  return 0;
}
