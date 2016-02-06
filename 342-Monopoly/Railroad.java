import java.util.Arrays;

public class Railroad extends Property
{
 
    public Railroad()
    //POST: A default Railroad object is created with address set to 0, name  set to " ", price
    //         set to 0, and owner set to bank
    {
        super(0, " ", 0); 
        owner = "bank";
    }
 
    public Railroad(int address, String name, int cost) 
    //PRE:  address is >= 0, name is initialized, and cost >= 0
    //POST: A Railroad object is returned with class member address set to address, class member 
    //         name set to name, class member price set to price, and owner set to "bank"
    {
        super(address, name, cost);
        owner = "bank";
    }

    public int calcRent(Player p,int diceVal, int numOwned)
    //PRE:  p is initialized
    //      diceVal >= 2 and diceVal <= 12
    //      numOwned >= 0
    //POST: FCTVL: Amount of rent the player owns in dollars
    {
        if(owner.equals(p.getToken()))                 //Return $0 if player owns lot
        {
            return 0;
        }
        if(numOwned == 1)                              //Owner owns 1 railroad
        {
            return 25;                                 //Rent is 25 dollars
        }
        else if(numOwned == 2)                         //Owner owns 2 railroads
        {
            return 50;                                 //Rent is 50 dollars
        }
        else if(numOwned == 3)                         //Owner owns 3 railroads
        {
            return 100;                                //Rent is 100 dollars
        }
        else if(numOwned == 4)                         //Owner owns 4 railroads
        {
            return 200;                                //Rent is 200 dollars
        }

        return 0;                                      //Return 0 dollars otherwise
    }

    public boolean payRent(Player p, int diceVal, int numOwned)
    //PRE:  p is initialized
    //      diceVal >= 2 and diceVal <= 12
    //      numOwned >= 0
    //POST: FCTVAL == true if player successfully paid rent, false otherwise.
    {
        int rent;                                             //Rent cost

        if (!owner.equals(p.getToken()) && !owner.equals("bank")) //Player owns railroad 
        {
            rent = (-1) * calcRent(p, diceVal, numOwned);     //Calculate rent player owns
            return p.changeWealth(rent);                      //Return if transaction was successful
        }

        return false;                                         //Player is not owner, can not pay rent
    }
    
    public boolean buy(Player p, Property[] properties)
    //PRE:  p is initialized, properties is initialized
    //POST: FCTVAL == true if player successfully bought railroad, false otherwise
    {
        boolean successfulTransaction = super.buy(p, properties); //Player buys property

        if(successfulTransaction)                         //Player was able to buy property
        {
            p.addRailRoad();                              //Player owns the railroad 
            return true;                                  //Buying was a success
        }

       return false;                                      //Buying failed
    }
 
    public String toString()
    //POST: FCTVAL == returns string representation of Railroad
    {
        return super.toString();
    }
    
    public String[] getPossibleActions(Player player)
    // PRE:  player is initialized
    // POST: FCTVAL == array of options player has upon landing on
    //       this space, to be used in a menu in a user interface
    {
        String [] options = new String[7];    //String of options the user can choose
        
        Arrays.fill(options, "");               //fills it with blank spaces; 
     
        if(owner.equals("bank"))       //player does not own property 
        {
            options[0] = "Buy Property?";
        }
   
        options[1] = "Do nothing";       //Player decides to skip 
        
        if(player.getPropertiesIndex() > 0) //If player owns property
            options[2] = "Buy House?";
     
        if(player.hotelCheck())     //if any player owned properties have 4 houses
        {
            options[3] = "Buy Hotel?";
        }
     
        if(player.getNumOfHouses()>0)   //if player owns any houses for selling  
        {
            options[4] = "Sell House for half value?";
        }
    
        if(player.getNumOfHotels()>0)   //if player owns any hotels for selling
        {
            options[5] = "Sell Hotel for half value?";
        }
        if(!owner.equals(player.getToken()) && !owner.equals("bank"))
        {
            options[6] = "Pay Rent";
        }
        return options;            //String of options user can do 
    }
}