#ifndef __VERTEX_H_
#define __VERTEX_H_

class vertdist
{
public:
  int dist;
  char vert;
  vertdist(){}
  vertdist(char c, int i): vert(c), dist(i){}
};

class vertcmp
{
public:
  bool operator()(const vertdist& lhs, const vertdist& rhs) const
  {
    return (lhs.dist > rhs.dist);
  }
};

#endif
