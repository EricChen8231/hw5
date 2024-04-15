#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Function prototype
void wordleHelper(std::string current, const std::set<std::string> &dict, std::set<std::string> &matches, int pos, std::string floatingLetters);

// Primary wordle function
std::set<std::string> wordle(const std::string &inputWord, const std::string &floatingLetters, const std::set<std::string> &dictionary)
{
    std::set<std::string> outputMatches;
    int currentPosition = 0;
    wordleHelper(inputWord, dictionary, outputMatches, currentPosition, floatingLetters);
    return outputMatches;
}

// Helper function to recursively find wordle matches
void wordleHelper(std::string currentWord, const std::set<std::string> &dictionary, std::set<std::string> &matches, int position, std::string floatingLetters)
{
    int numDashes = 0;

    // Base case: If the entire word is processed, check if it's a valid match and return
    if (position == currentWord.size())
    {
        if (floatingLetters.empty())
        {
            if (dictionary.find(currentWord) != dictionary.end())
            {
                matches.insert(currentWord);
            }
            return;
        }
    }

    // If the current position in the word is not a dash, move to the next position
    if (currentWord[position] != '-')
    {
        wordleHelper(currentWord, dictionary, matches, position + 1, floatingLetters);
        return;
    }

    // Count the number of dashes in the current word
    for (char letter : currentWord)
    {
        if (letter == '-')
        {
            numDashes++;
        }
    }

    // If there are more dashes than floating letters, try all possible letters
    if (numDashes > static_cast<int>(floatingLetters.size()))
    {
        for (char letter = 'a'; letter <= 'z'; ++letter)
        {
            if (floatingLetters.find(letter) != std::string::npos)
            {
                currentWord[position] = letter;
                wordleHelper(currentWord, dictionary, matches, position + 1, floatingLetters);
            }
            else
            {
                currentWord[position] = letter;
                wordleHelper(currentWord, dictionary, matches, position + 1, floatingLetters);
            }
        }
    }
    else // Otherwise, use floating letters
    {
        int floatingIndex = 0;
        for (size_t i = 0; i < currentWord.size(); ++i)
        {
            if (currentWord[i] == '-')
            {
                currentWord[i] = floatingLetters[floatingIndex++];
            }
        }
        wordleHelper(currentWord, dictionary, matches, position + 1, floatingLetters);
    }
}