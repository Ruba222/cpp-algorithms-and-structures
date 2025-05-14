#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(T newData) : data(newData), next(nullptr) {}
    };

    Node* topNode;
    int size;

public:
    Stack() : topNode(nullptr), size(0) {}

    void push(T element) {
        Node* newNode = new Node(element);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    T pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty\n";
            return T();
        }
        Node* temp = topNode;
        T poppedElement = temp->data;
        topNode = topNode->next;
        delete temp;
        size--;
        return poppedElement;
    }

    T top() {
        if (isEmpty()) {
            std::cerr << "Stack is empty\n";
            return T();
        }
        return topNode->data;
    }

    bool isEmpty() {
        return size == 0;
    }

    int stackSize() {
        return size;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    void print() {
        Node* temp = topNode;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    ~Stack() {
        clear();
    }
};

int main() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(4);
    std::cout << "Stack size: " << stack.stackSize() << std::endl;
    std::cout << "Top element: " << stack.top() << std::endl;
    std::cout << "Popped element: " << stack.pop() << std::endl;
    std::cout << "Stack size after pop: " << stack.stackSize() << std::endl;
    stack.print();
    return 0;
}
