package generic;

import charactor.ADHero;
import charactor.APHero;
import charactor.Hero;

import java.util.ArrayList;

public class TestGeneric {
    public static void main(String[] args) {
        ArrayList<APHero> apHeroList = new ArrayList<APHero>();
        apHeroList.add(new APHero());

        ArrayList<? extends Hero>heroList = apHeroList;

        Hero h = heroList.get(0);

        //can not put element into it
//        heroList.add(new ADHero());
    }
}
