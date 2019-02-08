import java.util.Arrays;

public class Utility extends Property 
{

    public Utility()
    //POST: A default Utility object is created with address set to 0, name set to " ", price
    //         set to 0, and owner set to "bank"
    {
        super(0, " ", 0); 
        owner = "bank";
    }

    public Utility(int address, String name, int cost)
    //PRE:  address is >= 0, name is initialized, and cost >= 0
    //POST: A Utility object is returned with class member address set to address, class member 
    //         owner set to name, class member price set to cost, and owner set to "bank"
    {
        super(address, name, cost);
        owner = "bank";
    }

    public int calcRent(Player p, int diceValue, int numOwned)
    //PRE:  p is initialized
    //      diceValue <= 12 and diceValue >= 2
    //      numOwned >= 0
    //POST: Amount of rent player owns in dollars 
    {
        int rentAmt = 0;                               //Rent owned
        
        if(owner.equals(p.getToken()))                 //Player owns lot
        {
            return rentAmt;                            //Return 0  dollars
        }  
        if (numOwned == 1)                             //Player owns 1 utility 
        {
            rentAmt = 4 * diceValue;                   //Rent is 4 times diceValue
        }
        else if (numOwned == 2)                        //Player owns 2 utilities
        {
            rentAmt = 10 * diceValue;                  //Rent is 10 times diceValue
        }

        return rentAmt;                                //Return calculated rent in dollars
    }
 
    public boolean payRent(Player p, int diceVal, int numOwned)
    //PRE:  p is initialized
    //      diceVal <= 12 and diceVal >= 2
    //      numOwned > 0
    //POST: FCTVAL == true if player successfully paid rent, false otherwise.
    {
        int rent;

        if (!owner.equals(p.getToken()) && !owner.equals("bank")) //Player owns utility
        {
                rent = (-1) * calcRent(p, diceVal, numOwned); //Calculate rent
                return p.changeWealth(rent);            //Charge rent and check if purchase successful
        }

        return false;                                   //Return false if player does not own utility
    }

    public boolean buy(Player p, Property[] properties)
    //PRE:  p is initialized, properties is initialized
    //POST: FCTVAL = true if purchase of utility was successful, false otherwise
    {
        boolean successfulTransaction = super.buy(p, properties); //Player buys property

        if(successfulTransaction)                       //Player was able to buy property
        {
                p.addUtility();                         //Player owns the utility
                return true;                            //Buying was a success
        }

        return false;                                   //Buying failed
    }

    public String toString()
    //POST: FCVAL == returns string representation of Utility
    {
        return super.toString();
    }
    
    public String[] getPossibleActions(Player player)
    // PRE:  player is initialized
    // POST: FCTVAL == array of options player has upon landing on
    //       this space, to be used in a menu in a user interface
    {
        String [] options = new String[7];   //String of options the user can choose
        
        Arrays.fill(options, "");            //Fills it with blank spaces; 
     
        if(owner.equals("bank"))             //Player does not own property 
        {
            options[0] = "Buy Property?";
        }
   
        options[1] = "Do nothing";           //Player decides to skip
        
        if(player.getPropertiesIndex() > 0)  //If player owns property
            options[2] = "Buy House?";
     
        if(player.hotelCheck())              //If any player owned properties have 4 houses
        {
            options[3] = "Buy Hotel?";
        }
        if(player.getNumOfHouses()>0)        //If player owns any houses for selling 
        {
            options[4] = "Sell House for half value?";
        }
        if(player.getNumOfHotels()>0)        //If player owns any hotels for selling
        {
            options[5] = "Sell Hotel for half value?";
        }
        if(!owner.equals(player.getToken()) && !owner.equals("bank"))
        {
        options[6] = "Pay Rent";
        }
     
        return options;                      //String of options user can do 
    }

}