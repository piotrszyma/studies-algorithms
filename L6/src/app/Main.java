package app;

import graph.IndirectGraph;

import java.io.File;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {


//        IndirectGraph graph = new IndirectGraph()
        if (args[0].isEmpty()) {
            System.out.println("Add parameter");
            return;
        }

        String inputPath = new File(".").getCanonicalPath() + "\\" + args[0];
        InputParser inputParser = new InputParser(inputPath);

        if (args[1].equals("d")) {
            inputParser.parseFindSortestPath();
        } else {
            inputParser.parseFindMST();
        }
    }
}
