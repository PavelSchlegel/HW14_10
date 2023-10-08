#pragma once
#include <iostream>
#include <string>
#include <exception>

#define ALPHABEL_SIZE 26

class MyLittleTrie
{
private:
    struct Node
    {
        std::size_t next_count = 0;
        bool WordEnd = false;
        Node* next[ALPHABEL_SIZE];
        Node* parent = nullptr;
        ~Node()
        {
            for (std::size_t i = 0; i < ALPHABEL_SIZE; ++i) {
                if (next[i]) {
                    delete next[i];
                }
            }
        }
    };

    Node* newNode() noexcept
    {
        try {
            Node* ptr = new Node;
            for (std::size_t i = 0; i < ALPHABEL_SIZE; ++i) {
                ptr->next[i] = nullptr;
            }
            return ptr;
        }
        catch (const std::bad_alloc& error) {
            std::cout << "some error with new operator" << std::endl;
            return nullptr;
        }
    }

    void insert(const std::string& key) noexcept
    {
        if (root) {
            if ( ! root->next[key[0] - 'a']) {

                root->next[key[0] - 'a'] = newNode();
                root->next_count++;
                Node* rec = root->next[key[0] - 'a'];
                rec->parent = root;

                for (int index = 1; index < key.size(); ++index) {
                    rec->next_count++;
                    rec->next[key[index] - 'a'] = newNode();
                    rec->next[key[index] - 'a']->parent = rec;
                    rec = rec->next[key[index] - 'a'];
                }
                rec->WordEnd = true;
                return;

            } else {
                Node* rec = root->next[key[0] - 'a'];
                for (int index = 1; index < key.size(); ++index) {
                    if (rec->next[key[index] - 'a']) {
                        rec = rec->next[key[index] - 'a'];
                        continue;
                    }
                    rec->next[key[index] - 'a'] = newNode();
                    rec->next_count++;
                    rec->next[key[index] - 'a']->parent = rec;
                    rec = rec->next[key[index] - 'a'];
                }
                rec->WordEnd = true;
                return;
            }
        }
    }

    void Print(const Node* root) noexcept
    {
        if (root) {
            if (root->WordEnd) {
                std::cout << print_buf << std::endl;
            }

            if (root->next_count == 0) {
                return;
            }

            for (std::size_t i = 0; i < ALPHABEL_SIZE; ++i) {
                if (root->next[i]) {
                    print_buf.push_back(i + 'a');
                    Print(root->next[i]);
                    print_buf.pop_back();
                }
            }
        }
    }

    bool Search(Node* root, const std::string& key) noexcept
    {
        if (root) {
            if (root->next[key[0] - 'a']) {
                Node * search = root->next[key[0] - 'a'];
                for (std::size_t i = 1; i < key.size(); ++i) {
                    if (search->next[key[i] - 'a']) {
                        search = search->next[key[i] - 'a'];
                        continue;
                    }
                    return false;
                }
                if (!search->WordEnd) {
                    return false;
                }
                return true;
            }
            return false;
        }
        return false;
    }

    void byPref(Node* root,const std::string& pref) noexcept
    {
        if (root) {
            if (pref.size() == 1) {
                if (root->next[pref[0] - 'a']) {
                    print_buf.push_back(pref[0]);
                    Print(root->next[pref[0] - 'a']);
                    return;
                }
            }

            Node* ptr = root;
            for (std::size_t i = 0; i < pref.size(); ++i) {
                if ( ! ptr->next[pref[i] - 'a'] ) {
                    std::cout << "\033[1;31mno words for prefix: \033[0m" << pref << std::endl;
                    return;
                }
                print_buf.push_back(pref[i]);
                ptr = ptr->next[pref[i] - 'a'];
            }
            Print(ptr);
            return;
        }
    
    }

    Node* root;
    std::string print_buf;

public:
    MyLittleTrie() = delete;
    explicit MyLittleTrie(const std::string& str) noexcept
    : root(newNode())
    {
        insert(str);
    }

    MyLittleTrie(std::initializer_list<std::string> list) noexcept
    : root(newNode())
    {
        for (auto& rec : list) {
            insert(rec);
        }
    }

    ~MyLittleTrie()
    {
        if (root) {
            delete root;
        }
    }

    bool search(const std::string& word) noexcept
    {
        return Search(root, word);

    }

    void add_word(const std::string& word) noexcept
    {
        insert(word);
    }

    void print() noexcept
    {
        Print(root);
        print_buf.clear();
    }

    void searchByPref(const std::string& pref) noexcept
    {
        byPref(root, pref);
        print_buf.clear();
    }
};