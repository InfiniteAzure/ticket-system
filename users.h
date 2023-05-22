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

    bplus<user_name> manage;
    std::fstream save;
    int write_place = 0;

    int write_value(user v) {
        save.seekp(sizeof(int) + (write_place) * sizeof(v));
        save.write(reinterpret_cast<char *>(&v), sizeof(v));
        write_place++;
        return write_place - 1;
    }

    User_system(): manage("u_tree","u_value","u_alloc") {
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

    ~User_system() = default;

    int init(int pri_,std::string &username_,std::string &password,std::string &name,std::string &mail) {
        user u;
        user_name us;
        put(us.user_name_,username_);
        put(u.username,username_);
        put(u.password,password);
        put(u.name,name);
        put(u.mail,mail);
        u.pri = pri_;
        int p = write_value(u);
        manage.insert(p,us);
        return 1;
    }


};

#endif //TICKET_SYSTEM_USERS_H
