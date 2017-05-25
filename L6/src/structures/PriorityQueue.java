package structures;

public interface PriorityQueue<T extends HeapElement> {
   void insert(T element);
   T getBest();
   T extractBest();
   void modifyKey(int objectIndex, double newPriority);
}
