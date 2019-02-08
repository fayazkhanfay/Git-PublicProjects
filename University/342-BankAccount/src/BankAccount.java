public class BankAccount
{
    private String name;      		     // name of account holder
    private double balance;   			 // how much money is in account, $
    private boolean accountType;		 // Savings == true, Checking == false 
    
    public BankAccount()
    // POST: A default BankAccount object is created with name set to a blank and
    //       and balance set to $0.00
    {
       this(0.0); 
    }

    public BankAccount(double balance)
    // PRE:  balance >= 0.00 and balance is in dollars
    // POST: A BankAccount object is created with name set to a blank and the class member 
    //		 balance set to balance accountType is set to false(Checking)
    {
       accountType = false; 	
       name = " ";
       
       if(balance >= 0)             	 // validate proposed initial balance
          this.balance = balance; 
       else
          this.balance = 0; 
    }

    public BankAccount(double balance,String name,String accountType)
    // PRE:	 balance in dollars and balance >= 0.00
    //		 accountType need to be initialized
    //		 name needs to be initialized 
    // POST: When a BankAccount object is created, name will set (this.name) and balance 
    //		 will set (this.balance). If accountType is "savings" then (this.acccountType) 
    //		 is set to true and accountType is "checking" (this.accountType) set to false
    {
       this.name = name; 
       
       if(balance >= 0)             	 // validate proposed initial balance
           this.balance = balance; 
        else
           this.balance = 0; 
       
       if(accountType.equals("savings")) //checks if String accountType is savings
    	   this.accountType = true;
    
       
       if(accountType.equals("checking"))//checks if String accountType is checking 
    	   this.accountType = false;
       
    }
    
    public String accountType()
    // This method checks the object (this.accountType) for either true or false. 
    // If (this.accountType) is true then returns "savings", is false then returns "checking"
    {
    	if(this.accountType == true)
    	   return "savings";
    	else
    	   return "checking";
    }
    
    public void ResetAccount(String newName, double newBalance)
    // PRE:  newName has been assigned a value
    //       && newBalance >= 0.00 and newBalance is in dollars
    // POST: This account object is reset with name set to newName
    //       and balance set to newBalance
    {
        name = newName;                  // Match up private variables with parameters
        balance = newBalance;            // Could do error checking here with an if(balance >= 0)
    }

    public boolean Withdraw(double amount) 
    // PRE:  amount >= 0.00 and amount is in dollars
    // POST: amount is deducted from the balance stored for this account
    {
    	if(balance - amount >= 0)		   //checks if balance is sufficient for withdraw
    	{
    	   balance = balance - amount;     //updates balance after withdrawing
    	   return true;    
    	}
    	else
    		return false;
    }

    public double GetBalance() 
    // POST: FCTVAL == current balance of this account in dollars
    {
        return balance;
    }

    public void DisplayBalance() 
    // POST: The current balance of this account has been displayed to the screen
    {
        System.out.printf("Your balance is currently $%.2f\n", balance); 
    }
}