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

    private final int testingArraySize = 5;
    private final int numberOfRandomTests = 100;

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
}