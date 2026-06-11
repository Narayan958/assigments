public class SavingsAccount extends Account {
    private double interestRate;

    public SavingsAccount() {
        this(0, "Unknown", 0.0, 0.0);
    }

    public SavingsAccount(int accNo, String name, double balance, double rate) {
        super(accNo, name, balance);
        this.interestRate = rate;
    }

    public double calculateInterest() {
        return getBalance() * interestRate / 100;
    }

    @Override
    public void display() {
        super.display();
        System.out.println("Interest Rate: " + interestRate + "%");
        System.out.println("Interest: " + calculateInterest());
    }
}