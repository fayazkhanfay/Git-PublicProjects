
public class Airport 
{
	/*We created an Array of Airport but then we store the object of airport in
	 * array 
	 * */
	private Node head;//Node class created at the bottom of this file 
	private boolean visited;//used for the dfs method
	private int airportNum;//essentially the index position
	
	public Airport(int airportNum)
	{
		head= null;//eventully will point at a Node
		visited = false;
		this.airportNum = airportNum;//index number 
		
	}
	
	public void connectFileList(Node lList)// for keeping track filenames
	{
		head= lList;
	}
	
	public Node returnNode()
	{
		return head;
	}
	
	public int returnUnvisit(Airport [] air)
	{
		/*this method will travese throught the specific index and check every Node airport
		 * but I sent array to refernece it to see if we have already been their or not
		 * if already been it will continue to traverse till either null or found unVisited*/
		Node traverse = head;
		while(traverse!= null)
		{
			
			if(air[traverse.airport].visited == false )//found not visited
				return traverse.airport;
			
			traverse= traverse.next ; 
		}
		return -999;//this is the condition in dfs method to stop searching because traversed till null
	}
	
	public void markVisit()//marks it as visited from dfs method 
	{
		visited = true;
	}
	
	public boolean isVisited()// return whether the index has been visited or not 
	{
		if (visited== true)
			return true;
		else
			return false;
	}
	
	public void markUnvisit()//used for reseting everything in the array air 
	{
		visited= false ; 
	}
	
	public int getHead()//used for the push method or link method to see if array air [i] is pointing at anything
	{
		if (head== null)
			return 1;
		else
			return 0;
	}
	
	public void link(int connectAirport)//just link it to air[i]
	{
		Node tempNode = new Node(connectAirport);
		head = tempNode; 
	}
	
	public void link (String fileName)
	{
		Node tempNode = new Node(fileName);
		head = tempNode;
	}
	
	public int testTravel(int val2)//used for testing but not acctullly used for assignemnt 
	{
		if (head.getAirport()==val2)
			return 1;
		else
			return 0;
		
	}
	
	
	public void traverse()//used for doList method. report airport and connects to by single flight 
	{
		Node tempNode = head;
		while(tempNode != null)
		{
			System.out.println("Airport "+ airportNum + " to " + tempNode.getAirport());
			tempNode = tempNode.next;
		}
	}

	public void push(int connectAirport) //to the front 
	{
		Node tempNode = new Node(connectAirport);
		tempNode.next= head;
		head =tempNode;
		
	}
	
	public void push(String filename) //to the front 
	{
		
		Node tempNode = new Node(filename);
		tempNode.next= head;
		head =tempNode;
		
	}
	public void delTraverse(int connectAirport)//used for doDelete method 
	{
		/*GARBAGE COLLECTION TAKES CARE OF EVERYTHNG. JUST DISCONNECT*/
		Node tempNode = head;
		
		if(tempNode.getAirport() == connectAirport)
		{
			head = tempNode.next;
			return;
		}
		else
			tempNode = tempNode.next;
		
		while(tempNode.next != null)//done this way so it easier to disconnext
		{
			if(tempNode.next.getAirport()== connectAirport)
			{
				tempNode.next = tempNode.next.next;//this connect to the next after that and the connection lost middle
				return;
			}
			tempNode= tempNode.next;
		}
		
		Node lastNode =head;
		
		while(lastNode.next != tempNode)//special circumstance for the last node 
		{	
			lastNode= lastNode.next;
		}
		
		lastNode.next = null;
		
		System.out.println("Airport "+ airportNum + " to " + connectAirport + " does not exist.NO DELETE ");
	}
	
	public boolean filePrevExist(String filename)//checks the link list 
	{
		Node traverse = head;
		while (traverse !=null)
		{
		
			if(traverse.filename.equals(filename) )//this is how you compare two strings !!!!
			{
				System.out.println("File previously used");
				return true;
			}
			traverse = traverse.next;
		}
		
		return false;
	}

}


class Node //WHY NO PRIVATE OR PUBLIC 
{
	int airport; //WHY NOT MAKE THIS PRIVATE //for accounting airport number 
	Node next;//carries the address of the next node or null 
	String filename;
	
	
	Node(int airport) //why am I not writitng void 
	{
		this.airport = airport;// when constructed takes in the airport number for this node 
		next = null;
	}
	
	Node (String fileName)
	{
		this.filename= fileName;
		next = null;
	}
	
	
	public int getAirport()
	{
		return airport;// sends the node number like a getter 
	}
	
	public String getFileName()
	{
		return filename;
	}
}
