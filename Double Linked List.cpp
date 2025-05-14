#include <iostream>
using namespace std;

template<typename elementType>
class Node {
public:
    elementType info;
    Node<elementType>* prev;
    Node<elementType>* next;

    Node(elementType information) {
        info = information;
        prev = nullptr;
        next = nullptr;
    }
};

template<typename elementType>
class DoubleLinkedList {
    Node<elementType> *Head;
    Node<elementType> *Tail;

public:
    DoubleLinkedList() : Head(nullptr), Tail(nullptr) {}

    void insertAtHead(elementType element) {
        Node<elementType> *newNode = new Node<elementType>(element);
        if (Head == nullptr) {
            Head = newNode;
            Tail = newNode;
        } else {
            newNode->next = Head;
            Head->prev = newNode;
            Head = newNode;
        }
    }

    void insertAtTail(elementType element) {
        Node<elementType> *newNode = new Node<elementType>(element);
        if (Head == nullptr) {
            Head = newNode;
            Tail = newNode;
        } else {
            Tail->next = newNode;
            newNode->prev = Tail;
            Tail = newNode;
        }
    }

    void insertAt(elementType element, int index) {
        if (index < 0) {
            cout << "Invalid index." << endl;
            return;
        }
        if (index == 0) {
            insertAtHead(element);
            return;
        }

        Node<elementType> *newNode = new Node<elementType>(element);
        Node<elementType> *current = Head;
        int pos = 0;
        while (current != nullptr && pos != index) {
            current = current->next;
            pos++;
        }
        if (current == nullptr) {
            cout << "Invalid index." << endl;
            delete newNode; // Clean up allocated memory
            return;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }

    void removeAtHead() {
        Node<elementType> *current = Head;
        if(Head== nullptr){

            cout<<"the list is already empty"<<endl;
        }
        if(Head->next== nullptr){
            Head= nullptr;
        }
        else {
            Head = Head->next;
            Head->prev= nullptr;
        }
        delete current;
    }

    void removeAtTail() {
        if (Head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        if (Head == Tail) {
            removeAtHead();
            return;
        }
        Node<elementType> *current = Tail;
        Tail = Tail->prev;
        Tail->next = nullptr;
        delete current;
    }

    void removeAt(int index) {
        if (index < 0) {
            cout << "Invalid index." << endl;
            return;
        }
        if (index == 0) {
            removeAtHead();
            return;
        }

        Node<elementType> *current = Head;
        int pos = 0;
        while (current != nullptr && pos != index) {
            current = current->next;
            pos++;
        }
        if (current == nullptr) {
            cout << "Invalid index." << endl;
            return;
        }
        current->prev->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            Tail = current->prev;
        }
        delete current;
    }

    elementType retrieveAt(int index) {
        if (index < 0) {
            cout << "Invalid index." << endl;
            return elementType();
        }
        if (index == 0 && Head != nullptr) {
            return Head->info;
        }

        Node<elementType> *current = Head;
        int pos = 0;
        while (current != nullptr && pos != index) {
            current = current->next;
            pos++;
        }
        if (current == nullptr) {
            cout << "Invalid index." << endl;
            return elementType();
        }
        return current->info;
    }

    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx == secondItemIdx) {
            // Nothing to swap if indices are the same
            return;
        }

        if (firstItemIdx > secondItemIdx) {
            // Ensure firstItemIdx is smaller for simplicity
            swap(firstItemIdx, secondItemIdx);
            return;
        }

        if (Head == NULL || Head->next == NULL) {
            // If the list is empty or has only one node, nothing to swap
            return;
        }

        // Find the nodes to be swapped
        Node<elementType> *firstNode = Head;
        Node<elementType> *secondNode = Head;
        for (int i = 0; i < firstItemIdx; ++i) {
            firstNode = firstNode->next;
        }
        for (int i = 0; i < secondItemIdx; ++i) {
            secondNode = secondNode->next;
        }

        // Swap the nodes
        if (firstNode->prev != NULL) {
            firstNode->prev->next = secondNode;
        } else {
            Head = secondNode;
        }
        if (secondNode->prev != NULL) {
            secondNode->prev->next = firstNode;
        } else {
            Head = firstNode;
        }

        if (firstNode->next != NULL) {
            firstNode->next->prev = secondNode;
        }
        if (secondNode->next != NULL) {
            secondNode->next->prev = firstNode;
        }

        // Swap prev and next pointers of the nodes
        Node<elementType> *temp = firstNode->prev;
        firstNode->prev = secondNode->prev;
        secondNode->prev = temp;

        temp = firstNode->next;
        firstNode->next = secondNode->next;
        secondNode->next = temp;


        if (Tail == firstNode) {
            Tail = secondNode;
        } else if (Tail == secondNode) {
            Tail = firstNode;
        }
    }



    void replaceAt(elementType newElement, int index) {
        if (index < 0) {
            cout << "Invalid index." << endl;
            return;
        }
        if (index == 0 && Head != nullptr) {
            Head->info = newElement;
            return;
        }

        Node<elementType>* current = Head;
        int pos = 0;
        while (current != nullptr && pos != index) {
            current = current->next;
            pos++;
        }
        if (current == nullptr) {
            cout << "Invalid index." << endl;
            return;
        }
        current->info = newElement;
    }

    bool isExist(elementType element) {
        Node<elementType>* current = Head;
        while (current != nullptr) {
            if (current->info == element) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool isEmpty() {
        return Head == nullptr;
    }

    int DoubleLinkedListSize() {
        int size = 0;
        Node<elementType>* current = Head;
        while (current != nullptr) {
            size++;
            current = current->next;
        }
        return size;
    }

    void clear() {
        Node<elementType>* current = Head;
        while (current != nullptr) {
            Node<elementType>* temp = current;
            current = current->next;
            delete temp;
        }
        Head = nullptr;
        Tail = nullptr;
    }

    void print() {
        Node<elementType>* current = Head;
        while (current != nullptr) {
            cout << current->info << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    DoubleLinkedList<int> list;
    list.insertAtHead(5);
    list.insertAtTail(10);
    list.insertAt(8, 10);
    list.insertAt(8, 1);
    list.print();
    std::cout << "Size: " << list.DoubleLinkedListSize() << std::endl;
    list.removeAtTail();
    list.print();
    list.removeAt(10);
    list.print();
    std::cout << "Is 10 exists? " << std::boolalpha << list.isExist(10) << std::endl;
    list.replaceAt(7, 1);
    list.print();
    list.swap(0, 1);
    list.print();
    return 0;

}
