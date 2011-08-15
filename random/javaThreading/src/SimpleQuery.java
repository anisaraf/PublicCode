import java.util.Date;
import java.util.Random;


public class SimpleQuery implements Query {

    private int priority;
    private String id;
    private Resource<Integer> resource;
    private QueryStatus status = QueryStatus.OnScheduler;
    private ResourceManager resourceManager = ResourceManager.getInstance();
    private Integer userResource = null;
    private Integer queryResource = null;
    
    // needed to determing priority
    public User user;
    public Date createdOn;
    
    public SimpleQuery(String identity, Date date, User u, Resource<Integer> res){
    	user = u;
    	resource = res;
    	id = identity;
        createdOn = date;
    }
    
    // gets all the resources required for this query to run.
    private boolean getResources() throws Exception{	
    	try {
	    userResource = (Integer) resourceManager.getResource(user.getIdentity());
	    queryResource = (Integer) resourceManager.getResource(resource.getIdentity());
	    if(userResource == null || queryResource == null){
		releaseResources();	
		return false;
	    }
	    return true;
	} catch (Exception e) {
	    releaseResources();
	    throw e;
	}
    }	
    
    //releases the resources held by this query
    private synchronized void releaseResources(){
    	try {
	    resourceManager.returnResource(user.getIdentity(), userResource);
	    userResource = null;
	    resourceManager.returnResource(resource.getIdentity(), queryResource);
	    queryResource = null;
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
    public QueryStatus call() {
    	try {

	    //get Resources 
	    status = QueryStatus.WaitingForResources;
	    boolean resourceAcquired = this.getResources();
    		
	    if(!resourceAcquired){
		return status;
	    }
   
	    status = QueryStatus.Running;
	    System.out.println(String.format("Dispatching Query %s for User %s,R%s using Resource %s,R%s", id, user.getIdentity(), userResource, resource.getIdentity(), queryResource));
    		
	    //simulate work. We have the resource objects as well so we could simulate work on them to if needed
	    Random random = new Random();
	    Thread.sleep(random.nextInt(10000 + 100));
    		
	    System.out.println(String.format("Finished Query %s for User %s,R%s using Resource %s,R%s", id, user.getIdentity(), userResource, resource.getIdentity(), queryResource));
	    releaseResources();
	    status = QueryStatus.Finished;
	    return status;
    	} catch (Throwable e) {
	    // Thread was interupped (in all likelihood by the dispatcher)
	    releaseResources();
	    if(status != QueryStatus.WaitingForResources){
		System.out.println(String.format("Killed Query %s for User %s using Resource %s", id, user.getIdentity(), resource.getIdentity()));	
	    } 
	    return status;
    	} 
    }

    public String getIdentity(){
	return id;
    }
	
    public QueryStatus getStatus() {
	return status;
    }
	

    public void printRunningStatus() {
	System.out.println(String.format("Running Query %s for User %s,R%s using Resource %s,R%s", id, user.getIdentity(), userResource, resource.getIdentity(), queryResource));
    }	
}



/*
Implements the logic for a query. The query is mostly self-contained;
It is responsible for acquiring the needed resources, and setting its
status to report back to the dispatcher on its state, when it is interuppted.

Potential pitfalls: If a query doesn't set its status correctly, it
might keep getting rescheduled / never run. Some enhancements to make
the dispatcher more intelligent/ different queriers less error-prone
should be considered
 */
