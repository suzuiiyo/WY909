package collection;

import java.util.ArrayList;
import java.util.HashSet;

public class testCollection16 {
    public static void main(String[] args) {
        ArrayList<Integer> numberList = new ArrayList<>();
        System.out.println("--------------List----------");
        System.out.println("insert 9 9 to List");
        numberList.add(9);
        numberList.add(9);

        System.out.println("two 9 show in List");
        System.out.println(numberList);

        System.out.println("-------------Set------------");
        HashSet<Integer> numberSet = new HashSet<Integer>();
        System.out.println("insert 9 9 to HashSet");

        numberSet.add(9);
        numberSet.add(9);
        System.out.println("only one 9 will be in Set");
        System.out.println(numberSet);
    }
}
