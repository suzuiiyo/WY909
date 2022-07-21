package collection;

import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.TreeSet;

public class TestCollection17 {
    public static void main(String[] args) {
        HashSet<Integer> numberSet1 = new HashSet<Integer>();
        numberSet1.add(88);
        numberSet1.add(8);
        numberSet1.add(888);

        System.out.println(numberSet1.toString());

        LinkedHashSet<Integer> numberSet2 = new LinkedHashSet<Integer>();
        numberSet2.add(88);
        numberSet2.add(8);
        numberSet2.add(888);

        System.out.println(numberSet2.toString());

        TreeSet<Integer> numberSet3 = new TreeSet<Integer>();
        numberSet3.add(88);
        numberSet3.add(8);
        numberSet3.add(888);

        System.out.println(numberSet3.toString());
    }
}
