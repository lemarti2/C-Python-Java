/*
  Filename   : Josephus.cc
  Author     : Leandro Martinez
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Josephus class, used to eliminate elements in a list of unsigned
  integers following a user input pattern.
*/
/************************************************************/
//System includes

#include <iostream>
#include <vector>
#include "List.hpp"

/************************************************************/

typedef unsigned uint;

/************************************************************/
//Using declarations

using std::cout;
using std::cin;
using std::endl;
using std::vector;

/************************************************************/

vector<int>
execute (List<int>& J, uint k);

int
main (int agrs, char* argv[])
{
  uint N;
  uint k;
  cout << "N ==> ";
  cin >> N;
  cout << "k ==> ";
  cin >> k;
  List<int> J;
  for(uint i = 1; i <= N; ++i)
  {
    J.push_back(i);
  }
  
  vector<int> V = execute(J, k);
  cout << "Execution order: ";
  for(uint i = 0; i < V.size()-1; ++i){
    cout << V[i] << ", ";
  }
  cout << V[V.size()-1] << endl;
  cout << "Survivor       : " << J.front();
  cout <<   endl;
  return EXIT_SUCCESS;
}

/************************************************************/
/*
  Assume N = 5, and k = 3. k will execute 3 * (N-1). In this case k will execute
  12 times since i = 0; i < k will run as far as N > 1; N = size.
  T(N) = (N-1)k;
  T(N) = Nk - k;
  In terms of Big O notation we can leave out (-k) and conclude O(Nk) since (-k)
  will have litte to no effect performance wise when it comes to large cases.
 */

/************************************************************/

vector<int>
execute (List<int>& J, uint k)
{
  vector<int> V;
  auto iter = J.end();	
  while( J.size() > 1) {
    for(uint i = 0; i < k; ++i){
      if(iter == --J.end()){
	iter++;
      }
      ++iter;
    }
    V.push_back(*iter);
    iter = J.erase(iter);
    --iter;
  }
  return V;
}

/************************************************************/

