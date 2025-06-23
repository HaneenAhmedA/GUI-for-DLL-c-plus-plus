



/*
 * Names: Mayas ayman alhafiry / Haneen Ahmed Abd El Kareem
 * String Manipulation using Doubly Linked List
 */



#include <iostream>
using namespace std;

class Node {
public:
    char info;
    Node* next;
    Node* prev;

    Node(char i) {
        info = i;
        next = nullptr;
        prev = nullptr;
    }
};

class DLL {
private:
    Node* head;
    Node* tail;

public:
    DLL() {
        head = nullptr;
        tail = nullptr;
    }


    void insertion(char ch, int p) {
        Node* n = new Node(ch);
        // empty list
        if (head == nullptr) {
            head = n;
            tail = n;
            n->prev = nullptr;
            n->next = nullptr;
            return;
        }


        // insert in the first
        if (p==0) {
            n->prev = nullptr;
            n->next = nullptr;
            head->next->prev = n;
            head = n;
            return;
        }

        // insert in the position
        Node* cur;
        cur = head;
        int c=0;  // counter
        while (c != p-1 && cur->next != nullptr) {
            c++;
            cur = cur->next;
        }

        // the position does not exist
        if (p-1 > c) {
            cout << "The position does not exist in the list\n";
            return;
        }

        // insert in the end of list
        if (cur->next == nullptr) {
            tail = n;
            n->next = nullptr;
        }
        // position not in the top
        else {
            cur->next->prev = n;
            n->next = cur->next;
        }
        n->prev = cur;
        cur->next = n;

    }

    void printList() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->info;
            current = current->next;
        }
        cout << endl;
    }

void deletion(int position) {
        if (head == nullptr) {
            cout << "Error: List is empty!" << endl;
            return;
        }

        Node* current = head;

        for (int i = 0; i < position; i++) {
            if (current->next == nullptr) {
                cout << "Error: Position out of string length!" << endl;
                return;
            }
            current = current->next;
        }

        if (current == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
    }



    void Concatenation(DLL&obj)
    {
        if(obj.head == NULL)
        {
            return;
        }
        else if(head == NULL)
        {
            head =obj.head ;
            tail =obj.tail;
        }
        else
        {
            tail->next = obj.head;
            if (obj.head)
        {
            obj.head->prev = tail;
        }
            tail = obj.tail;
        }
    }


    void subString(int index, int len) {
        Node* cur = head;
        int c=0;
        while (c!=index && cur->next!=nullptr) {
            c++;
            cur = cur->next;
        }
        if (cur->next == nullptr) {
            cout << "the index does not exist\n";
            return;
        }

        DLL s;
        int indx=0;
        for (int i=0; i<len; i++) {
            s.insertion(cur->info, indx);
            cur = cur->next;
            indx++;
        }
        s.printList();
    }


    int StringLength()
    {

        Node*current;
        current = head;
        int ctr = 0;
        while(current != NULL)
        {
            ctr++;
            current=current->next;
        }
        return ctr;
    }


    void search(string pattern) {
    Node* current = head;
    int index = 0;

    while (current != NULL) {
        Node* temp = current;
        int i = 0;

        while (temp !=NULL && i < pattern.length() && temp->info == pattern[i]) {
            temp = temp->next;
            i++;
        }

        if (i == pattern.length()) {
            cout << "found at index " << index << endl;
            return;
        }

        current = current->next;
        index++;
    }

    cout << "Substring not found!" << endl;
}



void replacement(string s, string newS) {

        if (head == nullptr) {
            cout << "the list is empty\n";
            return;
        }

        // search for s index
        Node* current = head;
        int index = 0;
        bool flag=false;

        while (current != NULL) {
            Node* temp = current;
            int i = 0;

            while (temp !=NULL && i < s.length() && temp->info == s[i]) {
                temp = temp->next;
                i++;
            }

            if (i == s.length()) {
                flag = true;
                break;
            }
            flag = false;
            current = current->next;
            index++;
        }
        if (!flag) {
            index = -1;
        }
        if (index == -1) {
            cout << "String you want to replaced not found\n" << endl;
            return;
        }
        //


        int sLength = s.length();
        int newLength = newS.length();
        Node* nexNode = head;   // the first node after old string

        int c=0;
        while (c!=index+sLength) {
            if (nexNode==nullptr) {
                break;
            }
            c++;
            nexNode = nexNode->next;
        }

        for (int i=0; i<newLength; i++) {
            this->insertion(newS[i], i+index);           // new string inserted but not delete the old nodes
        }

        Node* lastNode=head;   // last node in new index
        int count=0;
        while (count != newLength+index-1) {
            count++;
            lastNode = lastNode->next;
        }

        // last node in new index refer to first node after old string to delete old nodes
        lastNode->next = nexNode;
        if (nexNode!=nullptr)
            nexNode->prev = lastNode;

    }



};





int main() {
    DLL list1, list2;
    string str1, str2;

    cout << "Enter string to add to list 1: ";
    cin >> str1;
    for (int i = 0; i < str1.length(); i++) {
        list1.insertion(str1[i], i);
    }

    cout << "Enter string to add to list 2: ";
    cin >> str2;
    for (int i = 0; i < str2.length(); i++) {
        list2.insertion(str2[i], i);
    }


    cout << "concatenated lists: ";
    list1.Concatenation(list2);
    list1.printList();

    cout<<"the length of the string: ";
    cout <<list1.StringLength()<<endl;


    int pos1;
    cout << "choose a character by index to remove: ";
    cin >> pos1;
    cout << "list after removal: ";
    list1.deletion(pos1);
    list1.printList();



    int l,i;
    cout << "enter index and length to get substring: ";
    cin>>l;
    cin>>i;
    cout<<"substring: ";
    list1.subString(l,i);

    string word;
    cout << "search for string in the list: ";
    cin>>word;
    list1.search(word);


    string k,p;
    cout<<"enter 2 substrings to replace one with another: ";
    cin>>k;
    cin>>p;
    cout<<"list after replacement: ";
    list1.replacement(k,p);
    list1.printList();





    return 0;
}
