#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
   T data;
   Node<T>* next;

   Node(T newData) : data(newData), next(nullptr) {}
};

template <typename T>
class CircularLinkedList {
private:
   Node<T>* head;
   int size;

public:
   //constructor
   CircularLinkedList() : head(nullptr), size(0) {}

   // Destructor
   ~CircularLinkedList() {
       clear();
   }

   void insertAtHead(T element) {
       Node<T>* newNode = new Node<T>(element);
       if (head == nullptr) {
           newNode->next = newNode; // Point to itself to form a circular list
       } else {
           newNode->next = head->next;
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
       newNode->next = head->next;
       head->next = newNode;
       head = newNode;
       ++size;
   }

   void insertAt(T element, int index) {
       if (index <= 0) {
           insertAtHead(element);
       } else if (index >= size) {
           insertAtTail(element);
       } else {
           Node<T>* newNode =new Node<T>(element);
           Node<T>* current = head->next;
           for (int i = 0; i < index - 1; ++i) {
               current = current->next;
           }
           newNode->next = current->next;
           current->next = newNode;
           ++size;
       }
   }

   // Method to remove the element at the head
   void removeAtHead() {
       if (head == nullptr) {
           return;
       }
       if (head->next == head) {
           delete head;
           head = nullptr;
       } else {
           Node<T>* temp = head->next;
           head->next = temp->next;
           delete temp;
       }
       --size;
   }

   // Method to remove the element at the tail
   void removeAtTail() {
       if (head == nullptr) {
           return;
       }
       Node<T>* current = head->next;
       while (current->next != head) {
           current = current->next;
       }
       if (current == head) {
           delete head;
           head = nullptr;
       } else {
           current->next = head->next;
           delete head;
           head = current;
       }
       --size;
   }

   void removeAt(int index) {
       if (index < 0 || index >= size) {
           return;
       }
       if (index == 0) {
           removeAtHead();
       } else if (index == size - 1) {
           removeAtTail();
       } else {
           Node<T>* current = head->next;
           for (int i = 0; i < index - 1; ++i) {
               current = current->next;
           }
           Node<T>* temp = current->next;
           current->next = temp->next;
           delete temp;
           --size;
       }
   }

   T retrieveAt(int index) {
       if (index < 0 || index >= size) {
           throw out_of_range("Index out of range");
       }
       Node<T>* current = head->next;
       for (int i = 0; i < index; ++i) {
           current = current->next;
       }
       return current->data;
   }

   void replaceAt(T newElement, int index) {
       if (index < 0 || index >= size) {
           throw out_of_range("Index out of range");
       }
       Node<T>* current = head->next;
       for (int i = 0; i < index; ++i) {
           current = current->next;
       }
       current->data = newElement;
   }

   bool isExist(T element) {
       Node<T>* current = head->next;
       while (current != head) {
           if (current->data == element) {
               return true;
           }
           current = current->next;
       }
       return false;
   }

   bool isItemAtEqual(T element, int index) {
       if (index < 0 || index >= size) {
           cout<<"Index out of range \n";
       }
       return retrieveAt(index) == element;
   }

   // Method to swap two nodes without swapping data
   void swap(int firstItemIdx, int secondItemIdx) {
       if (firstItemIdx < 0 || firstItemIdx >= size || secondItemIdx < 0 || secondItemIdx >= size) {
           cout << "Index out of range" << endl;
           return;
       }
       if (firstItemIdx == secondItemIdx) {
           return;
       }
       Node<T>* firstPrev = head;
       for (int i = 0; i < firstItemIdx; ++i) {
           firstPrev = firstPrev->next;
       }
       Node<T>* secondPrev = head;
       for (int i = 0; i < secondItemIdx; ++i) {
           secondPrev = secondPrev->next;
       }
       Node<T>* first = firstPrev->next;
       Node<T>* second = secondPrev->next;
       firstPrev->next = second;
       secondPrev->next = first;
       Node<T>* temp = first->next;
       first->next = second->next;
       second->next = temp;

       // Update head if needed
       if (first == head) {
           head = second;
       } else if (second == head) {
           head = first;
       }
   }



   bool isEmpty()  {
       return size == 0;
   }

   int linkedListSize()  {
       return size;
   }

   void clear() {
       while (!isEmpty()) {
           removeAtHead();
       }
   }

   void print() {
       if (isEmpty()) {
           cout << "List is empty." << endl;
           return;
       }
       Node<T>* current = head->next;
       cout << "List elements: ";
       do {
           cout << current->data << " ";
           current = current->next;
       } while (current != head->next);
       cout << endl;
   }

};

int main() {
   CircularLinkedList <int> list;
   list.insertAtHead(5);
   list.insertAtTail(10);
   list.insertAt(8, 1);
   list.print();

   cout << "Size of the list: " << list.linkedListSize() << endl;
   cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
   list.replaceAt(7, 1);
   list.print();
   list.swap(0, 2);
   list.print();
   return 0;
}
