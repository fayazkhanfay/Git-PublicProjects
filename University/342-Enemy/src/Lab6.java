//Programmer: Fayaz Khan
//Assignment: Lab 5 
//Date:       September 29, 2015
//Description:Program uses test drivers to test methods in Enemy class.			

public class Lab6
{
	
	public static void main(String[] args) 
	{
		
		Enemy enemy1 = new Enemy();  	
		Enemy enemy2 = new Enemy(5,2);
		Enemy enemy3 = new Enemy(85,3);
		
		
		System.out.println("enemy1: " + enemy1.toString());
		System.out.println("enemy2: " + enemy2.toString());
		System.out.println("enemy3: " + enemy3.toString());
		
		enemy1.hit();
		enemy2.hit();
		enemy3.hit();
		
		System.out.println("enemy1, after hit: " + enemy1.toString());
		System.out.println("enemy2, after hit: " + enemy2.toString());
		System.out.println("enemy3, after hit: " + enemy3.toString());
		
		enemy1.inactive();
		
		System.out.println("enemy1, strength: " + enemy1.strength());
		System.out.println("enemy1 inactive, danger: " + enemy1.danger(1));
		
		enemy2.active();
		
		System.out.println("enemy2, strength: " + enemy2.strength());
		System.out.println("enemy2 level 2 active, danger: " + enemy2.danger(12));
		
		System.out.println("enemy3,strength:" + enemy3.strength() + " danger: " + enemy3.danger(9));
		
		System.out.println("enemy1 after active method, danger: " + enemy1.danger(1));
		
		if(enemy1.battle(enemy2))
			System.out.println("Enemy1 is stronger than Enemy2");
		else
			System.out.println("Enemy2 is stronger than Enemy1");
		
		if(enemy3.battle(enemy2))
			System.out.println("Enemy3 is stronger than Enemy3");
		else
			System.out.println("Enemy2 is stronger than Enemy3");
			
	}

}
