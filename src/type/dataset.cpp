/*
 * dataset.cpp
 *
 *  Created on: May 30, 2014
 *      Author: jcliberatol
 *      Updated by: cesandovalp
 */

#include "dataset.h"

dataset::dataset(int size)
{
    this->size = size;
    count_set_bits = NULL;
    bitset_list = NULL;
    frequency_list = NULL;
}

dataset::~dataset()
{
}

unsigned int dataset::countItems() const { return ((matrix.empty()) ? 0 : size); }

int dataset::freq(vector<char> bitset) { return (matrix[bitset]); }

unsigned int dataset::countIndividuals() const
{
    map<vector<char>, int>::const_iterator it;
    int counter = 0;

    for (it = matrix.begin(); it != matrix.end(); ++it)
        counter += it->second;

    return (counter);
}

void dataset::push(vector<char> n) { matrix[n]++; }

void dataset::push(vector<char> n, int k) { matrix[n] = matrix[n] + k; }

void dataset::flush() { matrix.clear(); }

void dataset::print()
{
    for (iterator = matrix.begin(); iterator != matrix.end(); ++iterator)
    {
        for (int var = 0; var < size; ++var)
        {
            int k = iterator->first[var];
            cout << k;
        }
        cout << " " << iterator->second << std::endl;
    }
}

int dataset::countBitSet(Matrix<char> * bitset, int index)
{
    if (count_set_bits == NULL)
    {
        count_set_bits = new int[matrix.size()];
        for (int i = 0; i < matrix.size(); i++)
            count_set_bits[i] = -1;
    }

    if (count_set_bits[index] == -1)
    {
        count_set_bits[index] = 0;
        for (int i = 0; i < size; i++)
            if (bitset[i])
                count_set_bits[index]++;
    }

    return (count_set_bits[index]);
}

Matrix<char>* dataset::getBitsetList()
{
    if (bitset_list == NULL)
    {
        map<vector<char>, int>::const_iterator it;
        map<vector<char>, int>::const_iterator begin = matrix.begin();
        map<vector<char>, int>::const_iterator end = matrix.end();

        bitset_list = new Matrix<char>(matrix.size(),size);

        frequency_list = new Matrix<int>(matrix.size(),0);

        int counter = 0;
        int j;

        for (it = begin; it != end; ++it, ++counter)
        {
            j = 0;

            for (it2 = it->first.begin(); it2 != it->first.end(); ++it2, ++j)
            {
                (*bitset_list)(counter, j) = it2;
            }

        	(*frequency_list)(counter,0) = it->second;
        }
    }

    return bitset_list;
}

Matrix<int> * dataset::getFrequencyList()
{
    if (bitset_list == NULL)
        getBitsetList();
    return frequency_list;
}
