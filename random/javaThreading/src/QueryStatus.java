
public enum QueryStatus {
	OnScheduler,
	WaitingForResources,
	TimedOut,
	Running,
	Finished,
	Aborted
}

/*
  Enum for the different status that a Query reports back the the dispatcher.
 */