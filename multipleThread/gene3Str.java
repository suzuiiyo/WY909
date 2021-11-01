package multipleThread;

import java.lang.reflect.Field;
import java.util.Arrays;
import java.util.Random;
import java.util.StringTokenizer;

public class gene3Str {
    public static void main(String[] args) {
        Random r = new Random();
        char[] ch = new char[3];
        String str = "";
        for(int i=0; i<ch.length; i++) {
            ch[i] = (char)r.nextInt(100);
            String str1 = String.valueOf(ch[i]);
            str += str1;
        }
        System.out.println(str);

        String finalStr = str;
        String finalStr1 = str;
        Thread t1 = new Thread(){
            @Override
            public void run(){
                Random r2 = new Random();
                char[] chTry = new char[3];
                String strTry = "";
                while(true){
                    for(int i =0; i<chTry.length; i++){
                        chTry[i] = (char)r.nextInt(100);
                        String str2 = String.valueOf(chTry[i]);
                        strTry += str2;
                    }
                    System.out.println(strTry);
                    if(strTry.equals(finalStr)) {
                        System.out.printf("cracked success! and str is %s, strTrt is %s", finalStr1, strTry);
                        break;
                    }else{
                        strTry = "";
                    }
//                    }else {
//                        Field valueField = null;
//                        try {
//                            valueField = String.class.getDeclaredField("value");
//                        } catch (NoSuchFieldException e) {
//                            e.printStackTrace();
//                        }
//                        valueField.setAccessible(true);
//                        try {
//                            char[] value = (char[]) valueField.get(strTry);
//                        } catch (IllegalAccessException e) {
//                            e.printStackTrace();
//                        }
//                    }
                }
            }
        };
        t1.start();
    }
}
