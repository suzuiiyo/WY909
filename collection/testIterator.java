package collection;

import charactor.Hero;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class testIterator {
    public static void main(String[] args) {
        List<Hero> heros = new ArrayList<Hero>();

        for(int i=0; i<5; i++){
            heros.add(new Hero("Hero name " + i));
        }

        System.out.println("-------------use the iterator of while---------------");
        Iterator<Hero> it = heros.iterator();

        while(it.hasNext()){
            Hero h = it.next();
            System.out.println(h);
        }

        System.out.println("------------use the iterator of for ------------------");
        for(Iterator<Hero> iterator = heros.iterator(); iterator.hasNext();){
            Hero hero = (Hero) iterator.next();
            System.out.println(hero);
        }
    }
}
