//
// Created by linuxer on 22.06.19.
//

#ifndef CAESAR_CAESAR_H
#define CAESAR_CAESAR_H
#include <map>


class caesar {
public:
    void setAlphabet(const std::string &alphabet);

    void setPlaintext(const std::string &plaintext);

    void setRotations(int rotations);

    void prepare();

    void rotateAlphabet();

    void replace();

private:
    std::map<char, char> alphabetMap;
    std::string plainText;
    std::string cryptedText;
public:
    const std::string &getCryptedText() const;

private:
    std::string alphabet;
    int rotations;
};


#endif //CAESAR_CAESAR_H
