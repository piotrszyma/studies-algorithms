package graph;

import structures.HeapElement;
import structures.MinPriorityQueue;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Piotr Szyma on 31.05.2017.
 */
public class GraphPrimMST implements GraphMST {

    private IndirectGraph MinimalSpanningTree;
    private IndirectGraph searchedGraph;

    public GraphPrimMST(IndirectGraph searchedGraph) {
        this.searchedGraph = searchedGraph;
    }

    private void findMST() {
        MinimalSpanningTree = new IndirectGraph(searchedGraph.maxNumberOfVertexes());

        Integer[] parent = new Integer[searchedGraph.maxNumberOfVertexes()];
        List<Integer> notIncluded = new ArrayList<>();
        MinPriorityQueue minPriorityQueue = new MinPriorityQueue();

        minPriorityQueue.insert(new HeapElement<>(0, 0));

        for (int i = 1; i < searchedGraph.maxNumberOfVertexes(); i++) {
            minPriorityQueue.insert(new HeapElement<>(i, Double.MAX_VALUE));
        }

        for (int i = 1; i < searchedGraph.maxNumberOfVertexes(); i++) {
            notIncluded.add(i);
        }

        while (notIncluded.size() > 0) {
            HeapElement vertex = minPriorityQueue.extractBest();
            Integer withLowestKeyIndex = (Integer) vertex.getValue();
            double withLowestKeyWeight = vertex.getPriority();

            notIncluded.remove(withLowestKeyIndex);

            if (parent[withLowestKeyIndex] != null) {
                MinimalSpanningTree.addEdge(withLowestKeyIndex, parent[withLowestKeyIndex], withLowestKeyWeight);
            }

            for (int vertexID : searchedGraph.getAdjacent(withLowestKeyIndex)) {
                if (notIncluded.contains(vertexID)) {
                    double vertexWeight = searchedGraph.getEdgeWeight(vertexID, withLowestKeyIndex);
                    if (minPriorityQueue.modifyKey(minPriorityQueue.getIndex(vertexID), vertexWeight)) {
                        parent[vertexID] = withLowestKeyIndex;
                    }
                }
            }
        }


    }

    @Override
    public IndirectGraph getMST() {
        findMST();
        return MinimalSpanningTree;
    }
}
