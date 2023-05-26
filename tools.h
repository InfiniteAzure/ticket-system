//
// Created by Xue Jiarui on 2023/5/25.
//

#ifndef TICKET_SYSTEM_TOOLS_H
#define TICKET_SYSTEM_TOOLS_H

class date {
public:
    int month = 0;
    int day = 0;

    date() {};

    date(std::string s) {
        month = (s[0] - '0') * 10 + s[1] - '0';
        day = (s[3] - '0') * 10 + s[4] - '0';
    }

    void print() {
        std::cout << month / 10 << month % 10 << ":" << day / 10 << day % 10;
    }

    friend bool operator<(date a, date b) {
        if (a.month != b.month) {
            return a.month < b.month;
        } else {
            return a.day < b.day;
        }
    }

    friend bool operator>(date a, date b) {
        if (a.month != b.month) {
            return a.month > b.month;
        } else {
            return a.day > b.day;
        }
    }

    friend bool operator>=(date a, date b) {
        if (a.month != b.month) {
            return a.month >= b.month;
        } else {
            return a.day >= b.day;
        }
    }

    friend bool operator<=(date a, date b) {
        if (a.month != b.month) {
            return a.month <= b.month;
        } else {
            return a.day <= b.day;
        }
    }

    friend bool operator==(date a, date b) {
        if (a.month != b.month) {
            return a.month == b.month;
        } else {
            return a.day == b.day;
        }
    }

    friend date operator+(date a, int x) {
        a.day += x;
        if (a.day > 30) {
            if (a.month == 6) {
                a.day -= 30;
                a.month++;
                while (a.day > 31) {
                    a.day -= 31;
                    a.month++;
                }
            } else {
                if (a.day > 31) {
                    a.day -= 31;
                    a.month++;
                }
            }
        }
        return a;
    }

    friend date operator-(date a, int x) {
        a.day -= x;
        if (a.day < 0) {
            a.day += 31;
            a.month--;
        }
        return a;
    }

    friend int operator-(date a, date b) {
        while (a.month > b.month) {
            if (a.month == 9 || a.month == 8) {
                a.month--;
                a.day += 31;
            } else if (a.month == 7) {
                a.month--;
                a.day += 30;
            }
        }
        return a.day - b.day;
    }
};

class day_time{
public:
    int hour = 0;
    int minute = 0;

    day_time();

    day_time(std::string s) {
        hour = (s[0] - '0') * 10 + s[1] - '0';
        minute = (s[3] - '0') * 10 + s[4] - '0';
    }

    void print() {
        std::cout << hour / 10 << hour % 10 << ":" << minute / 10 << minute % 10;
    }

    friend bool operator<(day_time a, day_time b) {
        if (a.hour != b.hour) {
            return a.hour < b.hour;
        } else {
            return a.minute < b.minute;
        }
    }
    friend bool operator>(day_time a, day_time b) {
        if (a.hour != b.hour) {
            return a.hour > b.hour;
        } else {
            return a.minute > b.minute;
        }
    }
    friend bool operator<=(day_time a, day_time b) {
        if (a.hour != b.hour) {
            return a.hour <= b.hour;
        } else {
            return a.minute <= b.minute;
        }
    }
    friend bool operator>=(day_time a, day_time b) {
        if (a.hour != b.hour) {
            return a.hour >= b.hour;
        } else {
            return a.minute >= b.minute;
        }
    }
    friend bool operator==(day_time a, day_time b) {
        if (a.hour != b.hour) {
            return a.hour == b.hour;
        } else {
            return a.minute == b.minute;
        }
    }

    friend day_time operator+(day_time a,int b) {
        a.minute += b;
        a.hour += a.minute / 60;
        a.minute = a.minute % 60;
    }

    friend int operator-(day_time a,day_time b) {
        return 60 * (a.hour - b.hour) + a.minute - b.minute;
    }
};

int day_time_between(date a,day_time a2,date b,day_time b2) {
    return 1440 * (b - a) + (a2 - b2);
}

#endif //TICKET_SYSTEM_TOOLS_H
