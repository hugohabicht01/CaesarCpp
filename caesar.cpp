//
// Created by linuxer on 22.06.19.
//

#include "caesar.h"
#include <iostream>
#include <algorithm>


void caesar::setAlphabet(const std::string &alphabet) {
    if (alphabet.length() != 26)
        throw "Alphabet does not use ASCII-chars"; // alphabet uses non ASCII-chars
    caesar::alphabet = alphabet;
}


void caesar::setPlaintext(const std::string &plaintext) {
    caesar::plainText = plaintext;
}

void caesar::setRotations(int rotations) {
    caesar::rotations = rotations;
}

void caesar::prepare() {
    /*
     * "Remembers the position of uppercase chars to replace them at the end
     */
    for (char c : this->plainText) {

        if (65 <= c && c <= 90) {
            this->uppercaseChars.push_back(true);
        } else {
            this->uppercaseChars.push_back(false);
        }
    }
    std::transform(this->plainText.begin(), this->plainText.end(), this->plainText.begin(), ::tolower);
}

void caesar::rotateAlphabet() {
    /*
     * Generates an std::map<char, char>alphabetMap for lookups
     */
    char rotatedChar;
    int valueOfChar;
    for (char originalChar: this->alphabet) {
        valueOfChar = originalChar - 'a';
        rotatedChar = (char) (((valueOfChar + this->rotations) % 26) + 'a');
        this->alphabetMap[originalChar] = rotatedChar;
    }
}

void caesar::replace() {
    /*
     * Replaces the chars with shifted chars
     */

    char replacedChar {};
    for (char c : this->plainText) {
        if ('a' <= c && c <= 'z') {
            replacedChar = alphabetMap.find(c)->second;
        } else {
            replacedChar = c;
        }
        this->cryptedText += replacedChar;
    }
}

std::string caesar::getCryptedText(){
    /*
     * Changes old uppercase chars which got converted to lowercase back to uppercase
     */
    int counter {0};
    std::string _str {};
    for (bool bit : this->uppercaseChars) {
        if (bit) {
            _str.push_back(toupper(this->cryptedText.at(counter)));
//            this->cryptedText.replace(counter, 1, toupper(this->cryptedText.at(counter)));
//            this->cryptedText[counter] = toupper(this->cryptedText.at(counter));
        } else {
            _str.push_back(this->cryptedText.at(counter));
        }
        counter += 1;
    }
    this->cryptedText = _str;
    return cryptedText;
}
