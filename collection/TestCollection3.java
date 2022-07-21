package collection;

import charactor.Hero;

import java.util.ArrayList;

public class TestCollection3 {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();

        for(int i=0; i<5; i++){
            heros.add(new Hero("hero " + i));
        }
        Hero specialHero = new Hero("special hero");
        heros.add(specialHero);

        System.out.println(heros.toString());

        System.out.print("虽然一个新的对象名字也叫 hero 1，但是contains的返回是:");
        System.out.println(heros.contains(new Hero("hero 1")));
        System.out.print("而对specialHero的判断，contains的返回是:");
        System.out.println(heros.contains(specialHero));
    }
}
