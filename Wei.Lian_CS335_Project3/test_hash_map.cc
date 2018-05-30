/*******************************************************************************
  Title          : test_hash_map.cc
  Author         : Wei Lian
  Created on     : April 7, 2018
  Description    : Implementation to the main interface
  Purpose        : 
  Usage          : 
  Build with     : 
  Modifications  : 

*******************************************************************************/
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "quadratic_probing.h"
#include "separate_chaining.h"
#include "double_probing.h"

using namespace std;
//textbook algorithm
bool oneCharoff(const string &word1,const string &word2)
{
  if(word1.length()!=word2.length())
    return false;
  int diffs =0;
  for(int i=0;i<word1.length();++i)
  {
    if(word1[i]!=word2[i])
    {
      if(++diffs>1)
      {
        return false;
      }
    }
  }
  return diffs==1;
}


template <typename HashTableType>
void TestComputeAdjacentWords(HashTableType &hash_table, 
		     const vector<string> &words) {
  // This is for computing timing.
  const auto begin = chrono::high_resolution_clock::now();

  hash_table.MakeEmpty();  
  //..Insert your own code using algorithm described in Figure 4.73
  string word1,word2;
  size_t longest=0;
  vector<string>wordbylength;
  vector<vector<string>>wordlength;



  for(auto & str: words)
  {
    if(longest<str.length())
      longest=str.length();
  }
  for(size_t i=0;i<=longest;++i)
  {
    for(auto & str: words)
    {
      if(str.length()==i)
      {
        wordbylength.push_back(str);
      }
    }
    wordlength.push_back(wordbylength);
    wordbylength.clear();
  }
  for( auto & entry : wordlength )
  {
    const vector<string> &groupsWords=entry;

    for(int i=0; i<groupsWords.size();++i)
    {
      for(int j=i+1;j<groupsWords.size();++j)
      {
        if(oneCharoff(groupsWords[i],groupsWords[j]))
        {
          hash_table.Insert(groupsWords[i],groupsWords[j]);
          hash_table.Insert(groupsWords[j],groupsWords[i]);
        }
      }
    }

  }
  /*
  hash_table.Insert("good","goof");
  hash_table.Insert("good","goot");
  hash_table.Insert("goodaa","gootaa");
  hash_table.Insert("good","gooq");*/



  const auto end = chrono::high_resolution_clock::now();

  cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;
  //use the check function to make sure the word is in the dictionary,and print out the associated words.

  cout<<"Please enter a word: "<<endl;
  cin>>word1;
  //use the check function to make sure the word is in the dictionary,and print out the associated words.
  hash_table.check(word1);
  cout<<"Please enter another word: "<<endl;
  cin>>word2;
  hash_table.check(word2);
}

vector<string> ReadWordsFromFile(const string &words_filename) {
  vector<string> the_words;
  // Implement this...
  ifstream file(words_filename);
  string line;
  if(!file.is_open())
  {
    cerr<<words_filename<<" "<<"can not be open"<<endl;
  }
  else
  {
    while(!file.eof())
    {
      getline(file,line);
      the_words.push_back(line);
    }
  }
  file.close();
  return the_words;
}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " words_file_name hash_type (chaining, quadratic or double)" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const vector<string> the_words = ReadWordsFromFile(words_filename);

  const string param_flag(argv[2]);

  if (param_flag == "chaining") {
    HashSeparateChaining<string> separate_chaining_table;
    TestComputeAdjacentWords(separate_chaining_table, the_words);
  } else if (param_flag == "quadratic") {
    HashQuadraticProbing<string> quadratic_probing_table;    
    TestComputeAdjacentWords(quadratic_probing_table, the_words);
  } else if (param_flag == "double") {
    HashDoubleProbing<string> double_probing_table;
    TestComputeAdjacentWords(double_probing_table, the_words);    
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
