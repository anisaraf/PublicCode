interface Resource<T> {
    T createResource();
    String getIdentity();
}

/* 
Interface for creating different types of resources, that can be added to ResourcePool and is managed by the ResourceManager.
 */

