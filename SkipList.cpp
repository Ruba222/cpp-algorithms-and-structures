 #include <iostream>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
public:
    Node* above;
    Node* below;
    Node* next;
    Node* prev;
    string Name;
    int key;

    Node(int key, string name = "") {
        this->Name = name;
        this->key = key;
        this->next = nullptr;
        this->above = nullptr;
        this->below = nullptr;
        this->prev = nullptr;
    }
};

class SkipList {
public:
    Node *head;
    Node *tail;
    int height = 0;

    const int neg_inf = INT_MIN;
    const int pos_inf = INT_MAX;

    SkipList() {
        head = new Node(neg_inf);
        tail = new Node(pos_inf);
        head->next = tail;
        tail->prev = head;
    }

    bool flipCoin() {
        return rand() % 2 == 0; // 50% chance
    }

    void addEmptyLevel() {
        Node *newHead = new Node(neg_inf);
        Node *newTail = new Node(pos_inf);
        newHead->next = newTail;
        newTail->prev = newHead;

        newHead->below = head;
        head->above = newHead;

        newTail->below = tail;
        tail->above = newTail;

        head = newHead;
        tail = newTail;

        height++;
    }

    Node *SkipSearch(int key) {
        Node *current = head;
        while (current) {
            while (current->next && current->next->key <= key) {
                current = current->next;
            }
            if (current->key == key) {
                return current;
            }
            current = current->below;
        }
        return nullptr;
    }
    Node* SkipSearchByName(string name) {
        Node* current = head;
        while (current->below) {
            current = current->below; // Move to the bottom level
        }
        current = current->next; // Skip the head sentinel

        while (current != tail) {
            if (current->Name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Node *SkipInsert(int key, string name = "") {
        Node *position = head;
        while (position->below) position = position->below;

        while (position->next->key < key) position = position->next;

        Node *newNode = new Node(key, name);
        newNode->next = position->next;
        newNode->prev = position;
        position->next->prev = newNode;
        position->next = newNode;

        int level = 0;
        while (flipCoin()) {
            if (level >= height) addEmptyLevel();

            while (position->above == nullptr) position = position->prev;
            position = position->above;

            Node *upperNode = new Node(key, name);
            upperNode->next = position->next;
            upperNode->prev = position;
            position->next->prev = upperNode;
            position->next = upperNode;

            upperNode->below = newNode;
            newNode->above = upperNode;

            newNode = upperNode;
            level++;
        }
        return newNode;
    }

    void SkipRemove(int key) {
        Node *node = SkipSearch(key);
        if (!node) {
            cout << "Player with score " << key << " not found!" << endl;
            return;
        }

        while (node) {
            Node *nextNode = node->above;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            node = nextNode;
        }
    }

    void displayTopPlayers(int n) {
        Node *current = head;
        while (current->below) current = current->below; // Move to the bottom level
        current = current->next; // Skip the head sentinel node

        cout << "Top " << n << " Players:" << endl;
        while (current != tail && n--) {
            cout << current->Name << " - " << current->key << endl;
            current = current->next;
        }
    }
    vector<Node*> getAllNodes() {
        std::vector<Node*> nodes;

        // Traverse to the bottom level
        Node *current = head;
        while (current->below) {
            current = current->below;
        }
        current = current->next;  // Skip the head sentinel
        while (current != tail) {  // Ensure we do not include the tail node
            if (current == nullptr) {
                break;
            }

            nodes.push_back(current);
            current = current->next;
        }

        return nodes;
    }



    // New function to sort and print only the first n nodes
    void printTopNPlayers(int n) {
        vector<Node*> allNodes = getAllNodes();

        // Sort the vector in descending order based on score (key)
        std::sort(allNodes.begin(), allNodes.end(), [](Node* a, Node* b) {
            return a->key > b->key; // Sort in descending order
        });

        // Print only the first n players
        std::cout << "Top " << n << endl;
        for (int i = 0; i < n && i < allNodes.size(); ++i) {
            std::cout << allNodes[i]->Name << ": " << allNodes[i]->key << std::endl;
        }
    }



    ~SkipList() {
        while (head) {
            Node *current = head;
            head = head->below;

            while (current) {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};
class Game {
private:
    SkipList skip;

public:
    void addPlayer(int score, string name) {
        skip.SkipInsert(score, name);
    }

    void removePlayer(string name) {
        Node* playerNode = skip.SkipSearchByName(name);
        if (playerNode) {
            skip.SkipRemove(playerNode->key);
            cout << "Player " << name << " removed from the game." << endl;
        } else {
            cout << "Player " << name << " not found!" << endl;
        }
    }

    void displayLeaderboard(int N) {
        skip.printTopNPlayers(N);
    }

    void updatePlayerScore(int score, string name) {
        Node* playerNode = skip.SkipSearchByName(name);
        if (playerNode) {
            skip.SkipRemove(playerNode->key);
            skip.SkipInsert(score, name);
            cout << "Updated score for " << name << " to " << score << endl;
        } else {
            cout << "Player " << name << " not found!" << endl;
        }
    }

    void viewPlayerScore(string name) {
        Node* playerNode = skip.SkipSearchByName(name);
        if (playerNode) {
            cout << name << "'s current score: " << playerNode->key << endl;
        } else {
            cout << "Player " << name << " not found!" << endl;
        }
    }
};



int main(){
    SkipList skip;
    skip.SkipInsert(9);
    skip.SkipInsert(90);
    skip.SkipInsert(900);
    skip.SkipInsert(9000);
    skip.SkipRemove(9);
    if(skip.SkipSearch(9)){
        cout<<"  found "<<endl;
    }
    else {
        cout<<"not  found"<<endl;
    }
    if(skip.SkipSearch(90)){
        cout<<"  found "<<endl;
    }
    else {
        cout<<"not found"<<endl;
    }

    Game game;
    game.addPlayer(10,"p1");
    game.addPlayer(20,"p2");
    game.addPlayer(30,"p3");
    game.addPlayer(40,"p4");
    game.addPlayer(50,"p5");
    cout<<"display top 3";
    game.displayLeaderboard(3);

    game.removePlayer("p5");
    cout<<"display top 3 after removing the top 1 player"<<endl;
    game.displayLeaderboard(3);

    game.updatePlayerScore(80,"p5");
    game.viewPlayerScore("p3");
}