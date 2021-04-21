#include <iostream>
#include "bitio.hh"

BitIO::BitIO(std::ostream* os, std::istream* is) {
    if (!os && is) {
        output = nullptr;
        input = is;                                                        // if only istream is given, set object's output stream to nullptr and take the given input stream
    }   
    else if (!is && os) {
        output = os;
        input = nullptr;                                                   // if only ostream is given, set object's input stream to nullptr and take the given output stream
    }
    else if ((os && is) || (!os && !is)) {
        output = nullptr;
        input = nullptr;                                                   // else if either none or both are given, set both to null
    }
}
BitIO::~BitIO() = default;


void BitIO::output_bit(bool bit) {
    int push = static_cast<int>(bit);                                      // take the given bool and convert it to an int
    char obit = static_cast<char>(push + '0');                             // take that int, add the ASCII value of '0' to it and cast it to a char, either 0 or 1
    output->put(obit);                                                     // put that char onto the output stream
}

bool BitIO::input_bit() {
    bool ibit;                                                             // initialise an boolean
    if (input->peek() != EOF) {
        char pull = input->get();                                          // if next char in istream isn't EOF, get the first char in the input stream
        ibit = static_cast<bool>(pull - '0');                              // convert it to a binary value by subtracting the ASCII value of '0' from the char, either 0 or 1
    }                                                               
    else {                                                                 
        ibit = false;                                                      // else if EOF is reached, set ibit as false as there are no characters left to read
    }
    return ibit;                                                           // return that binary value
}