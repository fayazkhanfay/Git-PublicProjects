import java.util.Arrays;

public class CornerSquare extends Board
{
 public CornerSquare()
 //POST: A default CornerSquare object address set to 0 and name set to "" 
 {
  super(0,"");
 }

 
 public CornerSquare(int location, String name)
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
 public boolean payRent(Player p,int diceValue, int numbOwmed) 
 //PRE: Player p is initialized, 2 >= diceValue <=12  and numbOwned > 0
 //POST: FCTVAL == if player pass Go corner will return true and receive $200, else will be false 
 { 
              //Nothing happens with Jail and free parking
  if(this.address >= 0 && this.address <= 11)   //Go corner receives $200 
   return p.changeWealth(200);
  else
   return false;         //Did not pass Go and does not receive $200
 }

 @Override
 public String[] getPossibleActions(Player player) 
 // PRE:  player is initialized
    // POST: FCTVAL == array of options player has upon landing on
    //       this space, to be used in a menu in a user interface
 {
  String [] options = new String[7];    //String of options the user can choose
  
  Arrays.fill(options, "");      //fill array with blank spaces
  
  return options;         //String of options user can do 
 }
 
 
}