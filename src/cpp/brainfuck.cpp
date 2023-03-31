#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

int main(int argc, char const *argv[]) {

    if (argc < 2) { // basic error handling
        
        std::cout << "No file to run" << std::endl;
        return 0;
    }
    else if (argc > 2) {
        std::cout << "Too many input arguments" << std::endl;
        return 0;
    }
    else {
        int len = std::strlen(argv[1]);
        if (!((argv[1][len-2] == '.' && argv[1][len-1] == 'b') || (argv[1][len-3] == '.' && argv[1][len-2] == 'b' && argv[1][len-1] == 'f'))) {
            std::cout << "Wrong filetype" << std::endl;
            return 0;
        }
    }
    
    std::fstream file;
    std::string temp;
    std::string prior;
    std::string instructions;
    file.open(argv[1]);
    while (file >> temp) {
        prior += temp;
    }

    file.close();
    
    //std::cout << prior << std::endl;
    
    for (int i = 0; i < prior.size(); i++) {
        if (prior[i] == '+')
            instructions += prior[i];
        if (prior[i] == '-')
            instructions += prior[i];
        if (prior[i] == '<')
            instructions += prior[i];
        if (prior[i] == '>')
            instructions += prior[i];
        if (prior[i] == '.')
            instructions += prior[i];
        if (prior[i] == ',')
            instructions += prior[i];
        if (prior[i] == '[')
            instructions += prior[i];
        if (prior[i] == ']')
            instructions += prior[i];
    }
    
    //std::cout << instructions << std::endl;

    int ip = 0;
    int dp = 0;
    int dataLength = 1024;
    int* data = (int*)calloc(dataLength, sizeof(int));

    std::cout << instructions [ip] << std::endl;

    while (ip < instructions.size()) {
        if (instructions[ip] == '<') {
            dp--;
        } else if (instructions[ip] == '>') {
            dp++;
        } else if (instructions[ip] == '+') {
            data[dp]++;
        } else if (instructions[ip] == '-') {
            data[dp]--;
        } else if (instructions[ip] == '.') {
            printf("%c", data[dp]);
        } else if (instructions[ip] == ',') {
            char c;
            scanf(" %c", &c);
            data[dp] = c;
        } else if (instructions[ip] == '[') {
            if (data[dp] == 0) {
                int count = 1;
                while (count != 0) {
                    ip++;
                    if (instructions[ip] == '[') {
                        count++;
                    } else if (instructions[ip] == ']') {
                        count--;
                    }
                }
                
            }
        } else if (instructions[ip] == ']') {
            if (data[dp] != 0) {
                int count = -1;
                while (count != 0) {
                    ip--;
                    if (instructions[ip] == '[') {
                        count++;
                    } else if (instructions[ip] == ']') {
                        count--;
                    }
                }
            }
        }
        ip++;
    }
    

    return 0;
}
