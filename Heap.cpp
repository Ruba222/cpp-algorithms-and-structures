#include <iostream>
#include <vector>
using namespace std;
class HEAP {
public:
    vector<int> heap;

    void MAX_HEAPIFY(vector<int>& heap, int parent, int SIZE) {
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
        void MIN_HEAPIFY(vector<int> &heap, int parent, int SIZE) {
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
        int extract_max() {
            if (heap.size() < 1) {
                cout << "heap is empty" << endl;
            }
            BUILD_MAX_HEAP(heap);
            int max = heap[0];
            heap[0] = heap.back();     // Replace root with the last element/////////////////////////////
            heap.pop_back();
            MAX_HEAPIFY(heap, 0, heap.size()); // Restore max-heap
            return max;
        }
    int Get_max() {
        if (heap.size() < 1) {
            cout << "heap is empty" << endl;
        }

        MAX_HEAPIFY(heap, 0, heap.size());
        return heap[0];
    }
    int extract_min() {
        if (heap.size() < 1) {
            cout << "heap is empty" << endl;
        }
        BUILD_MIN_HEAP(heap);
        int min = heap[0];
        heap[0] = heap.back();     // Replace root with the last element
        heap.pop_back();
       // MIN_HEAPIFY(heap, 0, heap.size()); // Restore min-heap
        return min;
    }
    void BUILD_MAX_HEAP(vector<int>& heap) {
        int SIZE = heap.size();
        for (int i = SIZE / 2 - 1; i >= 0; i--) {
            MAX_HEAPIFY(heap, i, SIZE);
        }
    }
    void BUILD_MIN_HEAP(vector<int>& heap) {
        int SIZE = heap.size();
        for (int i = SIZE / 2 - 1; i >= 0; i--) {
            MIN_HEAPIFY(heap, i, SIZE);
        }
    }

    void insert(int i){
        heap.push_back(i);
        BUILD_MAX_HEAP(heap);
    }
    void HEAPSORT(vector<int>& heap) {
        int SIZE = heap.size();
        BUILD_MAX_HEAP(heap);
        for (int i = SIZE - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            MAX_HEAPIFY(heap, 0, i);
        }
    }
    int size(){
        return heap.size();
    }
    };
class PriorityQueue {
private:
    HEAP heap;

public:
    PriorityQueue() {}


    void push(int priority) {
        heap.insert(priority);
    }


    int pop() {
        return heap.extract_max();
    }


    bool empty() {
        return heap.size() == 0;
    }

    int top() {
        if (heap.size() > 0) {
            return heap.Get_max();
        }

    }
};


        int main() {
            HEAP maxHeap;
            PriorityQueue pq;

            // Testing the HEAP class with different operations
            cout << "Testing HEAP class:\n";

            // Insert elements into the max-heap
            maxHeap.insert(35);
            maxHeap.insert(12);
            maxHeap.insert(48);
            maxHeap.insert(58);
            maxHeap.insert(23);
            maxHeap.insert(5);
            cout << "Heap after inserting elements (should be max-heap): ";
            for (int elem : maxHeap.heap) cout << elem << " ";
            cout << endl;

            // Extract maximum element and print it
            cout << "Extracted max element: " << maxHeap.extract_max() << endl;
            cout << "Heap after extracting max: ";
            for (int elem : maxHeap.heap) cout << elem << " ";
            cout << endl;

            // Insert a few more elements and print the new max
            maxHeap.insert(60);
            maxHeap.insert(1);
            cout << "Heap after more insertions: ";
            for (int elem : maxHeap.heap) cout << elem << " ";
            cout << endl;

            cout << "Current max element: " << maxHeap.Get_max() << endl;

            // Extract minimum element and print it
            cout << "Extracted min element: " << maxHeap.extract_min() << endl;
            cout << "Heap after extracting min: ";
            for (int elem : maxHeap.heap) cout << elem << " ";
            cout << endl;

            // Perform heap sort
            maxHeap.HEAPSORT(maxHeap.heap);
            cout << "Heap after HEAPSORT (sorted in ascending order): ";
            for (int elem : maxHeap.heap) cout << elem << " ";
            cout << endl;

            // Testing the PriorityQueue class with push and pop operations
            cout << "\nTesting PriorityQueue class:\n";

            // Insert elements with different priorities
            pq.push(90);
            pq.push(40);
            pq.push(70);
            pq.push(20);

            // Show the top element
            cout << "Top element in PriorityQueue: " << pq.top() << endl;

            // Pop elements one by one and display
            cout << "Popping elements from PriorityQueue: "<<endl;
            while (!pq.empty()) {
                cout << "remove  : "<<pq.pop() << endl;
            }
            cout << endl;

            // Edge case: attempt to pop from an empty priority queue
            cout << "Trying to pop from an empty PriorityQueue:\n";
            if (pq.empty()) {
                cout << "PriorityQueue is empty.\n";
            } else {
                cout << "Popped from PriorityQueue: " << pq.pop() << endl;
            }



        return 0;
    }

