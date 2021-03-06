#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FileInputManager {
public:
    FileInputManager(const string& input_file_name)
        : input_file_name_(input_file_name) {
        input_file_stream_.open(input_file_name_);
    }
    ~FileInputManager() {
        input_file_stream_.close();
    }

    bool IsFileValid() {
        if (!input_file_stream_.is_open()) {
            return false;
        }
        return true;
    }

    vector <string> GetInputStringsFromFile();

private:
    bool IsEndOfFile() {
        return input_file_stream_.eof();
    }

    ifstream input_file_stream_;
    string input_file_name_;
};

