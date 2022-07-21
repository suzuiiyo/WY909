package collection;

import charactor.Hero;

import java.util.ArrayList;

public class testSet {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();
        for(int i=0; i<5; i++){
            heros.add(new Hero("hero " + i));
        }
        Hero specialHero = new Hero("special hero");
        heros.add(specialHero);

        System.out.println(heros);
        System.out.println("replace iindex is 5 with hero 5");
        heros.set(5, new Hero("hero 5"));
        System.out.println(heros);
    }
}
