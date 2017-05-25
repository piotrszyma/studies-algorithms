package graph;

import structures.HeapElement;
import structures.MinPriorityQueue;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by Piotr Szyma on 25.05.2017.
 */
public class GraphKruskalMST implements GraphMST {

    private Graph MinimalSpanningTree;
    private Graph searchedGraph;

    public GraphKruskalMST(Graph searchedGraph) {
        this.searchedGraph = searchedGraph;
        MinimalSpanningTree = new Graph(searchedGraph.numberOfVertexes());
    }

    private void findMST() {
        Map<String, Double> searchedGraphGraphsEdgesWithWeights = searchedGraph.getGraphsEdgesWithWeights();
        MinPriorityQueue minPriorityQueue = new MinPriorityQueue();

        for (Map.Entry<String, Double> entry : searchedGraphGraphsEdgesWithWeights.entrySet()) {
            String vertex = entry.getKey();
            Double priority = entry.getValue();
            minPriorityQueue.insert(new HeapElement<>(vertex, priority));
        }

        while (MinimalSpanningTree.numberOfEdges() != searchedGraph.numberOfVertexes() - 1) {

            HeapElement edgeWithMinimalWeight = minPriorityQueue.extractBest();
            String[] vertexIDs = ((String) edgeWithMinimalWeight.getValue()).split("#");
            int edgeFirstVertexID = Integer.parseInt(vertexIDs[0]);
            int edgeSecondVertexID = Integer.parseInt(vertexIDs[1]);
            double edgeWeight = edgeWithMinimalWeight.getPriority();

            MinimalSpanningTree.addEdge(edgeFirstVertexID, edgeSecondVertexID, edgeWeight);

            if (MinimalSpanningTree.isCyclic()) {
                MinimalSpanningTree.removeEdge(edgeFirstVertexID, edgeSecondVertexID);
            }

        }
    }

    @Override
    public Graph getMST() {
        try {
            findMST();
        } catch (IndexOutOfBoundsException e) {
            throw new IllegalStateException("This graph is not connected");
        }
        return MinimalSpanningTree;
    }
}
