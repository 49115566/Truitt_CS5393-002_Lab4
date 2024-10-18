#include <iostream>
#include <vector>
#include <stdexcept>  // for error handling
#include <cmath>

/*
Task                                        	Time Complexity
Insert element                       	        O(log n)
Display the size of the PriorityQ	            O(1)
Display all contents                           	O(n log n)
Print whether PriorityQ is Empty                O(1)

Space Complexity: O(n)
*/

class PriorityQ {
private:
    std::vector<int> heap;

    // Helper function to get the parent index
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Helper function to get the left child index
    int leftChild(int i) {
        return (2 * i + 1);
    }

    // Helper function to get the right child index
    int rightChild(int i) {
        return (2 * i + 2);
    }

    // Maintain heap property while pushing an element upwards
    void heapifyUp(int i) {
        if (i && heap[parent(i)] < heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            heapifyUp(parent(i));
        }
    }

    // Maintain heap property while popping an element
    void heapifyDown(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int largest = i;

        if (left < size() && heap[left] > heap[largest])
            largest = left;

        if (right < size() && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Check if the heap is empty
    bool empty() const {
        return heap.size() == 0;
    }

    // Get the size of the heap
    int size() const {
        return heap.size();
    }

    // Get the top (maximum) element from the priority queue
    int top() {
        try {
            if (empty())
                throw std::underflow_error("Error: Priority Queue is empty.");
            return heap[0];
        }
        catch (const std::underflow_error& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }

    // Push a new element into the priority queue
    void push(int value) {
        try {
            heap.push_back(value);
            heapifyUp(size() - 1);
            std::cout << "Success: " << value << " has been added to the Priority Queue." << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: Failed to push value into Priority Queue." << std::endl;
        }
    }

    // Pop the top (maximum) element from the priority queue
    void pop() {
        try {
            if (empty())
                throw std::underflow_error("Error: Cannot pop from an empty Priority Queue.");

            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);

            std::cout << "Success: Top element has been popped from the Priority Queue." << std::endl;
        }
        catch (const std::underflow_error& e) {
            std::cerr << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: Failed to pop element from Priority Queue." << std::endl;
        }
    }

    // Print all elements of the Priority Queue in descending order
    void print() {
        if (empty()) {
            std::cout << "Priority Queue is empty." << std::endl;
        } else {
            std::cout << "Priority Queue elements in descending order: ";

            // Create a copy of the heap to avoid modifying the original heap
            std::vector<int> heapCopy = heap;
            int heapSize = heapCopy.size();

            // Keep popping the top element (maximum) from the copy until empty
            while (!heapCopy.empty()) {
                // Print the top element (the maximum in the max-heap)
                std::cout << heapCopy[0] << " ";
                
                // Replace the root with the last element and reduce heap size
                heapCopy[0] = heapCopy.back();
                heapCopy.pop_back();
                heapSize--;

                // Heapify down to maintain heap property in the copy
                int i = 0;
                while (true) {
                    int left = 2 * i + 1;
                    int right = 2 * i + 2;
                    int largest = i;

                    if (left < heapSize && heapCopy[left] > heapCopy[largest])
                        largest = left;
                    if (right < heapSize && heapCopy[right] > heapCopy[largest])
                        largest = right;

                    if (largest == i)
                        break;

                    std::swap(heapCopy[i], heapCopy[largest]);
                    i = largest;
                }
            }

            std::cout << std::endl;
        }
    }
};

//Must be changed.
int main() {
    PriorityQ pq;

    int vals[] = {50, 30, 10, 40, 20, 100, 70, 90, 60, 80};

    for(int i = 0; i < 10; i++){
        std::cout << vals[i] << ' ';
        pq.push(vals[i]);
        pq.print();
    }
    std::cout << std::endl;

    std::cout << pq.size() << " elements in priority Q" << std::endl;

    while(!pq.empty()){
        std::cout << "Priority Q not empty." << std::endl;
        pq.print();
        std::cout << "Top element: " << pq.top() << std::endl;
        std::cout << "Popping" << std::endl;
        pq.pop();
    }

    std::cout << "Priority Q empty." << std::endl;
    std::cout << "Top element anyway: " << pq.top() << std::endl;
    
    return 0;
}
