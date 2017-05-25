package structures;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class MinHeap extends Heap {

    public MinHeap() {
        this.array = new ArrayList<>();
    }

    @Override
    void heapify(int thisIndex) {

        int leftIndex = getLeft(thisIndex);
        int rightIndex = getRight(thisIndex);
        int minimumIndex;

        if (leftIndex < array.size()) {
            if (array.get(thisIndex).getPriority() > array.get(leftIndex).getPriority()) {
                minimumIndex = leftIndex;
            } else minimumIndex = thisIndex;
        } else minimumIndex = thisIndex;

        if (rightIndex < array.size()) {
            if (array.get(rightIndex).getPriority() < array.get(minimumIndex).getPriority()) {
                minimumIndex = rightIndex;
            }
        }

        if (minimumIndex != thisIndex) {
            Collections.swap(array, minimumIndex, thisIndex);
            heapify(minimumIndex);
        }
    }

    @Override
    public void build(HeapElement[] array) {
        this.array = Arrays.asList(array);
        for (int i = this.array.size() / 2 + 1; i >= 0; i--) {
            heapify(i);
        }
    }
}
