package charactor;

/**
 * @author youpub
 */
public class CheckingAccount extends accountBank{
    private double overdraftProtection;
    public CheckingAccount(double balance){
        super(balance);
    }

    public CheckingAccount(double balance, double overdraftProtection){
        super(balance);
        this.overdraftProtection = overdraftProtection;
    }

    @Override
    public void withdraw(double outBank) throws OverdraftException{
        if(outBank > this.balance + overdraftProtection){
            double  deficit = outBank - (this.balance + overdraftProtection);
            throw new OverdraftException("touzhi too much", deficit);
        }
        this.balance -= outBank;
    }

    public static void main(String[] args){
        CheckingAccount a = new CheckingAccount(1000, 500);
        a.deposit(1000);

        System.out.println(a.getBalance());

        try{
            a.withdraw(600);
            System.out.println(a.getBalance());
            a.withdraw(600);
            System.out.println(a.getBalance());
            a.withdraw(600);
            System.out.println(a.getBalance());
            a.withdraw(600);
            System.out.println(a.getBalance());
            a.withdraw(600);
            System.out.println(a.getBalance());
        }catch (OverdraftException e){
            System.err.println("touzhi is over" + e.getDeficit());
            e.printStackTrace();
        }
    }
}
