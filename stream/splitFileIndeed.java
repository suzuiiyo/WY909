package stream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class splitFileIndeed {
    public static void main(String[] args){
        //100K
        int eachSize = 100*1024;
        File srcFile = new File("/home/youpub/Downloads/toSplit.png");
        splitFile(srcFile, eachSize);
    }
    /**
     * 拆分的思路，先把源文件的所有内容读取到内存中，然后从内存中挨个分到子文件里
     * @param srcFile 要拆分的源文件
     * @param eachSize 按照这个大小，拆分
     */
    private static void splitFile(File srcFile, int eachSize){
        if(0 == srcFile.length()) {
            throw new RuntimeException("length is 0, cannot be split");
        }

        byte[] fileContent = new byte[(int) srcFile.length()];
        //read file to array
        try{
            FileInputStream fis = new FileInputStream(srcFile);
            fis.read(fileContent);
            fis.close();
        }catch (IOException e){
            e.printStackTrace();
        }

        //calculate how many pieces to split the sorFile
        int pieceNum;
        if(0 == fileContent.length % eachSize) {
            pieceNum = (int) (fileContent.length / eachSize);
        }
        else
        {
            pieceNum = (int) (fileContent.length / eachSize) + 1;
        }

        for(int i=0; i<pieceNum; i++){
            String eachFileName = srcFile.getName() + "-" + i;
            File eachFile = new File(srcFile.getParent() + "/XYZ", eachFileName);
            byte[] eachContent;

            //not the last one
            if(i != pieceNum - 1){
                eachContent = Arrays.copyOfRange(fileContent, eachSize*i, eachSize*(i+1));
            }else{
                eachContent = Arrays.copyOfRange(fileContent, eachSize*i, fileContent.length);
            }

            try{
                FileOutputStream fos = new FileOutputStream(eachFile);
                fos.write(eachContent);
                fos.close();
                System.out.printf("output file%s, it's size is %d bytes%n", eachFile.getAbsoluteFile(), eachFile.length());
            }catch (IOException e){
                e.printStackTrace();
            }

        }
    }
}
