/*******************************************************************************
  Title          : quadratic_probing.h
  Author         : Wei Lian
  Created on     : April 7, 2018
  Description    : Implementation to the HashQuadraticProbing class with interface
  Purpose        : 
  Usage          : 
  Build with     : 
  Modifications  : 

*******************************************************************************/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

#include "is_prime.h"

using namespace std;

// Quadratic probing implementation.
template <typename HashedObj>
class HashQuadraticProbing {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashQuadraticProbing(size_t size = 101000) : array_(PrimeProject::NextPrime(size))
    { MakeEmpty(); }
  
  void check(const HashedObj &x)
  {
    size_t current_pos=FindPos(x);
    cout<<"the lists are : "<<endl;
    for(auto& lol:array_[current_pos].values)
      cout<<lol<<endl;
  }  

  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x,const HashedObj & y) {
    // Insert x as active
    size_t current_pos = FindPos(x);

    
    array_[current_pos].element_ = x;
    array_[current_pos].values.push_back(y);
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x,HashedObj && y) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    
    array_[current_pos] = std::move(x);
    array_[current_pos].values.push_back(std::move(y));
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    cout<<current_size_<<endl;
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

 private:        
  struct HashEntry {
    HashedObj element_;
    vector<HashedObj>values;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      current_pos += offset;  // Compute ith probe.
      offset += 2;
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;
    int old_size=current_size_;

    // Create new double-sized, empty table.
    array_.resize(PrimeProject::NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    //cout<<current_size_<<endl;
    // Copy table over.
    current_size_=0;
    for(auto &this_array:old_array)
    {
      array_.push_back(this_array);
    }
    current_size_=old_size;

      
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // QUADRATIC_PROBING_H
