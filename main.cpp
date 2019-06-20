#include <iostream>
#include <map>
#include <fstream>
#include "argh.h"


using namespace std;

void readFile(const string& file, string *dest){
        string line;
        ifstream inputFile(file);
        if (inputFile.is_open()) {
                while (getline(inputFile, line)) {
                        *dest += (line + "\n");
                }
                inputFile.close();
        }
}

map<char, char> rotate(int rotations){
        map<char , char> alphabetMap {};
        char originalChar, rotatedChar;
        int valueOfChar;
        const string alphabet_ascii_lowercase = "abcdefghijklmnopqrstuvwxyz";
        for (int index = 0; index < alphabet_ascii_lowercase.length(); ++index) {
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
        if (!(cmdl({"rotations", "r"}) >> rotations)) {
                cerr << "Rotations argument missing.\n";
                return 1;
        }
        if (getline(cmdl({"text", "t"}), input, '\0')) {
//        if (!cmdl[{"text", "t"}]) {
//            input = cmdl({"text", "t"}).str();
        } else if (cmdl({"file", "f"}) >> filename) {
                readFile(filename, &input);
        } else {
                cerr << "You have to specify a text or file argument. \n";
                return 1;
        }
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        alphabet = rotate(rotations);
        cout << replace(input, alphabet);
        return 0;
}