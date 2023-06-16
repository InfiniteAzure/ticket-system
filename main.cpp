#include <iostream>
#include "bplus.h"
#include "users.h"
#include "processor.h"
#include "train_system.h"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    freopen("../basic/1.in", "r", stdin);
    freopen("../ans.out", "w", stdout);
    std::string op;
    User_system user_system;
    train_system t_system;
    while (std::getline(std::cin, op)) {
        processor s(op);
        if (s.words[0] == "[38948]") {
            int nmsl = 0;
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
        } else if (s.words[1] == "add_train") {
            train_system::train t;
            int i = 2;
            std::string st[10];
            while (i <= s.size - 1) {
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
            put(t.train_id, st[0]);
            t.station_num = to_int(st[1]);
            t.seat_num = to_int(st[2]);
            sjtu::vector<std::string> ans1, ans2, ans3, ans4, ans5;
            cut(st[3], ans1);
            for (int j = 0; j < t.station_num; ++j) {
                put(t.stations[j], ans1[j]);
            }
            cut(st[4], ans2);
            for (int j = 0; j < t.station_num; ++j) {
                if (j == 0) {
                    t.prices[j] = 0;
                } else {
                    t.prices[j] = t.prices[j - 1] + to_int(ans2[j - 1]);
                }
            }
            cut(st[6], ans3);
            cut(st[7], ans4);
            for (int j = 0; j < t.station_num; ++j) {
                if (j == 0) {
                    day_time d(st[5]);
                    t.go[j] = d;
                } else if (j != t.station_num - 1) {
                    t.stop[j - 1] = t.go[j - 1] + to_int(ans3[j - 1]);
                    t.go[j] = t.stop[j - 1] + to_int(ans4[j - 1]);
                } else {
                    t.stop[j - 1] = t.go[j - 1] + to_int(ans3[j - 1]);
                }
            }
            cut(st[8], ans5);
            date d1(ans5[0]);
            date d2(ans5[1]);
            t.start = d1;
            t.finish = d2;
            t.type = st[9][0];
            int ans = t_system.add_train(t, st[0]);
            std::cout << s.words[0] << " " << ans << '\n';
        } else if (s.words[1] == "delete_train") {
            int ans = t_system.delete_train(s.words[3]);
            std::cout << s.words[0] << " " << ans << '\n';
        } else if (s.words[1] == "release_train") {
            int ans = t_system.release_train(s.words[3]);
            std::cout << s.words[0] << " " << ans << '\n';
        } else if (s.words[1] == "delete_train") {
            int ans = t_system.delete_train(s.words[3]);
            std::cout << s.words[0] << " " << ans << '\n';
        } else if (s.words[1] == "query_train") {
            std::cout << s.words[0] << " ";
            int i = 2;
            std::string st[2];
            while (i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-i") {
                    st[0] = s.words[i + 1];
                } else if (a == "-d") {
                    st[1] = s.words[i + 1];
                }
                i += 2;
            }
            date da(st[1]);
            int ans = t_system.query_train(st[0], da);
            if (ans == -1) {
                std::cout << ans << '\n';
            }
        } else if (s.words[1] == "query_ticket") {
            int i = 2;
            std::string st[4];
            st[3] = not_changed;
            while (i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-s") {
                    st[0] = s.words[i + 1];
                } else if (a == "-t") {
                    st[1] = s.words[i + 1];
                } else if (a == "-d") {
                    st[2] = s.words[i + 1];
                } else if (a == "-p") {
                    st[3] = s.words[i + 1];
                }
                i += 2;
            }
            date da(st[2]);
            t_system.query_ticket(st[0],st[1],da,!(st[3] == "cost"),s.words[0]);
        } else if (s.words[1] == "query_transfer") {
            std::cout << s.words[0];
            int i = 2;
            std::string st[4];
            st[3] = not_changed;
            while (i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-s") {
                    st[0] = s.words[i + 1];
                } else if (a == "-t") {
                    st[1] = s.words[i + 1];
                } else if (a == "-d") {
                    st[2] = s.words[i + 1];
                } else if (a == "-p") {
                    st[3] = s.words[i + 1];
                }
                i += 2;
            }
            date da(st[2]);
            //std::cout << "transfer nmsl" << '\n';
            t_system.query_transfer(st[0],st[1],da,!(st[3] == "cost"));
        } else if (s.words[1] == "buy_ticket") {
            int i = 2;
            std::string st[7];
            st[6] = not_changed;
            while (i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-u") {
                    st[0] = s.words[i + 1];
                } else if (a == "-i") {
                    st[1] = s.words[i + 1];
                } else if (a == "-d") {
                    st[2] = s.words[i + 1];
                } else if (a == "-n") {
                    st[3] = s.words[i + 1];
                } else if (a == "-f") {
                    st[4] = s.words[i + 1];
                } else if (a == "-t") {
                    st[5] = s.words[i + 1];
                } else if (a == "-q") {
                    st[6] = s.words[i + 1];
                }
                i += 2;
            }
            train_system::order o;
            put(o.user_id,st[0]);
            put(o.train_id,st[1]);
            date da(st[2]);
            o.d = da;
            put(o.start,st[4]);
            put(o.arrive,st[5]);
            o.number = to_int(st[3]);
            if (st[6] == "true") {
                o.cond = -1;
            } else {
                o.cond = 0;
            }
            long long ans = t_system.buy_ticket(o,user_system);
            if (ans == -2) {
                std::cout << s.words[0] << " queue" << '\n';
            } else if (ans == -1) {
                std::cout << s.words[0] << " -1" << '\n';
            } else {
                std::cout << s.words[0] << " " << ans << '\n';
            }
        } else if (s.words[1] == "query_order") {
            std::cout << s.words[0] << " ";
            int ans = t_system.query_order(s.words[3],user_system);
            if (ans == -1) {
                std::cout << "-1" << '\n';
            }
        } else if (s.words[1] == "refund_ticket") {
            std::string st[2];
            st[1] = not_changed;
            int i = 2;
            while (i <= s.size - 1) {
                std::string a = s.words[i];
                if (a == "-u") {
                    st[0] = s.words[i + 1];
                } else if (a == "-n") {
                    st[1] = s.words[i + 1];
                }
                i += 2;
            }
            int n;
            if (st[1] == not_changed) {
                n = -1;
            } else {
                n = to_int(st[1]);
            }
            int ans = t_system.refund_ticket(st[0],n,user_system);
            std::cout << s.words[0] << " " << ans << '\n';
        } else if (s.words[1] == "clean") {
            t_system.clear();
            user_system.clear();
            std::cout << s.words[0] << " 0" << '\n';
        }
    }
    return 0;
}
