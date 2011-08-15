import java.io.BufferedReader;
import java.io.FileReader;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class GetAllQueries {

	public static Map<String, Query> getResources(String filename, Map<String, User> users) throws Exception{
		try{	
			Map<String, Query> queries = new HashMap<String, Query>();
			BufferedReader br = new BufferedReader( new FileReader(filename));
			String strLine = "";
			StringTokenizer st = null;
			br.readLine(); // remove header
			
			//read comma separated file line by line
			while( (strLine = br.readLine()) != null)
			{
				st = new StringTokenizer(strLine, ",");
				String uid = st.nextToken();
				String qid = st.nextToken();
				DateFormat df = new SimpleDateFormat("MM/DD/yyyy HH:mm:ss");	
				Date createdOn = df.parse(st.nextToken());
				Resource<Integer> r = new ResourceCache(st.nextToken());
				queries.put(qid, new SimpleQuery(qid, createdOn, users.get(uid), r));
			}
			return queries;
		}
		catch(Exception e){
			throw e;
		}

	}
}


/*Notes:
Very little effort was spent here. This class basically reads the text file, and creates the object based on the data.

Future Enhancements:
Encapsulate this logic - so that we are not repeating it across files. See GetAllCaches.java, GetAllUsere.java

 */