package collection;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class compareLinkedListArrayList {
    public static void main(String[] args) {
        List<Integer> l;
        l = new ArrayList<>();
        insertFirst(l, "ArrayList");

        l = new LinkedList<>();
        insertFirst(l, "linkedList");
    }

    private static void insertFirst(List<Integer> l, String type){
        int total = 1000 * 100;
        final int number = 5;
        long start = System.currentTimeMillis();
        for(int i =0; i<total; i++){
            l.add(0, number);
        }
        long end = System.currentTimeMillis();
        System.out.printf("insert %d data before %s, waste time %d ms:",total, type, end-start);
    }
}
