package structures;

public interface PriorityQueue<T extends HeapElement> {
   void insert(T element);
   T getBest();
   T extractBest();
   boolean modifyKey(int objectIndex, double newPriority);
}
