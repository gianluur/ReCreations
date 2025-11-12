// @file vector.hpp

#pragma once

#include "utilities/types.h"
// #include "result.hpp" // Rimosso
#include "memory.hpp"
#include <stddef.h> // Per nullptr

// @brief The status codes for operations within the Vector class.
enum class VectorStatus: int8 {
    OK = 1,
    ALLOCATION_ERROR = 0,
    OUT_OF_BOUNDS_ERROR = -1,
    EMPTY_VECTOR_ERROR = -2,
    UNINITIALIZED_ERROR = -3, // Aggiunto per l'errore di inizializzazione nel costruttore
};

// @brief A contiguous growable array type that manages its own memory for storing elements.
// @param T The type of elements stored in the vector.
template <typename T>
class Vector {
public:
    // === Constructor & Deconstructor ===

    // @brief Default constructor. Creates an empty vector with zero capacity.
    Vector() = default;

    // @brief Convenience constructor that attempts to initialize the Vector.
    // @param initial_capacity The starting number of elements the vector can hold.
    // Note: Errors are stored internally and must be checked with isInitialized().
    Vector<T>(const uint64 initial_capacity);

    // @brief Destructor. Frees the memory allocated for the vector's items.
    ~Vector();

    // === Disable copy semantics ===

    // @brief Deleted copy constructor. Vector objects are non-copyable.
    Vector(const Vector&) = delete;

    // @brief Deleted copy assignment operator. Vector objects are non-copyable.
    Vector& operator=(const Vector&) = delete;

    // === Enable move semantics ===

    // @brief Move constructor. Transfers ownership of resources (items, size, capacity) from another Vector.
    // @param other The Vector to move resources from.
    Vector(Vector&& other) noexcept;

    // @brief Move assignment operator. Transfers ownership of resources from another Vector, deallocating current resources first.
    // @param other The Vector to move resources from.
    // @return A reference to the current Vector object.
    Vector& operator=(Vector&& other) noexcept;

    // === Public Methods ===

    // @brief Appends an element to the end of the vector. Triggers a reallocation if capacity is reached.
    // @param element The element to be added.
    // @return A VectorStatus object indicating success (OK) or failure (ALLOCATION_ERROR if resize fails).
    VectorStatus push(T element); 

    // @brief Removes the last element of the vector and copies it into 'out_element'.
    // @param out_element A reference where the popped element will be stored.
    // @return A VectorStatus object indicating success (OK) or failure (EMPTY_VECTOR_ERROR).
    VectorStatus pop(T& out_element);

    // @brief Inserts an element at a specified index, shifting subsequent elements.
    // @param index The position where the element should be inserted.
    // @param element The element to be inserted.
    // @return A VectorStatus object indicating success (OK) or failure (OUT_OF_BOUNDS_ERROR or ALLOCATION_ERROR).
    VectorStatus insert(uint64 index, T element);

    // @brief Removes the element at a specified index and copies it into 'out_element', shifting subsequent elements back.
    // @param index The position of the element to remove.
    // @param out_element A reference where the removed element will be stored.
    // @return A VectorStatus object indicating success (OK) or an error status on failure (OUT_OF_BOUNDS_ERROR).
    VectorStatus remove(uint64 index, T& out_element);

    // @brief Gets the element at a specified index.
    // @param index The index of the element to retrieve.
    // @return A pointer to the element on success, or nullptr on failure (OUT_OF_BOUNDS_ERROR).
    T* get(uint64 index) const;

    // @brief Sets the element at a specified index to a new value.
    // @param index The index of the element to modify.
    // @param element The new value for the element.
    // @return A VectorStatus object indicating success (OK) or failure (OUT_OF_BOUNDS_ERROR).
    VectorStatus set(uint64 index, T element);

    // @brief Returns the current number of elements in the vector.
    // @return The size of the vector.
    uint64 getSize() const;

    // @brief Returns the total allocated memory capacity of the vector.
    // @return The capacity of the vector.
    uint64 getCapacity() const;

    // @brief Checks if the vector has been successfully initialized.
    // @return true if initialized successfully, false otherwise.
    bool isInitialized() const;

private:
    // @brief Pointer to the dynamically allocated array of items.
    T *items = nullptr;

    // @brief The current number of elements stored in the vector.
    uint64 size = 0;

    // @brief The total number of elements the vector can currently hold without reallocating.
    uint64 capacity = 0;

    // @brief Indicates whether the vector has been correctly initialized.
    bool initialized = false;

    // @brief Creates and initializes a new Vector with a given capacity.
    // @param initial_capacity The starting number of elements the vector can hold.
    // @return A VectorStatus object indicating success (OK), or an error status on failure (ALLOCATION_ERROR).
    VectorStatus initialize_items(uint64 initial_capacity);
};


// === Implementation of Vector<T> ===

template <typename T>
VectorStatus Vector<T>::initialize_items(uint64 initial_capacity) {
    if (initial_capacity == 0) {
        // Handle zero capacity initialization
        this->items = nullptr;
        this->size = 0;
        this->capacity = 0;
        this->initialized = true; 
        return VectorStatus::OK;
    }

    // Allocate memory for the initial capacity
    this->items = static_cast<T*>(memory::allocate(initial_capacity * sizeof(T)));
    if (this->items == nullptr) {
        // Handle allocation failure and return an error
        this->initialized = false;
        return VectorStatus::ALLOCATION_ERROR;
    }

    // Initialize size and capacity
    this->size = 0;
    this->capacity = initial_capacity;

    // Return the successfully initialized Vector
    this->initialized = true;
    return VectorStatus::OK;
}

