import java.util.ArrayList;
import java.util.List;

/**
����ֻ�ڱ���׶���Ч��Java�еķ��ͣ�ֻ�ڱ���׶���Ч���ڱ�������У���ȷ���鷺�ͽ���󣬻Ὣ���͵������Ϣ�����������ڶ��������뿪�����ı߽紦������ͼ�������ת���ķ�����Ҳ����˵��������Ϣ������뵽����ʱ�׶�
 */
public class GnericExa2 {
    public static void main(String[] args) {
        List<String> stringArrayList = new ArrayList<>();
        List<Integer> integerArrayList = new ArrayList<>();

        Class classStringArrayList = stringArrayList.getClass();
        Class classIntegerArrayList = integerArrayList.getClass();

        //�������list����,�����������߼��Ͽ��Կ����Ƕ����ͬ�����ͣ�ʵ���϶�����ͬ�Ļ�������
        if (classStringArrayList.equals(classIntegerArrayList)) {
            System.out.println("���Ͳ���: " + "������ͬ");
        }
    }
}
