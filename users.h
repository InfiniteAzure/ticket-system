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

    bplus<user_name,user> manage;

    User_system(): manage("u_tree","u_value","u_alloc") {};

    ~User_system() = default;

    int init (int pri_,std::string username_,std::string password,std::string name,std::string mail) {
        user u;
        user_name us;
        put(us.user_name_,username_);
        put(u.username,username_);
        put(u.password,password);
        put(u.name,name);
        put(u.mail,mail);
        u.pri = pri_;
        manage.insert(u,us);
        return 1;
    }


};

#endif //TICKET_SYSTEM_USERS_H
