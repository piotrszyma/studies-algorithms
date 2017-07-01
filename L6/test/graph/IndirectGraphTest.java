package graph;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * @author Piotr Szyma
 * @date 14.06.2017
 */
public class IndirectGraphTest {
    IndirectGraph graph;

    @Before
    public void setUp() throws Exception {
        graph = new IndirectGraph(5);
    }

    @Test
    public void isCyclic() throws Exception {
        graph.addEdge(0, 1, 0.3);
        graph.addEdge(1, 2, 0.3);
        graph.addEdge(2, 3, 0.5);
        graph.addEdge(3, 4, 0.5);
//        graph.addEdge(4, 1, 0.5);
//        graph.removeEdge(4, 1);
        graph.printGraph();
        System.out.println(graph.isCyclic());
        assertTrue(graph.isCyclic());
    }

}