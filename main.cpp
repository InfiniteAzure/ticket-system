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
    train_system t_system;
    while(std::getline(std::cin, op)) {
        processor s(op);
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
        } else if (s.words[1] == "add_train") {
            train_system::train t;
            int i = 2;
            std::string st[9];
            while(i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-i") {
                    st[0] = s.words[i + 1];
                } else if (a == "-n") {
                    st[1] = s.words[i + 1];
                } else if (a == "-m") {
                    st[2] = s.words[i + 1];
                } else if (a == "-s") {
                    st[3] = s.words[i + 1];
                } else if (a == "-p") {
                    st[4] = s.words[i + 1];
                } else if (a == "-x") {
                    st[5] = s.words[i + 1];
                } else if (a == "-t") {
                    st[6] = s.words[i + 1];
                } else if (a == "-o") {
                    st[7] = s.words[i + 1];
                } else if (a == "-d") {
                    st[8] = s.words[i + 1];
                } else {
                    st[9] = s.words[i + 1];
                }
                i += 2;
            }
            put(t.train_id,st[0]);
            t.station_num = to_int(st[1]);
            t.seat_num = to_int(st[2]);
            sjtu::vector<std::string> ans1,ans2,ans3,ans4,ans5;
            cut(st[3],ans1);
            for (int j = 0;j < t.station_num;++j) {
                put(t.stations[j],ans1[j]);
            }
            cut (st[4],ans2);
            for (int j = 0;j < t.station_num;++j) {
                t.prices[j] = to_int(ans2[j]);
            }
            cut (st[6],ans3);
            cut (st[7],ans4);
            for (int j = 0;j < t.station_num;++j) {
                if (j == 0) {
                    day_time d(st[5]);
                    t.go[j] = d;
                } else if (j != t.station_num - 1){
                    t.stop[j - 1] = t.go[j - 1] + to_int(ans3[j - 1]);
                    t.go[j] = t.stop[j - 1] + to_int(ans4[j - 1]);
                } else {
                    t.stop[j - 1] = t.go[j - 1] + to_int(ans3[j - 1]);
                }
            }
            cut(st[8],ans5);
            date d1(ans5[1]);
            date d2(ans5[2]);
            t.start = d1;
            t.finish = d2;
            t.type = st[9][0];
            int ans = t_system.add_train(t,st[0]);
            std::cout << s.words[0] << " " << ans << '\n';
        }
    }
    return 0;
}
