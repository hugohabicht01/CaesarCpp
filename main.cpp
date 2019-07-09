#include <iostream>
#include <map>
#include <fstream>
#include "argh.h"
#include "caesar.h"


void readFile(const std::string& file, std::string *dest){
        std::string line;
        std::ifstream inputFile(file);
        if (inputFile.is_open()) {
                while (getline(inputFile, line)) {
                        *dest += (line + "\n");
                }
                inputFile.close();
        }
}


int main(int argc, const char** argv) {
    int rotations {};
    std::string rotationsString {};
    std::string filename {};
    std::string input {};
    argh::parser cmdl;
    cmdl.add_params({"-r", "--rotations", "-f", "--file", "-t", "--text"});
    cmdl.parse(argc, argv);
    if (!(cmdl({"rotations", "r"}) >> rotations)) {
            std::cerr << "Rotations argument missing.\n";
            return 1;
    }
    if (getline(cmdl({"text", "t"}), input, '\0')) {
    } else if (cmdl({"file", "f"}) >> filename) {
            readFile(filename, &input);
    } else {
            std::cerr << "You have to specify a text or file argument. \n";
            return 1;
    }

    caesar crypt;
    crypt.setAlphabet("abcdefghijklmnopqrstuvwxyz");
    crypt.setPlaintext(input);
    crypt.setRotations(rotations);
    crypt.rotateAlphabet();
    crypt.prepare();
    crypt.replace();
    std::cout << crypt.getCryptedText() << "\n";
    return 0;
}