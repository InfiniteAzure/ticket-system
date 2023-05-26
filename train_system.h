//
// Created by Xue Jiarui on 2023/5/25.
//

#ifndef TICKET_SYSTEM_TRAIN_SYSTEM_H
#define TICKET_SYSTEM_TRAIN_SYSTEM_H

#include "tools.h"
#include "bplus.h"

class train_system {
public:
    struct train {
        char train_id[35];
        date start;
        date finish;
        day_time go[100];
        day_time stop[100];
        int seat_num;
        int station_num;
        int prices[100];
        char type;
        char stations[100][35];
        bool released = false;
        int save_place;
    };

    struct train_id {
        char train_id_[35];

        friend bool operator<(train_id a, train_id b) {
            return get(a.train_id_) < get(b.train_id_);
        }

        friend bool operator>(train_id a, train_id b) {
            return get(a.train_id_) > get(b.train_id_);
        }

        friend bool operator<=(train_id a, train_id b) {
            return get(a.train_id_) <= get(b.train_id_);
        }

        friend bool operator>=(train_id a, train_id b) {
            return get(a.train_id_) >= get(b.train_id_);
        }

        friend bool operator==(train_id a, train_id b) {
            return get(a.train_id_) == get(b.train_id_);
        }
    };

    struct t_date {
        char train_id_[35];
        date d;

        friend bool operator<(t_date a, t_date b) {
            if (get(a.train_id_) != get(b.train_id_)) {
                return get(a.train_id_) < get(b.train_id_);
            } else {
                return a.d < b.d;
            }
        }

        friend bool operator>=(t_date a, t_date b) {
            if (get(a.train_id_) != get(b.train_id_)) {
                return get(a.train_id_) >= get(b.train_id_);
            } else {
                return a.d >= b.d;
            }
        }

        friend bool operator>(t_date a, t_date b) {
            if (get(a.train_id_) != get(b.train_id_)) {
                return get(a.train_id_) > get(b.train_id_);
            } else {
                return a.d > b.d;
            }
        }

        friend bool operator<=(t_date a, t_date b) {
            if (get(a.train_id_) != get(b.train_id_)) {
                return get(a.train_id_) <= get(b.train_id_);
            } else {
                return a.d <= b.d;
            }
        }

        friend bool operator==(t_date a, t_date b) {
            if (get(a.train_id_) != get(b.train_id_)) {
                return get(a.train_id_) == get(b.train_id_);
            } else {
                return a.d == b.d;
            }
        }
    };

    struct ticket_cond {
        int t[100];
    };

    struct station {
        char station_name[35];
        int save_place;

        friend bool operator<(station a, station b) {
            if (get(a.station_name) != get(b.station_name)) {
                return get(a.station_name) < get(b.station_name);
            } else {
                return a.save_place < b.save_place;
            }
        }

        friend bool operator>(station a, station b) {
            if (get(a.station_name) != get(b.station_name)) {
                return get(a.station_name) > get(b.station_name);
            } else {
                return a.save_place > b.save_place;
            }
        }

        friend bool operator<=(station a, station b) {
            if (get(a.station_name) != get(b.station_name)) {
                return get(a.station_name) <= get(b.station_name);
            } else {
                return a.save_place <= b.save_place;
            }
        }

        friend bool operator>=(station a, station b) {
            if (get(a.station_name) != get(b.station_name)) {
                return get(a.station_name) >= get(b.station_name);
            } else {
                return a.save_place >= b.save_place;
            }
        }

        friend bool operator==(station a, station b) {
            if (get(a.station_name) != get(b.station_name)) {
                return get(a.station_name) == get(b.station_name);
            } else {
                return a.save_place == b.save_place;
            }
        }
    };

    bplus<train_id> trains;
    bplus<t_date> tickets;
    bplus<station> stations;
    std::fstream save;
    std::fstream ticket_saver;
    int write_place = 0;
    int t_write_place = 0;

