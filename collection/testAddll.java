package collection;

import charactor.Hero;
import com.sun.source.tree.ArrayAccessTree;
import java.util.ArrayList;

public class testAddll {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();

        for(int i=0; i<5; i++){
            heros.add(new Hero("hero " + i));
        }
        System.out.println("ArrayList heros:\t" + heros);

        ArrayList anotherHeros = new ArrayList();
        anotherHeros.add(new Hero("hero a"));
        anotherHeros.add(new Hero("hero b"));
        anotherHeros.add(new Hero("hero c"));
        System.out.println("another heros:\t" + anotherHeros);
        heros.addAll(anotherHeros);
        System.out.println("add another into current:");
        System.out.println("ArrayList heros:\t" + heros);
    }
}
