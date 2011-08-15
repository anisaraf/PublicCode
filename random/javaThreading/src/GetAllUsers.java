import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class GetAllUsers {

	public static Map<String, User> getUsers(String filename) throws Exception{
		try{	
			Map<String, User> users = new HashMap<String, User>();
			BufferedReader br = new BufferedReader( new FileReader(filename));
			String strLine = "";
			StringTokenizer st = null;
			br.readLine(); // remove header
			
			//read comma separated file line by line
			while( (strLine = br.readLine()) != null)
			{
				st = new StringTokenizer(strLine, ",");
				String id = st.nextToken();
				users.put(id, new User(id,Integer.parseInt(st.nextToken()),Integer.parseInt(st.nextToken())));
			}
			return users;
		}
		catch(Exception e){
			throw e;
		}

	}
}

/*Notes:
Very little effort was spent here. This class basically reads the text file, and creates the object based on the data.

Future Enhancements:
Encapsulate this logic - so that we are not repeating it across files. See GetAllCaches.java, GetAllQueries.java

 */