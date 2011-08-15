
public class Cache {
	public String CacheId;
	public int ResourceCount;
	
	Cache(String id, int resourceCount){
		CacheId = id;
		ResourceCount = resourceCount;
	}
	
	public String getIdentity(){
		return CacheId;
	}
}
