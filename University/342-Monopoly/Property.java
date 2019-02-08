import java.util.Arrays;

public class Property extends Board
{
    protected int price;                                //Buying price of property
    protected String owner;                             //Owner of property

    public Property()
    //POST: A default Property object is created with address set to 0, name set to " ",
    //         owner set to "bank", rent set to 10, and price set to 150.
    {
        super(0, " ");
        owner = "bank";
        price = 150;
    }

    public Property(int address, String name, int cost)
    //PRE:  address is initialized and address >= 0
    //      cost >= 0
    //      name is initialized
    //POST: A Property object is created  with class member address set to address, class member
    //         name set to name, price set to cost, and owner set to "bank".
    {
        super(address, name);
        price = cost;
        owner = "bank";
    }

    public boolean buy(Player p, Board[] properties)
    //PRE:  p is initialized
    //POST: FCTVAL == true if player successfully bought property, false otherwise
    {
        boolean canBuy = false;                         //Boolean for if player has money to buy
     
        if (owner.equals("bank"))                       //Owner is bank
        {
            canBuy = p.buyProperty(price, address, properties); //Check if player has money to buy
        }
        if(canBuy)                                      //Player bought property
        {
            owner = p.getToken();                       //They are set to property owner
            return true;                                //Successful buy
        }

        return false;                                   //Unsuccessful buy
    } 
    
    public String getOwner()
    //POST: FCTVAL == returns the token of the property owner
    {
        return owner;
    }
    
    public int getPrice()
    //POST: FCTVAL == returns the price of the property 
    {
        return price;
    }
    
    @Override
    public boolean payRent(Player p, int diceVal, int numOwned) 
    //PRE:  p is initialized
    //      diceVal >= 2 and diceVal <= 12
    //      numOwned >= 0
    //POST: FCTVAL == true if player successfully paid rent, false otherwise
    {
        return false;
    }
    
    public int calcRent(Player p, int diceVal, int num) 
    //PRE:  p is initialized
    //      diceVal >= 2 and diceVal <= 12
    //      num >= 0
    //POST: FCTVAL == Amount of rent the player owns in dollars
    {
        return 0;
    }
 
    public String toString()
    //POST: FCTVAL == returns string representation of the property
    {
        return super.toString() + "Owner: " + owner + ". Price of Property: " + price + ". ";
    }
    
    @Override
    public String[] getPossibleActions(Player player) 
    // PRE:  player is initialized
    // POST: FCTVAL == array of options player has upon landing on
    //       this space, to be used in a menu in a user interface
    {
        String [] options = new String[7];              //String of options the user can choose
  
        Arrays.fill(options, "");                       //Fill array with blank spaces
  
        return options;                                 //String of options user can do 
    }
}