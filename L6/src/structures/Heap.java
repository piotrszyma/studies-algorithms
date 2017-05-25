package structures;

import java.util.List;

public abstract class Heap {

    List<HeapElement> array;

    abstract void heapify(int index);

    public abstract void build(HeapElement[] array);

    int getParent(int i) {
        if(i < 2) return 0;
        return (int) Math.ceil(i / 2) - 1;
    }

    int getLeft(int i) {
        return (2 * i) + 1;
    }

    int getRight(int i) {
        return (2 * i) + 2;
    }

}
