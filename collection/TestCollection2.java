package collection;

import charactor.Hero;

import java.util.ArrayList;

public class TestCollection2 {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();
        heros.add(new Hero("TIMP"));
        System.out.println(heros.size());

        heros.add(new Hero("DISK"));
        System.out.println(heros.size());
    }
}
