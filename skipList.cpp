#include <bits/stdc++.h>

using namespace std;

template<typename T>
class LinkList {
public:
    class Node {
    public:
        Node() = delete;

        explicit Node(T data) : data(data) {}

        T data;

        friend class LinkList;

        auto get_next() { return next; }

        auto get_prev() { return prev; }

        Node *down = nullptr;

    private:
        Node *next = nullptr;
        Node *prev = nullptr;
    };

    ~LinkList() {
        auto tmp = first;
        while (tmp) {
            auto t = tmp;
            tmp = tmp->next;
            delete t;
        }
    }

    auto add(T data, Node *p) {
        auto new_node = new Node(data);
        if (p == nullptr) {
            new_node->next = first;
            if (first)
                first->prev = new_node;
            first = new_node;
        } else {
            new_node->next = p->next;
            new_node->prev = p;
            p->next = new_node;
            if (new_node->next)
                new_node->next->prev = new_node;
        }
        return new_node;
    }

    void erase(Node *p) {
        if (p->prev)
            p->prev->next = p->next;
        if (p->next)
            p->next->prev = p->prev;
        if (first == p)
            first = p->next;
        delete p;
    }

    auto get_first() { return first; }

private:
    Node *first = nullptr;
};

template<typename T>
auto find_max_of_before(T x, typename LinkList<T>::Node *start) {
    auto tmp = start;
    if (tmp)
        while (tmp->get_next() && tmp->data < x)
            tmp = tmp->get_next();
    return tmp;
}

template<size_t max_level, typename T>
class SkipList {
public:
    SkipList() { srand(time(nullptr)); };

    auto add(T data) {
        auto level = random_level();
        if (this->level < level)
            this->level = level;
        auto a = levels[0].get_first();
        auto b = levels[0].get_first();
        a = nullptr;
        b = nullptr;
        for (int i = level; i >= 0; --i) {
            if (b)
                b = find_max_of_before(data, b->down);
            else
                b = find_max_of_before(data, levels[i].get_first());
            auto t = levels[i].add(data, b);
            if (a)
                a->down = t;
            a = t;
        }
    }

    auto find(T data) {
        auto node = levels[level].get_first();

        while (node) {
            if (node->data == data)
                return true;
            if (node->data > data) {
                if (node->get_prev())
                    node = node->get_prev();
                else if (node->down)
                    node = node->down;
                else
                    return false;
            } else if (node->get_next()) {
                if (node->get_next()->data > data) {
                    node = node->down;
                } else
                    node = node->get_next();
            } else if (node->down) {
                node = node->down;
            } else return false;
        }
        return false;
    }

    void erase(T data) {
        auto node = levels[0].get_first();
        node = nullptr;
        int i;
        for (i = level; i >= 0; --i) {
            node = levels[i].get_first();
            while (node->get_next()) {
                if (node->data == data)
                    break;
                node = node->get_next();
            }
            if (node->data == data)
                break;
        }
        auto tmp = node;
        for (int j = i; j >= 0; --j) {
            tmp = node;
            node = node->down;
            levels[j].erase(tmp);
        }
    }

    void print() {
        for (int i = 0; i < max_level; ++i) {
            cout << "level " << i << ": ";
            auto tmp = levels[i].get_first();
            while (tmp->get_next()) {
                cout << tmp->data << " ";
                tmp = tmp->get_next();
            }
            cout << "\n";
        }
    }

private:
    static size_t random_level() {
        return random() % max_level;
    }

    size_t level = 0;
    LinkList<T> levels[max_level];
};


int main() {
    SkipList<10, int> a;
    for (int i = 0; i < 100; ++i) {
        a.add(i);
    }

    cout
            << a.find(85)
            << a.find(89)
            << a.find(0)
            << a.find(-1)
            << a.find(5)
            << a.find(105)
            << endl;

    // a.print();

    for (int i = 0; i < 100; i++) {
        if (i % 5 == 2)
            a.erase(i);
    }

    cout
            << a.find(7)
            << a.find(12)
            << a.find(50)
            << endl;

    // a.print();
}