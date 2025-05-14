#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T newData) : data(newData), next(nullptr), prev(nullptr) {}
};

template <typename T>
class CircularDoublyLinkedList {
private:
    Node<T>* head;
    int size;

public:
    CircularDoublyLinkedList() : head(nullptr), size(0) {}

    ~CircularDoublyLinkedList() {
        clear();
    }

    void insertAtHead(T element) {
        Node<T>* newNode = new Node<T>(element);
        if (head == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;
        }
        head = newNode;
        ++size;
    }

    void insertAtTail(T element) {
        if (head == nullptr) {
            insertAtHead(element);
            return;
        }
        Node<T>* newNode = new Node<T>(element);
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
        ++size;
    }

    void insertAt(T element, int index) {
        if (index <= 0) {
            insertAtHead(element);
        } else if (index >= size) {
            insertAtTail(element);
        } else {
            Node<T>* newNode = new Node<T>(element);
            Node<T>* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
            ++size;
        }
    }

    void removeAtHead() {
        if (head == nullptr) {
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
            delete temp;
        }
        --size;
    }

    void removeAtTail() {
        if (head == nullptr) {
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head->prev;
            head->prev = temp->prev;
            temp->prev->next = head;
            delete temp;
        }
        --size;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            return;
        }
        if (index == 0) {
            removeAtHead();
        } else if (index == size - 1) {
            removeAtTail();
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            --size;
        }
    }

    T retrieveAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            return T();
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void replaceAt(T newElement, int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            return;
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->data = newElement;
    }

    bool isExist(T element) {
        if (head == nullptr) {
            return false;
        }
        Node<T>* current = head;
        do {
            if (current->data == element) {
                return true;
            }
            current = current->next;
        } while (current != head);
        return false;
    }

    bool isItemAtEqual(T element, int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range" << endl;
            return false;
        }
        return retrieveAt(index) == element;
    }

    void clear() {
        while (!isEmpty()) {
            removeAtHead();
        }
    }

    bool isEmpty() {
        return size == 0;
    }

    int linkedListSize() {
        return size;
    }

    void print() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }
        Node<T>* current = head;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
};

int main() {
    CircularDoublyLinkedList<int> list;
    list.insertAtHead(5);
    list.insertAtTail(10);
    list.insertAt(8, 1);
    list.print();

    cout << "Size of the list: " << list.linkedListSize();
}
