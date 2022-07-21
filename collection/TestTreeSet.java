package collection;

import charactor.Hero;

import java.util.Comparator;
import java.util.Random;
import java.util.TreeSet;

public class TestTreeSet {
    public static void main(String[] args) {
        Random r = new Random();

        Comparator<Hero> comparator = new Comparator<Hero>() {
            @Override
            public int compare(Hero h1, Hero h2) {
                if(h1.damage < h2.damage){
                    return 1;
                }else
                {
                    return -1;
                }
            }
        };

        TreeSet<Hero> heroTree = new TreeSet<>(comparator);
        for(int i =0; i<10; i++){
            heroTree.add(new Hero("hero " +i, r.nextInt(400), r.nextInt(100)));
        }

        System.out.println(heroTree.toString());

        for(Hero h : heroTree){
            System.out.println(h.damage);
        }
    }
}
