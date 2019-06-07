#include <iostream>
#include <map>


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
//        alphabetMap.insert(pair<char, char>(originalChar, rotatedChar));
        alphabetMap[originalChar] = rotatedChar;
    }
    return alphabetMap;
}

int main() {
    for (auto elem: rotate(2)) {
        cout << elem.first << " " << elem.second << "\n";
    }
    return 0;
}