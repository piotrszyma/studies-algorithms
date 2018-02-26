package graph;

import java.util.*;


public abstract class Graph {

    int numberOfVertexes;
    Map<String, Double> edgesWeights;
    LinkedList<Integer>[] adjacentVertexes;

    int maxNumberOfVertexes() {
        return numberOfVertexes;
    }

    int numberOfEdges() {
        return edgesWeights.size();
    }

    public abstract void addEdge(int w, int v, double weight);

}
