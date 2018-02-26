package app;

import graph.*;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

class InputParser {
    private String filename;
    private FileInputStream fileInputStream;

    InputParser(String filename) {
        this.filename = filename;
    }

    void parseFindMST() {

        try {
            fileInputStream = new FileInputStream(filename);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        Scanner scanner = new Scanner(fileInputStream);

        int numberOfVertexes = scanner.nextInt();
        int numberOfEdges = scanner.nextInt();

        IndirectGraph graph = new IndirectGraph(numberOfVertexes);

        scanner.nextLine();

        parseInputToGraph(scanner, graph, numberOfEdges);


        GraphKruskalMST graphKruskalMST = new GraphKruskalMST(graph);
        IndirectGraph KuskalMST = graphKruskalMST.getMST();

        System.out.println("Finding Minimal Spanning Tree");
        System.out.println("Kuskal's algrithm result:");
        KuskalMST.printGraph();
        System.out.println(KuskalMST.getGraphFullWeight());
        System.out.println();

        GraphPrimMST graphPrimMST = new GraphPrimMST(graph);
        IndirectGraph PrismMST = graphPrimMST.getMST();

        System.out.println("Prim's algorithm result:");
        PrismMST.printGraph();
        System.out.println(PrismMST.getGraphFullWeight());

    }

    private void parseInputToGraph(Scanner scanner, Graph graph, int numberOfEdges) {
        for (int i = 0; i < numberOfEdges; i++) {
            String parameters[] = scanner.nextLine().split("\\s+");
            int firstEdgeVertexID = Integer.parseInt(parameters[0]);
            int secondEdgeVertexID = Integer.parseInt(parameters[1]);
            double edgeWeight = Double.parseDouble(parameters[2]);
            graph.addEdge(firstEdgeVertexID, secondEdgeVertexID, edgeWeight);
        }
    }

    void parseFindSortestPath() {

        try {
            fileInputStream = new FileInputStream(filename);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        Scanner scanner = new Scanner(fileInputStream);

        int numberOfVertexes = scanner.nextInt();
        int numberOfEdges = scanner.nextInt();

        DirectedGraph graph = new DirectedGraph(numberOfVertexes);

        scanner.nextLine();

        parseInputToGraph(scanner, graph, numberOfEdges);

        GraphDijkstraAlgorithm graphDijkstraAlgorithm = new GraphDijkstraAlgorithm(graph);

        System.out.println("Finding shortest path between each vertex");
        System.out.println("Dijkstra's Algorithm");
        graphDijkstraAlgorithm.getShortestPath(0);

    }
}
