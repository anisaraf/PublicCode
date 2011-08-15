
public class ResourceCache implements Resource<Integer> {
	private String Name;
	private Integer Count = 0;
	
	public ResourceCache(String name) {
		Name = name;
	}
	
	public Integer createResource() {
		Count++;
		return Count;
	}
	
	public String getIdentity() {
		return Name;
	}
}

/*

A stub implementation of the Cached resource. It returns an integer,
which keeps count of how many such objects have been created. Similar
to Resource User but could be completely different!

Future enhancments: 
Some of these objects will leak if the resource count
decreases. Implement a destructor so that these resources can be
returned to the system, instead of being held indefnitely by a thread.

Add a function to do custom work on each resource.

 */