    train_system() : trains("t_tree", "t_alloc"), tickets("ti_tree", "ti_alloc"), stations("s_tree", "s_alloc") {
        save.open("t_value");
        if (!save.good()) {
            std::ofstream out;
            out.open("t_value");
            write_place = 0;
            out.write(reinterpret_cast<char *>(&write_place), sizeof(int));
            out.close();
            save.open("t_value");
        } else {
            save.seekg(0);
            save.read(reinterpret_cast<char *>(&write_place), sizeof(int));
        }
        ticket_saver.open("t_value");
        if (!ticket_saver.good()) {
            std::ofstream out;
            out.open("t_value");
            t_write_place = 0;
            out.write(reinterpret_cast<char *>(&write_place), sizeof(int));
            out.close();
            ticket_saver.open("t_value");
        } else {
            ticket_saver.seekg(0);
            ticket_saver.read(reinterpret_cast<char *>(&write_place), sizeof(int));
        }
    }

    int write_p() {
        write_place++;
        return write_place - 1;
    }

    int write_t() {
        t_write_place++;
        return t_write_place - 1;
    }

    int add_train(train t, std::string t_id) {
        train_id tr;
        put(tr.train_id_, t_id);
        int q = trains.find(tr);
        if (q != -1) {
            return -1;
        }
        int pos = write_p();
        t.save_place = pos;
        save.seekp(sizeof(int) + pos * sizeof(train));
        save.write(reinterpret_cast<char *>(&t), sizeof(train));
        trains.insert(pos, tr);
        return 0;
    }

    int delete_train(std::string t_id) {
        train_id tr;
        put(tr.train_id_, t_id);
        int pos = trains.find(tr);
        if (pos == -1) {
            return -1;
        }
        trains.erase(tr);
        return 0;
    }

    int release_train(std::string t_id) {
        train_id tr;
        put(tr.train_id_, t_id);
        int pos = trains.find(tr);
        if (pos == -1) {
            return 0;
        }
        train t;
        save.seekg(sizeof(int) + pos * sizeof(train));
        save.read(reinterpret_cast<char *>(&t), sizeof(train));
        if (t.released) {
            return -1;
        }
        t.released = true;
        save.seekp(sizeof(int) + pos * sizeof(train));
        save.write(reinterpret_cast<char *>(&t), sizeof(train));
        for (date d = t.start; d <= t.finish; d = d + 1) {
            t_date td;
            put(td.train_id_, t_id);
            td.d = d;
            ticket_cond tc;
            for (int i = 0; i < t.station_num; ++i) {
                tc.t[i] = t.seat_num;
            }
            int pd = write_t();
            ticket_saver.seekp(sizeof(int) + pd * sizeof(ticket_cond));
            ticket_saver.read(reinterpret_cast<char *>(&tc), sizeof(ticket_cond));
            tickets.insert(pd, td);
        }
        for (int i = 0; i < t.station_num; ++i) {
            station s;
            put(s.station_name, get(t.stations[i]));
            stations.insert(pos, s);
        }
        return 0;
    }

    int query_train(std::string t_id, date da) {
        train_id ti;
        put(ti.train_id_, t_id);
        int pos = trains.find(ti);
        if (pos == -1) {
            return -1;
        }
        train t;
        save.seekg(sizeof(int) + pos * sizeof(train));
        save.read(reinterpret_cast<char *>(&t), sizeof(train));
        t_date td;
        put(td.train_id_, t_id);
        td.d = da;
        if (!t.released) {
            std::cout << t.station_num << '\n';
            for (int i = 0; i < t.station_num; ++i) {
                std::cout << get(t.stations[i]) << " ";
                if (i == 0) {
                    std::cout << "xx-xx xx:xx ";
                } else {
                    date dat = da;
                    while (t.stop[i - 1].hour > 24) {
                        t.stop[i - 1].hour -= 24;
                        da = da + 1;
                    }
                    dat.print();
                    std::cout << ' ';
                    t.stop[i - 1].print();
                    std::cout << ' ';
                }
                std::cout << "-> ";
                if (i == t.station_num - 1) {
                    std::cout << "xx-xx xx:xx ";
                } else {
                    date dat = da;
                    while (t.go[i].hour > 24) {
                        t.go[i].hour -= 24;
                        dat = dat + 1;
                    }
                    dat.print();
                    std::cout << ' ';
                    t.go[i].print();
                    std::cout << ' ';
                }
                std::cout << t.prices[i] << ' ';
                if (i != t.station_num - 1) {
                    std::cout << t.station_num << '\n';
                } else {
                    std::cout << 'x' << '\n';
                }
            }
        } else {
            int pd = tickets.find(td);
            ticket_cond t_c;
            ticket_saver.seekp(sizeof(int) + pd * sizeof(ticket_cond));
            ticket_saver.read(reinterpret_cast<char *>(&t_c), sizeof(ticket_cond));
            std::cout << t.station_num << '\n';
            for (int i = 0; i < t.station_num; ++i) {
                std::cout << get(t.stations[i]) << " ";
                if (i == 0) {
                    std::cout << "xx-xx xx:xx ";
                } else {
                    date dat = da;
                    while (t.stop[i - 1].hour > 24) {
                        t.stop[i - 1].hour -= 24;
                        da = da + 1;
                    }
                    dat.print();
                    std::cout << ' ';
                    t.stop[i - 1].print();
                    std::cout << ' ';
                }
                std::cout << "-> ";
                if (i == t.station_num - 1) {
                    std::cout << "xx-xx xx:xx ";
                } else {
                    date dat = da;
                    while (t.go[i].hour > 24) {
                        t.go[i].hour -= 24;
                        dat = dat + 1;
                    }
                    dat.print();
                    std::cout << ' ';
                    t.go[i].print();
                    std::cout << ' ';
                }
                std::cout << t.prices[i] << ' ';
                if (i != t.station_num - 1) {
                    std::cout << t_c.t[i] << '\n';
                } else {
                    std::cout << 'x' << '\n';
                }
            }
        }
        return 0;
    }

