/**
 * Template of a competitive programmer
 *
 * https://gist.github.com/sumanth232/731704c76d7cee7ec71c
 */

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <cstring>
#include <cassert>
// #include<tr1/unordered_map>
using namespace std;

// typedef std::tr1::unordered_map<int,int> un_mapii;
typedef map<int,int> mapii;

#define GI ({int t;scanf("%d",&t);t;})
#define GD ({double t;scanf("%lf",&t);t;})
#define GF ({float t;scanf("%f",&t);t;})
#define GLL ({long long t;scanf("%lld",&t);t;})
#define GLD ({long double t;scanf("%Lf",&t);t;})

#define s(n) scanf("%d",&n)
#define sl(n) scanf("%ld",&n)
#define sll(n) scanf("%lld",&n)

#define sstr(str) scanf ("%s", str);

#define p(n) printf("%d ",n)
#define pl(n) printf("%ld ",n)
#define pll(n) printf("%lld ",n)

#define pf(n) printf("%f\n",n)
#define pd(n) printf("%lf\n",n)

#define pnl(n) printf("%d\n",n)
#define plnl(n) printf("%ld\n",n)
#define pllnl(n) printf("%lld\n",n)
#define nl() putchar_unlocked('\n')

#define ll long long
#define MAX(a,b) a>b?a:b
#define all(c) c.begin(), c.end()
#define rall(c) c.rbegin(), c.rend()    // reverse all
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
// #define tr(c,it) for(typeof(c.begin()) it = c.begin(); it !=c.end(); it++)
#define tr(c,it) for(auto it = c.begin(); it !=c.end(); it++)
#define ONES(X) __builtin_popcount((X))

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define forn(i, a, b) for(int i = (a); i < (b); ++i)
#define ford(i, a, b) for(int i = (a); i >= (b); --i)
#define fore(i, a, b) forn(i, a, b + 1)

typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector< vector<int> > vvi;
typedef vector<string> vstr;


#define sz(a) int((a).size())
#define szar(a) int(sizeof(ar)/sizeof(ar[0]))
#define osit ostream_iterator

void pvec(vi v)
{
  tr(v,it) { p(*it);}
  nl();
}

void pvec(vll v)
{
  tr(v,it) { pll(*it);}
  nl();
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
 {
    std::stringstream ss(s);                                            //  aa#bc#d -> aa, b,c,d
    std::string item;                                                   //  aa##c#d -> aa, "", c,d
    while (std::getline(ss, item, delim)) {                             //  aa#bc#  -> aa, bc, ""
        elems.push_back(item);                                          //  #a#b#   -> "", a, b, ""
    }
    if(s[s.size() - 1] == delim) elems.push_back("");
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

// CONSUMES THE NEW LINE CHARACTER AT THE END
inline int get()                  // working even in loops, working excellent
{
  char c;
  while(c=getchar_unlocked(),(c<'0'||c>'9')&&(c!='-'));
  bool Flag=(c=='-');
  if(Flag)
    c=getchar_unlocked();
  int X=0;
  while(c>='0'&&c<='9')
    {
      X=X*10+c-48;
      c=getchar_unlocked();
    }
  return Flag?-X:X;
}

// CONSUMES THE NEW LINE CHARACTER AT THE END
inline ll getll()                  // working even in loops, working excellent
{
  char c;
  while(c=getchar_unlocked(),(c<'0'||c>'9')&&(c!='-'));
  bool Flag=(c=='-');
  if(Flag)
    c=getchar_unlocked();
  ll X=0;
  while(c>='0'&&c<='9')
    {
      X=X*10+c-48;
      c=getchar_unlocked();
    }
  return Flag?-X:X;
}

// CONSUMES THE NEW LINE CHARACTER AT THE END
inline void get(char *str)

{
    register char c = 0;
    register int i = 0;
    while (c < 33)
        c = getchar_unlocked();

    while (c != '\n') {
        str[i] = c;
        c = getchar_unlocked();
        i = i + 1;
    }
    str[i] = '\0';

}

// DOES NOT PRINT NEW LINE CHARACTER
inline void output(int X)        // working even in loops, working excellent
{
  if(X<0)
    {
      putchar_unlocked('-');
      X=-X;
    }
  int Len=0,Data[10];
  while(X)
    {
      Data[Len++]=X%10;
      X/=10;
    }
  if(!Len)
    Data[Len++]=0;
  while(Len--)
    putchar_unlocked(Data[Len]+48);

  putchar_unlocked(' ');
}

// DOES NOT PRINT NEW LINE CHARACTER
inline void output(ll X)        // working even in loops, working excellent
{
  if(X<0)
    {
      putchar_unlocked('-');
      X=-X;
    }
  int Len=0,Data[10];
  while(X)
    {
      Data[Len++]=X%10;
      X/=10;
    }
  if(!Len)
    Data[Len++]=0;
  while(Len--)
    putchar_unlocked(Data[Len]+48);

  putchar_unlocked(' ');
}

template<class T>
void p2d(T c, int n,int m)
{
  nl();
  rep(i,n)
  {
    rep(j,m)
    {
      cout << c[i][j] << " ";
    }
    nl();
  }
}

int main()
{

// DONT USE FAST I/O METHODS when dealing with file input/ouput
// get() giving error if using the below file i/o

  /*#ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  #endif */


  return 0;
}
