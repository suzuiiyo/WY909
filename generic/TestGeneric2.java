package generic;

import charactor.ADHero;
import charactor.APHero;
import charactor.Hero;

import java.util.ArrayList;

public class TestGeneric2 {
    public static void main(String[] args) {
        ArrayList<? super Hero> heroList = new ArrayList<Object>();

        heroList.add(new Hero());
        heroList.add(new APHero());
        heroList.add(new ADHero());

        //cannot put data into it
//        Hero h= heroList.get(0);
    }
}
