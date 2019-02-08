import java.lang.Math;

public class God 
{
    public static String heTakethAndHeGiveth(Player aPlayer)
    //PRE:  aPlayer is instantiated and the player's wealth > 0
    //POST: aPlayer's wealth is reduced or increased by a random number between the negative value
    //      of the player's current wealth and the player's current wealth
    {
        int moneyAmtChanged;                  //The amount of money the God class will give or take
        int moneyMultiplier;      //The number that moneyAmtChanged should be multiplied by
                  
        
        moneyAmtChanged = 0;
        moneyMultiplier = 1;
        
        //This ensures that this class will always use a non-zero number for moneyAmtChanged
        while(moneyAmtChanged == 0)
        {
         moneyAmtChanged = (int)(1 + Math.random() *aPlayer.getWealth());
         moneyMultiplier = ((int)(1+ Math.random() * 10) %2 == 0) ? 1 : -1;
         moneyAmtChanged *= moneyMultiplier;
       
        }

        aPlayer.changeWealth(moneyAmtChanged);

        if(moneyAmtChanged > 0)                      //If moneyAmtChanged > 0, return a message that
        {                                            // he gave money
            return "God giveth: $" + moneyAmtChanged;
        }

        else                                         //If not, return the message that he took money
        {
            return "God taketh: $" + (-1 * moneyAmtChanged);
        }

    }

    public static String heBurneth(Player [] players, Board [] properties)
    //PRE:  players is initialized, properties is initialized
    //POST: 
    {
        int arraySize;                      //size of the players array
        int selectVictim;                   //array index of player to burn
        boolean aPlayerHasABuilding;        //A check to see if a player has a building.  If not, 
                                            //  just return

        Player[] playersWithBuildings;      //Array to store the players that have buildings
        int playersWithBuildingsIndex;      //Index to keep track of the next free slot in 
                                            //  playersWithBuildings array

        int numOfPlayersProperties;         //Number to store the number of properties the player owns

        Board[] playersProperties;          //Array to store the players' properties


        arraySize = players.length;

        aPlayerHasABuilding = false;
        playersWithBuildings = new Player[arraySize];
        playersWithBuildingsIndex = 0;

        //Check to see if there's a player that actually has a house or a hotel
        for(int i = 0; i < arraySize && players[i] != null; i++)
        {
            if(players[i].getNumOfHouses() > 0 || players[i].getNumOfHotels() > 0)   //If so, add them
            {                                                                        //to the 
                aPlayerHasABuilding = true;                                          //playersWithBuildings 
                playersWithBuildings[playersWithBuildingsIndex] = players[i];        //array
                playersWithBuildingsIndex++;       
            }
        }



        if (aPlayerHasABuilding == true)     //If there's a player that has a building, burn 
        {

            selectVictim = (int)(Math.random() * playersWithBuildingsIndex);  //Select a victim based 
                              // on the number of Players
                              // that have buildings
            
            numOfPlayersProperties = players[selectVictim].getPropertiesIndex(); //Get how many properties
                              // that victim player owns
            
            playersProperties = players[selectVictim].getPropertiesArray().clone(); //Copies the properties
                              // from the Player class

            if(players[selectVictim].getNumOfHotels() > 0)        //Vengeful God always goes for 
            {                                                     // the most expensive property first

             //Go to the victim player array and reduce the number of hotels he has
                players[selectVictim].setNumOfHotels(players[selectVictim].getNumOfHotels()-1);

                //Iterate through the player's properties array, looking for a hotel to burn
                for(int i = 0; i < numOfPlayersProperties; i++)
                {
                    //Find which property has the hotel
                    if(((Lot)playersProperties[i]).hotelOnLot() == true)
                    {
                        ((Lot)properties[((Lot)playersProperties[i]).getAddress()]).setHotel(false);
                        return "Player "+selectVictim+"The Lord hath burned thy hotel. Go in peace.\n";
                    }

                }

            }
            
            else             //God will destroy one of the houses
            {
             players[selectVictim].setNumOfHouses(players[selectVictim].getNumOfHouses()-1);
             
             //Iterate through the player's properties, looking for a house to burn
                for(int i = 0; i < numOfPlayersProperties; i++)
                {
                    //Find which property has the houses
                    if(((Lot)playersProperties[i]).getNumHousesOnLot() > 0)
                    {
                        ((Lot)properties[((Lot)playersProperties[i]).getAddress()]).burnHouse();
                        return "Player "+selectVictim+" The Lord hath burned one of thy houses. Go in peace.\n";
                    }

                }
            
            }

        }
        
        return "The Lord has decided to be merciful.\n";
    }
}