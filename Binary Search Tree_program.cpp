#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>

using namespace std;

class Item {
public:
    string itemName;
    string category;
    int price;

    const string &getItemName() const {
        return itemName;
    }

    const string &getCategory() const {
        return category;
    }

    int getPrice() const {
        return price;
    }

public:
    Item(string name, string cat, int p) : itemName(name), category(cat), price(p) {}

    bool operator<(const Item& other) const {
        string item = itemName;
        string another = other.itemName;

        transform(item.begin(), item.end(), item.begin(), ::tolower);
        transform(another.begin(), another.end(), another.begin(), ::tolower);

        return item < another;
    }

    bool operator>(const Item& other) const {
        string item = itemName;
        string another = other.itemName;

        transform(item.begin(), item.end(), item.begin(), ::tolower);
        transform(another.begin(), another.end(), another.begin(), ::tolower);

        return item > another;
    }
    void print() const {
        cout << "Item: " << itemName << " | Category: " << category << " | Price: " << price << endl;
    }
};
 //Node class for BST
class Node {
public:
    Item data;
    Node* left;
    Node* right;
    Node(Item item) : data(item), left(nullptr), right(nullptr) {}
    ~Node() {
        delete left;
        delete right;
    }
};

// Binary Search Tree class
class BST {
private:
    Node* root;

    // Private functions
    void add(Node*& node, const Item& item) {
        if (!node) {
            node = new Node(item);
            return;
        }
        if (item < node->data)
            add(node->left, item);
        else
            add(node->right, item);
    }

    Node* remove(Node* node, const string& name) {
        if (!node) return nullptr;

        if (name < node->data.getItemName())
            node->left = remove(node->left, name);
        else if (name > node->data.getItemName())
            node->right = remove(node->right, name);
        else {
            // Node to be deleted found
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data.getItemName());
            }
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        node->data.print();
        inOrder(node->right);
    }
    void inOrderd(Node* node) {
        if (!node) return;
        inOrderd(node->right);
        node->data.print();
        inOrderd(node->left);
    }
    void inorderbyitemdata(Node* node, vector<Item>& items) const {
        if (node == NULL) {
            return;
        }
        inorderbyitemdata(node->left, items);
        items.push_back(node->data);
        inorderbyitemdata(node->right, items);
    }

    // Collects all items in the tree into a vector
    void transferItems(Node* node, vector<Item>& items) {
        if (node != nullptr) {
            transferItems(node->left, items);
            items.push_back(node->data);
            transferItems(node->right, items);
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() {
        delete root;
    }

    void add(const Item& item) {
        add(root, item);
    }

    void remove(const string& name) {
        root = remove(root, name);
    }

    void displayNameAscending() {
        inOrder(root);
    }
    void displayNameDescending() {
        inOrderd(root);
    }


    void displayPriceAscending() {
        vector<Item> items;
        transferItems(root, items);
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getPrice() < b.getPrice();
        });
        for (const auto& item : items) {
            item.print();
        }
    }

    void displayPriceDescending() {
        vector<Item> items;
        transferItems(root, items);
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.getPrice() > b.getPrice();
        });
        for (const auto& item : items) {
            item.print();
        }
    }
    void displayitemdata() const {
        vector<Item> itms;
        inorderbyitemdata(root, itms);
        sort(itms.begin(), itms.end(), [](const Item& a, const Item& b) {

            return a.itemName < b.itemName;
        });
        for (const auto& item : itms) {
            item.print();
        }
        cout << endl;
    }
    bool isValidPrice(int price) const {
        return price >= 0; // Ensure price is non-negative
    }
    bool contains(Node* node, const string& name) {
        if (!node) return false;

        if (name < node->data.getItemName())
            return contains(node->left, name);
        else if (name > node->data.getItemName())
            return contains(node->right, name);
        else
            return true;
    }

    bool contains(const string& name) {
        return contains(root, name);
    }

};

