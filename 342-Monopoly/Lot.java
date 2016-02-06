import java.util.Arrays;

public class Lot extends Property
{
    private static final int HOUSE_HOTEL_COST  = 150;  //Cost of buying a hotel or a house
    private final int[] propertyRent;                  //Array of house and hotel rents
    private int numHouses;                             //Number of houses on lot
    private boolean hotelOnLot;                        //Hotel on lot status

    
    public Lot()
    //POST: A default Lot object is created with address set to 0, name set to " ", price set to 150,
    //         numHouses set to 0, hotelOnLot set to false, owner set to "bank", and an allocated 
    //         array of propertyRent is created.
    {
        super(0, " ", 150);
        numHouses = 0;
        hotelOnLot = false;
        propertyRent = new int[6];
        owner = "bank";
    }
    
    public Lot(int address, String name, int cost, int[] rents)
    //PRE:  address >= 0, name is initialized, cost >= 0, and rents is initialized.
    //      propertyRent and rents should have the same length
    //POST: A Lot object is created with class member address set to address, class member 
    //         name set to name, class member price set to cost, numHouses set to 0, hotlOnLot
    //         set to false, and an allocated array of propertyRent set to rents. 
    {
        super(address, name, cost);
        propertyRent = rents; 
        numHouses = 0;
        hotelOnLot = false;
        owner = "bank";
    }
    
    public boolean buyHouse(Player p)
    //PRE:  p is initialized. Player p is buying houses evenly and after owning all property of 
    //         the same color. 
    //POST: FCTVAL == true if player successfully buys house, false otherwise
    {
        boolean successfulTransaction;                         //Buying was success
        int chargeCost;                                        //Cost of buying
        
        if(owner.equals(p.getToken()))                         //Player owns lot
        {
            if(numHouses < 4 && hotelOnLot == false)           //Less than 4 houses on lot
            {
                chargeCost = (-1) * HOUSE_HOTEL_COST;
                successfulTransaction = p.changeWealth(chargeCost); //Charge for house
            
                if(successfulTransaction)                      //Player successfully bought house
                {
                    numHouses++;                               //number of houses increases
                    p.setNumOfHouses(p.getNumOfHouses()+1);
                    return true;                               //Successful transaction
                }
            }
        }
        
        return false;                                          //Unsuccessful transaction
    }
    
    public boolean buyHotel(Player p)
    //PRE:  p is initialized. Player is buying evenly and owns all lots of the same color.
    //      Player also owns 4 houses before buying hotel
    //POST: FCTVAL == true if player successfully buys hotel, false otherwise
    {
        boolean successfulTransaction;                      //Buying was success
        int chargeCost;                                     //Cost of buying

        if(owner.equals(p.getToken()))                      //Player owns lot
        {
            if(numHouses == 4 && hotelOnLot == false)       //player owns 4 houses and no hotels
            {
                chargeCost = (-1) * HOUSE_HOTEL_COST;
                successfulTransaction = p.changeWealth(chargeCost); //Charge for hotel
               
                if(successfulTransaction)                   //Player successfully bought hotel
                {
                    hotelOnLot = true;                      //Hotel status is true
                    p.setNumOfHouses(p.getNumOfHouses() - 4);
                    p.setNumOfHotels(p.getNumOfHotels() + 1);
                    numHouses = 0;                          //Player returns houses
                    return true;                            //Successful transaction
                } 
            }
        }
        
        return false;                                       //Unsuccessful transaction
    }
    
    public boolean payRent(Player p, int diceVal, int numOwned)
    //PRE:  p is initialized. 
    //      diceVal >= 2 and diceVal <= 12
    //      numOwned >= 0
    //POST: FCTVAL == true if player successfully paid rent, false otherwise
    {
        int index;                                       //Index in propertyRent array
        int rent;                                        //Rent player owes
     
        if(hotelOnLot == true)
        {
            index = 5;                                   //Where rent for hotel is stored in array
        }
        else
        {
            index = numHouses;                           //Index of house
        }
     
        if (!owner.equals(p.getToken()) && !owner.equals("bank")) //The player at least one property
        {
            rent = (-1) * calcRent(p, diceVal, index);             //Calculate rent
            return p.changeWealth(rent);                  //Charge rent and return success
        }
     
        return false;                                     //Unsuccessful, player does not own lot
    }

