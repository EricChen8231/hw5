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
void wordleHelper(std::string current, const std::set<std::string> &dict, std::set<std::string> &match, int pos, std::string floatingLetters);

std::set<std::string> wordle(const std::string &in, const std::string &floating, const std::set<std::string> &dict);

// Primary wordle function
std::set<std::string> wordle(const std::string &inputWord, const std::string &floatingLetters, const std::set<std::string> &dictionary)
{
    std::set<std::string> output;
    int currentPosition = 0;
    wordleHelper(inputWord, dictionary, output, currentPosition, floatingLetters);
    return output;
}

// Helper function to recursively find wordle matches
void wordleHelper(std::string currentWord, const std::set<std::string> &dictionary, std::set<std::string> &matches, int index, std::string floatingLetters)
{
    int numDashes = 0;
    std::string floatingLettersCopy = floatingLetters;

    // Base case: If the entire word is processed, check if it's a valid match and return
    if (index == currentWord.size())
    {
        if (floatingLettersCopy.empty())
        {
            if (dictionary.find(currentWord) != dictionary.end())
            {
                matches.insert(currentWord);
            }
        }
        return;
    }

    // If the current index in the word is not a dash, move to the next index
    if (currentWord[index] != '-')
    {
        wordleHelper(currentWord, dictionary, matches, index + 1, floatingLettersCopy);
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
    if (numDashes > static_cast<int>(floatingLettersCopy.size()))
    {
        for (char letter = 'a'; letter <= 'z'; ++letter)
        {
            if (floatingLettersCopy.find(letter) != std::string::npos)
            {
                std::string temp = floatingLettersCopy;
                currentWord[index] = letter;
                temp.erase(temp.find(letter), 1);
                wordleHelper(currentWord, dictionary, matches, index + 1, temp);
            }
            else
            {
                currentWord[index] = letter;
                wordleHelper(currentWord, dictionary, matches, index + 1, floatingLettersCopy);
            }
        }
    }
    else
    { // Otherwise, use floating letters
        for (char letter : floatingLettersCopy)
        {
            std::string temp = floatingLettersCopy;
            currentWord[index] = letter;
            temp.erase(temp.find(letter), 1);
            wordleHelper(currentWord, dictionary, matches, index + 1, temp);
        }
    }
}