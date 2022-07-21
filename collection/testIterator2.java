package collection;
import charactor.Hero;

import java.beans.IntrospectionException;
import java.util.ArrayList;
import java.util.List;

public class testIterator2 {
    public static void main(String[] args) {
        List<Hero> heros = new ArrayList<Hero>();

        for(int i=0; i<20; i++){
            heros.add(new Hero("hero name " + i));
        }

        System.out.println(heros.toString());
        List<Hero> deletingHeros = new ArrayList<>();

        for(Hero h : heros){
            int id = Integer.parseInt(h.name.substring(10));
            if(0 == id%8){
                deletingHeros.add(h);
            }
        }
        for(Hero h : deletingHeros){
            heros.remove(h);
        }
        System.out.println(heros.toString());

//        for(Hero h: heros){
//            int id = Integer.parseInt(h.name.substring(10));
//            if(0 == id%4){
//                heros.remove(h);
//            }
//        }
    }
}
