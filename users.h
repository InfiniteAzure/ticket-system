//
// Created by Xue Jiarui on 2023/5/22.
//

#ifndef TICKET_SYSTEM_USERS_H
#define TICKET_SYSTEM_USERS_H

class User_system {
public:
    struct user {
        int pri = 0;
        char username[35] = {0};
        char name[30] = {0};
        char mail[35] = {0};
        char password[35] = {0};
        int save_place = -1;
    };

    struct user_name {
        char user_name_[35] = {0};
        friend bool operator<(user_name a,user_name b) {
            return get(a.user_name_) < get(b.user_name_);
        }
        friend bool operator>(user_name a,user_name b) {
            return get(a.user_name_) > get(b.user_name_);
        }
        friend bool operator<=(user_name a,user_name b) {
            return get(a.user_name_) <= get(b.user_name_);
        }
        friend bool operator>=(user_name a,user_name b) {
            return get(a.user_name_) >= get(b.user_name_);
        }
        friend bool operator==(user_name a,user_name b) {
            return get(a.user_name_) == get(b.user_name_);
        }
    };

    struct user_node {
        user u;
        user_node *next = nullptr;
    };

    bplus<user_name> manage;
    std::fstream save;
    int write_place = 0;

    user_node *login[50] = {nullptr};

    User_system(): manage("u_tree","u_alloc") {
        save.open("u_value");
        if (!save.good()) {
            std::ofstream out;
            out.open("u_value");
            write_place = 0;
            out.write(reinterpret_cast<char *>(&write_place), sizeof(int));
            out.close();
            save.open("u_value");
        } else {
            save.seekg(0);
            save.read(reinterpret_cast<char *>(&write_place), sizeof(int));
        }
    };

    ~User_system() {
        save.seekp(0);
        save.write(reinterpret_cast<char *>(&write_place), sizeof(int));
        save.close();
    };

    int get_hash(std::string s) {
        int ans = 0;
        for (int i = 0;i < s.length();++i) {
            ans *= 5;
            ans += s[i];
            ans = ans % 47;
        }
        return ans;
    }

    void add_user(user a) {
        user_node *tmp = new user_node;
        int m = get_hash(get(a.username));
        tmp->next = login[m];
        login[m] = tmp;
        tmp->u = a;
    }

    user *find(std::string u_name) {
        int a = get_hash(u_name);
        user_node *p = login[a];
        while (p != nullptr && get(p->u.username) != u_name) {
            p = p->next;
        }
        if (p == nullptr) {
            return nullptr;
        } else {
            user *ans = &p->u;
            return ans;
        }
    }

    void remove_user(std::string u_name) {
        if (find(u_name) == nullptr) {
            return;
        }
        int p = get_hash(u_name);
        user_node *del = login[p];
        if (u_name == get(del->u.username)) {
            login[p] = del->next;
            delete del;
            return;
        } else {
            user_node *pre = login[p];
            del = del->next;
            while (u_name != get(del->u.username)) {
                del = del->next;
                pre = pre->next;
            }
            pre->next = del->next;
            delete del;
        }
    }

    int write_value(user v) {
        save.seekp(sizeof(int) + (write_place) * sizeof(v));
        save.write(reinterpret_cast<char *>(&v), sizeof(v));
        write_place++;
        return write_place - 1;
    }



    int init(std::string &username_,std::string &password,std::string &name,std::string &mail) {
        user u;
        user_name us;
        put(us.user_name_,username_);
        put(u.username,username_);
        put(u.password,password);
        put(u.name,name);
        put(u.mail,mail);
        u.pri = 10;
        int p = write_value(u);
        u.save_place = p;
        manage.insert(p,us);
        return 1;
    }

    int add_user(std::string &username_,std::string &password,std::string &name,std::string &mail,
    std::string &cur_user,int pri_) {
        user *p;
        p = find(cur_user);
        if (p == nullptr) {
            return -1;
        }
        if (p->pri <= pri_) {
            return -1;
        }
        user_name us;
        put(us.user_name_,username_);
        int q;
        q = manage.find(us);
        if (q != -1) {
            return -1;
        }
        user u;
        put(u.username,username_);
        put(u.password,password);
        put(u.name,name);
        put(u.mail,mail);
        u.pri = pri_;
        int pos = write_value(u);
        manage.insert(pos,us);
        return 0;
    }

    int log_in(std::string u_name,std::string password_) {
        if (find(u_name) != nullptr) {
            return -1;
        }
        user_name u;
        put(u.user_name_,u_name);
        int pos = manage.find(u);
        if (pos == -1) {
            return -1;
        }
        user a;
        save.seekg(sizeof(int) + pos * sizeof(a));
        save.write(reinterpret_cast<char *>(&a), sizeof(a));
        if (get(a.password) != password_) {
            return -1;
        }
        add_user(a);
        return 0;
    }

    int log_out(std::string u_name) {
        user *p = find(u_name);
        if (p == nullptr) {
            return -1;
        }
        remove_user(u_name);
        return 0;
    }

    int query_profile(std::string c_user,std::string u_name) {
        user *p = find(u_name);
        if (p == nullptr) {
            return -1;
        }
        user_name us;
        put(us.user_name_,u_name);
        int pos = manage.find(us);
        if (pos == -1) {
            return -1;
        }
        user q;
        save.seekg(sizeof(int) + pos * sizeof(q));
        save.write(reinterpret_cast<char *>(&q), sizeof(q));
        if (c_user != u_name && p->pri <= q.pri) {
            return -1;
        }
        std::cout << get(q.username) << " " << get(q.name) << " "
                  << get(q.mail) << " " << q.pri;
        return 0;
    }


};

#endif //TICKET_SYSTEM_USERS_H
