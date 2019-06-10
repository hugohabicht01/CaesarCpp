#include <iostream>
#include <map>
#include <args.hxx>
#include <fstream>

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
    string filename {};
    string input {};


    args::ArgumentParser parser("This is a program to de-/encrypt caesar encryption");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<int> rotationsArg(parser, "rotations", "The rotations flag", {'r'});
    args::ValueFlag<string> fileArg(parser, "file", "Input file instead of using stdin", {'f'});
    args::PositionalList<string> inputArg(parser, "input text", "The input text to de-/encrypt");
    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (const args::Completion& e)
    {
        std::cout << e.what();
        return 0;
    }
    catch (const args::Help&)
    {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if(!rotationsArg) {
        cerr << "The rotations argument is missing";
        cerr << parser;
        return 1;
    }

    if (!inputArg && !fileArg) {
        cerr << "The text or file argument is missing";
        cerr << parser;
        return 1;
    }

    if (fileArg && inputArg) {
        cerr << "An error occured, You can not use a file as input and a string at the same time";
        cerr << parser;
        return 1;
    }
    rotations = args::get(rotationsArg);
    if (inputArg) {
        for (auto c: inputArg) {
            input += c;
        }
    } else if (fileArg) {
        filename = args::get(fileArg);
        ifstream inputfile (filename);
        string line;
        if (inputfile.is_open())
        {
            while ( getline (inputfile,line) )
            {
                input += line;
            }
            inputfile.close();
        }
    }
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    alphabet = rotate(rotations);
    cout << replace(input, alphabet);
    return 0;
}