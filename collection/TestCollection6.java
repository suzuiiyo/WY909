package collection;

import charactor.Hero;

import java.util.ArrayList;
import java.util.List;


public class TestCollection6 {
    public static void main(String[] args) {
        List<Hero> heros = new ArrayList<Hero>();

        for(int i=0; i<5; i++){
            heros.add(new Hero("hero name " + i));
        }

        System.out.println("----------------for loop-----------------");
        for(int i=0; i< heros.size(); i++){
            Hero h = heros.get(i);
            System.out.println(h);
        }
    }
}
