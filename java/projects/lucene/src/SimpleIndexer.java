package lucene;
import org.apache.lucene.util.Version;
import org.apache.lucene.document.Field;

import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.document.Document;

import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.store.SimpleFSDirectory;

import org.apache.lucene.analysis.standard.StandardAnalyzer;

import java.io.FileReader;
import java.io.IOException;
import java.io.File;

public class SimpleIndexer {
    public static void main(String[] args) throws Exception{
	if(args.length != 2){
	    throw new Exception("Usage: java " + SimpleIndexer.class.getName() + "<index dir> <data dir>");
	}
	String indexDir = args[0];
	String dataDir = args[1];
	long start = System.currentTimeMillis();
	SimpleIndexer indexer = new SimpleIndexer(indexDir);
	int numIndexed = indexer.index(dataDir);
	indexer.close();
	long end = System.currentTimeMillis();    

	System.out.println("Indexing " + numIndexed + " files took " + (end - start) + " milliseconds");
	
    }

    private IndexWriter writer;
    
    public SimpleIndexer(String indexDir) throws IOException {
	Directory dir = new SimpleFSDirectory(new File(indexDir), null);
	writer = new IndexWriter(dir , new StandardAnalyzer(Version.LUCENE_CURRENT) , true , IndexWriter.MaxFieldLength.UNLIMITED);
    }

    public void close() throws IOException {
	writer.close();
    }

    public int index(String dataDir) throws Exception {
	File[] files = new File(dataDir).listFiles();
	for (int i = 0; i < files.length ; i++) {
	    File f = files[i];
	    if(!f.isDirectory() && !f.isHidden() && f.exists() && f.canRead() && acceptFile(f) ) {
		indexFile(f);
	    }  
	}

	return writer.numDocs();
    }

    protected boolean acceptFile(File f){
	return f.getName().endsWith(".tt");
    }

    protected Document getDocument(File f) throws Exception {
	Document doc = new Document();
	doc.add(new Field("contents", new FileReader(f)));
	doc.add(new Field("filename", f.getCanonicalPath(), Field.Store.YES, Field.Index.NOT_ANALYZED));;
	return doc;
    }

    private void indexFile(File f) throws Exception {
        System.out.println("INdexing " + f.getCanonicalPath());
	Document doc = getDocument(f);
	if(doc!=null)
	    writer.addDocument(doc);
    }

    
	
    
}