package collection;

import charactor.Hero;

import java.util.*;
import java.util.stream.Collectors;

public class TestComparator {
    public static void main(String[] args) {
        Random r = new Random();
        List<Hero> heros = new ArrayList<Hero>();

        for(int i=0; i<10; i++){
            heros.add(new Hero("hero " + i, r.nextInt(100), r.nextInt(100)));
        }
        System.out.println("initialed Set:");
        System.out.println(heros);

        Comparator<Hero> c = new Comparator<Hero>() {
            @Override
            public int compare(Hero h1, Hero h2) {
                if(h1.hp>=h2.hp) {
                    return 1;
                }
                else {
                    return -1;
                }
            }
        };
        heros.sort(c);
        System.out.println("after sort the set is: ");
        System.out.println(heros);
    }
}
