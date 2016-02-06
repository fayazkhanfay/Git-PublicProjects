import java.util.Arrays;

public class TaxSquare extends Board
{
 public TaxSquare()
 //POST: A default TaxSquare object address set to 0 and name set to "" 
 {
  super(0,"");
 }

 public TaxSquare(int location, String name)
 //PRE: location >= 0 and location is initialized, name is initialized 
 //POST: An object is created 
 {
  super(location, name);
 }
 
 
 public String toString()
    //POST: FCVAL == returns string representation of object
    {
     return super.toString();
    }
 
 
 @Override
 public boolean payRent(Player p,int diceValue, int numbOwned) 
 //PRE: Player p is initialized, 2 >= diceValue <=12  and numbOwned > 0
 //POST: FCTVAL == if player is on Income Tax or Luxury Tax will return true else will be false 
 {
  if(!p.changeWealth(0))  //checks for bankrupt
   return false;
  
  if(this.address==4)    //Income Tax
   return p.changeWealth(-75);
  
  if(this.address == 38)  //Luxury Tax
   return p.changeWealth(-200);
  
  return false;    //Return false if neither on Income tax or luxury tax
 }
 
 @Override
 public String[] getPossibleActions(Player player) 
 // PRE:  player is initialized
 // POST: FCTVAL == array of options player has upon landing on
 //       this space, to be used in a menu in a user interface
 {
  String [] options = new String[7];   //String of options the user can choose
        
     Arrays.fill(options, "");               //fills it with blank spaces; 
   
     options[1] = "Do nothing";    //Player decides to skip 
     
     if(player.getPropertiesIndex() > 0)  //if player owns property
         options[2] = "Buy House?";  
     
     if(player.hotelCheck())     //if any player owned propeties have 4 houses
      options[3] = "Buy Hotel?";
     
     if(player.getNumOfHouses()>0)   //if player owns any houses for selling 
      options[4] = "Sell House for half value?";
    
     if(player.getNumOfHotels()>0)   //if player owns any hotels for selling 
      options[5] = "Sell Hotel for half value?";
     
     options[6]= "Pay Rent";
     return options;       //String of options user can do 
 }
}
