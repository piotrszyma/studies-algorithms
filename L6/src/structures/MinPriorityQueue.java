package structures;

import java.util.Collections;

public class MinPriorityQueue extends MinHeap implements PriorityQueue {


    @Override
    public void insert(HeapElement element) {
        double elementPriority = element.getPriority();
        element.setPriority(Double.MAX_VALUE);
        array.add(element);
        modifyKey(array.size() - 1, elementPriority);
    }

    @Override
    public HeapElement getBest() {
        if (array.size() < 1) {
            throw new IndexOutOfBoundsException("Heap underflow");
        }
        return array.get(0);
    }

    @Override
    public HeapElement extractBest() {

        if (array.size() < 1) {
            throw new IndexOutOfBoundsException("Heap underflow");
        }

        HeapElement maxElement = array.get(0);
        array.set(0, array.get(array.size() - 1));
        array.remove(array.size() - 1);
        this.heapify(0);
        return maxElement;
    }

    @Override
    public void modifyKey(int index, double newPriority) {
        if (array.get(index).getPriority() < newPriority) {
            throw new IllegalArgumentException("New priority is higher than old priority!");
        }
        array.get(index).setPriority(newPriority);
        while (index > 0 && array.get(getParent(index)).getPriority() > array.get(index).getPriority()) {
            Collections.swap(array, index, getParent(index));
            index = getParent(index);
        }
    }
}
