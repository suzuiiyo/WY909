package stream;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class codingFile {
    public static void main(String[] args) {
        encodeFile(new File("/home/youpub/Downloads/encodingFile.txt"), new File("/home/youpub/Downloads/encodedFile.txt"));
    }

    public static void encodeFile(File encodingFile, File encodedFile){
        try(FileReader fr = new FileReader(encodingFile);
                FileWriter fw = new FileWriter(encodedFile)){
            char[] all = new char[(int) encodingFile.length()];
            fr.read(all);

            encode(all);

            fw.write(all);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public static void encode(char[] fileContent){
        for(int i=0; i< fileContent.length; i++)
        {
            char c = fileContent[i];
            if(isLetterOrDigit(c)){
                switch (c){
                    case '9' :
                        c = '0';
                        break;
                    case 'Z' :
                        c = 'a';
                        break;
                    case 'z' :
                        c = 'A';
                        break;
                    default:
                        c++;
                        break;
                }
            }
            fileContent[i] = c;
        }
    }

    public static boolean isLetterOrDigit(char c) {
        // 不使用Character类的isLetterOrDigit方法是因为，中文也会被判断为字母
        String letterOrDigit =
                "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        return -1 != letterOrDigit.indexOf(c);
    }
}
