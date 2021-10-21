

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class Main {

    static int ARRAY_LEN = 20 ;//(int) Math.pow(2,27);
    static  String FILE_PATH = "data.txt";

    /*
        Reads the input file. Streams used instead of Scanner or BufferedReader because of memory errors.
        Stream reads file char by char and returns ASCII code. So function saves codes unless it is 32 (Space character)
        and then saves that integer to array than saves again until the other space
     */
    public static int[] readFile() {
        int[] data = new int[ARRAY_LEN];
        try {
            InputStream inputStream = new FileInputStream(new File(FILE_PATH));
            BufferedInputStream bufferedInputStream = new BufferedInputStream(inputStream);
            Reader reader = new InputStreamReader(bufferedInputStream, StandardCharsets.UTF_8);
            int c;
            int index = 0;
            String current = "";
            while ((c = reader.read()) >= 0 ) {
                if (c == 32) {
                    data[index] = Integer.parseInt(current);
                    index += 1;
                    current = "";
                } else {
                    current += Character.toString((char)c);
                }
            }
            return data;
        } catch (FileNotFoundException error) {
            System.out.println("File not found");
            return data;
        } catch (IOException e) {
            e.printStackTrace();
            return data;
        }
    }

    public static void main(String[] args) {
        System.out.println("Reading file");
        int[] data = readFile();
        System.out.println("File read");

        PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(ARRAY_LEN, Collections.reverseOrder());
        long start = System.currentTimeMillis();

        Collections.addAll(priorityQueue,Arrays.stream(data).boxed().toArray(Integer[]::new));

        long end = System.currentTimeMillis();

        float executionTime = (end-start) / 1000F;

        System.out.println("Execution took " + executionTime + " seconds" );

    }
}
