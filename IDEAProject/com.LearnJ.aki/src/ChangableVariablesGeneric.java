/**
 * @author yangw
 */

//�ɱ�������ͷ���
public class ChangableVariablesGeneric {
    public <T> void printMsg(T... args){
        for(T t : args){
            System.out.println("���Ͳ���: " + " t is " + t);
        }
    }

    public static void main(String[] args) {
        new ChangableVariablesGeneric().printMsg("111", 222, "aaaa", "2323.4", 55.55);
    }
}

