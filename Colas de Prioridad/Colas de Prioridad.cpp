#include <iostream>
#include <stdexcept>
#include <string>

#include "HeapPriorityQueue.h"
#include "LinkedPriorityQueue.h"
#include "PriorityQueue.h"

void testPriorityQueue(PriorityQueue<std::string>& queue) {
	if (!queue.isEmpty() || queue.getSize() != 0)
		throw std::runtime_error("New queue should be empty.");

	queue.insert("routine", 2);
	queue.insert("emergency", 0);
	queue.insert("follow-up", 1);
	if (queue.getSize() != 3 || queue.min() != "emergency")
		throw std::runtime_error("Queue did not return the highest-priority item.");

	if (queue.removeMin() != "emergency" || queue.removeMin() != "follow-up" ||
		queue.removeMin() != "routine" || !queue.isEmpty())
		throw std::runtime_error("Queue removal order is incorrect.");

	queue.insert("temporary", 1);
	queue.clear();
	if (!queue.isEmpty() || queue.getSize() != 0)
		throw std::runtime_error("clear() did not empty the queue.");
}

int main() {
	HeapPriorityQueue<std::string> heapQueue;
	LinkedPriorityQueue<std::string> linkedQueue(3);

	testPriorityQueue(heapQueue);
	testPriorityQueue(linkedQueue);

	std::cout << "HeapPriorityQueue and LinkedPriorityQueue tests passed.\n";
	return 0;
}
