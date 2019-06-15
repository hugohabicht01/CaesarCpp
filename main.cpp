#include <iostream>
#include <map>
#include <args.hxx>
#include <fstream>
#include "argh.h"

using namespace std;


map<char, char> rotate(int rotations){
    map<char , char> alphabetMap {};
    char originalChar, rotatedChar;
    int valueOfChar;
    const string alphabet_ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
    for (int index = 0; index < 25; ++index) {
        originalChar = alphabet_ascii_lowercase[index];
        valueOfChar = originalChar - 97;
        rotatedChar = (char) (((valueOfChar + rotations) % 26) + 97);
        alphabetMap[originalChar] = rotatedChar;
    }
    return alphabetMap;
}


string replace(string input, map<char, char>& alphabetMap) {
    string replacedText {};
    char replacedChar {};

    for (int index = 0; index < input.length(); ++index) {
        char c = input[index];
        if ('a' <= c && c <= 'z') {
            replacedChar = alphabetMap.find(c)->second;
        } else {
            replacedChar = c;
        }
        replacedText += replacedChar;
    }
    return replacedText;
}



int main(int argc, const char** argv) {
    map<char ,char> alphabet;
    int rotations {};
    string rotationsString {};
    string filename {};
    string input {};
    argh::parser cmdl;
    cmdl.add_params({"-r", "--rotations", "-f", "--file", "-t", "--text"});
    cmdl.parse(argc, argv);
    if (cmdl("rotations") || cmdl("r")) {
        try {
            rotations = stoi(cmdl("rotations").str());
            cout << rotations;
        }
        catch (int e) {
            rotations = stoi(cmdl("r").str());
        }
    }
    /*
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    alphabet = rotate(rotations);
    cout << replace(input, alphabet);
     */
    return 0;
}