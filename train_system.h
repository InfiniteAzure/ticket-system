//
// Created by Xue Jiarui on 2023/5/25.
//

#ifndef TICKET_SYSTEM_TRAIN_SYSTEM_H
#define TICKET_SYSTEM_TRAIN_SYSTEM_H

#include "tools.h"
#include "bplus.h"
#include "vector.hpp"

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

    struct o_t {
        char train_id[35];
        date depart;
        int save_place;

        friend bool operator<(o_t a, o_t b) {
            if (get(a.train_id) != get(b.train_id)) {
                return get(a.train_id) < get(b.train_id);
            } else if (!(a.depart == b.depart)) {
                return a.depart < b.depart;
            } else {
                return a.save_place < b.save_place;
            }
        }

        friend bool operator>(o_t a, o_t b) {
            if (get(a.train_id) != get(b.train_id)) {
                return get(a.train_id) > get(b.train_id);
            } else if (!(a.depart == b.depart)) {
                return a.depart > b.depart;
            } else {
                return a.save_place > b.save_place;
            }
        }

        friend bool operator<=(o_t a, o_t b) {
            if (get(a.train_id) != get(b.train_id)) {
                return get(a.train_id) <= get(b.train_id);
            } else if (!(a.depart == b.depart)) {
                return a.depart <= b.depart;
            } else {
                return a.save_place <= b.save_place;
            }
        }

        friend bool operator>=(o_t a, o_t b) {
            if (get(a.train_id) != get(b.train_id)) {
                return get(a.train_id) >= get(b.train_id);
            } else if (!(a.depart == b.depart)) {
                return a.depart >= b.depart;
            } else {
                return a.save_place >= b.save_place;
            }
        }

        friend bool operator==(o_t a, o_t b) {
            if (get(a.train_id) != get(b.train_id)) {
                return get(a.train_id) == get(b.train_id);
            } else if (!(a.depart == b.depart)) {
                return a.depart == b.depart;
            } else {
                return a.save_place == b.save_place;
            }
        }
    };

    struct o_u {
        char user_name[35];
        int save_place;

        friend bool operator<(o_u a, o_u b) {
            if (get(a.user_name) != get(b.user_name)) {
                return get(a.user_name) < get(b.user_name);
            } else {
                return a.save_place < b.save_place;
            }
        }

        friend bool operator<=(o_u a, o_u b) {
            if (get(a.user_name) != get(b.user_name)) {
                return get(a.user_name) <= get(b.user_name);
            } else {
                return a.save_place <= b.save_place;
            }
        }

        friend bool operator>(o_u a, o_u b) {
            if (get(a.user_name) != get(b.user_name)) {
                return get(a.user_name) > get(b.user_name);
            } else {
                return a.save_place > b.save_place;
            }
        }

        friend bool operator>=(o_u a, o_u b) {
            if (get(a.user_name) != get(b.user_name)) {
                return get(a.user_name) >= get(b.user_name);
            } else {
                return a.save_place >= b.save_place;
            }
        }

        friend bool operator==(o_u a, o_u b) {
            if (get(a.user_name) != get(b.user_name)) {
                return get(a.user_name) == get(b.user_name);
            } else {
                return a.save_place == b.save_place;
            }
        }
    };


    struct order {
        char user_id[35];
        char train_id[35];
        char start[35];
        char arrive[35];
        int number;
        int price;
        int cond;
        int save_place;
        date d;
        day_time go;
        day_time arrival;
    };

    bplus<train_id> trains;
    bplus<t_date> tickets;
    bplus<station> stations;
    bplus<o_u> u_order;
    bplus<o_t> t_order;
    std::fstream save;
    std::fstream ticket_saver;
    std::fstream order_saver;
    int write_place = 0;
    int t_write_place = 0;
    int o_write_place = 0;

    train_system() : trains("t_tree", "t_alloc"), tickets("ti_tree", "ti_alloc"),
                     stations("s_tree", "s_alloc"), u_order("us_tree", "us_alloc"), t_order("tr_tree", "tr_alloc") {
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
        ticket_saver.open("ti_value");
        if (!ticket_saver.good()) {
            std::ofstream out;
            out.open("ti_value");
            t_write_place = 0;
            out.write(reinterpret_cast<char *>(&t_write_place), sizeof(int));
            out.close();
            ticket_saver.open("ti_value");
        } else {
            ticket_saver.seekg(0);
            ticket_saver.read(reinterpret_cast<char *>(&t_write_place), sizeof(int));
        }
        order_saver.open("o_value");
        if (!order_saver.good()) {
            std::ofstream out;
            out.open("o_value");
            o_write_place = 0;
            out.write(reinterpret_cast<char *>(&o_write_place), sizeof(int));
            out.close();
            order_saver.open("o_value");
        } else {
            order_saver.seekg(0);
            order_saver.read(reinterpret_cast<char *>(&o_write_place), sizeof(int));
        }
    }

    ~train_system() {
        save.seekp(0);
        save.write(reinterpret_cast<char *>(&write_place), sizeof(int));
        ticket_saver.seekp(0);
        ticket_saver.write(reinterpret_cast<char *>(&t_write_place), sizeof(int));
        order_saver.seekp(0);
        order_saver.write(reinterpret_cast<char *>(&o_write_place), sizeof(int));
        save.close();
        ticket_saver.close();
        order_saver.close();
    }

    int write_p() {
        write_place++;
        return write_place - 1;
    }

    int write_t() {
        t_write_place++;
        return t_write_place - 1;
    }

    int write_o() {
        o_write_place++;
        return o_write_place - 1;
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
        train t;
        save.seekg(sizeof(int) + pos * sizeof(train));
        save.read(reinterpret_cast<char *>(&t), sizeof(train));
        if (t.released) {
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
            ticket_saver.write(reinterpret_cast<char *>(&tc), sizeof(ticket_cond));
            tickets.insert(pd, td);
        }
        for (int i = 0; i < t.station_num; ++i) {
            station s;
            put(s.station_name, get(t.stations[i]));
            s.save_place = t.save_place;
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
        if (da < t.start || da > t.finish) {
            return -1;
        }
        if (!t.released) {
            std::cout << get(t.train_id) << " " << t.type << '\n';
            for (int i = 0; i < t.station_num; ++i) {
                std::cout << get(t.stations[i]) << " ";
                if (i == 0) {
                    std::cout << "xx-xx xx:xx ";
                } else {
                    date dat = da;
                    while (t.stop[i - 1].hour >= 24) {
                        t.stop[i - 1].hour -= 24;
                        dat = dat + 1;
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
                    while (t.go[i].hour >= 24) {
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
                    std::cout << t.seat_num << '\n';
                } else {
                    std::cout << 'x' << '\n';
                }
            }
        } else {
            int pd = tickets.find(td);
            ticket_cond t_c;
            ticket_saver.seekg(sizeof(int) + pd * sizeof(ticket_cond));
            ticket_saver.read(reinterpret_cast<char *>(&t_c), sizeof(ticket_cond));
            std::cout << get(t.train_id) << " " << t.type << '\n';
            for (int i = 0; i < t.station_num; ++i) {
                std::cout << get(t.stations[i]) << " ";
                if (i == 0) {
                    std::cout << "xx-xx xx:xx ";
                } else {
                    date dat = da;
                    while (t.stop[i - 1].hour >= 24) {
                        t.stop[i - 1].hour -= 24;
                        dat = dat + 1;
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
                    while (t.go[i].hour >= 24) {
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
        if (b.I.count == 0) {
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
    }


    int query_ticket(std::string start, std::string end, date da, bool is_time, std::string header) {
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
        int cursor1 = 0, cursor2 = 0;
        while (cursor1 < vint_s.size() && cursor2 < vint_fin.size()) {
            if (vint_s[cursor1] < vint_fin[cursor2]) {
                cursor1++;
            } else if (vint_s[cursor1] > vint_fin[cursor2]) {
                cursor2++;
            } else {
                v_ans.push_back(vint_s[cursor1]);
                cursor1++;
                cursor2++;
            }
        }
        sjtu::vector<train> v_train;
        for (int i = 0; i < v_ans.size(); ++i) {
            train t;
            save.seekg(sizeof(int) + v_ans[i] * sizeof(train));
            save.read(reinterpret_cast<char *>(&t), sizeof(train));
            v_train.push_back(t);
        }
        if (is_time) {
            timing t[v_ans.size()];
            for (int i = 0; i < v_ans.size(); ++i) {
                int s, e;
                for (int j = 0; j < v_train[i].station_num; ++j) {
                    if (get(v_train[i].stations[j]) == start) {
                        s = j;
                    }
                    if (get(v_train[i].stations[j]) == end) {
                        e = j;
                    }
                }
                if (s > e) {
                    t[i].train_id = get(v_train[i].train_id);
                    t[i].time = -1;
                    t[i].index = i;
                } else {
                    t[i].train_id = get(v_train[i].train_id);
                    t[i].time = v_train[i].stop[e - 1] - v_train[i].go[s];
                    t[i].index = i;
                    t[i].s = s;
                    t[i].e = e;
                }
            }
            merge_sort(t, 0, v_ans.size() - 1);
            int size = 0;
            for (int i = 0; i < v_ans.size(); ++i) {
                if (t[i].time != -1) {
                    train target = v_train[t[i].index];
                    date d = da;
                    while (target.go[t[i].s].hour >= 24) {
                        d = d - 1;
                        target.go[t[i].s].hour -= 24;
                    }
                    if (d >= target.start && d <= target.finish) {
                        size++;
                    }
                }

            }
            std::cout << header << ' ' << size << '\n';
            for (int i = 0; i < v_ans.size(); ++i) {
                if (t[i].time != -1) {
                    train *target = &v_train[t[i].index];
                    date d = da;
                    while (target->go[t[i].s].hour >= 24) {
                        d = d - 1;
                        target->go[t[i].s].hour -= 24;
                    }
                    date depart = d;
                    if (d >= target->start && d <= target->finish) {
                        std::cout << get(target->train_id) << " ";
                        std::cout << start << " ";
                        da.print();
                        std::cout << " ";
                        target->go[t[i].s].print();
                        std::cout << " -> ";
                        std::cout << end << " ";
                        while (target->stop[t[i].e - 1].hour >= 24) {
                            d = d + 1;
                            target->stop[t[i].e - 1].hour -= 24;
                        }
                        d.print();
                        std::cout << " ";
                        target->stop[t[i].e - 1].print();
                        std::cout << " ";
                        std::cout << target->prices[t[i].e] - target->prices[t[i].s] << " ";
                        t_date td;
                        put(td.train_id_, target->train_id);
                        td.d = depart;
                        int po = tickets.find(td);
                        ticket_cond t_c;
                        ticket_saver.seekg(sizeof(int) + po * sizeof(ticket_cond));
                        ticket_saver.read(reinterpret_cast<char *>(&t_c), sizeof(ticket_cond));
                        int min = target->seat_num;
                        for (int j = t[i].s; j < t[i].e; ++j) {
                            if (t_c.t[j] < min) {
                                min = t_c.t[j];
                            }
                        }
                        std::cout << min << "\n";
                    }
                }
            }
        } else {
            pricing pr[v_train.size()];
            for (int i = 0; i < v_ans.size(); ++i) {
                int s, e;
                for (int j = 0; j < v_train[i].station_num; ++j) {
                    if (get(v_train[i].stations[j]) == start) {
                        s = j;
                    }
                    if (get(v_train[i].stations[j]) == end) {
                        e = j;
                    }
                }
                if (s > e) {
                    pr[i].train_id = get(v_train[i].train_id);
                    pr[i].price = -1;
                    pr[i].index = i;
                } else {
                    pr[i].train_id = get(v_train[i].train_id);
                    pr[i].price = v_train[i].prices[e] - v_train[i].prices[s];
                    pr[i].index = i;
                    pr[i].s = s;
                    pr[i].e = e;
                }
            }
            merge_sort(pr, 0, v_train.size() - 1);
            int size = 0;
            for (int i = 0; i < v_ans.size(); ++i) {
                if (pr[i].price != -1) {
                    train target = v_train[pr[i].index];
                    date d = da;
                    while (target.go[pr[i].s].hour >= 24) {
                        d = d - 1;
                        target.go[pr[i].s].hour -= 24;
                    }
                    if (d >= target.start && d <= target.finish) {
                        size++;
                    }
                }
            }
            std::cout << header << ' ' << size << '\n';
            for (int i = 0; i < v_ans.size(); ++i) {
                if (pr[i].price != -1) {
                    train *target = &v_train[pr[i].index];
                    date d = da;
                    while (target->go[pr[i].s].hour >= 24) {
                        d = d - 1;
                        target->go[pr[i].s].hour -= 24;
                    }
                    date depart = d;
                    if (d >= target->start && d <= target->finish) {
                        std::cout << get(target->train_id) << " ";
                        std::cout << start << " ";
                        da.print();
                        std::cout << " ";
                        target->go[pr[i].s].print();
                        std::cout << " -> ";
                        while (target->stop[pr[i].e - 1].hour >= 24) {
                            d = d + 1;
                            target->stop[pr[i].e - 1].hour -= 24;
                        }
                        std::cout << end << " ";
                        d.print();
                        std::cout << " ";
                        target->stop[pr[i].e - 1].print();
                        std::cout << " ";
                        std::cout << target->prices[pr[i].e] - target->prices[pr[i].s] << " ";
                        t_date td;
                        put(td.train_id_, target->train_id);
                        td.d = depart;
                        int po = tickets.find(td);
                        ticket_cond t_c;
                        ticket_saver.seekg(sizeof(int) + po * sizeof(ticket_cond));
                        ticket_saver.read(reinterpret_cast<char *>(&t_c), sizeof(ticket_cond));
                        int min = target->seat_num;
                        for (int j = pr[i].s; j < pr[i].e; ++j) {
                            if (t_c.t[j] < min) {
                                min = t_c.t[j];
                            }
                        }
                        std::cout << min << "\n";
                    }
                }
            }

        }
        return 0;
    }

    long long buy_ticket(order o, User_system &us) {
        User_system::user *p = us.find(get(o.user_id));
        if (p == nullptr) {
            return -1;
        }
        train_id qu;
        put(qu.train_id_, get(o.train_id));
        int po = trains.find(qu);
        if (po == -1) {
            return -1;
        }
        train buyer;
        save.seekg(sizeof(int) + po * sizeof(train));
        save.read(reinterpret_cast<char *>(&buyer), sizeof(train));
        if (!buyer.released) {
            return -1;
        }
        int s = -1, e = -1;
        for (int i = 0; i < buyer.station_num; ++i) {
            if (get(o.start) == get(buyer.stations[i])) {
                s = i;
            }
            if (get(o.arrive) == get(buyer.stations[i])) {
                e = i;
            }
        }
        if (e == -1 || s == -1 || e < s) {
            return -1;
        }
        t_date td;
        put(td.train_id_, get(o.train_id));
        td.d = o.d;
        td.d = td.d - buyer.go[s].hour / 24;
        if (td.d < buyer.start || td.d > buyer.finish) {
            return -1;
        }
        int t_pos = tickets.find(td);
        ticket_cond t_c;
        ticket_saver.seekg(sizeof(int) + t_pos * sizeof(ticket_cond));
        ticket_saver.read(reinterpret_cast<char *>(&t_c), sizeof(ticket_cond));
        bool flag = true;
        for (int i = s; i < e; ++i) {
            if (t_c.t[i] < o.number) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            if (o.cond == -1) {
                o_t t;
                put(t.train_id, get(o.train_id));
                int pos = write_o();
                t.save_place = pos;
                t.depart = td.d;
                t_order.insert(pos, t);
                o_u u;
                put(u.user_name, get(o.user_id));
                u.save_place = pos;
                u_order.insert(pos, u);
                o.go = buyer.go[s];
                o.arrival = buyer.stop[e - 1];
                int j = 0;
                while (o.go.hour >= 24) {
                    o.go.hour -= 24;
                    j++;
                }
                o.arrival.hour -= 24 * j;
                long long ans = buyer.prices[e] - buyer.prices[s];
                o.price = ans;
                order_saver.seekp(sizeof(int) + pos * sizeof(order));
                order_saver.write(reinterpret_cast<char *>(&o), sizeof(order));
                return -2;
            } else {
                return -1;
            }
        }
        o.cond = 0;
        for (int i = s; i < e; ++i) {
            t_c.t[i] -= o.number;
        }
        ticket_saver.seekp(sizeof(int) + t_pos * sizeof(t_c));
        ticket_saver.write(reinterpret_cast<char *>(&t_c), sizeof(t_c));
        o_t t;
        put(t.train_id, get(o.train_id));
        int pos = write_o();
        t.save_place = pos;
        t.depart = td.d;
        t_order.insert(pos, t);
        o_u u;
        put(u.user_name, get(o.user_id));
        u.save_place = pos;
        u_order.insert(pos, u);
        o.go = buyer.go[s];
        o.arrival = buyer.stop[e - 1];
        int i = 0;
        while (o.go.hour >= 24) {
            o.go.hour -= 24;
            i++;
        }
        o.arrival.hour -= 24 * i;
        long long ans = buyer.prices[e] - buyer.prices[s];
        o.price = ans;
        ans *= o.number;
        order_saver.seekp(sizeof(int) + pos * sizeof(order));
        order_saver.write(reinterpret_cast<char *>(&o), sizeof(order));
        return ans;
    }

    void search_o(o_u query, bplus<o_u> &b, sjtu::vector<int> &vint) {
        int flag = -1;
        bplus<o_u>::Node n;
        if (b.I.count == 0) {
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
            if (get(n.k[i].user_name) == get(query.user_name)) {
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
                    if (get(n.k[i].user_name) == get(query.user_name)) {
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
                if (get(n.k[i].user_name) == get(query.user_name)) {
                    vint.push_back(n.k[i].save_place);
                    flag = 1;
                } else if (flag == 1) {
                    flag = 0;
                }
            }
        }
    }

    void search_ot(o_t query, bplus<o_t> &b, sjtu::vector<int> &vint) {
        int flag = -1;
        bplus<o_t>::Node n;
        if (b.I.count == 0) {
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
            if (get(n.k[i].train_id) == get(query.train_id) &&
                n.k[i].depart == query.depart) {
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
                    if (get(n.k[i].train_id) == get(query.train_id) &&
                        n.k[i].depart == query.depart) {
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
                if (get(n.k[i].train_id) == get(query.train_id) &&
                    n.k[i].depart == query.depart) {
                    vint.push_back(n.k[i].save_place);
                    flag = 1;
                } else if (flag == 1) {
                    flag = 0;
                }
            }
        }
    }

    int query_order(std::string u_name, User_system &u) {
        User_system::user *p;
        p = u.find(u_name);
        if (p == nullptr) {
            return -1;
        }
        o_u o_search;
        put(o_search.user_name, u_name);
        o_search.save_place = -1;
        sjtu::vector<int> v_ans;
        sjtu::vector<order> v_o;
        search_o(o_search, u_order, v_ans);
        for (int i = 0; i < v_ans.size(); ++i) {
            order o;
            order_saver.seekg(sizeof(int) + v_ans[i] * sizeof(order));
            order_saver.read(reinterpret_cast<char *>(&o), sizeof(order));
            v_o.push_back(o);
        }
        std::cout << v_o.size() << '\n';
        for (int i = v_o.size() - 1; i >= 0; --i) {
            order *print = &v_o[i];
            if (print->cond == -1) {
                std::cout << "[pending] ";
            } else if (print->cond == -2) {
                std::cout << "[refunded] ";
            } else {
                std::cout << "[success] ";
            }
            std::cout << get(print->train_id) << ' ';
            std::cout << get(print->start) << ' ';
            print->d.print();
            std::cout << " ";
            print->go.print();
            date da = print->d;
            while (print->arrival.hour >= 24) {
                da = da + 1;
                print->arrival.hour -= 24;
            }
            std::cout << " -> ";
            std::cout << get(print->arrive) << ' ';
            da.print();
            std::cout << " ";
            print->arrival.print();
            std::cout << " ";
            std::cout << print->price << " " << print->number << '\n';
        }
        return 0;
    }

    int refund_ticket(std::string u_name, int n, User_system &u) {
        User_system::user *p;
        p = u.find(u_name);
        if (p == nullptr) {
            return -1;
        }
        o_u o_search;
        put(o_search.user_name, u_name);
        o_search.save_place = -1;
        sjtu::vector<int> v_ans;
        order o;
        search_o(o_search, u_order, v_ans);
        if (n > v_ans.size()) {
            return -1;
        }
        order_saver.seekg(sizeof(int) + v_ans[v_ans.size() - n] * sizeof(order));
        order_saver.read(reinterpret_cast<char *>(&o), sizeof(order));
        order *change = &o;
        if (change->cond == -2) {
            return -1;
        }
        if (change->cond == -1) {
            change->cond = -2;
            order_saver.seekp(sizeof(int) + v_ans[v_ans.size() - n] * sizeof(order));
            order_saver.write(reinterpret_cast<char *>(&*change), sizeof(order));
            return 0;
        }
        change->cond = -2;
        train_id t;
        put(t.train_id_, get(change->train_id));
        int pos = trains.find(t);
        train sell;
        save.seekg(sizeof(int) + pos * sizeof(train));
        save.read(reinterpret_cast<char *>(&sell), sizeof(train));
        sjtu::vector<int> pending;
        ticket_cond t_c;
        int s, e;
        for (int i = 0; i < sell.station_num; ++i) {
            if (get(sell.stations[i]) == get(change->start)) {
                s = i;
            }
            if (get(sell.stations[i]) == get(change->arrive)) {
                e = i;
            }
        }
        date da = change->d;
        da = da - (sell.go[s].hour / 24);
        t_date td;
        td.d = da;
        put(td.train_id_, get(sell.train_id));
        int po = tickets.find(td);
        ticket_saver.seekg(sizeof(int) + po * sizeof(t_c));
        ticket_saver.read(reinterpret_cast<char *>(&t_c), sizeof(t_c));
        for (int i = s; i < e; ++i) {
            t_c.t[i] += change->number;
        }
        order_saver.seekp(sizeof(int) + v_ans[v_ans.size() - n] * sizeof(order));
        order_saver.write(reinterpret_cast<char *>(&*change), sizeof(order));
        o_t query;
        put(query.train_id, get(sell.train_id));
        query.save_place = -1;
        query.depart = da;
        search_ot(query, t_order, pending);
        sjtu::vector<order> pending_order;
        for (int i = 0; i < pending.size(); ++i) {
            order ors;
            order_saver.seekg(sizeof(int) + pending[i] * sizeof(order));
            order_saver.read(reinterpret_cast<char *>(&ors), sizeof(order));
            pending_order.push_back(ors);
        }
        for (int i = 0; i < pending.size(); ++i) {
            if (pending_order[i].cond == -1) {
                order *c = &pending_order[i];
                int st, en;
                for (int j = 0; j < sell.station_num; ++j) {
                    if (get(sell.stations[j]) == get(c->start)) {
                        st = j;
                    }
                    if (get(sell.stations[j]) == get(c->arrive)) {
                        en = j;
                    }
                }
                bool flag = true;
                for (int j = st; j < en; ++j) {
                    if (t_c.t[j] < c->number) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    for (int j = st; j < en; ++j) {
                        t_c.t[j] -= c->number;
                    }
                    c->cond = 0;
                }
                order_saver.seekp(sizeof(int) + pending[i] * sizeof(order));
                order_saver.write(reinterpret_cast<char *>(&*c), sizeof(order));
            }
        }
        ticket_saver.seekp(sizeof(int) + po * sizeof(t_c));
        ticket_saver.write(reinterpret_cast<char *>(&t_c), sizeof(t_c));
        return 0;
    }

    struct hash_node {
        std::string train_id;
        std::string station;
        int place;
        hash_node *next = nullptr;
    };

    int hash(std::string s) {
        int ans = 0;
        for (int i = 0; i < s.length(); ++i) {
            ans *= 5;
            int n;
            if (s[i] < 0) {
                n = s[i] * -1;
            } else {
                n = s[i];
            }
            ans += n;
            ans = ans % 47;
        }
        return ans;
    }

    void query_transfer(std::string start, std::string finish, date da, bool is_time) {
        sjtu::vector<int> train_A;
        sjtu::vector<int> train_B;
        station s_start, s_finish;
        put(s_start.station_name, start);
        put(s_finish.station_name, finish);
        s_start.save_place = -1;
        s_finish.save_place = -1;
        search(s_start, stations, train_A);
        search(s_finish, stations, train_B);
        sjtu::vector<train> A_station, B_station;
        for (int i = 0; i < train_A.size(); ++i) {
            train tmp;
            save.seekg(sizeof(int) + train_A[i] * sizeof(train));
            save.read(reinterpret_cast<char *>(&tmp), sizeof(train));
            A_station.push_back(tmp);
        }
        for (int i = 0; i < train_B.size(); ++i) {
            train tmp;
            save.seekg(sizeof(int) + train_B[i] * sizeof(train));
            save.read(reinterpret_cast<char *>(&tmp), sizeof(train));
            B_station.push_back(tmp);
        }
        hash_node *n[50] = {nullptr};
        for (int i = 0; i < train_A.size(); ++i) {
            train *t = &A_station[i];
            bool flag = false;
            for (int j = 0; j < t->station_num; ++j) {
                if (flag) {
                    int p = hash(get(t->stations[j]));
                    hash_node *no = new hash_node;
                    no->train_id = get(t->train_id);
                    no->station = get(t->stations[j]);
                    no->next = n[p];
                    no->place = i;
                    n[p] = no;
                } else if (get(t->stations[j]) == start) {
                    flag = true;
                }
            }
        }
        train *ans_A = nullptr;
        train *ans_B = nullptr;
        int time = 100000000;
        int price = 1000000000;
        date ans_A_go,ans_B_go;
        day_time ans_t1,ans_t2,ans_t3,ans_t4;
        std::string mid;
        int price1,price2;
        for (int i = 0; i < train_B.size(); ++i) {
            train *t = &B_station[i];
            for (int j = 0; j < t->station_num; ++j) {
                if (get(t->stations[j]) == finish) {
                    break;
                }
                int p = hash(get(t->stations[j]));
                hash_node *check = n[p];
                int as,af,bs,bf;
                while (check != nullptr) {
                    if (check->station == get(t->stations[j])
                        && check->train_id != get(t->train_id)) {
                        train *A = &A_station[check->place];
                        train *B = &B_station[i];
                        date A_go = da;
                        day_time t1, t2, t3, t4;
                        for (int k = 0; k < A->station_num; ++k) {
                            if (get(A->stations[k]) == start) {
                                t1 = A->go[k];
                                as = k;
                            }
                            if (get(A->stations[k]) == check->station) {
                                t2 = A->stop[k - 1];
                                af = k;
                            }
                        }
                        for (int k = 0; k < B->station_num; ++k) {
                            if (get(B->stations[k]) == check->station) {
                                t3 = B->go[k];
                                bs = k;
                            }
                            if (get(B->stations[k]) == finish) {
                                t4 = B->stop[k - 1];
                                bf = k;
                            }
                        }
                        A_go = da - t1.hour / 24;
                        if (A_go >= A->start && A_go <= A->finish) {
                            day_time A_arrive;
                            A_arrive = t2;
                            A_arrive.hour = t2.hour % 24;
                            date mid_arrive;
                            mid_arrive = A_go + t2.hour / 24;
                            day_time B_arrive;
                            B_arrive = t3;
                            B_arrive.hour = B_arrive.hour % 24;
                            date B_go;
                            B_go = mid_arrive;
                            B_go = B_go - t3.hour / 24;
                            day_time mid_arr;
                            mid_arr = t2;
                            mid_arr.hour = mid_arr.hour % 24;
                            if (mid_arr > B_arrive) {
                                B_go = B_go + 1;
                            }
                            if (B_go <= B->finish) {
                                if (B_go < B->start) {
                                    B_go = B->start;
                                }
                                int ans_time = day_time_between(A_go, t1, B_go, t4);
                                int ans_price = A->prices[af] - A->prices[as] + B->prices[bf] - B->prices[bs];
                                if (is_time) {
                                    if (time > ans_time) {
                                        time = ans_time;
                                        price = ans_price;
                                        ans_A = A;
                                        ans_B = B;
                                        ans_A_go = A_go;
                                        ans_B_go = B_go;
                                        ans_t1 = t1;
                                        ans_t2 = t2;
                                        ans_t3 = t3;
                                        ans_t4 = t4;
                                        mid = check->station;
                                        price1 = A->prices[af] - A->prices[as];
                                        price2 = B->prices[bf] - B->prices[bs];
                                    } else if (time == ans_time) {
                                        if (price > ans_price) {
                                            time = ans_time;
                                            price = ans_price;
                                            ans_A = A;
                                            ans_B = B;
                                            ans_A_go = A_go;
                                            ans_B_go = B_go;
                                            ans_t1 = t1;
                                            ans_t2 = t2;
                                            ans_t3 = t3;
                                            ans_t4 = t4;
                                            mid = check->station;
                                            price1 = A->prices[af] - A->prices[as];
                                            price2 = B->prices[bf] - B->prices[bs];
                                        } else if (price == ans_price) {
                                            if (get(A->train_id) < get(ans_A->train_id)) {
                                                time = ans_time;
                                                price = ans_price;
                                                ans_A = A;
                                                ans_B = B;
                                                ans_A_go = A_go;
                                                ans_B_go = B_go;
                                                ans_t1 = t1;
                                                ans_t2 = t2;
                                                ans_t3 = t3;
                                                ans_t4 = t4;
                                                mid = check->station;
                                                price1 = A->prices[af] - A->prices[as];
                                                price2 = B->prices[bf] - B->prices[bs];
                                            } else if (get(A->train_id) == get(ans_A->train_id)) {
                                                if (get(B->train_id) < get(ans_B->train_id)) {
                                                    time = ans_time;
                                                    price = ans_price;
                                                    ans_A = A;
                                                    ans_B = B;
                                                    ans_A_go = A_go;
                                                    ans_B_go = B_go;
                                                    ans_t1 = t1;
                                                    ans_t2 = t2;
                                                    ans_t3 = t3;
                                                    ans_t4 = t4;
                                                    mid = check->station;
                                                    price1 = A->prices[af] - A->prices[as];
                                                    price2 = B->prices[bf] - B->prices[bs];
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (price > ans_price) {
                                        time = ans_time;
                                        price = ans_price;
                                        ans_A = A;
                                        ans_B = B;
                                        ans_A_go = A_go;
                                        ans_B_go = B_go;
                                        ans_t1 = t1;
                                        ans_t2 = t2;
                                        ans_t3 = t3;
                                        ans_t4 = t4;
                                        mid = check->station;
                                        price1 = A->prices[af] - A->prices[as];
                                        price2 = B->prices[bf] - B->prices[bs];
                                    } else if (price == ans_price) {
                                        if (time > ans_time) {
                                            time = ans_time;
                                            price = ans_price;
                                            ans_A = A;
                                            ans_B = B;
                                            ans_A_go = A_go;
                                            ans_B_go = B_go;
                                            ans_t1 = t1;
                                            ans_t2 = t2;
                                            ans_t3 = t3;
                                            ans_t4 = t4;
                                            mid = check->station;
                                            price1 = A->prices[af] - A->prices[as];
                                            price2 = B->prices[bf] - B->prices[bs];
                                        } else if (time == ans_time) {
                                            if (get(A->train_id) < get(ans_A->train_id)) {
                                                time = ans_time;
                                                price = ans_price;
                                                ans_A = A;
                                                ans_B = B;
                                                ans_A_go = A_go;
                                                ans_B_go = B_go;
                                                ans_t1 = t1;
                                                ans_t2 = t2;
                                                ans_t3 = t3;
                                                ans_t4 = t4;
                                                mid = check->station;
                                                price1 = A->prices[af] - A->prices[as];
                                                price2 = B->prices[bf] - B->prices[bs];
                                            } else if (get(A->train_id) == get(ans_A->train_id)) {
                                                if (get(B->train_id) < get(ans_B->train_id)) {
                                                    time = ans_time;
                                                    price = ans_price;
                                                    ans_A = A;
                                                    ans_B = B;
                                                    ans_A_go = A_go;
                                                    ans_B_go = B_go;
                                                    ans_t1 = t1;
                                                    ans_t2 = t2;
                                                    ans_t3 = t3;
                                                    ans_t4 = t4;
                                                    mid = check->station;
                                                    price1 = A->prices[af] - A->prices[as];
                                                    price2 = B->prices[bf] - B->prices[bs];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    check = check->next;
                }
            }
        }
        if (ans_A == nullptr) {
            std::cout << " 0" << '\n';
        } else {
            std::cout << " " << get(ans_A->train_id) << " " << start << " ";
            da.print();
            std::cout << " ";
            ans_t1.hour = ans_t1.hour % 24;
            ans_t1.print();
            std::cout << " -> ";
            std::cout << mid << " ";
            date da1;
            da1 = ans_A_go + ans_t2.hour / 24;
            da1.print();
            std::cout << " ";
            ans_t2.hour = ans_t2.hour % 24;
            ans_t2.print();
            std::cout << " ";
            std::cout << price1 << " ";
            t_date td1;
            put(td1.train_id_,get(ans_A->train_id));
            td1.d = ans_A_go;
            int pd = tickets.find(td1);
            ticket_cond tc1;
            ticket_saver.seekg(sizeof(int) + pd * sizeof(ticket_cond));
            ticket_saver.read(reinterpret_cast<char *>(&tc1), sizeof(ticket_cond));
            int seats1 = ans_A->seat_num;
            bool flag = false;
            for (int i = 0;i < ans_A->station_num;++i) {
                if (get(ans_A->stations[i]) == start) {
                    flag = true;
                }
                if (get(ans_A->stations[i]) == mid) {
                    break;
                }
                if (flag) {
                    seats1 = std::min(seats1,tc1.t[i]);
                }
            }
            std::cout << seats1 << '\n';

            std::cout << get(ans_B->train_id) << " " << mid << " ";
            date da3;
            da3 = ans_B_go + ans_t3.hour / 24;
            da3.print();
            std::cout << " ";
            ans_t3.hour = ans_t3.hour % 24;
            ans_t3.print();
            std::cout << " -> ";
            std::cout << finish << " ";
            date da2;
            da2 = ans_B_go + ans_t4.hour / 24;
            da2.print();
            std::cout << " ";
            ans_t4.hour = ans_t4.hour % 24;
            ans_t4.print();
            std::cout << " ";
            std::cout << price2 << " ";
            t_date td2;
            put(td2.train_id_,get(ans_B->train_id));
            td2.d = ans_B_go;
            int pd2 = tickets.find(td2);
            ticket_cond tc2;
            ticket_saver.seekg(sizeof(int) + pd2 * sizeof(ticket_cond));
            ticket_saver.read(reinterpret_cast<char *>(&tc2), sizeof(ticket_cond));
            int seats2 = ans_B->seat_num;
            bool flag2 = false;
            for (int i = 0;i < ans_B->station_num;++i) {
                if (get(ans_B->stations[i]) == mid) {
                    flag2 = true;
                }
                if (get(ans_B->stations[i]) == finish) {
                    break;
                }
                if (flag2) {
                    seats2 = std::min(seats2,tc2.t[i]);
                }
            }
            std::cout << seats2 << '\n';
        }
        for (int i = 0;i < 50;++i) {
            while (n[i] != nullptr) {
                hash_node *del = n[i];
                n[i] = n[i]->next;
                delete del;
            }
        }
    }

    void clear() {
        trains.clear();
        tickets.clear();
        t_order.clear();
        u_order.clear();
        stations.clear();
        write_place = 0;
        t_write_place = 0;
        o_write_place = 0;
    }
};


#endif //TICKET_SYSTEM_TRAIN_SYSTEM_H
