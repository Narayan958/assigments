public class CurrentAccount extends Account {
    private double overdraftLimit;

    public CurrentAccount() {
        this(0, "Unknown", 0.0, 0.0);
    }

    public CurrentAccount(int accNo, String name, double balance, double limit) {
        super(accNo, name, balance);
        this.overdraftLimit = limit;
    }

    @Override
    public void withdraw(double amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("Invalid withdrawal");
        }

        if (amount > getBalance() + overdraftLimit) {
            throw new IllegalArgumentException("Overdraft limit exceeded");
        }

        setBalance(getBalance() - amount);
    }

    @Override
    public void display() {
        super.display();
        System.out.println("Overdraft Limit: " + overdraftLimit);
    }
}