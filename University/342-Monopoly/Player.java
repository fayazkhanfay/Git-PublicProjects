
public class Player
{
    //Data Dictionary
    private static final int NUM_OF_BOARD_POSITIONS = 40;       //Number of board positions

    private int wealth;                                         //The amount of money a player has
    private int playerPosition;                                 //The player's position on the board
    private String token;                                       //The player's token
    private Board[] properties;                               //The player's properties, array
                                                                // is indexed via propertiesIndex
    private int propertiesIndex;
    private String stringVal;                                   //String representation of all of 
                                                                //  the player's properties
    private int numOfRailroadsOwned;                            //The number of railroads the player
                                                                //  owns
    private int numOfUtilitiesOwned;                            //The number of utilities the player
                                                                //  owns
    
    private int numOfHotels;                                    //The amount of hotels that the player
                                                                //  owns
    private int numOfHouses;                                    //The amount of hotels that the player
                                                                //  owns

    public Player()
    //POST: A default Player object is contructed with moneyAmt set to 1500 (the starting amount of
    //      money for each player in the game), playerPosition set to 0, token set to 0, and 
    //      allocating the properties array
    {
        wealth = 1;
        playerPosition = 0;
        token = " ";
        properties = new Board[NUM_OF_BOARD_POSITIONS];
        stringVal = " ";
        numOfUtilitiesOwned = 0;
        numOfRailroadsOwned = 0;
        propertiesIndex = 0;

    }

    public Player(String token)
    //PRE:  token >=0
    //POST: A Player object is constructed with private class member token being set to token
    {
        this();
        this.token = token;
    }

    public void movePosition(int diceValue)
    //PRE:  diceValue >=2 && diceValue <= 12 && diceValue is the sum of both dice in game
    //POST: The Player's position is updated by moving it ahead by the sum of the dice values
    {
        playerPosition += diceValue;
        
        if(playerPosition >= 40)
        {
            playerPosition -= 40;
        }
    }

    public boolean changeWealth(int changeValue)
    //PRE:  changeValue is initialized
    //POST: FCTVAL == true if the game should continue or false if it should not (player has become
    //      bankrupt)
    {  
        wealth += changeValue;

        return (wealth >= 0) ? true : false;
    }

    public boolean buyProperty(int cost, int propertyBoardPosition, Board[] properties)
    //PRE:  cost > 0 && propertyBoardPosition > 0 && propertyBoardPosition <= 40 && the property on 
    //      propertyBoardPosition is not owned by another player
    //POST: properties is updated to indicate that the player owns the property on the board position
    //      FCTVAL == true if the purchase was successful, false if it was not
    {
        if((wealth - cost) > 0)
        {
            wealth -= cost;
            this.properties[propertiesIndex] = ((Property)(properties[propertyBoardPosition]));
            propertiesIndex++;
            return true;
        }
        else
        {
            return false;
        }

    }

    public void addRailRoad()
    //POST: FCTVAL == private class member numOfRailroadsOwned is increased by one
    {
        numOfRailroadsOwned++;
    }

    public void addUtility()
    //POST: FCTVAL == private class member numOfUtilitiesOwned is increased by one
    {
        numOfUtilitiesOwned++;
    }

    public Board[] getPropertiesArray()
    {
        return properties;
    }

    public String getProperties()
    //PRE:  properties is initialized
    //POST: FCTVAL == string representation of all of the Player's properties and the address
    //      of the property on the board
    {               
        stringVal = " ";                  //Clear out stringVal from previous calls to getProperties
        
        //Iterate through the private properties array, printing out all of the property names
        for(int i = 0; i < propertiesIndex; i++)
        {
            if(stringVal == " ")                    //If the stringVal is empty, then we haven't stored any
            {                                       //  properties yet
                stringVal += properties[i].name + "[" + properties[i].address + "]";
            }

            else                                    //If there are any additional properties to be printed out,
            {                                       //  then prepend the comma

                stringVal += ", " + properties[i].name + "[" + properties[i].address + "]";
            }
        }

        return stringVal;
    }

    public String toString()
    //PRE: properties is initialized
    //POST: FCTVAL == string representation of all of the Player object's attributes
    {
        stringVal = getProperties();
        return "Player's Token:" + token + "\n" + "Player's Wealth: " + wealth + "\n" + 
                "Player's position: " + playerPosition + "\n" + 
                "Number of Railroads this player owns: " + numOfRailroadsOwned + "\n" +
                "Number of utilities this player owns: " + numOfUtilitiesOwned + "\n" +
                "Number of houses this player owns: " + numOfHouses + "\n" +
                "Number of hotels this player owns: " + numOfHotels + "\n" +
                "Properties owned by player: " + stringVal + "\n";

    }

    public String getWealthAndPosition()
    //POST: FCTVAL == string representation of private class members toke, playerPosition, and wealth
    {
        return "Player: " + token + " Location: " + playerPosition + " Wealth: " + wealth + "\n";
    }

    public int getWealth()
    //POST: FCTVAL == private class member wealth
    {
        return wealth;
    }

    public int getPlayerPosition()
    //POST:  FCTVAL == private class member playerPosition
    {
        return playerPosition;
    }

    public String getToken()
    //POST: FCTVAL == private class member token
    {
        return token;
    }

    public int getNumOfRailRoads()
    //POST: FCTVAL == private class member numOfRailroadsOwned
    { 
        return numOfRailroadsOwned;
    }

    public int getNumOfUtilities()
    //POST: FCTVAL == private class member numOfUtilitiesOwned
    {
        return numOfUtilitiesOwned;
    }

    public int getNumOfHouses() 
    //POST: FCTVAL == number of houses player owns
    {
        return numOfHouses;
    }

    public void setNumOfHouses(int numOfHouses)
    //PRE: numOfHouses >= 0
    //POST: Sets class member numOfHouses to numofHouses
    {
        this.numOfHouses = numOfHouses;
    }
    public int getNumOfHotels() 
    //POST: FCTVAL == number of hotels player owns
    {
        return numOfHotels;
    }

    public void setNumOfHotels(int numOfHotels)
    //PRE: numOfHotels >= 0
    //POST: Sets class member numOfHotels to numofHotels
    {
        this.numOfHotels = numOfHotels;
    }

    public int getPropertiesIndex()
    //POST: FCTVAL == private data member 
    {
        return propertiesIndex;
    }

    public boolean hotelCheck()
    //POST: FCTVAL == Returns true if any player owned properties has 4 houses else false 
    {
        int trav = 0;                   //used to traverse through player owned propeties 
        
        while(trav < propertiesIndex)   //traverse till number of properties 
        {
      	  if(properties[trav] instanceof Lot)
      	  {
      		  if(((Lot) properties[trav]).getNumHousesOnLot() ==4) 
      			  return true;
      	  }
      	  trav++;
        }
        
        return false;                   //none of the player owned properties have 4 houses 
    }
}