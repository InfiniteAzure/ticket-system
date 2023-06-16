//
// Created by Xue Jiarui on 2023/5/22.
//

#ifndef TICKET_SYSTEM_BPLUS_H
#define TICKET_SYSTEM_BPLUS_H

#include <fstream>
#include "vector.hpp"

void put(char *a, std::string s) {
    for (int i = 0; i < s.length(); ++i) {
        a[i] = s[i];
    }
    a[s.length()] = '\0';
}

int to_int(std::string s) {
    if (s == "nmsl_fuck") {
        return -1;
    }
    int ans = 0;
    for (int i = 0; i < s.length(); ++i) {
        ans *= 10;
        ans += s[i] - '0';
    }
    return ans;
}

std::string get(char *a) {
    int i = 0;
    std::string ans;
    while (a[i] != '\0') {
        ans += a[i];
        i++;
    }
    return ans;
}

template<class Key>
class bplus {
    const static int MAXS = 1000;
public:
    struct Node {
        int save_place;
        Key k[MAXS + 1];
        int pos[MAXS + 2];
        int father = -1;
        bool is_leaf = false;
        int used_space;
        int prev = -1;
        int next = -1;
    };

    std::string tree_name;
    std::fstream tree;
    std::string allocator_name;
    std::fstream allocator;

    struct index {
        int root;
        int write;
        int count;
    };

    index I;
    int allocator_size;
    int alloc[108];

    bplus(std::string t, std::string a) {
        tree_name = t;
        allocator_name = a;
        tree.open(tree_name);
        if (!tree.good()) {
            std::ofstream out;
            out.open(tree_name);
            I.root = -1;
            I.write = 0;
            I.count = 0;
            out.write(reinterpret_cast<char *>(&I), sizeof(index));
            out.close();
            tree.open(tree_name);
        } else {
            tree.seekg(0);
            tree.read(reinterpret_cast<char *>(&I), sizeof(index));
        }

        allocator.open(allocator_name);
        if (!allocator.good()) {
            std::ofstream out;
            out.open(allocator_name);
            allocator_size = 0;
            out.write(reinterpret_cast<char *>(&allocator_size), sizeof(int));
            out.close();
            allocator.open(allocator_name);
        } else {
            allocator.seekg(0);
            allocator.read(reinterpret_cast<char *>(&allocator_size), sizeof(int));
            for (int i = 0; i < allocator_size; ++i) {
                allocator.read(reinterpret_cast<char *>(&alloc[i]), sizeof(int));
            }
        }
    }

    ~bplus() {
        tree.seekp(0);
        tree.write(reinterpret_cast<char *>(&I), sizeof(index));
        tree.close();
        allocator.seekp(0);
        allocator.write(reinterpret_cast<char *>(&allocator_size), sizeof(int));
        for (int i = 0; i < allocator_size; ++i) {
            allocator.write(reinterpret_cast<char *>(&alloc[i]), sizeof(int));
        }
        allocator.close();
    }

    Node get_node(int query) {
        tree.seekg(sizeof(index) + query * sizeof(Node));
        Node ans;
        tree.read(reinterpret_cast<char *>(&ans), sizeof(Node));
        return ans;
    }

    int get_place() {
        if (allocator_size != 0) {
            int ans = alloc[allocator_size - 1];
            allocator_size--;
            return ans;
        } else {
            I.write++;
            return I.write - 1;
        }
    }

