import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class Main {
	
	private static final SchedulerStrategy s = new SchedulerStrategy();
	private static final int TimeBetweenDispatchms = 5000;
	
	public static boolean dispatch() throws Exception {
		boolean dispatched = false;;
		System.out.println("\nRunning Dispatch");
		s.prioritize();
		s.printRunningQueries();
		while(s.runNextScheduledQuery() != null){
			dispatched = true;
			Thread.sleep(10);
		}
		return dispatched;
	}
	
	public static void main(String[] args) throws Exception {
		while(dispatch()){
			System.out.println("Sleeping Dispatch loop");
			Thread.sleep(TimeBetweenDispatchms);
		}
		s.shutdown();
		System.out.println("Shutting down - no more tasks will be dispatched.");
	}
}

/* Notes:

Implements the main dispatcher loops. The dispatcher will keep running
as long as there is something to schedule. As soon as it runs out of
things to schedule and all the current tasks have finished running the
dispatcher will exit. You can update the text files, and the
information will be reflected in the dispatcher as long as the
dispatcher hasn't finished running all existing queries.

*/