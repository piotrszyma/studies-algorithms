package structures;

public class HeapElement<T> implements Element<T> {
    private T value;
    private double priority;

    public HeapElement(T value, double priority) {
        this.value = value;
        this.priority = priority;
    }

    @Override
    public T getValue() {
        return value;
    }

    @Override
    public double getPriority() {
        return priority;
    }

    @Override
    public void setPriority(double priority) {
        this.priority = priority;
    }

    @Override
    public void setValue(T value) {
        this.value = value;
    }
}
