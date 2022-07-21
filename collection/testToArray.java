package collection;

import charactor.Hero;

import java.sql.Array;
import java.util.ArrayList;

public class testToArray {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();

        for(int i=0; i<5; i++){
            heros.add(new Hero("hero " + i));
        }
        Hero specialHero = new Hero("special hero");
        heros.add(specialHero);
        System.out.println(heros);
        Hero hs[] = (Hero[])heros.toArray(new Hero[]{});
        System.out.println("array:" + hs);
    }
}
