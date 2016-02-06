//Programmer: Fayaz Khan
//Assignment: Lab 5 
//Date:       September 24, 2015
//Description:Program uses test drivers to test methods in BankAccount class with different 
//			  bank account types 

public class Lab05 
{
	public static void main(String[] args) 
	{
		int initialBalance = 1000;		//Initial deposit for both bank account 
		String sType = "savings"; 		//Bank account type "savings"
		String cType = "checking";		//Bank account type "checking"
		String firstHolder = "Sidra"; 	//account owner number one
		String secondHolder = "Bushra";	//account owner number two 
		double withdraw$250 = 250;      //first withdraw intended to be successful
	    double withdraw$1100 = 1100;	//second withdraw intended to be unsuccessful 
	    
	    //Two different bank accounts, sAccount == savings and cAccount == checking
	    BankAccount sAccount = new BankAccount(initialBalance,firstHolder,sType);
	    BankAccount cAccount = new BankAccount(initialBalance,secondHolder,cType);
	    
	    //Prints the starting balance 
	    System.out.printf("Your balance is currently $%.2f\n", sAccount.GetBalance()); 
	    
	    //checks the type of account  whether it is savings or checking
	    System.out.println("This is a " + sAccount.accountType() + " bank account");
	    
	    //checks the type of account  whether it is savings or checking
	    System.out.println("This is a " + cAccount.accountType() + " bank account");
	    
	    //Attempting to withdraw from bank account 
	    System.out.printf(String.format("Withdrawl is pending of amount $%.2f\n", withdraw$250)); 
	    if(sAccount.Withdraw(withdraw$250))				//Checks if funds are sufficient 
	    	System.out.println("Withdrawal Succesful");
	    else
	    	System.out.println("Withdrawal Unsuccesful, Insufficient funds");
	    
	    //Displays the current balance of account
	    sAccount.DisplayBalance();
	    
	    //Second test Attempting to withdraw from bank account 
	    System.out.printf(String.format("Withdrawl is pending of amount $%.2f\n", withdraw$1100)); 
	    if(cAccount.Withdraw(withdraw$1100))			//Checks if funds are sufficient 
	    	System.out.println("Withdrawal Succesful");
	    else
	    	System.out.println("Withdrawal Unsuccesful, Insufficient funds");
	    
	    //Displays the current balance of account
	    cAccount.DisplayBalance();
	    
	    //Displays whether it is a savings or checking account 
	    System.out.println("This is a " + sAccount.accountType() + " bank account");
	    
	    //Reseting account with a new name and new balance 
	    sAccount.ResetAccount(secondHolder, initialBalance);
	    System.out.println("The savings account is resetting with new name and balance");
	    System.out.printf("Your balance is currently $%.2f\n", sAccount.GetBalance()); 
	}

}
