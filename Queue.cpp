#include <iostream>
using namespace std;

template<typename elementType>
class Node{
public:
    elementType info;
    Node<elementType>* next;
 Node(elementType information){
        info = information;
        next = nullptr;
    }
};

template<typename elementType>
class Queue{
    Node<elementType>* head;
public:
    Queue(){
        head = nullptr;
    }

    void enqueue(elementType element){
        Node<elementType> *newElement = new Node(element);
        if(head == nullptr){
            head = newElement;
        } else {
            Node<elementType>* current = head;
            while(current->next != nullptr){
                current = current->next;
            }
            current->next = newElement;
            newElement->info=element;
        }
    }

    elementType dequeue(){
        if(head == nullptr){
            cout << "Queue is empty" << endl;
            return elementType();
        }
        Node<elementType>* current = head;
        elementType value = head->info;
        head = head->next;
        delete current;
        return value;
    }

    elementType first(){
        if(head == nullptr){
            cout << "Queue is empty" << endl;
            return elementType();
        } else {
            return head->info;
        }
    }

    bool isEmpty(){
        return (head == nullptr);
    }

    int queueSize(){
        Node<elementType>* current = head;
        int size = 0;
        while(current != nullptr){
            current = current->next;
            size++;
        }
        return size;
    }

    void clear(){
        Node<elementType>* temp;
        while(head != nullptr){
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print(){
        Node<elementType>* current = head;
        while(current != nullptr){
            cout << current->info << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main(){
    Queue<int> l;
    l.enqueue(4);
    l.enqueue(5);
    l.enqueue(6);
    l.dequeue();
    cout << "First element: " << l.first() << endl;
    l.print();
    cout << "Queue size: " << l.queueSize() << endl;
    l.clear();
    l.enqueue(48);
    l.print();
    return 0;
}
