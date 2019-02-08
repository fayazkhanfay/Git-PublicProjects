public abstract class Board 
{
    protected final int address;                     //Address of board location
    protected final String name;                     //Name of board location
    
    public Board()
    //POST: A default Board object is created with address set to 0 and name set to " ".
    {
        address = 0;
        name = " ";
    }
    
    public Board(int address, String name)
    //PRE:  address is initialized and address >=0
    //      name is initialized
    //POST: A Board object is created with class member address set to address and class 
    //        member name set to name.
    {
     this.address = address;
     this.name = name;
    }
                 
    public abstract boolean payRent(Player p, int diceVal, int numOwned);
    //PRE:  p is initialized
    //      diceVal >= 1 and diceVal <= 12
    //      numOwned >= 0
    //POST: FCTVAL == true if player successfully paid rent, false otherwise
    
    
    public abstract String[] getPossibleActions(Player player); 
    //PRE: p is initialized
    //POST: FCTVAL == array of options player has upon landing on
    //      this space, to be used in a menu in a user interface
    
    public String toString()
    //POST: FCTVAL == string representation of board
    {
        return "Location name: " + name + ". Address: " + address + ". ";
    }
    
    public int getAddress()
    //POST: FCTVAL == private data member address
    {
        return address;
    }

}