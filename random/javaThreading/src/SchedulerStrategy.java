import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class SchedulerStrategy{

    // Add new strategy through comparator. The comparator should
    // be able to prioritize all the different types of Queries
    // you have.
    private static class PriorityComparator implements Comparator<Query>{
	@Override
	    public int compare(Query query1, Query query2){
	    if(query1 == null || query2 == null)
		return -1;
	    SimpleQuery q1 = (SimpleQuery) query1;
	    SimpleQuery q2 = (SimpleQuery) query2;
			 
	    int q1Priority = q1.user.Priority;
	    int q2Priority = q2.user.Priority;
			 
	    if(q1Priority > q2Priority) {
		return -1;
	    }else if(q1Priority < q2Priority){
		return 1;
	    }else{
		return q1.createdOn.compareTo(q2.createdOn);
	    }		
	}
    }
	
    private final ResourceManager resourceManager = ResourceManager.getInstance();	

    //priority queue which contains all queries that need to be run
    private final Queue<Query> scheduledQueries = new PriorityQueue<Query>(10, new PriorityComparator());

    // contains the statuses of all the threads which are running querieres. Updated by calling prioritize.
    private final Map<Query, Future<QueryStatus> > executingQueries = new HashMap<Query, Future<QueryStatus>>();
    private ExecutorService executor = Executors.newCachedThreadPool();
	
    private final Map<String, Query> runningQueriesMap = new HashMap<String, Query>();
    private final Map<String, Query> finishedQueriesMap = new HashMap<String, Query>();
    private final Map<String, Query> scheduledQueriesMap = new HashMap<String, Query>();
	
    private Map<String, User> users;
    private Map<String, Cache> caches;
	
    //We can call the add function multiple times, and it will read the file and make appropriate changes

    //Reads user info from file, and creates appropriate resources
    private void addUsersFromFile(String filename) throws Exception{
	users = GetAllUsers.getUsers(filename);
	for(User u: users.values()){
	    if(resourceManager.isResourceAvailable(u.getIdentity())) {
		resourceManager.updateResource(u.getIdentity(), u.MaxConcurrentReports);
	    } else {
		resourceManager.addResource(new ResourceUser(u.getIdentity()), u.MaxConcurrentReports);
	    }
	}
    }
	
    //Reads Cache/Resources info from file, and creates appropriate resources
    private void addCacheFromFile(String filename) throws Exception{
	caches = GetAllCache.getResources(filename);
	for(Cache c: caches.values()) {
	    if(resourceManager.isResourceAvailable(c.getIdentity())) {
		resourceManager.updateResource(c.getIdentity(), c.ResourceCount);
	    } else {
		resourceManager.addResource(new ResourceCache(c.getIdentity()), c.ResourceCount);
	    }
	}
    }
	
    //Reads Queries from files. 
    private void addQueriesFromFile(String filename) throws Exception{
	Map<String,Query> queriesNew = GetAllQueries.getResources(filename, users);		
	for(String qId: queriesNew.keySet())
	    if(!finishedQueriesMap.containsKey(qId) && !runningQueriesMap.containsKey(qId) && !scheduledQueriesMap.containsKey(qId)) {
		scheduledQueriesMap.put(qId, queriesNew.get(qId));
	    }
	scheduledQueries.addAll(scheduledQueriesMap.values());
    }

    // Reads all the data, allocationing/updating resources as necessary. 
    private void updateInitialState() throws Exception{
	addUsersFromFile("src/UsersInfo.txt");
	addCacheFromFile("src/CacheInfo.txt");
	addQueriesFromFile("src/QueryInfo.txt");
    }

    // This method goes through all the running threads, and decides their fate.
    // After taking care of the running threads, it reads the new queries/resources state, and updates the states.
    // This method should be called before the first call the runNextScheduledQuery() in every dispatch loop
    public void prioritize() throws  Exception{
	// clear the maps, since we will decide again which threads are running etc.
	runningQueriesMap.clear();
	scheduledQueriesMap.clear();
	
	// walk through the executing threads, rescheduling the ones waiting for resources, and updating the running,finished maps
	for(Iterator<Query> i = executingQueries.keySet().iterator(); i.hasNext();){
	    Query q =  i.next();
	    if(executingQueries.get(q).isDone()) {
		if(executingQueries.get(q).get() != QueryStatus.Finished)
		    //somehting went wrong - we didn't finish so reschedule the thread
		    scheduledQueriesMap.put(q.getIdentity(), q);
		else 
		    finishedQueriesMap.put(q.getIdentity(), q);
		i.remove();
	    } else {
		// re-schedule queries which didn't get resources
		if(q.getStatus() == QueryStatus.WaitingForResources && executingQueries.get(q).cancel(true)){
		    scheduledQueriesMap.put(q.getIdentity(), q);
		    i.remove();
		} else {
		    runningQueriesMap.put(q.getIdentity(),q);
		}
	    }
	}
	
	// read new resource/query info so that the priority queue/resources are all up-to-date
	this.updateInitialState();	
    }
	
    // Execute the topmost priority query in a new thread
    public Query runNextScheduledQuery(){
	Query q = scheduledQueries.poll();
	if(q != null)
	    executingQueries.put(q, executor.submit(q));
	return q;
    }
	
    public void printRunningQueries() {
	for(Query q : runningQueriesMap.values())
	    q.printRunningStatus();
    }

    public void shutdown() {
	executor.shutdown();
    }
	
}	

/* Notes:

The class manages the prioritizing the queries, and running them in
separate threads. It defines a comparator, which decided how the tasks
are to be scheduled, and maintains the state of various threads. 

Some future enhancements: Clean up the file readers to use a single
interface/database.  Take the Strategy Parameter as a parameter
instead of defining it in this class.  I feel that the
logic/bookingkeeing for the tasks can probably be further simplified -
instead of keeping separate maps for the different states.

*/