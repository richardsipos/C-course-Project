// A set_multi_util osztály template, ami
// a konstruktorában megadott std::set-et bővíti ki úgy logikailag, hogy az
// elemeknek valódi multiplicitása lehessen. A set elemei kezdetben 1-es
// multiplicitással rendelkeznek, de újabb elemeket lehet a set-hez adni.
// Ha ezen keresztül új elem kerül az adatszerkezetbe, akkor az a std::set
// objektumba is be fog kerülni. Törölni többféleképpen is lehet:
// erase_one_element egy elemet töröl az adatszerkezetből: eggyel csökken a
// multiplicitása, ha pedig a multiplicitás nulla, akkor a set-ből is törölni
// kell. Az erase tagfüggvények egyből az összes multiplicitást törlik az
// adatszerkezetből: kulcsot, az std::set iterátora által mutatott értéket,
// illetve az std::set egy intervallumát.


#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include "setmulti.h"
#include <string>
#include "setmulti.h"
#include <functional>

const int max = 1000;

bool check()
{
  std::set<int> si;
  for( int i = 0; i < max; ++i )
  {
    si.insert( i );
  }

  set_multi_util<int> us( si );
  for( int i = 0; i <= max; ++i )
  {
    us.insert( i );
  }

  std::set<std::string> st;
  st.insert( "C++" );
  st.insert( "Ada" );
  st.insert( "Pascal" );
  set_multi_util<std::string> ust( st );
  ust.insert( "Ada" );
  ust.insert( "Ada" );
  ust.insert( "Ada" );
  ust.insert( "Pascal" );
  const set_multi_util<std::string> cust( ust );

  if ( 4 != ust.count( "Ada" ) || 0 != ust.count( "C" ) ||
       1 != ust.count( "C++" ) || 1 != si.count( max ) ||
       2 != cust.count( "Pascal" ) || 1 != si.count( 1 ) ||
       2 != us.count( max / 2 ) || 1 != us.count( max ) ||
       1 != st.count( "Ada" ) || 1 != st.count( "Pascal" ) ||
       max + 1 != si.size() || 3 != st.size() )
  {
    return false;
  }

  ust.erase_one_element( "Ada" );
  ust.erase_one_element( "Ada" );
  ust.erase_one_element( "C++" );
  ust.insert( "Python" );
  ust.insert( "Python" );
  ust.erase( "Python" );

  us.erase( 0 );
  us.erase_one_element( 1 );

  if ( 1 != si.count( max / 2 ) || 2 != us.count( max / 2 ) ||
       2 != ust.count( "Ada" ) || 0 != st.count( "Python" ) ||
       0 != ust.count( "Python" ) || 0 != st.count( "C++" ) ||
       0 != ust.count( "C++" ) || 4 != ust.size() ||
       1 != si.count( 1 ) || 1 != us.count( 1 ) || 0 != si.count( 0 ) )
  {
    return false;
  }

  ust.insert( "Ada" );
  ust.insert( "C++" );
  ust.insert( "C++" );
  ust.insert( "Python" );
  ust.insert( "Python" );
  ust.insert( "Fortran" );
  ust.insert( "Fortran" );
  ust.insert( "Haskell" );
  ust.insert( "Objective-C" );
  ust.insert( "Objective-C" );
  ust.insert( "Cobol" );
  ust.erase( st.find( "Fortran" ), st.find( "Objective-C" ) );
  ust.erase( st.find( "Cobol" ) );
  ust.erase( st.find( "Python" ) );

  us.erase( si.find( 1 ), si.find( max / 2 ) );
  us.erase( si.find( max / 2 ) );

  return ( 0 == ust.count( "Cobol" ) && 2 == ust.count( "C++" ) &&
       0 == ust.count( "Haskell" ) && 3 == ust.count( "Ada" ) &&
       0 == ust.count( "Fortran" ) && 0 == us.count( max / 3 ) &&
       0 == si.count( max / 2 ) && 2 == us.count( max - 1 ) );
}

int main()
{
  std::cout
    << "Your solution is "
    << (check() ? "" : "not ")
    << "ready for submission."
    << std::endl;
}