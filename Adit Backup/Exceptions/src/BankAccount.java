
public class BankAccount {
private static final Exception NegativeBalanceException = null;
double balance;
void withdraw(double amount) throws Exception {
	if (amount > balance) {
		throw NegativeBalanceException;
	}
}

void handleTransaction(){
	withdraw(balance+1);
}

void main(String[] args) {
	BankAccount ba = new BankAccount();
	ba.handleTransaction();
}

}
