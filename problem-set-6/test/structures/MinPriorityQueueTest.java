package structures;

import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import static org.junit.Assert.*;

public class MinPriorityQueueTest {

    MinPriorityQueue minPriorityQueue;
    int numberOfRandomTests = 10;
    int testingArraySize = 10;
    private Random randomGenerator;
    private HeapElement[] dataArray;


    @Before
    public void setUp() throws Exception {
        minPriorityQueue = new MinPriorityQueue();
        randomGenerator = new Random();
        dataArray = new HeapElement[testingArraySize];
        for (int i = 0; i < testingArraySize; i++) {
            dataArray[i] = new HeapElement<>(i * 10, i);
        }

    }

    @Test
    public void checkIfExtractMethodWorks() throws Exception {
        minPriorityQueue.insert(new HeapElement<>("node1", 3.2));
        minPriorityQueue.extractBest();
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


    @Test
    public void checkIfHeapPropertyWorks() {
        for (int k = numberOfRandomTests; k > 0; k--) {
            HeapElement[] randomElements = new HeapElement[testingArraySize];


            for (int i = 0; i < testingArraySize; i++) {
                String randomDouble = String.format("%.2f", randomGenerator.nextDouble());
                String formattedRandomDouble = randomDouble.replace(",", ".");
                randomElements[i] = new HeapElement<>(i, Double.parseDouble(formattedRandomDouble));
                minPriorityQueue.insert(randomElements[i]);
            }

            for (int i = 0; i < testingArraySize; i++) {
                randomElements[i] = minPriorityQueue.extractBest();
            }

            for (int i = 0; i < testingArraySize - 1; i++) {
                assertTrue(randomElements[i].getPriority() <= randomElements[i + 1].getPriority());
            }


        }
    }

    @Test
    public void testData() {
        minPriorityQueue.insert(new HeapElement<>("x", 0.35));
        minPriorityQueue.insert(new HeapElement<>("x", 0.37));
        minPriorityQueue.insert(new HeapElement<>("x", 0.28));
        minPriorityQueue.insert(new HeapElement<>("x", 0.16));
        minPriorityQueue.insert(new HeapElement<>("x", 0.32));
        minPriorityQueue.insert(new HeapElement<>("x", 0.38));
        minPriorityQueue.insert(new HeapElement<>("x", 0.17));
        minPriorityQueue.insert(new HeapElement<>("x", 0.19));
        minPriorityQueue.insert(new HeapElement<>("x", 0.26));
        minPriorityQueue.insert(new HeapElement<>("x", 0.36));
        minPriorityQueue.insert(new HeapElement<>("x", 0.29));
        minPriorityQueue.insert(new HeapElement<>("x", 0.34));
        minPriorityQueue.insert(new HeapElement<>("x", 0.40));
        minPriorityQueue.insert(new HeapElement<>("x", 0.52));
        minPriorityQueue.insert(new HeapElement<>("x", 0.58));
        minPriorityQueue.insert(new HeapElement<>("x", 0.93));

        double listOfResults[] = new double[16];
        for (int i = 0; i < 16; i++) {
            listOfResults[i] = minPriorityQueue.extractBest().getPriority();
        }

        for (int i = 0; i < 15; i++) {
            assertTrue(listOfResults[i] < listOfResults[i + 1]);
        }
    }
}