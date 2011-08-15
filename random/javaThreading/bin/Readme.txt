Hi Ersin,

Please find the implemented solution for the queuing manager.

Some Caveats:

1)I didn't do a make file etc. since I am not very familiar with
either java make files / don't have a java environment set up. I think
you should be able to drop the source files into eclipse and run
them. I didn't use any special libraries etc. The text files must be
in the src directory, and you can keep updating them, and they should
be picked up by the dispatcher.

To update the files: You can update the User file, and the Cache file
by increasing/decreasing the number of resources.  For Queries, you
cannot re-use a query id. As long as you don't reuse a query id, you
can keep adding as many Queries as you want.  [Shortcoming: the query
id and user id should not be reused either so you can't use a user id
of 1 and have a query id of 1 because of the way resources are set up
- it can be fixed by modifying the id's on the fly when they are read]

I added a new column to the query file specifying the Cache
(Resource). Obviously, my solution can easily be modified to pick
either resource, by treating all the caches as one resource, but since
my solution is more general I am leaving it the way it is.

2)Similarly for testing, I didn't do either JUnit/user a proper
logger, since setting these up would have taken me significant
time. Since I am mostly doing C++/Perl, I don't have the java work flow
set up on my home laptop, and setting these up/getting them to work
would have taken me a fair bit of time. Testing multithreaded programs
in general is difficult, and hence setting up a logger would have been
ideal, so that when a heisenbug happens, we can at least retrace our
steps.

3) Again, I am mostly new to Java (and multithreaded programming in
general), and since you said you'll prefer a Java solution I looked
into the libraries. As such, my code might not follow the Java best
practices etc. There are no java doc style comments ( I personally
don't like them, but they seem to be the standard in the java world.)

4) I added notes to each of the source files, but I'll outline the general solution here.

The general thinking is to create resource pools for all the
constraints. Thus we create resource pools for users (concurrent
reports) and the caches. The relevant classes are ResourcePool.java,
ResourceManager.Java, Resource.Java, ResourceCache.java,
ResourceUser.java

The scheduler maintains a priority queue, and keeps track of all the
running threads. When we reprioritize - it reclaims all the threads
that are waiting for resources, reads in new resources/query
information, and adds them in the correct order to the priority
queue. We can specify the priority strategy with the help of a
comparator. (Main.java, SchedulerStrategy.java)

Then there is the Query class, which basically knows what resources it
needs, what user it belongs to and runs on its own thread. It reports
back its status through the QueryStatus enum. This helps the
dispatcher keep track of which tasks are waiting, finished, running
etc. (Query.java, SimpleQuery.java, QueryStatus.java)

There are some classes (these could be cleaned up more) which read the
text files and create User/Cache/Query objects. (GetAllUsers.java,
GetAllCache.java, GetAllQueries.java, User.java, Cache.java). These
could be cleanup up more, but in the interest of time I didn't spend
too much effort cleaning up the interface here.

Some enhancements to the original problem: By modifying the way the
semaphore is acquired (ResourcePool.java), you can configure whether
the jobs are dispatched only when the dispatcher runs, or whether we
can dispatch jobs as running jobs finish. If you use a blocking
semaphore, then we keep dispatching tasks as resources become
available, until prioritize() is called to reclaim all waiting tasks. If
you use a non-blocking semaphore, then we only dispatch if a resource
is available, and don't wait to grab a resource.

I also print our some information about when the Dispatcher starts a
new run (reprioritizes/reads in state), and when it sleeps. After it
sleeps the threads report back as they are dispatched/finished. Also
since I keep track of the resources/count, each resource is basically
treated as unique, and hence I print out the resource being used by
each query as well. Sample Output:

Running Dispatch
Dispatching Query 24 for User 5,R1 using Resource CacheA,R1
Dispatching Query 25 for User 5,R2 using Resource CacheA,R2
Dispatching Query 23 for User 1,R1 using Resource CacheA,R3
Dispatching Query 30 for User 1,R2 using Resource CacheB,R1
Dispatching Query 31 for User 1,R3 using Resource CacheB,R2
Sleeping Dispatch loop
Finished Query 31 for User 1,R3 using Resource CacheB,R2
Finished Query 30 for User 1,R2 using Resource CacheB,R1
Finished Query 24 for User 5,R1 using Resource CacheA,R1

Running Dispatch
Running Query 23 for User 1,R1 using Resource CacheA,R3
Running Query 25 for User 5,R2 using Resource CacheA,R2
Dispatching Query 26 for User 5,R1 using Resource CacheA,R1
Dispatching Query 32 for User 1,R3 using Resource CacheB,R1
Sleeping Dispatch loop
Finished Query 23 for User 1,R1 using Resource CacheA,R3
Finished Query 25 for User 5,R2 using Resource CacheA,R2

Running Dispatch
Running Query 32 for User 1,R3 using Resource CacheB,R1
Running Query 26 for User 5,R1 using Resource CacheA,R1
Dispatching Query 33 for User 5,R2 using Resource CacheB,R2
Dispatching Query 27 for User 3,R1 using Resource CacheA,R3
Dispatching Query 28 for User 3,R2 using Resource CacheA,R2
Sleeping Dispatch loop
Finished Query 26 for User 5,R1 using Resource CacheA,R1
Finished Query 33 for User 5,R2 using Resource CacheB,R2
Finished Query 27 for User 3,R1 using Resource CacheA,R3
Finished Query 32 for User 1,R3 using Resource CacheB,R1

Running Dispatch
Running Query 28 for User 3,R2 using Resource CacheA,R2
Dispatching Query 29 for User 3,R3 using Resource CacheA,R1
Sleeping Dispatch loop
Finished Query 28 for User 3,R2 using Resource CacheA,R2

Running Dispatch
Running Query 29 for User 3,R3 using Resource CacheA,R1
Shutting down
Finished Query 29 for User 3,R3 using Resource CacheA,R1


Looking forward to hearing back from you! Let me know if you encounter any issues with running the code.

Thanks,
Ani
