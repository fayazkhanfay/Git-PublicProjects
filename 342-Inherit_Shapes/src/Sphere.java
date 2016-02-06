
public class Sphere extends ThreeDimensionalShape
{
	protected double radii; 			//the length of radii of the Sphere
	
	public Sphere(String name, double x, double y, double z, double radii) 
	//PRE:  name, x, y, z and radii are initialized 
	//POST: A Sphere object located at (x,y,z) with name and radii is created 
	{	
		super(name, x, y, z);

		this.radii = radii;
	}
	
	public String toString()
	// POST: FCTVAL == string representation of the Cube
	{ 
		return super.toString() +",radii: " + radii;  
	}
		
}
