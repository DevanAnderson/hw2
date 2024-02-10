#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    //O(n logn)
    std::set<std::string> words;
    string word = "";
    //iterate through all the characters
    for(uint32_t i = 0; i < rawWords.size(); ++i){
        char character = rawWords.at(i);
        //check if the charater is a space, period, or single quote
        if(character == ' ' || character == '.' || character == '\''){
            //if the word is greater than two, add it to the set of words
            if(word.size() >= 2){
                words.insert(word);
            }
            //clear word and go to the next character
            word = "";
        }
        else{
        //add the character to the word
        word += character;
        }
    }
    //check if the final word is greater than 2
    if(word.size() >= 2){
        words.insert(word);
    }

    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
