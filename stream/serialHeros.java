package stream;

import charactor.Hero;

import java.io.*;

public class serialHeros {
    public static void main(String[] args) {
        Hero[] heroArr = new Hero[10];
        for(int i=0; i<heroArr.length; i++){
            heroArr[i] = new Hero(String.valueOf(i), i*10);
        }
        File f = new File("/home/youpub/Downloads/heros.lol");
        try(FileOutputStream fos = new FileOutputStream(f);
            ObjectOutputStream oos = new ObjectOutputStream(fos);

            FileInputStream fis = new FileInputStream(f);
            ObjectInputStream ois = new ObjectInputStream(fis);
            )
        {
            oos.writeObject(heroArr);
            Hero[] heroArr2 = (Hero[])ois.readObject();

            for(Hero hero : heroArr2){
                System.out.println(hero.name + "*" + hero.hp);
            }
        }catch (IOException | ClassNotFoundException e){
            e.printStackTrace();
        }
    }
}
