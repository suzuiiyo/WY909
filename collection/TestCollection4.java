package collection;
import charactor.Hero;
import java.util.ArrayList;

public class TestCollection4 {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();

        for(int i=0; i<5; i++){
            heros.add(new Hero("hero " + i));
        }
        Hero specialHero = new Hero("special hero");
        heros.add(specialHero);

        System.out.println(heros.get(5));
    }
}
