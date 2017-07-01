package structures;

import org.junit.Before;
import org.junit.Test;

import java.util.Random;

import static org.junit.Assert.*;

/**
 * Created by Piotr Szyma on 24.05.2017.
 */
public class MinHeapTest {

    private MinHeap minHeap;
    private HeapElement[] dataArray;
    private Random randomGenerator;

    private final int testingArraySize = 50;
    private final int numberOfRandomTests = 10;

    @Before
    public void setUp() throws Exception {
        randomGenerator = new Random();
        minHeap = new MinHeap();
        dataArray = new HeapElement[testingArraySize];
        for (int i = 0; i < testingArraySize; i++) {
            dataArray[i] = new HeapElement<>(i * 10, i);
        }

    }

    @Test
    public void checkIfBuildFunctionWorks() throws Exception {
        minHeap.build(dataArray);
        assertTrue(minHeap.array.get(0).getPriority() == 0.0);
    }

    @Test
    public void checkIfHeapifyWorks() throws Exception {
        for(int k = numberOfRandomTests; k > 0; k--) {
            HeapElement[] randomElements = new HeapElement[testingArraySize];
            MinHeap randomMinHeap = new MinHeap();
            for (int i = 0; i < testingArraySize; i++) {
                randomElements[i] = new HeapElement<>(i, (double) randomGenerator.nextInt(100));
            }

            randomMinHeap.build(randomElements);

            for (int i = 1; i < minHeap.array.size(); i++) {
                assertTrue(minHeap.array.get(minHeap.getParent(i)).getPriority() <= minHeap.array.get(i).getPriority());
            }
        }

    }

    @Test
    public void checkParentsLeftRightFunc() {
        assertTrue(minHeap.getParent(0) == 0);
        assertTrue(minHeap.getParent(1) == 0);
        assertTrue(minHeap.getParent(2) == 0);
        assertTrue(minHeap.getParent(3) == 1);
        assertTrue(minHeap.getParent(4) == 1);
        assertTrue(minHeap.getLeft(0) == 1);
        assertTrue(minHeap.getLeft(1) == 3);
        assertTrue(minHeap.getLeft(2) == 5);
        assertTrue(minHeap.getLeft(3) == 7);
        assertTrue(minHeap.getLeft(4) == 9);
        assertTrue(minHeap.getRight(0) == 2);
        assertTrue(minHeap.getRight(1) == 4);
        assertTrue(minHeap.getRight(2) == 6);
        assertTrue(minHeap.getRight(3) == 8);
        assertTrue(minHeap.getRight(4) == 10);
    }

    @Test
    public void petersTest() {
        HeapElement[] elements = new HeapElement[11];
        elements[0] = new HeapElement<>(1,1);
        elements[1] = new HeapElement<>(3,3);
        elements[2] = new HeapElement<>(2,2);
        elements[3] = new HeapElement<>(16,16);
        elements[4] = new HeapElement<>(9,9);
        elements[5] = new HeapElement<>(7,7);
        elements[6] = new HeapElement<>(80,80);
        elements[7] = new HeapElement<>(2,2);
        elements[8] = new HeapElement<>(4,4);
        elements[9] = new HeapElement<>(6,6);
        elements[10] = new HeapElement<>(7,7);

        Heap aMinHeap = new MinHeap();
        aMinHeap.build(elements);
        for(HeapElement element: aMinHeap.array) {
            System.out.print(element.getPriority() + " ");
        }
        System.out.println();
   }

}