//Description:Includes methods to construct objects and utilizing overloading methods.Includes
//			  data members how strong enemies are,how much strength they lose per hit, the 
//			  threshold strength level for enemies being dangerous,their vertical levels,and 
//			  whether or not they are active.Methods include for Enemy default constructor,
//			  initializer constructor,modifier that processes the effects of an enemy suffering 
//			  a single hit,two modifiers renders them inactive or active. Enemy class also 
//			  contains accessors  to get the current strength of an enemy,get the danger the 
//			  enemy poses to the player located at a given vertical level, and allows two enemies' 
//			  strengths to be compared.	

public class Enemy 
{
	private static final int THRESHOLD = 15;	//the minimum for an enemy to be a threat   
	private static final int FULLSTRENGTH = 100;//default starting for each enemy 
	private final int DAMAGE;					//Amount of strength subtracted after each hit
	private static boolean active;				//true if active, false otherwise 
	private int strength;						//Enemy strength starts at 100 and ends at 0 
	private boolean threat;						//strength >= 15 threat is true,false otherwise
	private int verticalLevel;					//location of enemies 
	
	public Enemy ()
	// POST: a default Enemy object strength is set to full, DAMAGE is set to ten, threat == true
	//		 place on vertical level 1 and is active. 
	{
		this(10,1);
	}
	
	public Enemy(int damage,int verticalLevel)
	// PRE:  damage is >= 0 
	//		 verticalLevel >= 1
	// POST: a Enemy object is created with with full strength, threat == true and active == true.
	//		 (this.damage) == damage and (this.verticalLevel) == verticalLevel. 
	{
		strength = FULLSTRENGTH;
		DAMAGE = damage;
		threat = true;
		this.verticalLevel = verticalLevel;
		active = true; 
	}
	
	public void hit()
	// POST: when an enemy is hit subtracts damage from strength and then updates strength value 
	{
		strength = strength - DAMAGE; 
	}
	
	public int strength()
	// POST: FCTVAL == current strength of enemy
	{
		return strength;
	}
	
	public void inactive()
	// POST: makes enemy inactive by setting active == false
	{
		active = false;
	}
	
	public void active()
	// POST: makes enemy active by setting active == true
	{
		active = true;
	}
	
	public int danger(int playerLevel)
	// PRE:  playerLevel >= 1
	// POST: FCTVAL == active == false returns 0
	//		 FCTVAL == strength > 15 returns strength minus vertical level; otherwise,
	//		 FCTVAL == 0;
	{
		int checkDanger = 0;         //to make sure the danger not returned is less than 0 
		
		if(active == false)
			return 0;
		
		if(strength > THRESHOLD)
		{
			checkDanger = strength-(Math.abs(playerLevel-verticalLevel));
			
			if(checkDanger >= 0)
				return checkDanger;
			else
				return 0;
		}
		else
			return 0;
	}
	
	public boolean battle(Enemy enemy)
	// PRE:  enemy is initialized
	// POST: FCTVAL == true when this.strength > enemy.strength; 
	// 		 FCTVAL == false otherwise
	{
		if(this.strength > enemy.strength )
			return true;
		else
			return false;
	}
	
	public String toString()
	// POST: FCTVAL == returns all information about object
	{	
		return "Enemy Strength: " + strength + " Damage: " + DAMAGE + " level: " + verticalLevel;		
	}
	
}
