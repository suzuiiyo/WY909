package stream;

import java.io.*;
import java.text.DecimalFormatSymbols;
import java.util.Calendar;

public class mergeFileIndeed {
    public static void main(String[] args){
        murgeFile("/home/youpub/Downloads/XYZ", "toSplit.png");
    }
    /**
    * 合并的思路，就是从png-0开始，读取到一个文件，就开始写出到 png中，直到没有文件可以读
    * @param folder
    *            需要合并的文件所处于的目录
    * @param fileName
    *            需要合并的文件的名称
    * @throws FileNotFoundException
    */

    private static void murgeFile(String folder, String fileName){
        try{
            File destFile = new File(folder, fileName);
            FileOutputStream fos = new FileOutputStream(destFile);
            int index = 0;
            while(true){
                File eachFile = new File(folder, fileName + "-" + index++);
                if(!eachFile.exists()) {
                    break;
                }

                FileInputStream fis = new FileInputStream(eachFile);
                byte[] eachContent = new byte[(int) eachFile.length()];
                fis.read(eachContent);
                fis.close();

                fos.write(eachContent);
                //flush
                fos.flush();
                System.out.printf("get %s write into desFile %n", eachFile);
            }
            fos.close();
            System.out.printf("des file's size is %,d byte", destFile.length());
        }catch (FileNotFoundException e){
            e.printStackTrace();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}

