package graph;

import java.util.*;

public class DirectedGraph extends Graph {

    @SuppressWarnings("unchecked") //for new LinkedList[numberOfVertexes]
    public DirectedGraph(int numberOfVertexes) {
        this.numberOfVertexes = numberOfVertexes;
        this.edgesWeights = new HashMap<>();
        this.adjacentVertexes = new LinkedList[numberOfVertexes];

        for (int i = 0; i < numberOfVertexes; i++) {
            adjacentVertexes[i] = new LinkedList<>();
        }
    }

    @Override
    public void addEdge(int w, int v, double weight) {
        if (adjacentVertexes[w].contains(v)) {
            throw new IllegalArgumentException("Edge already in graph");
        }
        adjacentVertexes[w].add(v);
        addEdgeWeight(w, v, weight);
    }

    private void addEdgeWeight(int w, int v, double weight) {
        edgesWeights.put(w + "#" + v, weight);
    }

    double getEdgeWeight(int w, int v) {
        return edgesWeights.get(w + "#" + v);
    }

    List<Integer> getAdjacent(int vertexID) {
        return adjacentVertexes[vertexID];
    }

}
