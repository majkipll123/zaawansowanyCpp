namespace cpplab
{
    template<typename T>
        class vector{
        public:
            T* arr;
 
            // capacity is the total storage
            // capacity of the vector
            int capacity;
        
            // current is the number of elements
            // currently present in the vector
            int current;

        };
}