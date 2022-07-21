package lambda;


import charactor.Hero;
import java.util.*;

public class TestAggregate {
    public static void main(String[] args) {
        Random r = new Random();
        List<Hero> heros = new ArrayList<>();
        for(int i=0; i<10; i++){
            heros.add(new Hero("Hero " +i, r.nextInt(1000)));
        }
        System.out.println("after initial collection data(the last data repeat):");
        System.out.println(heros);

        //troditional way
        Collections.sort(heros, new Comparator<>() {
            @Override
            public int compare(Hero o1, Hero o2) {
                return (int) (o2.hp - o1.hp);
            }
        });

        System.out.println(heros.toString());
        Hero hero = heros.get(2);
        System.out.printf("the third high hp hero searched by troditional way is %s: %n", hero.name);

        //collections way
        String name = heros
                .stream()
                .sorted((h1, h2)->h1.hp>h2.hp?-1:1)
                .skip(2)
                .map(h->h.getName())
                .findFirst()
                .get();

        System.out.printf("the third high hp hero searched by collection way is %s: %n", name);
    }
}
