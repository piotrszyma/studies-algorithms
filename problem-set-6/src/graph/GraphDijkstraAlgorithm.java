package graph;

import structures.HeapElement;
import structures.MinPriorityQueue;

import java.util.*;

public class GraphDijkstraAlgorithm {

    private DirectedGraph MinimalSpanningTree;
    private DirectedGraph searchedGraph;
    private Integer parent[];
    private List<Integer> shortestPath[];
    private List<Integer> notIncluded;
    private List<Integer> included;
    private int searchedIndex = 0;

    public GraphDijkstraAlgorithm(DirectedGraph searchedGraph) {
        this.searchedGraph = searchedGraph;
    }

    private void findMST() {
        MinimalSpanningTree = new DirectedGraph(searchedGraph.maxNumberOfVertexes());
        parent = new Integer[searchedGraph.maxNumberOfVertexes()];
        notIncluded = new ArrayList<>();
        included = new ArrayList<>();
        MinPriorityQueue minPriorityQueue = new MinPriorityQueue();

        minPriorityQueue.insert(new HeapElement<>(searchedIndex, 0));

        for (int i = 0; i < searchedGraph.maxNumberOfVertexes(); i++) {
            if (i != searchedIndex) {
                minPriorityQueue.insert(new HeapElement<>(i, Double.MAX_VALUE));
            }
        }

        for (int i = 1; i < searchedGraph.maxNumberOfVertexes(); i++) {
            notIncluded.add(i);
        }

        while (notIncluded.size() > 0) {
            HeapElement vertex = minPriorityQueue.extractBest();
            Integer withLowestKeyIndex = (Integer) vertex.getValue();
            double withLowestKeyWeight = vertex.getPriority();

            included.add(withLowestKeyIndex);
            notIncluded.remove(withLowestKeyIndex);
            if (parent[withLowestKeyIndex] != null) {
                MinimalSpanningTree.addEdge(parent[withLowestKeyIndex], withLowestKeyIndex, withLowestKeyWeight);
            } else {
                MinimalSpanningTree.addEdge(0, withLowestKeyIndex, withLowestKeyWeight);

            }

            for (int vertexID : searchedGraph.getAdjacent(withLowestKeyIndex)) {
                if (notIncluded.contains(vertexID)) {
                    double vertexWeight = searchedGraph.getEdgeWeight(withLowestKeyIndex, vertexID);
                    if (minPriorityQueue.modifyKey(minPriorityQueue.getIndex(vertexID), vertexWeight + withLowestKeyWeight)) {
                        parent[vertexID] = withLowestKeyIndex;
                    }
                }
            }
        }


    }

    @SuppressWarnings("unchecked") //for new LinkedList[numberOfVertexes]
    public List<Integer>[] getShortestPath(int searchedIndex) {
        double sumOfAll = 0.0;
        this.searchedIndex = searchedIndex;
        findMST();
        shortestPath = new ArrayList[parent.length];
        for (int i = 0; i < parent.length; i++) {
            shortestPath[i] = new ArrayList<>();
        }
        Integer previousVertex;
        Integer currentVertex;
        for (int i = 0; i < parent.length; i++) {

            currentVertex = i;
            while (currentVertex != null) {
                previousVertex = currentVertex;
                currentVertex = parent[currentVertex];
                shortestPath[i].add(previousVertex);
            }
            Collections.reverse(shortestPath[i]);
        }

        for (int i = 0; i < parent.length; i++) {

            ListIterator<Integer> it = shortestPath[i].listIterator(1);
            Integer previous = null;
            Integer current;
            Double sumOfWeights = 0.0;

            if (it.hasNext()) {
                previous = it.next();
                sumOfWeights += searchedGraph.getEdgeWeight(searchedIndex, previous);

            }
            while (it.hasNext()) {
                current = it.next();
                sumOfWeights += searchedGraph.getEdgeWeight(previous, current);
                previous = current;
            }

            String sumOfWeightsString = String.format(Locale.ENGLISH, "%.2f", sumOfWeights);
            System.out.printf("%d to %d (%s) ", searchedIndex, i, sumOfWeightsString);
            it = shortestPath[i].listIterator(1);

            if (it.hasNext()) {
                previous = it.next();
                System.out.print(searchedIndex + "->" + previous + "  " + searchedGraph.getEdgeWeight(searchedIndex, previous) + "  ");

            }
            while (it.hasNext()) {
                current = it.next();
                System.out.print(previous + "->" + current + "  " + searchedGraph.getEdgeWeight(previous, current) + "  ");
                previous = current;
            }

            sumOfAll += sumOfWeights;

            System.out.println();

        }

        System.out.println(sumOfAll);
        return shortestPath;
    }
}
