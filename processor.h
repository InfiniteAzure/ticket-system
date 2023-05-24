//
// Created by Xue Jiarui on 2023/5/24.
//

#ifndef TICKET_SYSTEM_PROCESSOR_H
#define TICKET_SYSTEM_PROCESSOR_H

class processor{
public:
    std::string line;
    std::string words[25];
    int size;

    processor(std::string s) {
        line = s;
        int i = 0;
        int pos = 0;
        while (line[i] != '\0') {
            std::string tmp;
            while (line[i] != ' ' && line[i] != '\0') {
                tmp += line[i];
                i++;
            }
            if (line[i] == '\0') {
                words[pos] = tmp;
                pos++;
                break;
            }
            i++;
            words[pos] = tmp;
            pos++;
        }
        size = pos;
    }

    ~processor() = default;

};

#endif //TICKET_SYSTEM_PROCESSOR_H
