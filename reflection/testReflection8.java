package reflection;

import charactor.Hero;

import java.io.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class testReflection8 {
    public static void main(String[] args) throws IOException {
        File f = new File("/home/youpub/IdeaProjects/demo1/src/reflection/hero.config");
        FileReader fis = new FileReader(f);
        BufferedReader br = new BufferedReader(fis);

        List<String> strList = new ArrayList<>();
        String nameStr;
        while((nameStr = br.readLine())!=null){
            strList.add(nameStr);
        }

        br.close();

        try {
            Class hero1Class = Class.forName(strList.get(0));
            Constructor c1 = hero1Class.getConstructor();
            Object h1 = c1.newInstance();
            Field h1NameField = hero1Class.getField("name");
            h1NameField.set(h1, strList.get(1));

            Class hero2Class = Class.forName(strList.get(2));
            Constructor c2 = hero2Class.getConstructor();
            Object h2 = c2.newInstance();
            Field h2NameField = hero2Class.getField("name");
            h2NameField.set(h2, strList.get(3));

            Method m = h1.getClass().getMethod("attackHero", Hero.class);
            m.invoke(h1, h2);
        }catch (ClassNotFoundException | NoSuchMethodException | InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchFieldException e){
            e.printStackTrace();
        }
    }
}
