//
// Created by linuxer on 22.06.19.
//

#include "caesar.h"


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
