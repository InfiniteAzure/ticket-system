//
// Created by Xue Jiarui on 2023/5/24.
//

#ifndef TICKET_SYSTEM_PROCESSOR_H
#define TICKET_SYSTEM_PROCESSOR_H

class processor{
public:
    std::string line;
    std::string words[25];

    processor(std::string s) {
        line = s;
        int i = 0;
        int pos = 0;
        while (line[i] != '\0') {
            std::string tmp;
            while (line[i] != ' ') {
                tmp += line[i];
                i++;
            }
            i++;
            words[pos] = line;
            pos++;
        }
    }

    ~processor() = default;

};

#endif //TICKET_SYSTEM_PROCESSOR_H
