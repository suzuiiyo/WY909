package collection;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class TestCollection13 {
    public static void main(String[] args) {
        List<Integer> l;
        l = new ArrayList<>();
        modify(l, "ArrayList");

        l = new LinkedList<>();
        modify(l, "LinkedList");
    }

    private static void modify(List<Integer> l, String type) {
        int total = 100 * 1000;
        int index = total / 2;
        final int number = 5;

        for (int i = 0; i < total; i++) {
            l.add(number);
        }
        long start = System.currentTimeMillis();

        for (int i = 0; i < total; i++) {
            int n = l.get(index);
            n++;
            l.set(index, n);
        }
        long end = System.currentTimeMillis();
        System.out.printf("%s total length %d, locate %d data, pick out, increase one, pull back, repeat %d times, totally waste time %d ms %n", type, total, index, total, end - start);
        System.out.println();
    }
}