void readItems(const string& filename, BST& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string itemName, category, priceStr;
    while (getline(file, itemName)) {
        if (itemName.empty()) {
            continue; // Skip empty line
        }

        if (!getline(file, category) || !getline(file, priceStr)) {
            break;
        }

        if (priceStr.empty()) {
            continue;
        }

        int price;
        price = stoi(priceStr);

        Item newItem(itemName, category, price);
        bst.add(newItem); // Add item to the BST
    }

    file.close();
}

void BST_Menu(){
    BST bst;
    string fileName = "items";
    readItems(fileName, bst);


    int choice;
    do {
        cout << "Binary Search Tree Menu:" << endl;
        cout << "1. Add item" << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Display Items Sorted by Name in Ascending Order" << endl;
        cout << "4. Display Items Sorted by Name in Descending Order" << endl;
        cout << "5. Display Items sorted by Prices in Ascending order" << endl;
        cout << "6. Display Items sorted by Prices in Descending order" << endl;
        cout << "7. Display Items sorted by Data Normally" << endl;
        cout << "0.Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, category;
                int price;
                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter category: ";
                getline(cin, category);
                do {
                    cout << "Enter price: ";
                    cin >> price;
                } while (!bst.isValidPrice(price));
                Item item(name, category, price);
                bst.add(item);
                cout<<name<<" added successfully"<<endl;
                break;
            }
            case 2: {
                string name;
                cout << "Enter item name to remove: ";
                cin.ignore();
                getline(cin, name);

                if (!bst.contains(name)) {
                    cout << "Error: The name entered does not match any of the items." << endl;
                } else {
                    bst.remove(name);
                    cout << name << " removed" << endl;
                }
                break;
            }
            case 3: {
                cout << "Items Sorted by Name in Ascending Order:" << endl;
                bst.displayNameAscending();
                break;
            }
            case 4: {
                cout << "Items Sorted by Name in Descending Order:" << endl;
                bst.displayNameDescending();
                break;
            }
            case 5: {
                cout << "Items sorted by price in ascending order:" << endl;
                bst.displayPriceAscending();
                break;
            }
            case 6: {
                cout << "Items sorted by price in descending order:" << endl;
                bst.displayPriceDescending();
                break;
            }
                // displayitemdata()
            case 7: {
                cout << "Items sorted by Data Normally:" << endl;
                bst.displayitemdata();
                break;
            }
            case 0: {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}



class Node2 {
public:
    Item data;
    Node2* left;
    Node2* right;
    int height;

    Node2(Item item) : data(item), left(nullptr), right(nullptr), height(1) {}
};

int max(int a, int b) {
    return (a > b) ? a : b;}

int height(Node2* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}
// AVL Tree class
class AVLTree {
private:
    Node2* root;

    // Private functions
    int getHeight(Node2* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalanceFactor(Node2* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    void readFromAvlTree(Node2* node, vector<Item>& sortedItems) {
        if (node == nullptr) return;
        readFromAvlTree(node->left, sortedItems);
        sortedItems.push_back(node->data);
        readFromAvlTree(node->right, sortedItems);
    }


    //right rotation on the AVL tree
    Node2* rightRotate(Node2* root) {
        Node2 *p;

        if (root == nullptr)
            cout << "Error in the tree" << endl;
        else if (root->left == nullptr)
            cout << "Error in the tree: No left subtree to rotate." << endl;
        else {
            p = root->left;
            root->left = p->right;
            p->right = root;
            root = p;
        }
    }

    Node2* leftRotate(Node2* root) {
        Node2* p;

        if (root == nullptr)
            cout << "Error in the tree" << endl;
        else if (root->right == nullptr)
            cout << "Error in the tree: No right subtree to rotate." << endl;
        else {
            p = root->right;
            root->right = p->left;
            p->left = root;
            root = p;
        }
    }


    Node2* insert(Node2* node, const Item& item) {
        if (node == nullptr) return new Node2(item);

        if (item < node->data)
            node->left = insert(node->left, item);
        else if (item > node->data)
            node->right = insert(node->right, item);
        else
            return node; // Duplicate keys not allowed

        // Update height of this current node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor to check  this node became unbalanced
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && item < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && item > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && item > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && item < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // No rotations needed
        return node;
    }

    Node2* minValueNode(Node2* node) {
        Node2* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node2* remove(Node2* node, const string& name) {
        if (node == nullptr) return nullptr;

        if (name < node->data.getItemName())
            node->left = remove(node->left, name);
        else if (name > node->data.getItemName())
            node->right = remove(node->right, name);
        else {
            // Node to be deleted found
            if (!node->left || !node->right) {
                Node2* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp; // Copy the contents of the non-empty child
                delete temp;
            } else {
                Node2* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data.getItemName());
            }
        }

        if (node == nullptr) return nullptr;

        // Update height of the current node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor to check whether this node became unbalanced
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);

        // Left Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);

        // Right Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(Node2* node) {
        if (node == NULL) return;
        inOrder(node->left);
        node->data.print();
        inOrder(node->right);
    }
    //Display all the items sorted by their name  descending,
    void inorderd(Node2* node)const{

        if (node == NULL) {
            return;
        }
        inorderd(node->right);
        node->data .print();
        inorderd(node->left);
    }
    void inorderbyitemdata(Node2* node, vector<Item>& items) const {
        if (node == NULL) {
            return;
        }
        inorderbyitemdata(node->left, items);
        items.push_back(node->data);
        inorderbyitemdata(node->right, items);
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        delete root;
    }

    void add(const Item& item) {
        root = insert(root, item);
    }

    void remove(const string& name) {
        root = remove(root, name);
    }

    void displayNameAscending() {
        inOrder(root);
    }
    //Display all the items sorted by their name  descending,
    void displayNamedecending() {
        inorderd(root);
    }
    void displayitemdata() const {
        vector<Item> itms;
        inorderbyitemdata(root, itms);
        sort(itms.begin(), itms.end(), [](const Item& a, const Item& b) {

            return a.itemName < b.itemName;
        });
        for (const auto& item : itms) {
            item.print();
        }
        cout << endl;
    }
    void displayPriceAscending() {
        vector<Item> sortedItems;
        readFromAvlTree(root, sortedItems);
        sort(sortedItems.begin(), sortedItems.end(), [](const Item& a, const Item& b) {
            return a.getPrice() < b.getPrice();
        });
        for (const auto& item : sortedItems) {
            item.print();
        }
    }
    void displayPriceDescending() {
        vector<Item> sortedItems;
        readFromAvlTree(root, sortedItems);
        sort(sortedItems.begin(), sortedItems.end(), [](const Item& a, const Item& b) {
            return a.getPrice() > b.getPrice();
        });
        for (const auto& item : sortedItems) {
            item.print();
        }
    }



    bool isValidPrice(int price) const {
        return price >= 0; // Ensure price is non-negative
    }

    bool contains(Node2* node, const string& name) {
        if (node == nullptr) return false;

        if (name < node->data.getItemName())
            return contains(node->left, name);
        else if (name > node->data.getItemName())
            return contains(node->right, name);
        else
            return true;
    }

    bool contains(const string& name) {
        return contains(root, name);
    }
};

void readItems(const string& filename, AVLTree& avl) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string itemName, category, priceStr;
    while (getline(file, itemName)) {
        if (itemName.empty()) {
            continue; // Skip empty line
        }

        if (!getline(file, category) || !getline(file, priceStr)) {
            break;
        }

        if (priceStr.empty()) {
            continue;
        }

        int price;
        price = stoi(priceStr);

        Item newItem(itemName, category, price);
        avl.add(newItem); // Add item to the AVL tree
    }

    file.close();
}

void AVL_Menu() {
    AVLTree avl;
    string fileName = "items";
    readItems(fileName, avl);


    int choice;
    do {
        cout << "AVL Tree Menu:" << endl;
        cout << "1. Add item" << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Display Items Sorted by Name in Ascending Order" << endl;
        cout << "4. Display Items Sorted by Name in Descending Order" << endl;
        cout << "5. Display Items Sorted by Normally Data item" << endl;
        cout << "6. Display Items Sorted by Price in Ascending Order" << endl;
        cout << "7. Display Items Sorted by Price in Descending Order" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, category;
                int price;
                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter category: ";
                getline(cin, category);
                do {
                    cout << "Enter price: ";
                    cin >> price;
                } while (!avl.isValidPrice(price));
                Item item(name, category, price);
                avl.add(item);
                cout<<name<<" added successfully"<<endl;
                break;
            }
            case 2: {
                string name;
                cout << "Enter item name to remove: ";
                cin.ignore();
                getline(cin, name);

                if (!avl.contains(name)) {
                    cout << "Error: The name entered does not match any of the items." << endl;
                } else {
                    avl.remove(name);
                    cout << name << " removed" << endl;
                }
                break;
            }
            case 3: {
                cout << "Items Sorted by Name in Ascending Order:" << endl;
                avl.displayNameAscending();
                break;
            }
                //Items Sorted by Name in Descending Order
            case 4: {
                cout << "Items Sorted by Name in Descending Order:" << endl;
                avl.displayNamedecending();
                break;
            }
                //"Items Sorted by Data Normally
            case 5: {
                cout << "Items Sorted by Data Normally:" << endl;
                avl.displayitemdata();
                break;
            }
            case 6: {
                cout << "Items Sorted by Price in Ascending Order:" << endl;
                avl.displayPriceAscending();
                break;
            }
            case 7: {
                cout << "Items Sorted by Price in Descending Order:" << endl;
                avl.displayPriceDescending();
                break;
            }


            case 0: {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice);

}

class HEAP {
public:
    vector<Item> heap;

    void MAX_HEAPIFY(vector<Item>& heap, int parent, int SIZE) {
        int LeftChild = (2 * parent) + 1;
        int RightChild = (2 * parent) + 2;
        int largest = parent;
        if (LeftChild < SIZE && heap[LeftChild] > heap[parent]) {
            largest = LeftChild;
        }
        if (RightChild < SIZE && heap[RightChild] > heap[largest]) {
            largest = RightChild;
        }
        if (largest != parent) {
            swap(heap[largest], heap[parent]);
            MAX_HEAPIFY(heap, largest, SIZE);
        }
    }
   void  MAX_HEAPIFY2(vector<Item>& heap, int parent, int SIZE) {
        int LeftChild = (2 * parent) + 1;
        int RightChild = (2 * parent) + 2;
        int largest = parent;
        if (LeftChild < SIZE && heap[LeftChild].getPrice() > heap[parent].getPrice()) {
            largest = LeftChild;
        }
        if (RightChild < SIZE && heap[RightChild].getPrice() > heap[largest].getPrice()) {
            largest = RightChild;
        }
        if (largest != parent) {
            swap(heap[largest], heap[parent]);
            MAX_HEAPIFY2(heap, largest, SIZE);
        }
    }

    void MIN_HEAPIFY(vector<Item>& heap, int parent, int SIZE) {
        int LeftChild = (2 * parent) + 1;
        int RightChild = (2 * parent) + 2;
        int smallest = parent;
        if (LeftChild < SIZE && heap[LeftChild] < heap[parent]) {
            smallest = LeftChild;
        }
        if (RightChild < SIZE && heap[RightChild] < heap[smallest]) {
            smallest = RightChild;
        }
        if (smallest != parent) {
            swap(heap[smallest], heap[parent]);
            MIN_HEAPIFY(heap, smallest, SIZE);
        }
    }
    void MIN_HEAPIFY2(vector<Item>& heap, int parent, int SIZE) {
        int LeftChild = (2 * parent) + 1;
        int RightChild = (2 * parent) + 2;
        int smallest = parent;
        if (LeftChild < SIZE && heap[LeftChild].getPrice() < heap[parent].getPrice()) {
            smallest = LeftChild;
        }
        if (RightChild < SIZE && heap[RightChild].getPrice() < heap[smallest].getPrice()) {
            smallest = RightChild;
        }
        if (smallest != parent) {
            swap(heap[smallest], heap[parent]);
            MIN_HEAPIFY2(heap, smallest, SIZE);
        }
    }

    void BUILD_MAX_HEAP(vector<Item>& heap) {
        int SIZE = heap.size();
        for (int i = SIZE / 2 - 1; i >= 0; i--) {
            MAX_HEAPIFY(heap, i, SIZE);
        }
    }
    void BUILD_MAX_HEAP2(vector<Item>& heap) {
        int SIZE = heap.size();
        for (int i = SIZE / 2 - 1; i >= 0; i--) {
            MAX_HEAPIFY2(heap, i, SIZE);
        }
    }

    void BUILD_MIN_HEAP(vector<Item>& heap) {
        int SIZE = heap.size();
        for (int i = SIZE / 2 - 1; i >= 0; i--) {
            MIN_HEAPIFY(heap, i, SIZE);
        }
    }
    void BUILD_MIN_HEAP2(vector<Item>& heap) {
        int SIZE = heap.size();
        for (int i = SIZE / 2 - 1; i >= 0; i--) {
            MIN_HEAPIFY2(heap, i, SIZE);
        }
    }

    void MAX_HEAPSORT(vector<Item>& heap) {
        int SIZE = heap.size();
        BUILD_MAX_HEAP(heap);
        for (int i = SIZE - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            MAX_HEAPIFY(heap, 0, i);
        }
    }
    void MAX_HEAPSORT2(vector<Item>& heap) {
        int SIZE = heap.size();
        BUILD_MAX_HEAP2(heap);
        for (int i = SIZE - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            MAX_HEAPIFY2(heap, 0, i);
        }
    }

    void MIN_HEAPSORT(vector<Item>& heap) {
        int SIZE = heap.size();
        BUILD_MIN_HEAP(heap);
        for (int i = SIZE - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            MIN_HEAPIFY(heap, 0, i);
        }
    }
    void MIN_HEAPSORT2(vector<Item>& heap) {
        int SIZE = heap.size();
        BUILD_MIN_HEAP2(heap);
        for (int i = SIZE - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            MIN_HEAPIFY2(heap, 0, i);
        }
    }

    void AddItem(const Item &item) {
        heap.push_back(item);
        BUILD_MAX_HEAP(heap);
    }
    void RemoveItem(const string& itemName) {
        auto it = find_if(heap.begin(), heap.end(), [&](const Item& item) {
            return item.itemName == itemName;
        });

        if (it != heap.end()) {
            heap.erase(it);
            // Rebuild the heap after removal
            BUILD_MAX_HEAP(heap);
            cout<<" item Removed Successfully"<<endl;


        } else
        {
           cout<<"the item name that you try to remove is not in the heap "<<endl;
            return ;
        }
    }





    void DiplaySortByNameAscending() {
        if(heap.size()==0){cout<<"heap is empty!"<<endl;}
        MAX_HEAPSORT(heap);
        for (int i = 0; i < heap.size(); i++) {
            heap[i].print();
            cout << endl;
        }
    }

    void DiplaySortByNameDescending() {
        if(heap.size()==0){cout<<"heap is empty!"<<endl;}
        MIN_HEAPSORT(heap);
        for (int i = 0; i < heap.size(); i++) {
            heap[i].print();
            cout << endl;
        }
    }
    void DiplaySortByPriceAscending() {
        if(heap.size()==0){cout<<"heap is empty!"<<endl;}
        MAX_HEAPSORT2(heap);
        for (int i = 0; i < heap.size(); i++) {
            heap[i].print();
            cout << endl;
        }
    }
    void DiplaySortByPriceDescending() {
        if(heap.size()==0){cout<<"heap is empty!"<<endl;}
        MIN_HEAPSORT2(heap);
        for (int i = 0; i < heap.size(); i++) {
            heap[i].print();
            cout << endl;
        }
    }
    void DisplayItemNormaly() {
        if(heap.size()==0){cout<<"heap is empty!"<<endl;}
        for (int i = 0; i < heap.size(); i++) {
            heap[i].print();
            cout << endl;
        }
    }
};


void readItems(const string& filename, HEAP& tree) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string itemName, category, priceStr;
    int lineCounter = 0;
    while (getline(file, itemName)) {
        // Skip empty lines
        if (itemName.empty()) {
            continue;
        }
        lineCounter++;
        if (!getline(file, category)) {

            break;
        }
        if (!getline(file, priceStr)) {

            break;
        }

        if (priceStr.empty()) {
            continue;
        }
        int price;
        price = stoi(priceStr);

        Item newItem(itemName, category, price);
        tree.AddItem(newItem);
    }

    file.close();
}

