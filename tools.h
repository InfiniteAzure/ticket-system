//
// Created by Xue Jiarui on 2023/5/25.
//

#ifndef TICKET_SYSTEM_TOOLS_H
#define TICKET_SYSTEM_TOOLS_H

void cut(std::string s,sjtu::vector<std::string> &ans) {
    int i = 0;
    while (s[i] != '\0') {
        std::string tmp;
        while (s[i] != '|' && s[i] != '\0') {
            tmp += s[i];
            i++;
        }
        if (s[i] == '\0') {
            ans.push_back(tmp);
            break;
        }
        i++;
        ans.push_back(tmp);
    }
}

struct timing {
    std::string train_id;
    int index;
    int time;
    int s;
    int e;

    friend bool operator<(timing a, timing b) {
        if (a.time != b.time) {
            return a.time < b.time;
        } else {
            return a.train_id < b.train_id;
        }
    }

    friend bool operator>(timing a, timing b) {
        if (a.time != b.time) {
            return a.time > b.time;
        } else {
            return a.train_id > b.train_id;
        }
    }

    friend bool operator<=(timing a, timing b) {
        if (a.time != b.time) {
            return a.time <= b.time;
        } else {
            return a.train_id <= b.train_id;
        }
    }

    friend bool operator>=(timing a, timing b) {
        if (a.time != b.time) {
            return a.time >= b.time;
        } else {
            return a.train_id >= b.train_id;
        }
    }

    friend bool operator==(timing a, timing b) {
        if (a.time != b.time) {
            return a.time == b.time;
        } else {
            return a.train_id == b.train_id;
        }
    }
};

struct pricing {
    std::string train_id;
    int index;
    int price;
    int s;
    int e;

    friend bool operator<(pricing a, pricing b) {
        if (a.price != b.price) {
            return a.price < b.price;
        } else {
            return a.train_id < b.train_id;
        }
    }

    friend bool operator>(pricing a, pricing b) {
        if (a.price != b.price) {
            return a.price > b.price;
        } else {
            return a.train_id > b.train_id;
        }
    }

    friend bool operator<=(pricing a, pricing b) {
        if (a.price != b.price) {
            return a.price <= b.price;
        } else {
            return a.train_id <= b.train_id;
        }
    }

    friend bool operator>=(pricing a, pricing b) {
        if (a.price != b.price) {
            return a.price >= b.price;
        } else {
            return a.train_id >= b.train_id;
        }
    }

    friend bool operator==(pricing a, pricing b) {
        if (a.price != b.price) {
            return a.price == b.price;
        } else {
            return a.train_id == b.train_id;
        }
    }
};

void merge(pricing *a, int l, int mid, int r) {
    pricing *tmp = new pricing[r - l + 1];
    int cursor1 = l;
    int cursor2 = mid + 1;
    for (int i = 0; i < r - l + 1; ++i) {
        if (cursor1 == mid + 1) {
            tmp[i] = a[cursor2];
            cursor2++;
        } else if (cursor2 == r + 1) {
            tmp[i] = a[cursor1];
            cursor1++;
        } else {
            if (a[cursor2] < a[cursor1]) {
                tmp[i] = a[cursor2];
                cursor2++;
            } else {
                tmp[i] = a[cursor1];
                cursor1++;
            }
        }
    }
    for (int i = l; i <= r; ++i) {
        a[i] = tmp[i - l];
    }
    delete[]tmp;
}

void merge_sort(pricing *a, int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);
    merge(a, l, mid, r);
}

void merge(timing *a, int l, int mid, int r) {
    timing *tmp = new timing[r - l + 1];
    int cursor1 = l;
    int cursor2 = mid + 1;
    for (int i = 0; i < r - l + 1; ++i) {
        if (cursor1 == mid + 1) {
            tmp[i] = a[cursor2];
            cursor2++;
        } else if (cursor2 == r + 1) {
            tmp[i] = a[cursor1];
            cursor1++;
        } else {
            if (a[cursor2] < a[cursor1]) {
                tmp[i] = a[cursor2];
                cursor2++;
            } else {
                tmp[i] = a[cursor1];
                cursor1++;
            }
        }
    }
    for (int i = l; i <= r; ++i) {
        a[i] = tmp[i - l];
    }
    delete[]tmp;
}

void merge_sort(timing *a, int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);
    merge(a, l, mid, r);
}

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
        std::cout << month / 10 << month % 10 << "-" << day / 10 << day % 10;
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
        if (a.day <= 0) {
            if (a.month == 7) {
                a.day += 30;
            } else {
                a.day += 31;
            }
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

class day_time {
public:
    int hour = 0;
    int minute = 0;

    day_time() {
        hour = 0;
        minute = 0;
    };

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

    friend day_time operator+(day_time a, int b) {
        a.minute += b;
        a.hour += a.minute / 60;
        a.minute = a.minute % 60;
        return a;
    }

    friend int operator-(day_time a, day_time b) {
        return 60 * (a.hour - b.hour) + a.minute - b.minute;
    }
};

int day_time_between(date a, day_time a2, date b, day_time b2) {
    return 1440 * (b - a) + (a2 - b2);
}

#endif //TICKET_SYSTEM_TOOLS_H
