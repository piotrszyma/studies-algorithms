package graph;

import java.util.*;


public class Graph {
    private int numberOfVertexes;
    private LinkedList<Integer>[] adjacentVertexes;
    private Map<String, Double> edgesWeights;

    @SuppressWarnings("unchecked") //for new LinkedList[numberOfVertexes]
    public Graph(int numberOfVertexes) {
        this.numberOfVertexes = numberOfVertexes;
        this.edgesWeights = new HashMap<>();
        this.adjacentVertexes = new LinkedList[numberOfVertexes];

        for (int i = 0; i < numberOfVertexes; i++) {
            adjacentVertexes[i] = new LinkedList<>();
        }
    }

    public void addEdge(int w, int v, double weight) {
        if (w > v) {
            int tmp = w;
            w = v;
            v = tmp;
        }

        boolean firstFound = false;
        for (int adjacentVertex : adjacentVertexes[w]) {
            if (adjacentVertex == v) {
                firstFound = true;
                break;
            }
        }

        for (int adjacentVertex : adjacentVertexes[v]) {
            if (adjacentVertex == w && firstFound) {
                throw new IllegalArgumentException("Edge already in graph");
            }
        }

        adjacentVertexes[w].add(v);
        adjacentVertexes[v].add(w);
        addEdgeWeight(w, v, weight);
    }

    private void addEdgeWeight(int w, int v, double weight) {
        if (w > v) {
            int tmp = w;
            w = v;
            v = tmp;
        }
        edgesWeights.put(w + "#" + v, weight);
    }

    private double getEdgeWeight(int w, int v) {
        if (w > v) {
            int tmp = w;
            w = v;
            v = tmp;
        }
        return edgesWeights.get(w + "#" + v);
    }

    public void removeEdge(int w, int v) {

        //w always smaller than v
        if (w > v) {
            int tmp = w;
            w = v;
            v = tmp;
        }

        int vertexId = 0;
        for (int adjacentVertex : adjacentVertexes[w]) {
            if (adjacentVertex == v) {
                adjacentVertexes[w].remove(vertexId);
                break;
            }
            vertexId++;
        }
        vertexId = 0;

        for (int adjacentVertex : adjacentVertexes[v]) {
            if (adjacentVertex == w) {
                adjacentVertexes[v].remove(vertexId);
                break;
            }
            vertexId++;
        }

        edgesWeights.remove(w + "#" + v);
    }

    public Boolean isCyclic() {
        Boolean visited[] = new Boolean[numberOfVertexes];
        Arrays.fill(visited, false);
        for (int checkedVertex = 0; checkedVertex < numberOfVertexes; checkedVertex++) {

            if (!visited[checkedVertex]) {
                if (isCyclicRecursion(checkedVertex, visited, -1)) {
                    return true;
                }
            }

        }

        return false;
    }

    private Boolean isCyclicRecursion(int checkedVertex, Boolean[] visited, int checkedVertexParent) {
        visited[checkedVertex] = true;
        for (int checkedVertexChild : adjacentVertexes[checkedVertex]) {
            if (!visited[checkedVertexChild]) {
                if (isCyclicRecursion(checkedVertexChild, visited, checkedVertex)) {
                    return true;
                }
            } else if (checkedVertexChild != checkedVertexParent) {
                return true;
            }
        }

        return false;
    }

    public Map<String, Double> getGraphsEdgesWithWeights() {
        return this.edgesWeights;
    }

    public int numberOfVertexes() {
        int size = numberOfVertexes;
        for (LinkedList<Integer> vertexFriends : adjacentVertexes) {
            if (vertexFriends.size() == 0) size--;
        }
        return size;
    }

    public int maxNumberOfVertexes() {
        return numberOfVertexes;
    }

    public int numberOfEdges() {
        return edgesWeights.size();
    }

    public void printGraph() {
        int vertexID = 0;
        for (LinkedList<Integer> listOfAdjacentVertexes : adjacentVertexes) {
            for (int secondVertexID : listOfAdjacentVertexes) {
                if (vertexID <= secondVertexID) {
                    System.out.println("" + vertexID + " " + secondVertexID + " w: " + getEdgeWeight(vertexID, secondVertexID));
                }
            }
            vertexID++;
        }
    }
}