    void deal(Node n) {
        if (n.is_leaf) {
            if (I.root == n.save_place) {
                Node tmp;
                tmp.save_place = get_place();
                tmp.is_leaf = true;
                n.next = tmp.save_place;
                tmp.prev = n.save_place;
                for (int i = n.used_space / 2; i < n.used_space; ++i) {
                    tmp.k[i - n.used_space / 2] = n.k[i];
                    tmp.pos[i - n.used_space / 2] = n.pos[i];
                }
                int a = n.used_space;
                n.used_space = n.used_space / 2;
                tmp.used_space = a - n.used_space;
                Key add_k = tmp.k[0];
                Node r;
                r.save_place = get_place();
                I.root = r.save_place;
                r.used_space = 1;
                r.pos[0] = n.save_place;
                r.pos[1] = tmp.save_place;
                r.k[0] = tmp.k[0];
                n.father = r.save_place;
                tmp.father = r.save_place;
                tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                tree.seekp(sizeof(index) + tmp.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&tmp), sizeof(Node));
                tree.seekp(sizeof(index) + r.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&r), sizeof(Node));
            } else {
                Node tmp;
                tmp.save_place = get_place();
                tmp.is_leaf = true;
                tmp.father = n.father;
                for (int i = n.used_space / 2; i < n.used_space; ++i) {
                    tmp.k[i - n.used_space / 2] = n.k[i];
                    tmp.pos[i - n.used_space / 2] = n.pos[i];
                }
                int a = n.used_space;
                n.used_space = n.used_space / 2;
                tmp.used_space = a - n.used_space;
                Key add_k = tmp.k[0];
                if (n.next != -1) {
                    Node next = get_node(n.next);
                    next.prev = tmp.save_place;
                    n.next = tmp.save_place;
                    tmp.next = next.save_place;
                    tmp.prev = n.save_place;
                    tree.seekp(sizeof(index) + next.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&next), sizeof(Node));
                } else {
                    n.next = tmp.save_place;
                    tmp.prev = n.save_place;
                }
                tree.seekp(sizeof(index) + tmp.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&tmp), sizeof(Node));
                tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                Node pa;
                pa = get_node(n.father);
                Key k = tmp.k[0];
                for (int i = 0; i < pa.used_space; ++i) {
                    if (k < pa.k[i]) {
                        for (int j = pa.used_space - 1; j >= i; --j) {
                            pa.k[j + 1] = pa.k[j];
                            pa.pos[j + 2] = pa.pos[j + 1];
                        }
                        pa.k[i] = k;
                        pa.pos[i + 1] = tmp.save_place;
                        pa.used_space++;
                        break;
                    }
                    if (i == pa.used_space - 1) {
                        pa.k[i + 1] = k;
                        pa.pos[i + 2] = tmp.save_place;
                        pa.used_space++;
                        break;
                    }
                }
                if (pa.used_space > MAXS) {
                    deal(pa);
                } else {
                    tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                }
            }
        } else {
            if (I.root != n.save_place) {
                Node tmp;
                tmp.save_place = get_place();
                tmp.father = n.father;
                tmp.is_leaf = false;
                if (n.next != -1) {
                    Node next = get_node(n.next);
                    next.prev = tmp.save_place;
                    tmp.next = next.save_place;
                    tree.seekp(sizeof(index) + next.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&next), sizeof(Node));
                }
                n.next = tmp.save_place;
                tmp.prev = n.save_place;
                Node pa;
                pa = get_node(n.father);
                for (int i = n.used_space / 2 + 1; i < n.used_space; ++i) {
                    tmp.k[i - n.used_space / 2 - 1] = n.k[i];
                }
                for (int i = n.used_space / 2 + 1; i < n.used_space + 1; ++i) {
                    tmp.pos[i - n.used_space / 2 - 1] = n.pos[i];
                }
                Key k = n.k[n.used_space / 2];
                int a = n.used_space;
                n.used_space = a / 2;
                tmp.used_space = a - n.used_space - 1;
                for (int i = 0; i <= tmp.used_space; ++i) {
                    Node c;
                    c = get_node(tmp.pos[i]);
                    c.father = tmp.save_place;
                    tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                }
                for (int i = 0; i < pa.used_space; ++i) {
                    if (k < pa.k[i]) {
                        for (int j = pa.used_space - 1; j >= i; --j) {
                            pa.k[j + 1] = pa.k[j];
                            pa.pos[j + 2] = pa.pos[j + 1];
                        }
                        pa.pos[i + 1] = pa.pos[i];
                        pa.k[i] = k;
                        pa.pos[i + 1] = tmp.save_place;
                        break;
                    }
                    if (i == pa.used_space - 1) {
                        pa.k[i + 1] = k;
                        pa.pos[i + 2] = tmp.save_place;
                        break;
                    }
                }
                pa.used_space++;
                tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                tree.seekp(sizeof(index) + tmp.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&tmp), sizeof(Node));
                if (pa.used_space > MAXS) {
                    deal(pa);
                } else {
                    tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                }
            } else {
                Node tmp;
                tmp.save_place = get_place();
                tmp.is_leaf = false;
                tmp.prev = n.save_place;
                n.next = tmp.save_place;
                for (int i = n.used_space / 2 + 1; i < n.used_space; ++i) {
                    tmp.k[i - n.used_space / 2 - 1] = n.k[i];
                    tmp.pos[i - n.used_space / 2 - 1] = n.pos[i];
                }
                tmp.pos[n.used_space - n.used_space / 2 - 1] = n.pos[n.used_space];
                Key k = n.k[n.used_space / 2];
                int a = n.used_space;
                n.used_space = a / 2;
                tmp.used_space = a - n.used_space - 1;
                Node r;
                r.save_place = get_place();
                r.k[0] = k;
                r.pos[0] = n.save_place;
                r.used_space = 1;
                r.pos[1] = tmp.save_place;
                I.root = r.save_place;
                tmp.father = r.save_place;
                n.father = r.save_place;
                for (int i = 0; i <= tmp.used_space; ++i) {
                    Node c;
                    c = get_node(tmp.pos[i]);
                    c.father = tmp.save_place;
                    tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                }
                tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                tree.seekp(sizeof(index) + tmp.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&tmp), sizeof(Node));
                tree.seekp(sizeof(index) + r.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&r), sizeof(Node));
            }
        }
    }

    void insert(int position, Key k) {
        if (I.count == 0) {
            I.write = 1;
            allocator_size = 0;
            I.root = 0;
            Node n;
            n.father = -1;
            n.save_place = 0;
            n.is_leaf = true;
            n.pos[0] = position;
            n.k[0] = k;
            n.next = -1;
            n.prev = -1;
            n.used_space = 1;
            I.count++;
            tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
            tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
        } else if (I.count < MAXS / 2) {
            Node n;
            n = get_node(I.root);
            for (int i = 0; i < n.used_space; ++i) {
                if (k < n.k[i]) {
                    for (int j = n.used_space - 1; j >= i; --j) {
                        n.k[j + 1] = n.k[j];
                        n.pos[j + 1] = n.pos[j];
                    }
                    n.k[i] = k;
                    n.pos[i] = position;
                    break;
                }
                if (i == n.used_space - 1) {
                    n.pos[n.used_space] = position;
                    n.k[n.used_space] = k;
                    break;
                }
            }
            n.used_space++;
            I.count++;
            tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
            tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
        } else {
            Node n;
            n = get_node(I.root);
            while (!n.is_leaf) {
                for (int i = 0; i < n.used_space; ++i) {
                    if (k < n.k[i]) {
                        n = get_node(n.pos[i]);
                        break;
                    }
                    if (i == n.used_space - 1) {
                        n = get_node(n.pos[n.used_space]);
                        break;
                    }
                }
            }
            for (int i = 0; i < n.used_space; ++i) {
                if (k < n.k[i]) {
                    for (int j = n.used_space - 1; j >= i; --j) {
                        n.k[j + 1] = n.k[j];
                        n.pos[j + 1] = n.pos[j];
                    }
                    n.k[i] = k;
                    n.pos[i] = position;
                    n.used_space++;
                    break;
                }
                if (i == n.used_space - 1) {
                    n.k[n.used_space] = k;
                    n.pos[n.used_space] = position;
                    n.used_space++;
                    break;
                }
            }
            I.count++;
            if (n.used_space > MAXS) {
                deal(n);
            } else {
                tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
            }
        }
    }

    void merge(Node n) {
        if (n.is_leaf) {
            Node pa = get_node(n.father);
            if (n.save_place != pa.pos[0]) {
                Node lend;
                lend = get_node(n.prev);
                if (lend.used_space - 1 >= MAXS / 3) {
                    for (int i = n.used_space - 1; i >= 0; --i) {
                        n.k[i + 1] = n.k[i];
                        n.pos[i + 1] = n.pos[i];
                    }
                    n.k[0] = lend.k[lend.used_space - 1];
                    n.pos[0] = lend.pos[lend.used_space - 1];
                    n.used_space++;
                    lend.used_space--;
                    tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                    tree.seekp(sizeof(index) + lend.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&lend), sizeof(Node));
                    for (int i = 0; i < pa.used_space + 1; ++i) {
                        if (n.save_place == pa.pos[i]) {
                            pa.k[i - 1] = n.k[0];
                            break;
                        }
                    }
                    tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                } else {
                    for (int i = 0; i < n.used_space; ++i) {
                        lend.k[lend.used_space + i] = n.k[i];
                        lend.pos[lend.used_space + i] = n.pos[i];
                    }
                    lend.used_space += n.used_space;
                    alloc[allocator_size] = n.save_place;
                    allocator_size++;
                    for (int i = 0; i < pa.used_space; ++i) {
                        if (pa.pos[i] == n.save_place) {
                            for (int j = i; j < pa.used_space; ++j) {
                                pa.pos[j] = pa.pos[j + 1];
                                pa.k[j - 1] = pa.k[j];
                            }
                            break;
                        }
                    }
                    pa.used_space--;
                    if (n.next != -1) {
                        Node c = get_node(n.next);
                        c.prev = lend.save_place;
                        tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                    }
                    lend.next = n.next;
                    tree.seekp(sizeof(index) + lend.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&lend), sizeof(Node));
                    if (pa.used_space < MAXS / 3) {
                        merge(pa);
                    } else {
                        tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                    }
                }
            } else {
                Node lend;
                lend = get_node(n.next);
                if (lend.used_space - 1 >= MAXS / 3) {
                    n.k[n.used_space] = lend.k[0];
                    n.pos[n.used_space] = lend.pos[0];
                    n.used_space++;
                    for (int i = 0; i < lend.used_space - 1; ++i) {
                        lend.k[i] = lend.k[i + 1];
                        lend.pos[i] = lend.pos[i + 1];
                    }
                    lend.used_space--;
                    pa.k[0] = lend.k[0];
                    tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                    tree.seekp(sizeof(index) + lend.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&lend), sizeof(Node));
                    tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                } else {
                    for (int i = 0; i < lend.used_space; ++i) {
                        n.k[n.used_space + i] = lend.k[i];
                        n.pos[n.used_space + i] = lend.pos[i];
                    }
                    n.used_space += lend.used_space;
                    if (lend.next != -1) {
                        Node c;
                        c = get_node(lend.next);
                        c.prev = n.save_place;
                        tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                    }
                    n.next = lend.next;
                    for (int i = 1; i < pa.used_space; ++i) {
                        pa.k[i - 1] = pa.k[i];
                        pa.pos[i] = pa.pos[i + 1];
                    }
                    pa.used_space--;
                    tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                    if (pa.used_space < MAXS / 3) {
                        merge(pa);
                    } else {
                        tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                    }
                }
            }
        } else {
            if (I.root == n.save_place) {
                if (n.used_space == 0) {
                    I.root = n.pos[0];
                    Node r = get_node(n.pos[0]);
                    r.father = -1;
                    tree.seekp(sizeof(index) + r.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&r), sizeof(Node));
                    alloc[allocator_size] = n.save_place;
                    allocator_size++;
                } else {
                    tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                    tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                }
            } else {
                Node pa = get_node(n.father);
                if (n.save_place != pa.pos[0]) {
                    Node lend;
                    lend = get_node(n.prev);
                    if (lend.used_space - 1 >= MAXS / 3) {
                        int a;
                        for (int i = 0; i < pa.used_space + 1; ++i) {
                            if (pa.pos[i] == n.save_place) {
                                a = i;
                                break;
                            }
                        }
                        for (int i = n.used_space - 1; i >= 0; --i) {
                            n.k[i + 1] = n.k[i];
                        }
                        n.k[0] = pa.k[a - 1];
                        for (int i = n.used_space; i >= 0; --i) {
                            n.pos[i + 1] = n.pos[i];
                        }
                        n.used_space++;
                        pa.k[a - 1] = lend.k[lend.used_space - 1];
                        n.pos[0] = lend.pos[lend.used_space];
                        lend.used_space--;
                        Node c = get_node(n.pos[0]);
                        c.father = n.save_place;
                        tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                        tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                        tree.seekp(sizeof(index) + lend.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&lend), sizeof(Node));
                        tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                    } else {
                        int a;
                        for (int i = 0; i < pa.used_space + 1; ++i) {
                            if (pa.pos[i] == n.save_place) {
                                a = i;
                                break;
                            }
                        }
                        for (int i = 0; i < n.used_space; ++i) {
                            lend.k[lend.used_space + 1 + i] = n.k[i];
                        }
                        for (int i = 0; i < n.used_space + 1; ++i) {
                            lend.pos[lend.used_space + 1 + i] = n.pos[i];
                        }
                        alloc[allocator_size] = n.save_place;
                        allocator_size++;
                        lend.k[lend.used_space] = pa.k[a - 1];
                        lend.used_space += n.used_space + 1;
                        for (int i = 0; i < lend.used_space + 1; ++i) {
                            Node c;
                            c = get_node(lend.pos[i]);
                            c.father = lend.save_place;
                            tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                            tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                        }
                        if (n.next != -1) {
                            Node next = get_node(n.next);
                            next.prev = lend.save_place;
                            tree.seekp(sizeof(index) + next.save_place * sizeof(Node));
                            tree.write(reinterpret_cast<char *>(&next), sizeof(Node));
                        }
                        lend.next = n.next;
                        for (int i = a; i < pa.used_space; i++) {
                            pa.k[i - 1] = pa.k[i];
                        }
                        for (int i = a; i < pa.used_space; ++i) {
                            pa.pos[i] = pa.pos[i + 1];
                        }
                        pa.used_space--;
                        tree.seekp(sizeof(index) + lend.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&lend), sizeof(Node));
                        if (pa.used_space < MAXS / 3) {
                            merge(pa);
                        } else {
                            tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                            tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                        }
                    }
                } else {
                    Node lend;
                    lend = get_node(n.next);
                    if (lend.used_space - 1 >= MAXS / 3) {
                        n.k[n.used_space] = pa.k[0];
                        pa.k[0] = lend.k[0];
                        n.pos[n.used_space + 1] = lend.pos[0];
                        for (int i = 0; i < lend.used_space - 1; ++i) {
                            lend.k[i] = lend.k[i + 1];
                        }
                        for (int i = 0; i < lend.used_space; ++i) {
                            lend.pos[i] = lend.pos[i + 1];
                        }
                        Node c;
                        n.used_space++;
                        lend.used_space--;
                        c = get_node(n.pos[n.used_space]);
                        c.father = n.save_place;
                        tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                        tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                        tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                        tree.seekp(sizeof(index) + lend.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&lend), sizeof(Node));
                    } else {
                        for (int i = 0; i < lend.used_space; ++i) {
                            n.k[n.used_space + 1 + i] = lend.k[i];
                        }
                        for (int i = 0; i < lend.used_space + 1; ++i) {
                            n.pos[n.used_space + 1 + i] = lend.pos[i];
                        }
                        n.k[n.used_space] = pa.k[0];
                        for (int i = 0; i < pa.used_space - 1; ++i) {
                            pa.k[i] = pa.k[i + 1];
                        }
                        for (int i = 0; i < pa.used_space - 1; ++i) {
                            pa.pos[i + 1] = pa.pos[i + 2];
                        }
                        n.used_space += lend.used_space + 1;
                        for (int i = 0; i < n.used_space + 1; ++i) {
                            Node c;
                            c = get_node(n.pos[i]);
                            c.father = n.save_place;
                            tree.seekp(sizeof(index) + c.save_place * sizeof(Node));
                            tree.write(reinterpret_cast<char *>(&c), sizeof(Node));
                        }
                        if (lend.next != -1) {
                            Node next = get_node(lend.next);
                            next.prev = n.save_place;
                            tree.seekp(sizeof(index) + next.save_place * sizeof(Node));
                            tree.write(reinterpret_cast<char *>(&next), sizeof(Node));
                        }
                        n.next = lend.next;
                        alloc[allocator_size] = lend.save_place;
                        allocator_size++;
                        tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                        tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                        pa.used_space--;
                        if (pa.used_space < MAXS / 3) {
                            merge(pa);
                        } else {
                            tree.seekp(sizeof(index) + pa.save_place * sizeof(Node));
                            tree.write(reinterpret_cast<char *>(&pa), sizeof(Node));
                        }
                    }
                }
            }
        }
    }

    void erase(Key k) {
        Node n;
        n = get_node(I.root);
        while (!n.is_leaf) {
            for (int i = 0; i < n.used_space; ++i) {
                if (k < n.k[i]) {
                    n = get_node(n.pos[i]);
                    break;
                }
                if (i == n.used_space - 1) {
                    n = get_node(n.pos[n.used_space]);
                    break;
                }
            }
        }
        bool flag = false;
        for (int i = 0; i < n.used_space; ++i) {
            if (n.k[i] == k) {
                for (int j = i; j < n.used_space - 1; ++j) {
                    n.k[j] = n.k[j + 1];
                    n.pos[j] = n.pos[j + 1];
                }
                flag = true;
                break;
            }
        }
        if (flag) {
            n.used_space--;
            I.count--;
            tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
            tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
            if (I.root != n.save_place) {
                if (n.used_space < MAXS / 3) {
                    merge(n);
                }
            } else {
                if (I.count == 0) {
                    alloc[allocator_size] = n.save_place;
                    allocator_size++;
                    I.root = -1;
                }
            }
        }
    }

    int find(Key k) {
        if (I.count == 0) {
            return -1;
        }
        Node n;
        n = get_node(I.root);
        while (!n.is_leaf) {
            for (int i = 0; i < n.used_space; ++i) {
                if (k < n.k[i]) {
                    n = get_node(n.pos[i]);
                    break;
                }
                if (i == n.used_space - 1) {
                    n = get_node(n.pos[n.used_space]);
                    break;
                }
            }
        }
        for (int i = 0; i < n.used_space; ++i) {
            if (n.k[i] == k) {
                return n.pos[i];
            }
        }
        return -1;
    }

    int modify(Key k, int pos) {
        if (I.count == 0) {
            return -1;
        }
        Node n;
        n = get_node(I.root);
        while (!n.is_leaf) {
            for (int i = 0; i < n.used_space; ++i) {
                if (k < n.k[i]) {
                    n = get_node(n.pos[i]);
                    break;
                }
                if (i == n.used_space - 1) {
                    n = get_node(n.pos[n.used_space]);
                    break;
                }
            }
        }
        for (int i = 0; i < n.used_space; ++i) {
            if (n.k[i] == k) {
                n.pos[i] = pos;
                tree.seekp(sizeof(index) + n.save_place * sizeof(Node));
                tree.write(reinterpret_cast<char *>(&n), sizeof(Node));
                return 0;
            }
        }
        return -1;
    }

    void clear() {
        I.count = 0;
        I.root = -1;
        I.write = 0;
    }
};


#endif //TICKET_SYSTEM_BPLUS_H
