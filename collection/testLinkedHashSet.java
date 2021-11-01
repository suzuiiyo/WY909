package collection;

import java.util.LinkedHashSet;
import java.util.Set;

public class testLinkedHashSet {
    public static void main(String[] args) {
        Set<Integer> result = new LinkedHashSet<>();
        String str = String.valueOf(Math.PI);

        str = str.replace(".", "");
        char[] cs = str.toCharArray();
        for(char c : cs){
            int num = Integer.parseInt(String.valueOf(c));
            result.add(num);
        }
        System.out.printf("in %s there are no duplicate num is: %n", String.valueOf(Math.PI));
        System.out.println(result);
    }
}
