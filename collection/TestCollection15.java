package collection;

import java.util.ArrayList;
import java.util.HashSet;

public class TestCollection15 {
    public static void main(String[] args) {
        ArrayList<Integer> numberList = new ArrayList<Integer>();
        System.out.println("-----------------List--------------");
        System.out.println("insert 9 5 1 to the List");
        numberList.add(9);
        numberList.add(5);
        numberList.add(1);
        System.out.println("List save data as insert sequence");
        System.out.println(numberList);
        System.out.println("----------------Set----------------");
        HashSet<Integer> numberSet = new HashSet<Integer>();
        System.out.println("inset 9  5 1 into the HashSet");
        //
        numberSet.add(9);
        numberSet.add(5);
        numberSet.add(1);
        System.out.println("Set save data doesn't as insert sequence");
        System.out.println(numberSet);
    }
}
