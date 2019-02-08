
public class ThreeDimensionalShape extends Shape
{
	protected double x; 		// x coordinate of a Three dimensional shape
	protected double y;			// y coordinate of a Three dimensional shape
	protected double z;			// z coordinate of a Three dimensional shape
	
	public ThreeDimensionalShape(String name, double x, double y, double z)
	// PRE:  name, x, y, and z are initialized 
	// POST: An instance is of ThreeDimensionalShape has been created. It
	//		 is located at (x, y, z) and named name 
	{
		SetName(name);
		
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public String toString()
	// POST: FCTVAL == string representation of the ThreeDimensionalShape object
	{
		return super.toString() + " Located: " + x + " ," + y + ", " + z;  
	}
	
}
