package graph;

import structures.HeapElement;
import structures.MinPriorityQueue;

import java.util.Map;

public class GraphKruskalMST implements GraphMST {

    private IndirectGraph MinimalSpanningTree;
    private IndirectGraph searchedGraph;

    public GraphKruskalMST(IndirectGraph searchedGraph) {
        this.searchedGraph = searchedGraph;
        MinimalSpanningTree = new IndirectGraph(searchedGraph.numberOfVertexes());
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
    public IndirectGraph getMST() {
        try {
            findMST();
        } catch (IndexOutOfBoundsException e) {
            throw new IllegalStateException("This graph is not connected");
        }
        return MinimalSpanningTree;
    }
}
