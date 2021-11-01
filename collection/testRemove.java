package collection;
import charactor.Hero;
import java.util.ArrayList;

public class testRemove {
    public static void main(String[] args) {
        ArrayList heros = new ArrayList();

        for(int i=0; i<5; i++){
            heros.add(new Hero("hero" + i));
        }
        Hero specialHero = new Hero("special hero");
        heros.add(specialHero);

        System.out.println(heros);
        System.out.println("remove index is 2");
        heros.remove(2);
        System.out.println(heros.toString());
        System.out.println("remove special hero");
        heros.remove(specialHero);
        System.out.println(heros);
    }
}