void Heap_Menu(){
    int c ;
    HEAP heap;
    do{
    cout<<"Heap Menu : "<<endl;
    cout<<"1- Read item from a file "<<endl;
    cout<<"2- Add item "<<endl;
    cout<<"3- Remove item "<<endl;
    cout<<"4- Display item data normally "<<endl;
    cout<<"5- Display  items sorted by their name ascending"<<endl;
    cout<<"6- Display  items sorted by their name descending"<<endl;
    cout<<"7- Display  items sorted by their price ascending"<<endl;
    cout<<"8- Display  items sorted by their price descending"<<endl;
    cout<<"0- Exit "<<endl;
    cout << "Enter your choice from HEAP menu: " << endl;
    cin>>c;

        switch (c) {
            case 1: {
                string fileName;
                cout << "Enter you file Name :";
                cin >> fileName;
                readItems(fileName, heap);
                cout<<"read items from file Successfully"<<endl;
                break;
            }
            case 2: {
                string name, category;
                int price;
                cout << "write item name :";
                cin.ignore();
                getline(cin, name);
                cout << "write item category :";
                getline(cin, category);
                cout << "write item price :";
                cin >> price;
                heap.AddItem(Item(name, category, price));
                cout<<" item Added Successfully"<<endl;
                break;
            }
            case 3: {
                string name;
                cout << "write item name :";
                cin.ignore();
                getline(cin, name);
                heap.RemoveItem(name);

                break;
            }
            case 4: {
                heap.DisplayItemNormaly();
                break;
            }
            case 5: {
                cout<<" Sorting By Name Ascending using MAX HEAP :"<<endl;
                heap.DiplaySortByNameAscending();
                break;
            }
            case 6: {
                cout<<" Sorting By Name Descending using MIN HEAP :"<<endl;
                heap.DiplaySortByNameDescending();
                break;
            }
            case 7: {
                cout<<" Sorting By Price Ascending using MAX HEAP :"<<endl;
                heap.DiplaySortByPriceAscending();
                break;
            }
            case 8: {
                cout<<" Sorting By Price Descending using MIN HEAP :"<<endl;
                heap.DiplaySortByPriceDescending();
                break;
            }
            case 0 :

                return ;

            default:
                cout<<"invalid choice "<<endl;

        }
    }
    while ( c);


}
void Main_Menu() {
    int choice;
    do{
        cout << "Here is a menu for non linear structure:" << endl;
        cout << "10. Binary Search Trees (BST) " << endl;
        cout << "20. Heaps " << endl;
        cout << "30. AVL Trees " << endl;
        cout << "40.for exit  " << endl;

        cout << "Enter your choice from non linear structures : " << endl;
        cin >> choice;

            switch (choice) {
                case  10 : {
                    BST_Menu();
                    break;
                }
                case 20 : {
                    Heap_Menu();
                    break;
                }
                case 30 : {
                  AVL_Menu();
                    break;
                }
                case 40 : {
                    return;
                }
                default:
                    cout << "invalid choice " << endl;

            }
        }
    while (choice!=40);

}




int main() {
Main_Menu();


}






