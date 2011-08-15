import java.util.concurrent.Callable;

public interface Query extends Callable<QueryStatus>{
	QueryStatus getStatus();
	String getIdentity();
	void printRunningStatus();
}


/* Note
   All queries that are executed must implement this interface. 
 */