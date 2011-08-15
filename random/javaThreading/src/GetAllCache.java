import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class GetAllCache {

	public static Map<String, Cache> getResources(String filename) throws Exception{
		try{	
			Map<String, Cache> cache = new HashMap<String, Cache>();
			BufferedReader br = new BufferedReader( new FileReader(filename));
			String strLine = "";
			StringTokenizer st = null;
			br.readLine(); // remove header
			
			//read comma separated file line by line
			while( (strLine = br.readLine()) != null)
			{
				st = new StringTokenizer(strLine, ",");
				String id = st.nextToken();
				int resourceCount = Integer.parseInt(st.nextToken());
				cache.put(id, new Cache(id, resourceCount));
			}
			return cache;
		}
		catch(Exception e){
			throw e;
		}

	}
}

/*Notes:
Very little effort was spent here. This class basically reads the text file, and creates the object based on the data.

Future Enhancements:
Encapsulate this logic - so that we are not repeating it across files. See GetAllQueries.java, GetAllUsers.java

 */