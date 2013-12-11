#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <queue>
#include <functional>
#include <list>
#include "vertex.h"
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
  map<char, int> pathlen; // <dest, dist from source to dest>
  char source;
  priority_queue<vertdist, vector<vertdist>, vertcmp> pq;
  list<char> seq;
  int numvert;
  vertdist srcdist;
  string contains = "";
  
  // init with some error checking
  if (argc != 3)
  {
    printf("Correct usage:  shortest <input file> <source vertex>\n");
    exit(1);
  }
  source = argv[2][0];
  input.open(argv[1]);
  while (input.peek() == COMMENT)	// removing comment lines
    input.getline(tmpstr, 80);
  input >> gtype;
  while (!input.eof())
  {
    char f, t;
    int w;
    input >> f;
    input >> t;
    input >> w;
    
    adj[f][t] = w;
    if (gtype == UNDIRECTED) adj[t][f] = w;
    if (contains.find(f) == -1) contains += f;
    if (contains.find(t) == -1) contains += t;
  }
  if (contains.find(source) == -1)
  {
    printf("Source does not exist in graph, or has out degree of 0.\n");
    exit(1);
  }

  // actual dijkstra code... finally 
  printf("Dijkstra:\nSource: %c\n", source);
  numvert = contains.size();
  srcdist.vert = source;
  srcdist.dist = 0;
  pq.push(srcdist);
  pathlen[srcdist.vert] = srcdist.dist;
  for (int i = 0; i < numvert; ++i)
  {
    if (contains[i] != source)
    {
      vertdist tmp(contains[i], 1000);
printf("Pushing '%c' to pq with weight of %d\n", tmp.vert, tmp.dist);
      pathlen[tmp.vert] = tmp.dist;
printf("pathlen[%c] = %d\n", tmp.vert, pathlen[tmp.vert]);
      pq.push(tmp);
    }
  }
  while (!pq.empty())
  {
    vertdist tmp = pq.top();
printf("Popping '%c' from pq with weight %d\n", tmp.vert, tmp.dist);
    pq.pop();
    //pathlen[tmp.vert] = tmp.dist;
printf("pathlen[%c] = %d\n", tmp.vert, pathlen[tmp.vert]);
    //seq.push_back(tmp);
    if (adj[source].find(tmp.vert) != adj[source].end())
    {
      if (pathlen[tmp.vert] > adj[source][tmp.vert])
        pathlen[tmp.vert] = adj[source][tmp.vert];
    }
    for (map<char, int>::iterator it = adj[tmp.vert].begin();
         it != adj[tmp.vert].end();
         ++it)
    {
printf("pathlen[%c] = %d\n", it->first, pathlen[it->first]);
printf("pathlen[%c] = %d\n    + %c -> %c = %d\n", tmp.vert, pathlen[tmp.vert], tmp.vert, it->first, adj[tmp.vert][it->first]);
      if (pathlen[it->first] >
          (pathlen[tmp.vert] + adj[tmp.vert][it->first]))
      {
printf("Switched!\n");
        pathlen[it->first] = (pathlen[tmp.vert] + adj[tmp.vert][it->first]);
      }
      else
      {
        if (adj[source].find(it->first) != adj[source].end())
        {
          if (pathlen[it->first] > adj[source][it->first])
            pathlen[it->first] = adj[source][it->first];
        }
      }
    }
  }

  for (map<char, int>::iterator itr = pathlen.begin(); 
       itr != pathlen.end(); 
       ++itr)
  {
    printf("NODE %c : %d\n", itr->first, itr->second);
  }
  printf("End Dijkstra\n");  

  input.close();
  return 0;
}
