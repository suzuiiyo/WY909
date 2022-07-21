package collection;

import charactor.Hero;

import java.util.ArrayList;
import java.util.List;

public class testLIst {
    public static void main(String[] args) {
        List heros = new ArrayList();
        heros.add(new Hero("garen"));
        System.out.println(heros.size());
    }
}
