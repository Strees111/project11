#include <iostream>
#include <cstring>
#include <fstream>
#include "database.h"

int countWords(const char *str) {
    int count = 0;
    bool inWord = false;
    while (*str != '\0') {
        if (*str == ' ') {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            ++count;
        }
        ++str;
    }
    return count;
}

char **split(const char *str, int &count) {
    count = countWords(str);
    char **result = new char *[count];
    int wordIndex = 0;
    const char *start = str;
    const char *end = str;
    while (*end != '\0') {
        if (*end == ' ' || *end == ',' || *end == ';') {
            if (start != end) {
                int length = end - start;
                result[wordIndex] = new char[length + 1];
                std::strncpy(result[wordIndex], start, length);
                result[wordIndex][length] = '\0';
                ++wordIndex;
            }
            start = end + 1;
        }
        ++end;
    }
    if (start != end) {
        int length = end - start;
        result[wordIndex] = new char[length + 1];
        std::strncpy(result[wordIndex], start, length);
        result[wordIndex][length] = '\0';
    }
    return result;
}
void upper(char* str){
    for (size_t i = 0; i < strlen(str); ++i) {
        str[i] = toupper(str[i]);
    }
}
void parse_command(const char *str, DataBase &DataBase) {
    int word_count;
    char **command = split(str, word_count);
    if (strcmp(command[0], "add") == 0) {
        upper(command[2]);
        upper(command[3]);
        if (!CheakDate(Flight::time(command[5]),Flight::time(command[7]),Flight::date(command[4]),Flight::date(command[6]))){
            std::cout << "Wrong arrival_time time" <<std::endl;
            return;
        }
        DataBase.add(Flight{command[1], command[2], command[3], command[4], command[5],command[6],command[7], atoi(command[8]), strtof(command[9], nullptr)});
    }
    else if(strcmp(command[0], "load") == 0){
        DataBase.load(command[1]);
    }
    else if(strcmp(command[0], "save") == 0){
        DataBase.save(command[1]);
    }
    else if (strcmp(command[0], "delete") == 0){
        DataBase.delete_ID(atoi(command[1]));
    }
    else if (strcmp(command[0], "clear") == 0){
        DataBase.clear();
    }
    else if (strcmp(command[0], "print") == 0){
        DataBase.print();
    }
    else if (strcmp(command[0], "schedule") == 0){
        upper(command[1]);
        DataBase.schedule(command[1],command[2]);
    }
    else if (strcmp(command[0], "from") == 0){
        upper(command[1]);
        upper(command[3]);
        DataBase.from(command[1],command[3],command[5]);
    }
    else if (strcmp(command[0], "find") == 0){
        upper(command[1]);
        upper(command[3]);
        DataBase.find(command[1],command[3]);
    }
    else if (strcmp(command[0], "buy") == 0){
        DataBase.buy(command[1],command[2]);
    }
    else if (strcmp(command[0], "export") == 0){
        std::ofstream os(command[1]);
        if (os.is_open()){
            DataBase.export_(os);
            os.close();
        }
        else{
            std::cout << "Failed to open file" << std::endl;
        }
    }
    else if(strcmp(command[0], "quit") == 0){
        return;
    }
    else{
        std::cout << "Unknown command: " << command[0] << std::endl;
    }
    for (int i = 0; i < word_count; ++i) {
        delete[] command[i];
    }
    delete[] command;
}

int main() {
    char buf[256]{};
    DataBase Data_Base;
    while (strcmp(buf, "quit") != 0) {
        std::cout << "> ";
        std::cin.getline(buf, 256);
        parse_command(buf, Data_Base);
    }
    return 0;
}
