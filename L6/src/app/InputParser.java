package app;

import graph.Graph;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

class InputParser {
    private String filename;
    private FileInputStream fileInputStream;

    InputParser(String filename) {
        this.filename = filename;
    }

    void parse() {

        try {
            fileInputStream = new FileInputStream(filename);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        Scanner scanner = new Scanner(fileInputStream);

        int numberOfVertexes = scanner.nextInt();
        int numberOfEdges = scanner.nextInt();

        Graph graph = new Graph(numberOfVertexes);

        scanner.nextLine();

        for (int i = 0; i < numberOfEdges; i++) {
            String parameters[] = scanner.nextLine().split("\\s+");
            int firstEdgeVertexID = Integer.parseInt(parameters[0]);
            int secondEdgeVertexID = Integer.parseInt(parameters[1]);
            double edgeWeight = Double.parseDouble(parameters[2]);
            graph.addEdge(firstEdgeVertexID - 1, secondEdgeVertexID - 1, edgeWeight);
        }


        graph.printGraph();
    }
}
