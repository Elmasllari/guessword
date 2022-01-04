#include "Game.h"

void Game::Set_Difficulty(int d) {
	difficulty = d;
}

int Game::GetRand() {
	std::mt19937 ran(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, 4);
	return dist(ran);
}

bool Game::vector_contains_word(const std::vector<std::string>& vec, const std::string& word) {

	for (auto& w : vec) {

		if (w == word) {

			return true;
		}
	}
	return false;
}



std::vector<int> Game::get_indexes(const std::string& word) {

	std::vector<int> index(26, 0); // create 26 ints with value 0 for every character in english language
	for (char c : word) {

		index[c - 'a']++;         //gives us an index for each letter , ex a-a = 0 , b-a = 1
	}
	return index;
}


// you get 1 point for guessing a character and an extra 1 point if you also find the correct position of the character
int Game::score_match(const std::string& word1, const std::string& word2)
{
	auto w1 = get_indexes(word1);
	auto w2 = get_indexes(word2);

	int score = 0;
	for (int i = 0; i < 26; i++) {								//check same character

		score += std::min(w1[i], w2[i]);
	}

	for (int i = 0; i < 5; i++) {								//check position

		if (word1[i] == word2[i]) {

			score++;
		}
	}

	return score;
}


void Game::Run() {
	
	int choice;
	std::cout << "------------------" << std::endl;
	std::cout << "New Game" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "Choose Difficulty with a number:" << std::endl;
	std::cout << "4.Very Hard" << std::endl;
	std::cout << "3.Hard" << std::endl;
	std::cout << "2.Medium:(default)" << std::endl;
	std::cout << "1.Easy" << std::endl;
	std::cin >> choice;

	switch (choice) {
	case 4: 	Set_Difficulty(7);	break;
	case 3: 	Set_Difficulty(9);	break;
	case 2: 	Set_Difficulty(13);	break;
	case 1: 	Set_Difficulty(17);	break;
	default:    Set_Difficulty(13);	break;
	}
	

	//if chosen difficulty is easy,medium or default, you will have to guess  
	//from the 2000s most popular five letter words instead of more diffucult ones
	if (difficulty > 10) {
		std::ifstream five_word_file("2000words.txt");
		for (std::string line; std::getline(five_word_file, line); ) {          	//populate vector with every word in file with 2000 most popular five letter words

			if (line.empty()) {

				continue;
			}
			five_words.push_back(line);
		}
	}
	else {
		std::ifstream five_word_file("5000words.txt");
		for (std::string line; std::getline(five_word_file, line); ) {          	//populate vector with every word in file with every five letter word

			if (line.empty()) {

				continue;
			}
			five_words.push_back(line);
		}
	}


//get random word
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(0, five_words.size() - 1);
const std::string target = five_words[dist(rng)];

//game loop
while (true)
{
	std::cout << "Guess a five letter word: ";
	std::string guess;
	std::getline(std::cin, guess);     // user guesses word

	for (auto& c : guess) {

		c = std::tolower(c);           // return word as lower case
	}


	if (guess.size() != 5) {

		std::cout << "Please guess only a five letter word" << std::endl;
		continue;
	}

	if (!vector_contains_word(five_words, guess)) {

		std::cout << guess << "  This isn't a word" << std::endl;
		continue;
	}

	const int score = score_match(guess, target);
	num_guess++;

	if (num_guess % 4 == 0) {							// reveal 1 unknown random letter for every 4 guesses you make
		int pos = GetRand();

		while (std::find(used.begin(), used.end(), pos) != used.end()) {     // check if letter was revealed before
			pos = GetRand();
		}

		std::cout << std::endl << "Hint:" << "Letter " << pos+1 << " is " << target[pos] << std::endl;
		used.push_back(pos);
	}


	if (num_guess >= difficulty) {     //if you used all number of guesses you lose
		std::cout << "You lose" << std::endl << "The word was " << target << std::endl;
		Run();						   // restart game
	}

	if (score == 10) {			// if you get 10 points you have guessed the word

		std::cout << "You win" << std::endl;
		std::cout << "Congratulations" << std::endl;
		Run();                  // restart game
	}
	else {


	}

	{
		std::cout << "  You got " << score << " points" << std::endl;
		std::cout << "You have " << difficulty-num_guess<< " guesses left" << std::endl;
		continue;
	}
	
	
}
}

