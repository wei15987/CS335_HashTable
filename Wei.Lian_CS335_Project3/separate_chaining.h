/*******************************************************************************
  Title          : separate_chaining.h
  Author         : Wei Lian
  Created on     : April 7, 2018
  Description    : Implementation to the HashSeparateChaining class with interface
  Purpose        : 
  Usage          : 
  Build with     : 
  Modifications  : 

*******************************************************************************/
#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

#include "is_prime.h"

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template <typename HashedObj>
class HashSeparateChaining {
 public:
  explicit HashSeparateChaining(int size = 101000) : current_size_{0} { 
    the_lists_.resize( 101000 ); }

  void check(const HashedObj &x)
  {
    auto &which_list=the_lists_[MyHash(x)];
    cout<<"the lists are : "<<endl;
    for(auto &lol:which_list)
      cout<<lol<<endl;

  }  

  bool Contains( const HashedObj & x ) const {
    auto & which_list = the_lists_[ MyHash( x ) ];
        return find( begin( which_list ), end( which_list ), x ) != end( which_list );
  }
  
  void MakeEmpty( ) {
    for( auto & this_list : the_lists_ )
      this_list.clear( );
  }
  
  bool Insert( const HashedObj & x,const HashedObj & y) {
    auto & which_list = the_lists_[ MyHash( x ) ];
    if( find( begin( which_list ), end( which_list ), y ) != end( which_list) )
      return false;
    which_list.push_back( y );
    

    
    
    // Rehash; see Section 5.5
    if( ++current_size_ > the_lists_.size( )/2 )
      Rehash( );
    
    return true;
  }
    
  bool Insert( HashedObj && x, HashedObj &&y ) {
    auto & which_list = the_lists_[ MyHash( x ) ];      
    if( find( begin( which_list ), end( which_list ), y ) != end( which_list ) )
      return false;
    which_list.push_back( std::move( y ) );
    
    // Rehash; see Section 5.5
    if( ++current_size_ > the_lists_.size( )/2 )
      Rehash( );
    
    return true;
  }


  bool Remove( const HashedObj & x ) {
    auto & which_list = the_lists_[ MyHash( x ) ];
    auto itr = find( begin( which_list ), end( which_list ), x );
    
    if( itr == end( which_list ) )
      return false;
    
    which_list.erase( itr );
    --current_size_;
    return true;
  }

 private:
  vector<list<HashedObj>> the_lists_; 
  int  current_size_;
  
  void Rehash( ) {
   vector<list<HashedObj>> old_lists = the_lists_;
   int old_size_=current_size_;
    
    // Create new double-sized, empty table
    the_lists_.resize( PrimeProject::NextPrime( 2 * the_lists_.size( ) ) );
    
    for(auto &this_list:the_lists_)
    {
      this_list.clear();
    }
    current_size_=0;


    for(auto &this_list:old_lists)
    {
      the_lists_.push_back(this_list);
    }

    current_size_=old_size_;
    // Copy table over*/

    
  }
    
  
  size_t MyHash( const HashedObj & x ) const {
    static hash<HashedObj> hf;
    return hf( x ) % the_lists_.size( );
  }
};

#endif
