package collection;

import charactor.Hero;

import java.sql.Array;
import java.util.ArrayList;

public class TestCollection5 {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();

        for(int i=0; i<5; i++){
            heros.add(new Hero("hero " + i));
        }
        Hero specialHero = new Hero("special hero");
        heros.add(specialHero);

        System.out.println(heros);
        System.out.println("special hero locates:" + heros.indexOf(specialHero));
        System.out.println("new hero but name is:" + heros.indexOf(new Hero("hero 1")));
    }
}
