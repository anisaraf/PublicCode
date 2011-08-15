Queuing System:

We have ad networks (users) who want to run reports to figure out how much they have spent, number of impressions, clicks, conversions etc. These reports are essentially queries against a data ware house/database (resource). We have seen that during peak hours (beginning of the day) when all of them try to run their reports, the load on the resource becomes bottle neck and not only results in slow response, but also affects other jobs like loading & aggregation running against the same resource. So, what we would like is some sort of queuing so that at any given point of time only a certain number of concurrent reports are allowed to run.

Constraints:
- Each user has a priority assigned to them (1- 100), default priority being 5
- Each user can run at max, 'x' reports concurrently
- Each resource has max capacity for 'y'

Setup:
- For user info, a table or file which looks like:

UserId     Priority maxConcurrentReports
1               10     3
5               20     2
3               05     5

- For resource capacity, a table or file which looks like:

ResouceId     Capacity
CacheA          3
CacheB          2

- Simulate "work" on each resource. For ex: just sleep for a some time in a thread

- The distribution of outstanding report queries to a resource should happen with according to some strategy which should be easily pluggable. For this assignment, we want it to be priority based. So, the user with highest priority gets to run first. If the priority is same then earliest created one should run first, if priority & created_on are same either one can go - doesn't matter

- Initial state:
UserId     QueryId     createdOn
1               23               04/11/2011 10:00:00
5               24               04/11/2011 10:00:00
5               25               04/11/2011 10:00:01
5               26               04/11/2011 10:00:02
3               27               04/11/2011 10:00:03
3               28               04/11/2011 10:00:04
3               29               04/11/2011 10:00:05
1               30               04/11/2011 10:00:01
1               31               04/11/2011 10:00:02
1               32               04/11/2011 10:00:03
5               33               04/11/2011 10:00:04
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

