
public class Lab07 
{

	public static void main(String[] args) 
	{
		Shape[] shape= new Shape[4];

		shape[0] = new Cube("Cube", 5.0,5.0,5.0,5.0);
		
		shape[1] = new Sphere("Sphere",10,10,10,10);
		
		shape[2] = new ThreeDimensionalShape("TreeDimensionalShape", 20,20,20);
		
		shape[3] = new Shape();
		
		System.out.println(shape[0].toString());
		System.out.println(shape[1].toString());
		System.out.println(shape[2].toString());
		System.out.println(shape[3].toString());
		
	}

}
