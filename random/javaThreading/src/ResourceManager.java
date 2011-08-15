import java.util.HashMap;
import java.util.Map;


public final class ResourceManager {
    private static final ResourceManager instance = new ResourceManager();
    private ResourceManager() {}  
    private static Map< String, ResourcePool > resources = new HashMap< String, ResourcePool> ();
    
    public static ResourceManager getInstance() {
        return instance;
    }
    
    public boolean isResourceAvailable(String resourceName) {
    	return resources.containsKey(resourceName);
    }
    
    public <T> void addResource(Resource<T> r, int resourceCount) {
    	resources.put(r.getIdentity(), new ResourcePool<T>(r, resourceCount));
    }
    
    public void updateResource(final String resourceName, final int resourceCount) throws Exception{
    	if(isResourceAvailable(resourceName)){
	    Thread updateThread = new Thread ( new Thread() {
		    public void run() {	
			try {
			    resources.get(resourceName).updateResourceCount(resourceCount);
			} catch (Exception e) {
			    e.printStackTrace();
			}
		    }
    		});
	    updateThread.start();	
	}	
    }	
   
    public <T> T getResource(String resourceName) throws Exception{
	if(isResourceAvailable(resourceName))
	    return ((T) (resources.get(resourceName).getResource()));
	else
	    return null;
    }
    
    public void returnResource(String resourceName, Object resource) throws Exception{
    	if(resources.containsKey(resourceName)){
	    resources.get(resourceName).returnResource(resource);
    	} 
    }
}

/*
  Singleton Class which manages all the pools of available resources. 
  Uses ResourcePool.java for the actual semaphore logic. 

  The class takes in a Resource (Resource.java) object along with the
  maximum allowed count for that resource.
 */