package structures;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class HeapElementTest {

    HeapElement<String> heapElement;

    @Before
    public void setUp() throws Exception {
        heapElement = new HeapElement<>("node", 2.0);
    }

    @Test
    public void setValue() throws Exception {
        heapElement.setValue("node2");
        assertTrue(heapElement.getValue().equals("node2"));
    }


}