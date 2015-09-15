#ifndef DATASET_H_
#define DATASET_H_

#include <map>
#include <vector>

namespace irtpp
{

class dataset
{

public:

    unsigned int size;
    map<vector<char>, int> matrix;
    Matrix<char>* bitset_list;
    int * count_set_bits;
    int * frequency_list;

    //Constructor
    dataset(int size);

    // Methods
    std::map<vector<char>, int>::const_iterator iterator; /**use this when reading in order*/
    map<vector<char>, int>::const_iterator begin = matrix.begin();
    map<vector<char>, int>::const_iterator end = matrix.end();
    inline void resetIterator(){iterator = matrix.begin();}
    inline char checkEnd(){return (iterator==matrix.end());}
    inline void iterate(){++iterator;}
    inline vector<char> getCurrentBitSet(){return (iterator->first);}
    inline int getCurrentFrequency(){return (iterator->second);}
    int countBitSet(Matrix<char> * bitset, int index);
    void push(vector<char>);/**Use this to fill the pattern matrix*/
    void push(vector<char>,int);/**Use this to fill the pattern matrix many times with a pattern*/
    int freq(vector<char>);//Frequency
    void flush();/**Use this to clean matrix*/
    void print();

    friend std::ostream& operator<< (std::ostream &, dataset &);/**Output operator*/

    //DataSet implementations
    int countItems () const;
    int countIndividuals () const;
    Matrix<char> * getBitsetList();
    Matrix<int> * getFrequencyList();

    //Destructor
    ~dataset();
};

}

#endif