    public int calcRent(Player p, int diceVal, int index)
    //PRE:  p is initialized
    //POST: FCTVL == Amount of rent the player owns in dollars
    {
        int rentAmt = propertyRent[index];               //Get rent for property
    
        if(owner.equals(p.getToken()))                   //Player owns lot
        {
            return 0;                                    //Return $0 when player owns lot
        }
     
        return rentAmt;                                  //Return calculated rent
    }
    
    public boolean sellHouse(Player p)
    //PRE:  p is initialized.
    //POST: FCTVAL == true if player successfully sold house back, false otherwise
    
    {
        if(numHouses >= 1 && owner.equals(p.getToken())) //Player owns property and has 1 house
       {
           numHouses--;                                  //Decrease number of houses on lot
           p.changeWealth(HOUSE_HOTEL_COST/2);           //Player gets half of buying price back
           p.setNumOfHouses(p.getNumOfHouses() - 1);     //Decrement number of houses player owns
           return true;                                  //Transaction successful
       }
        
       return false;                                     //Transaction was unsuccessful
    }
    
    public boolean sellHotel(Player p)
    //PRE:  p is initialized
    //POST: FCTVAL == true if player successfully sold hotel back, false otherwise
    {
        if(hotelOnLot == true && owner.equals(p.getToken()))  //Player owns lot and a hotel
       {
           p.changeWealth(HOUSE_HOTEL_COST/2);           //Player gets half of buying price back
           
           hotelOnLot = false;                           //No hotel on lot after selling
           p.setNumOfHotels(p.getNumOfHotels() - 1);     //Decrement number of hotels player owns
           numHouses = 4;                                //Player gets four houses back
           p.setNumOfHouses(p.getNumOfHouses() + 4);     //Add houses to player total houses
           
           
           return true;                                  //Transaction successful
       }
        
       return false;                                     //Transaction unsuccessful
    }
    
    public int getNumHousesOnLot()
    //POST: FCTVAL == number of houses on the lot
    {
        return numHouses;
    }
    
    public boolean hotelOnLot()
    //POST: FCTVAL == true if there is a hotel on lot, false otherwise
    {
        return hotelOnLot;
    }

    public String toString()
    //POST: FCTVAL == String representation of object
    {
        return super.toString() + "Price of Lot: " + price + ". Buying price of houses and hotel: "
                + HOUSE_HOTEL_COST + ". Number of houses on lot: " + numHouses +
                ". Hotel on lot: " + hotelOnLot + ". "; 
    }  
    
    public void setHotel(boolean setHotelStatus)
    //PRE:  setHotelStatus is initialized
    //POST: private data member hotelOnLot is set to setHotelStatus
    {
        hotelOnLot = setHotelStatus;
    }
    
    public void burnHouse()
    //POST: private data member numHouses is decremented by one
    {
     numHouses--;
    }
    
    public String[] getPossibleActions(Player player)
    // PRE:  player is initialized
    // POST: FCTVAL == array of options player has upon landing on
    //       this space, to be used in a menu in a user interface
    {
        String [] options = new String[7];      //String of options the user can choose
        
        Arrays.fill(options, "");               //Fills it with blank spaces; 
     
        if(owner.equals("bank"))                //Player does not own property 
        {
            options[0] = "Buy Property?";
        }
   
        options[1] = "Do nothing";              //Player decides to skip 
        
        if(player.getPropertiesIndex() > 0)  //If player owns property
            options[2] = "Buy House?";
     
        if(player.hotelCheck())                 //If any player owned properties have 4 houses
        {
            options[3] = "Buy Hotel?";
        }
     
        if(player.getNumOfHouses()>0)           //If player owns any houses for selling 
        {
            options[4] = "Sell House for half value?";
        }
        if(player.getNumOfHotels()>0)           //If player owns any hotels for selling
        {
            options[5] = "Sell Hotel for half value?";
        }
        if(!owner.equals(player.getToken()) && !owner.equals("bank"))
        {
            options[6] = "Pay Rent";
        }
        return options;                         //String of options user can do 
    }

}
         