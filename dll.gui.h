#pragma once
#include <string>
using namespace std;

class Node {
public:
    char info;
    Node* next;
    Node* prev;

    Node(char ch) : info(ch), next(nullptr), prev(nullptr) {}
};

class DLL {
private:
    Node* head;
    Node* tail;
public:
    DLL() : head(nullptr), tail(nullptr) {}

    Node* getHead() {
        return head;
    }

    int StringLength() {
        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    void insertion(char ch, int pos) {
        Node* n = new Node(ch);
        if (!head) {
            head = tail = n;
            return;
        }

        if (pos <= 0) {
            n->next = head;
            head->prev = n;
            head = n;
            return;
        }

        Node* cur = head;
        int i = 0;
        while (cur->next && i < pos - 1) {
            cur = cur->next;
            i++;
        }

        n->next = cur->next;
        if (cur->next) cur->next->prev = n;
        cur->next = n;
        n->prev = cur;

        if (!n->next) tail = n;
    }

    string toString() {
        string result;
        Node* cur = head;
        while (cur) {
            result += cur->info;
            cur = cur->next;
        }
        return result;
    }

    bool deletion(int position) {
        if (head == nullptr)
            return false; // List is empty

        Node* current = head;
        int i = 0;

        while (i < position && current != nullptr) {
            current = current->next;
            i++;
        }

        if (current == nullptr)
            return false; // Invalid position

        if (current == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        }
        else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        return true; // Deletion successful
    }
};
