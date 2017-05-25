package structures;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class MinPriorityQueueTest {

    MinPriorityQueue minPriorityQueue;

    @Before
    public void setUp() throws Exception {
        minPriorityQueue = new MinPriorityQueue();
    }

    @Test
    public void checkIfExtractMethodWorks() throws Exception {
        minPriorityQueue.insert(new HeapElement<>("node1", 3.2));
        HeapElement element = minPriorityQueue.extractBest();
        assertTrue(minPriorityQueue.array.size() == 0);
    }

    @Test
    public void checkIfInsertMethodWorks() throws Exception {
        minPriorityQueue.insert(new HeapElement<>("node1", 1.3));
        assertTrue(minPriorityQueue.array.get(0).getPriority() == 1.3);
        assertTrue(minPriorityQueue.array.get(0).getValue() == "node1");
    }


    @Test
    public void checkIfMultipleInsertionsWorks() throws Exception {
        minPriorityQueue.insert(new HeapElement<>("node1", 1.3));
        minPriorityQueue.insert(new HeapElement<>("node2", 0.3));
        assertTrue(minPriorityQueue.getBest().getValue() == "node2");
    }

    @Test
    public void checkIfGetBestMethodWorks() throws Exception {
        minPriorityQueue.insert(new HeapElement<>("node1", 1.3));
        minPriorityQueue.insert(new HeapElement<>("node2", 2.3));
        minPriorityQueue.insert(new HeapElement<>("node3", 3.3));
        minPriorityQueue.insert(new HeapElement<>("node4", 4.11));
        minPriorityQueue.insert(new HeapElement<>("node5", 0.7));
        assertTrue(minPriorityQueue.getBest().getValue() == "node5");
    }

    @Test
    public void checkIfMultipleInsertionAfterEachInsertionWorks() throws Exception {
        minPriorityQueue.insert(new HeapElement<>("node1", 1.3));
        assertTrue(minPriorityQueue.getBest().getValue() == "node1");
        minPriorityQueue.insert(new HeapElement<>("node2", 1.2));
        assertTrue(minPriorityQueue.getBest().getValue() == "node2");
        minPriorityQueue.insert(new HeapElement<>("node3", 1.4));
        assertTrue(minPriorityQueue.getBest().getValue() == "node2");
        minPriorityQueue.insert(new HeapElement<>("node4", 1.0));
        assertTrue(minPriorityQueue.getBest().getValue() == "node4");
        minPriorityQueue.insert(new HeapElement<>("node5", 0.9));
        assertTrue(minPriorityQueue.getBest().getValue() == "node5");
    }

    @Test
    public void checkIfModifyKeyWorks() throws Exception {
        minPriorityQueue.insert(new HeapElement<>("node1", 1.3));
        minPriorityQueue.insert(new HeapElement<>("node2", 1.2));
        minPriorityQueue.insert(new HeapElement<>("node3", 1.4));
        minPriorityQueue.insert(new HeapElement<>("node4", 1.0));
        minPriorityQueue.insert(new HeapElement<>("node5", 0.9));
        //[0.9, 1.0, 1.2, 1.3, 1.4]
        minPriorityQueue.modifyKey(4, 0.3);
        assertTrue(minPriorityQueue.getBest().getValue() == "node1");
    }

    @Test(expected = IndexOutOfBoundsException.class)
    public void checkIfExtractingBestFromEmptyQueueThrowsException() throws Exception {
        minPriorityQueue.extractBest();
    }
    @Test(expected = IndexOutOfBoundsException.class)
    public void checkIfAccessingBestFromEmptyQueueThrowsException() throws Exception {
        minPriorityQueue.getBest();
    }

    @Test(expected = IllegalArgumentException.class)
    public void checkIfTryingToIncreasePriorityFails() {
        minPriorityQueue.insert(new HeapElement<>("node1", 1.3));
        minPriorityQueue.modifyKey(0, 20.0);
    }
}