package structures;

import java.util.List;

public abstract class Heap {

    List<HeapElement> array;

    abstract void heapify(int index);

    public abstract void build(HeapElement[] array);

    int getParent(int i) {
        if(i == 0) return 0;
        int parentIndex = (i + 1) / 2;
        return parentIndex - 1;
    }

    int getLeft(int i) {
        return (2 * i) + 1;
    }

    int getRight(int i) {
        return (2 * i) + 2;
    }

}
