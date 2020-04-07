/*
Name: Aaron Gaskin
Section: 11153
UFID: 9930-5710
References used:
https://www.geeksforgeeks.org/fibonacci-heap-deletion-extract-min-and-decrease-key/?ref=rp
https://github.com/robinmessage/fibonacci/blob/master/test.cpp
*/

#include "fibonacci_heap.h"
#include <fstream>
#include <bits/stdc++.h>

/****************   Helper methods   ****************/

//Take a line that starts with '#', split, and add to tree
void AddHashtagToTree(string line, FibonacciHeap *fibHeap)
{
    istringstream ss(line);

    //Split the string at " "
    string hashtag;
    ss >> hashtag;
    string stringCount;
    ss >> stringCount;

    //Convert count to integer
    int count = atoi(stringCount.c_str());

    //send data to hashtable checker
    fibHeap->CheckIfHashtagExists(hashtag, count);
}

/****************   Main method   ****************/

int main(int argc, char *argv[])
{
    //verify correct number of inputs
    if (argc != 2)
    {
        cout << "ERROR: incorrect input, expecting exactly one file name." << endl;
        return 0;
    }

    //Verify file is reachable and readable
    string fileName = argv[1];
    ifstream reader(fileName);
    if (reader.is_open() && reader.good())
    {
        //Read file line by line and perform operations based on line
        string line = "";
        FibonacciHeap *fibHeap = new FibonacciHeap();
        string output;

        ofstream writer("output_file.txt");

        while (getline(reader, line))
        {
            //if hashtag, check if in hashtable
            if (line[0] == '#')
                AddHashtagToTree(line.substr(1), fibHeap);

            else if (line == "stop") //stop, end the program
                break;

            else //integer, print out n maxes
            {

                int n = atoi(line.c_str());
                output = fibHeap->PrintOutMaxes(n);
                writer << output << endl;
            }
        }

        reader.close();
        writer.close();
        delete fibHeap;
    }
    else
        cout << "ERROR: File not found." << endl;

    return 0;
}