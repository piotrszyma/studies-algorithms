package structures;

public interface Element<T> {
    T getValue();
    double getPriority();
    void setPriority(double priority);
    void setValue(T value);
}
