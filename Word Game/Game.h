#ifndef GAME_H
#define GAME_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <cctype>

class Game {

public:
	void Run();																		//game loop function to run in main.cpp
	

private:
	std::vector<int> get_indexes(const std::string& word);						//function to return the character of words as vector of ints (index)
    bool vector_contains_word(const std::vector<std::string>& vec, const std::string& word);   //function to check if the guessed word is a valid word
	int score_match(const std::string& word1, const std::string& word2);                // function to find the score
	std::vector<std::string> five_words;											//vector to store all words from file
	std::vector<int> used;															//vector to check if the position of the letter was used
	int num_guess;
	int difficulty;
	void Set_Difficulty(int d);
	int GetRand();																	//get random number from 0 to 4

};

#endif