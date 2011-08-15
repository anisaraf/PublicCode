
public class User {
	public String UserId;
	public int Priority;
	public int MaxConcurrentReports;
	
	User(String id, int p, int maxReports){
		UserId = id;
		Priority = p;
		MaxConcurrentReports = maxReports;
	}
	
	public String getIdentity(){
		return UserId;
	}
}