    void search(station query, bplus<station> &b, sjtu::vector<int> &vint) {
        int flag = -1;
        bplus<station>::Node n;
        if (b.I.root == -1) {
            std::cout << "null" << '\n';
            return;
        }
        n = b.get_node(b.I.root);
        while (!n.is_leaf) {
            for (int i = 0; i < n.used_space; ++i) {
                if (query < n.k[i]) {
                    n = b.get_node(n.pos[i]);
                    break;
                }
                if (i == n.used_space - 1) {
                    n = b.get_node(n.pos[n.used_space]);
                    break;
                }
            }
        }
        for (int i = 0; i < n.used_space; ++i) {
            if (get(n.k[i].station_name) == get(query.station_name)) {
                vint.push_back(n.k[i].save_place);
                flag = 1;
            } else if (flag == 1) {
                flag = 0;
            }
        }
        if (flag == -1) {
            if (n.next != -1) {
                n = b.get_node(n.next);
                for (int i = 0; i < n.used_space; ++i) {
                    if (get(n.k[i].station_name) == get(query.station_name)) {
                        vint.push_back(n.k[i].save_place);
                        flag = 1;
                    } else if (flag == 1) {
                        break;
                    }
                }
                if (flag == -1) {
                    return;
                }
            } else {
                return;
            }
        } else {
            if (flag == 0) {
                return;
            }
        }
        while (n.next != -1 && flag != 0) {
            n = b.get_node(n.next);
            for (int i = 0; i < n.used_space; ++i) {
                if (get(n.k[i].station_name) == get(query.station_name)) {
                    vint.push_back(n.k[i].save_place);
                    flag = 1;
                } else if (flag == 1) {
                    flag = 0;
                }
            }
        }
        std::cout << '\n';
    }

    int query_ticket(std::string start, std::string end, date da, bool is_time) {
        station s_s, s_e;
        put(s_s.station_name, start);
        s_s.save_place = -1;
        put(s_e.station_name, end);
        s_e.save_place = -1;
        sjtu::vector<int> vint_s;
        sjtu::vector<int> vint_fin;
        sjtu::vector<int> v_ans;
        search(s_s, stations, vint_s);
        search(s_e, stations, vint_fin);
        int cursor1 = 0,cursor2 = 0;
        while (cursor1 < vint_s.size() && cursor2 < vint_fin.size()) {
            if (vint_s[cursor1] < vint_fin[cursor2]) {
                cursor1++;
            } else if (vint_s[cursor1] < vint_fin[cursor2]) {
                cursor2++;
            } else {
                v_ans.push_back(vint_s[cursor1]);
                cursor1++;
                cursor2++;
            }
        }
        sjtu::vector<train> v_train;
        for (int i = 0;i < v_ans.size();++i) {
            train t;
            save.seekp(sizeof(int) + v_ans[i] * sizeof(train));
            save.write(reinterpret_cast<char *>(&t), sizeof(train));
            v_train.push_back(t);
        }
        if (is_time) {



        }
    }
};


#endif //TICKET_SYSTEM_TRAIN_SYSTEM_H