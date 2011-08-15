import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Semaphore;

public class ResourcePool<T> {
    private int totalResources;
    private final Semaphore sem;
    private final Queue<T> resources = new ConcurrentLinkedQueue<T>();
    private final Resource<T> resourceCreator;
    
    public ResourcePool(Resource<T> resourceClass, int resourceCount) {
    	totalResources = resourceCount;
    	resourceCreator = resourceClass;
    	sem = new Semaphore(totalResources,true);
    }

    public void updateResourceCount(int newCount) throws Exception{
	if(newCount > totalResources){
	    sem.release(newCount - totalResources);
	    totalResources = newCount;
	} else {
	    //get resoruce till we succeed - we will never release these
	    while(totalResources > newCount){
		if(getResource() != null);
		totalResources--;
	    }
	}
    }
  
    public T getResource()
	throws Exception {

	// First, get permission to take or create a resource
	boolean acquiredResource = true;
    
	//uncomment sem.acquire() and comment sem.tryAcquire() for intelligent dispatch
	acquiredResource = sem.tryAcquire();
	//sem.acquire();
   
	if(!acquiredResource){
	    return null;
	}
	// Then, actually take one if available...
	T res = resources.poll();
	if (res != null)
	    return res;

	// ...or create one if none available
	try {
	    return createResource();
	} catch (Exception e) {
	    // Don't hog the permit if we failed to create a resource!
	    sem.release();
	    throw e;
	}
    }

    private T createResource() {
	return resourceCreator.createResource();
    }

    public void returnResource(T res) {
	if(res != null) {
	    resources.add(res);
	    sem.release();
	}
    }

}


/* Notes:
   Resources Used:
   http://www.javamex.com/tutorials/synchronization_concurrency_semaphore2.shtml

   Usage: Should not really be used directly. Used by the
   ResourcesManager.java which manages the interface exposed for
   normal usage.

   By chaging the way the semaphore is acquired, you can customize
   whether you want queries to be dispatched only when the dispatcher
   runs, or as soon as resources are available. If you use the
   blocking call sem.acquire(), then queries are scheduled as soon as
   resources are available. If you use the non-blocking version,
   queries are scheduled only when the dispatcher runs

   Implementation of a resource pool. The class allows you to
   create/update resource pool. When updating resource pools, if the
   number of resources decrease, then the resource objects created by
   the resourceCreator is randomly taken from the queue and never returned.

   Future Enhnacements:
   Destroy those objects created by the resourceCreator when no longer needs.
*/