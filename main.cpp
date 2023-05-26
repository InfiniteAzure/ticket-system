#include <iostream>
#include "bplus.h"
#include "users.h"
#include "processor.h"
#include "train_system.h"

int main() {
    freopen("../basic_2/1.in", "r", stdin);
    freopen("../ans.out", "w", stdout);
    std::string op;
    User_system user_system;
    while(std::getline(std::cin, op)) {
        processor s(op);
        if (s.words[0] == "[492]") {
            int j = 1;
        }
        if (s.words[1] == "add_user") {
            int i = 2;
            std::string st[6];
            while (i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-c") {
                    st[0] = s.words[i + 1];
                } else if (a == "-u") {
                    st[1] = s.words[i + 1];
                } else if (a == "-p") {
                    st[2] = s.words[i + 1];
                } else if (a == "-n") {
                    st[3] = s.words[i + 1];
                } else if (a == "-m") {
                    st[4] = s.words[i + 1];
                } else {
                    st[5] = s.words[i + 1];
                }
                i += 2;
            }
            if (user_system.manage.I.count == 0) {
                int res;
                res = user_system.init(st[1], st[2], st[3], st[4]);
                std::cout << s.words[0] << " " << res << '\n';
            } else {
                int res;
                res = user_system.create_user(st[1], st[2], st[3], st[4], st[0], to_int(st[5]));
                std::cout << s.words[0] << " " << res << '\n';
            }
        } else if (s.words[1] == "login") {
            if (s.words[2] == "-u") {
                int res = user_system.log_in(s.words[3], s.words[5]);
                std::cout << s.words[0] << " " << res << '\n';
            } else {
                int res = user_system.log_in(s.words[5], s.words[3]);
                std::cout << s.words[0] << " " << res << '\n';
            }
        } else if (s.words[1] == "logout") {
            int res = user_system.log_out(s.words[3]);
            std::cout << s.words[0] << " " << res << '\n';
        } else if (s.words[1] == "query_profile") {
            if (s.words[2] == "-c") {
                std::cout << s.words[0] << " ";
                int res = user_system.query_profile(s.words[3], s.words[5]);
                if (res == -1) {
                    std::cout << -1;
                }
                std::cout << '\n';
            } else {
                std::cout << s.words[0] << " ";
                int res = user_system.query_profile(s.words[5], s.words[3]);
                if (res == -1) {
                    std::cout << -1;
                }
                std::cout << '\n';
            }
        } else if (s.words[1] == "modify_profile") {
            int i = 2;
            std::string st[6];
            for (int j = 0; j < 6; ++j) {
                st[j] = not_changed;
            }
            while (i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-c") {
                    st[0] = s.words[i + 1];
                } else if (a == "-u") {
                    st[1] = s.words[i + 1];
                } else if (a == "-p") {
                    st[2] = s.words[i + 1];
                } else if (a == "-n") {
                    st[3] = s.words[i + 1];
                } else if (a == "-m") {
                    st[4] = s.words[i + 1];
                } else {
                    st[5] = s.words[i + 1];
                }
                i += 2;
            }
            std::cout << s.words[0] << " ";
            int res = user_system.modify_profile(st[0], st[1], st[2],
                                                 st[3], st[4], to_int(st[5]));
            if (res == -1) {
                std::cout << -1;
            }
            std::cout << '\n';
        } else if (s.words[1] == "exit") {
            std::cout << s.words[0] << " bye" << '\n';
            break;
        }
    }
    return 0;
}
