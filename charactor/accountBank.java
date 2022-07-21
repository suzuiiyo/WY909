package charactor;

/**
 * @author youpub
 */
public class accountBank {
    protected double balance;

    public accountBank(double balance){
        this.balance = balance;
    }

    public double getBalance(){
        return balance;
    }

    public void deposit(double inBank){
        balance += inBank;
    }

    public void withdraw(double outBank) throws OverdraftException{
        if(outBank > this.balance)
        {
            throw new OverdraftException("too much to get out", outBank-this.balance);
        }
        else
        {
            this.balance -=  outBank;
        }
    }

    public static class OverdraftException extends Exception{
        private double deficit;

        public double getDeficit(){
            return deficit;
        }

        public OverdraftException(String msg, double deficit){
            super(msg);
            this.deficit = deficit;
        }
    }

    public static void main(String[] args){
        accountBank a = new accountBank(1000);
        a.deposit(1000);
        System.out.println(a.getBalance());

        try{
            a.withdraw(100);
            System.out.println(a.getBalance());
        }catch (OverdraftException e){
            System.err.println("deficit: " + e.getDeficit());
            e.printStackTrace();
        }
    }
}
