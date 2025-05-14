#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T newData) : data(newData), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    void insertAtHead(T element) {
        Node<T>* newNode = new Node<T>(element);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void insertAtTail(T element) {
        if (head == nullptr) {
            insertAtHead(element);
            return;
        }
        Node<T>* newNode = new Node<T>(element);
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        size++;
    }

    void insertAt(T element, int index) {
        if (index < 0 || index > size) {
            std::cerr << "Invalid index\n";
            return;
        }
        if (index == 0) {
            insertAtHead(element);
            return;
        }
        if (index == size) {
            insertAtTail(element);
            return;
        }
        Node<T>* newNode = new Node<T>(element);
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    void removeAtHead() {
        if (head == nullptr) {
            std::cerr << "List is empty\n";
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void removeAtTail() {
        if (head == nullptr) {
            std::cerr << "List is empty\n";
            return;
        }
        if (head->next == nullptr) {
            removeAtHead();
            return;
        }
        Node<T>* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        size--;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Invalid index\n";
            return;
        }
        if (index == 0) {
            removeAtHead();
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        Node<T>* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        size--;
    }

    T retrieveAt(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Invalid index\n";
            return T();
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    void replaceAt(T newElement, int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Invalid index\n";
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->data = newElement;
    }

    bool isExist(T element) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == element) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool isItemAtEqual(T element, int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Invalid index\n";
            return false;
        }
        return retrieveAt(index) == element;
    }

    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx < 0 || firstItemIdx >= size || secondItemIdx < 0 || secondItemIdx >= size) {
            std::cerr << "Invalid indices\n";
            return;
        }
        if (firstItemIdx == secondItemIdx) {
            return;
        }

        Node<T>* prevFirst = nullptr;
        Node<T>* currFirst = head;
        for (int i = 0; i < firstItemIdx; i++) {
            prevFirst = currFirst;
            currFirst = currFirst->next;
        }

        Node<T>* prevSecond = nullptr;
        Node<T>* currSecond = head;
        for (int i = 0; i < secondItemIdx; i++) {
            prevSecond = currSecond;
            currSecond = currSecond->next;
        }

        if (prevFirst != nullptr) {
            prevFirst->next = currSecond;
        } else {
            head = currSecond;
        }

        if (prevSecond != nullptr) {
            prevSecond->next = currFirst;
        } else {
            head = currFirst;
        }

        Node<T>* temp = currFirst->next;
        currFirst->next = currSecond->next;
        currSecond->next = temp;
    }

    bool isEmpty() {
        return size == 0;
    }

    int linkedListSize() {
        return size;
    }

    void clear() {
        while (head != nullptr) {
            removeAtHead();
        }
    }

    void print() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() {
        clear();
    }
};

int main() {
    LinkedList<int> list;
    list.insertAtHead(5);
    list.insertAtTail(10);
    list.insertAt(8, 1);
    list.print();
    std::cout << "Size: " << list.linkedListSize() << std::endl;
    list.removeAtTail();
    list.print();
    std::cout << "Is 10 exists? " << std::boolalpha << list.isExist(10) << std::endl;
    list.replaceAt(7, 1);
    list.print();
    list.swap(0, 1);
    list.print();
    return 0;
}
