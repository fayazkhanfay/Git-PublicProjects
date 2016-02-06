
public class Cube extends ThreeDimensionalShape
{
	protected double edge; 			//Length of any edge of the cube

	public Cube(String name, double x, double y, double z, double edge) 
	//PRE:  name, x, y, z and edge are initialized 
	//POST: A Cube object located at (x,y,z) with name and edge is created 
	{
		super(name, x, y, z);
		this.edge = edge;
	}
	
	public String toString()
	// POST: FCTVAL == string representation of the Cube
	{
		return super.toString() + " ,edge: " + edge;  
	}
}
