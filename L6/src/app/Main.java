package app;

import graph.Graph;
import graph.GraphKruskalMST;
import graph.GraphMST;
import structures.HeapElement;
import structures.MinHeap;

import java.io.File;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {

        String inputPath = new File(".").getCanonicalPath() + "\\" + args[0];
        InputParser inputParser = new InputParser(inputPath);
        inputParser.parse();

//        Graph graph = new Graph(8);
//        graph.addEdge(0, 1, 4.0);
//        graph.addEdge(0, 7, 8.0);
//        graph.addEdge(1, 2, 8.0);
//        graph.addEdge(1, 7, 11.0);
//        graph.addEdge(2, 8, 2.0);
//        graph.addEdge(2, 5, 4.0);
//        graph.addEdge(2, 3, 7.0);
//        graph.addEdge(3, 5, 14.0);
//        graph.addEdge(3, 4, 9.0);
//        graph.addEdge(4, 5, 10.0);
//        graph.addEdge(5, 6, 2.0);
//        graph.addEdge(6, 8, 6.0);
//        graph.addEdge(7, 8, 7.0);


//        graph.printGraph();

//        GraphMST graphKuskalMST = new GraphKruskalMST(graph);
//        graphKuskalMST.getMST().printGraph();


//        System.out.println(graph.isCyclic());
//        graph.removeEdge(4, 2);
//        System.out.println(graph.isCyclic());


    }
}
