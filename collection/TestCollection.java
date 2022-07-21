package collection;

import charactor.Hero;

import java.util.ArrayList;

public class TestCollection {
    public static void main(String[] args) {
        Hero heros[] = new Hero[30];
        heros[0] = new Hero("garen");

        heros[20] = new Hero("TIMO");

        ArrayList heroList = new ArrayList();
        for(int i=0; i<5; i++){
            heroList.add(new Hero("Hero " + i));
        }
        System.out.println(heroList);

        Hero specialHero = new Hero("special Hero");
        heroList.add(3, specialHero);

        System.out.println(heroList.toString());
    }
}