template <typename T>
Vector<T>::Vector(const uint64 initial_capacity) {
    // Perform initialization directly
    this->initialize_items(initial_capacity);
    // The 'initialized' flag is set within initialize_items
}


template <typename T>
Vector<T>::~Vector() {
    // Deallocate the memory block pointed to by items
    memory::deallocate(this->items);

    // Reset member variables to a safe, default state
    this->items = nullptr;
    this->size = 0;
    this->capacity = 0;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    // Transfer ownership of internal resources from 'other' to 'this'
    this->items = other.items;
    this->size = other.size;
    this->capacity = other.capacity;
 
    // Nullify 'other's pointers and counters to ensure its destructor doesn't free the memory
    other.items = nullptr;
    other.size = 0;
    other.capacity = 0;
    other.initialized = false;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    // Self-assignment check
    if (this != &other) {
        // Free current resources before acquiring new ones
        memory::deallocate(this->items);

        // Transfer ownership of internal resources from 'other' to 'this'
        this->items = other.items;
        this->size = other.size;
        this->capacity = other.capacity;
        this->initialized = other.initialized;

        // Nullify 'other's pointers and counters
        other.items = nullptr;
        other.size = 0;
        other.capacity = 0;
        other.initialized = false;
    }
    return *this;
}

template <typename T>
VectorStatus Vector<T>::push(T element) {
    // Handle uninitialized vector
    if (!this->initialized) {
        return VectorStatus::UNINITIALIZED_ERROR;
    }
    
    // Check if current size equals capacity, indicating a need for reallocation
    if (this->size == this->capacity) {
        // Double the current capacity (or set to 1 if starting from 0)
        uint64 new_capacity = this->capacity > 0 ? this->capacity * 2 : 1;
        
        // Attempt to reallocate memory with the new capacity
        T *new_items = static_cast<T*>(memory::reallocate(this->items, new_capacity * sizeof(T)));
        
        // Handle reallocation failure
        if (new_items == nullptr) {
            return VectorStatus::ALLOCATION_ERROR;
        }

        // Update the items pointer and capacity to the new memory block
        this->items = new_items;
        this->capacity = new_capacity;
    }
    
    // Insert the new element at the end and increment the size
    this->items[this->size++] = element;
    return VectorStatus::OK;
}

template <typename T>
VectorStatus Vector<T>::pop(T& out_element) {
    // Check for an empty vector
    if (this->size == 0) {
        return VectorStatus::EMPTY_VECTOR_ERROR; 
    }

    // Decrement size and retrieve the element (copy to output reference)
    out_element = this->items[--this->size];
    
    // Return success
    return VectorStatus::OK;
}

template <typename T>
VectorStatus Vector<T>::insert(uint64 index, T element) {
    // Check if the index is valid for insertion (up to and including current size)
    if (index > this->size) {
        return VectorStatus::OUT_OF_BOUNDS_ERROR;
    }
    
    // Check capacity and reallocate if necessary
    if (this->size == this->capacity) {
        uint64 new_capacity = this->capacity > 0 ? this->capacity * 2 : 1;
        T *new_items = static_cast<T*>(memory::reallocate(this->items, new_capacity * sizeof(T)));
        if (new_items == nullptr) {
            return VectorStatus::ALLOCATION_ERROR;
        }

        this->items = new_items;
        this->capacity = new_capacity;
    }

    // If index is the current size, elements don't need to be shifted (handled implicitly below)
    
    // Calculate how many elements need to be shifted
    const uint64 elements_to_shift = this->size - index;
    if (elements_to_shift > 0) {
        // Move memory block to create space for the new element at 'index'
        memory::move(
            &(this->items[index + 1]),  // Destination (one step right)
            &(this->items[index]),      // Source
            elements_to_shift * sizeof(T)
        );
    }

    // Insert the new element at the specified index
    this->items[index] = element;
    
    // Increment the size counter
    this->size++;

    return VectorStatus::OK;
}

template <typename T>
VectorStatus Vector<T>::remove(uint64 index, T& out_element) {
    // Check if the index is within the valid range (0 to size - 1)
    if (index >= this->size) {
        return VectorStatus::OUT_OF_BOUNDS_ERROR;
    }

    // Store the element to be removed before shifting
    out_element = this->items[index];
    
    // Calculate how many elements need to be shifted back
    const uint64 elements_to_shift = this->size - index - 1;
    
    if (elements_to_shift > 0) {
        // Move subsequent elements one position to the left (overwriting the element at 'index')
        memory::move(
            &(this->items[index]),      // Destination
            &(this->items[index + 1]),  // Source (one step right)
            elements_to_shift * sizeof(T)
        );
    }
    
    // Decrement the size counter
    this->size--;
    
    // Return success
    return VectorStatus::OK;
}

template <typename T>
T* Vector<T>::  get(uint64 index) const {
    // Check for an out-of-bounds access
    if (index >= this->size) {
        // Return nullptr on failure
        return nullptr;
    }

    // Return a pointer to the element on success
    return &(this->items[index]);
}

template <typename T>
VectorStatus Vector<T>::set(uint64 index, T element) {
    // Check for an out-of-bounds access
    if (index >= this->size) {
        return VectorStatus::OUT_OF_BOUNDS_ERROR;
    }

    // Assign the new element value
    this->items[index] = element;
    return VectorStatus::OK;
}

template <typename T>
uint64 Vector<T>::getSize() const {
    // Return the stored size count
    return this->size;
}

template <typename T>
uint64 Vector<T>::getCapacity() const {
    // Return the stored capacity count
    return this->capacity;
}

template <typename T>
bool Vector<T>::isInitialized() const {
    // Return the initialization status
    return this->initialized;
}