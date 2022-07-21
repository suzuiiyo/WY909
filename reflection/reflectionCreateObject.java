package reflection;

import charactor.Hero;

import java.lang.reflect.Constructor;

public class reflectionCreateObject {
    public static void main(String[] args) {
        Hero h1 = new Hero();
        h1.name = "delta";
        System.out.println(h1);

        try{
            String className = "charactor.Hero";
            Class pClass = Class.forName(className);

            Constructor c = pClass.getConstructor();
            Hero h2 = (Hero) c.newInstance();
            h2.name = "alpha";
            System.out.println(h2.toString());
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
