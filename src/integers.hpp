template <typename T>
class SafeInteger {
    static_assert(isInteger<T>::value, "SafeInteger can only be instantiated with integer types.");
public:

    // === Constructors and Conversions ===

    constexpr SafeInteger(T value) : value(value) {}

    constexpr operator T() const {
        return value;
    }

    constexpr SafeInteger<T> operator=(T value) {
        this->value = value;
        return *this;
    }

    constexpr SafeInteger<T>& operator=(const SafeInteger<T>& other) {
        if (this != &other) {
            this->value = other.value;
        }
        return *this;
    }

    // === Arithmetic Operators ===

    constexpr SafeInteger<T> operator+(const SafeInteger<T>& other) const {
        if constexpr (isSigned<T>::value) {
            // Check 1: Positive Overflow (a + b > MAX, where b > 0)
            if ((other.value > 0) && (this->value > limits<T>::max - other.value)) {
                // Handle overflow
            }
            // Check 2: Negative Underflow (a + b < MIN, where b < 0)
            else if ((other.value < 0) && (this->value < limits<T>::min - other.value)) {
                // Handle underflow
            }
        }
        else { // Unsigned types
            // Check 1: Overflow (a + b > MAX)
            if (this->value > limits<T>::max - other.value) {
                // Handle overflow
            }
        }

        return SafeInteger<T>(this->value + other.value);
    }

    constexpr SafeInteger<T> operator-(const SafeInteger<T>& other) const {
        if constexpr (isSigned<T>::value) {
            // Check 1: Positive Overflow (a - b > MAX, where b < 0, i.e., adding |b|)
            if ((other.value < 0) && (this->value > limits<T>::max + other.value)) {
                // Handle overflow
            }
            // Check 2: Negative Underflow (a - b < MIN, where b > 0)
            else if ((other.value > 0) && (this->value < limits<T>::min + other.value)) {
                // Handle underflow
            }
        }
        else { // Unsigned types
            // Check 1: Underflow (a - b < 0)
            if (this->value < other.value) {
                // Handle underflow
            }
        }

        return SafeInteger<T>(this->value - other.value);
    }

    constexpr SafeInteger<T> operator*(const SafeInteger<T>& other) const {
        if ((this->value == 0) || (other.value == 0)) {
            // No overflow possible
        }
        else if constexpr (isSigned<T>::value) {
            // Check 1: Positive Overflow (result > MAX)
            // Case 1: pos * pos. Check if this->value > MAX / other.value
            if ((other.value > 0) && (this->value > limits<T>::max / other.value)) {
                // Handle overflow
            }
            // Case 2: neg * neg. Check if this->value < MAX / other.value
            else if ((other.value < 0) && (this->value < limits<T>::max / other.value)) {
                // Handle overflow
            }
            // Check 2: Negative Underflow (result < MIN)
            // Case 3: pos * neg. Check if this->value < MIN / other.value
            else if ((other.value > 0) && (this->value < limits<T>::min / other.value)) {
                // Handle underflow
            }
            // Case 4: neg * pos. Check if this->value > MIN / other.value
            else if ((other.value < 0) && (this->value > limits<T>::min / other.value)) {
                // Handle underflow
            }
        }
        else { // Unsigned types
            // Check 1: Overflow (a * b > MAX)
            if (this->value > limits<T>::max / other.value) {
                // Handle overflow
            }
        }

        return SafeInteger<T>(this->value * other.value);
    }

    constexpr SafeInteger<T> operator/(const SafeInteger<T>& other) const {
        // Check 0: Division by zero (always an error)
        if (other.value == 0) {
            // Handle division by zero
        }
        else if constexpr (isSigned<T>::value) {
            // Check 1: Overflow/Underflow
            // The only case causing overflow is MIN / -1 (for two's complement)
            if ((this->value == limits<T>::min) && (other.value == -1)) {
                // Handle overflow
            }
        }
        // Unsigned division has no arithmetic overflow/underflow cases.

        return SafeInteger<T>(this->value / other.value);
    }

    constexpr SafeInteger<T> operator%(const SafeInteger<T>& other) const {
        // Check 0: Division by zero (always an error)
        if (other.value == 0) {
            // Handle division by zero
        }
        // Modulo has no arithmetic overflow/underflow cases.

        return SafeInteger<T>(this->value % other.value);
    }

    // === Unary Operators ===

    constexpr SafeInteger<T> operator-() const {
        if constexpr (isSigned<T>::value) {
            // Check 1: Overflow
            // The only case causing overflow is MIN negated (result is MAX + 1)
            if (this->value == limits<T>::min) {
                // Handle overflow
            }
        }
        // Unsigned negation is non-standard or defined to wrap, so we skip arithmetic checks.

        return SafeInteger<T>(-this->value);
    }
    
    // Prefix Increment: ++a
    constexpr SafeInteger<T>& operator++() {
        if constexpr (isSigned<T>::value) {
            // Check 1: Positive Overflow (a + 1 > MAX)
            if (this->value == limits<T>::max) {
                // Handle overflow
            }
        }
        else { // Unsigned types
            // Check 1: Overflow (a + 1 > MAX)
            if (this->value == limits<T>::max) {
                // Handle overflow
            }
        }

        ++this->value;
        return *this;
    }

    // Postfix Increment: a++
    constexpr SafeInteger<T> operator++(int) {
        SafeInteger<T> temp = *this;
        ++(*this); // Delegate to prefix operator
        return temp;
    }

    // Prefix Decrement: --a
    constexpr SafeInteger<T>& operator--() {
        if constexpr (isSigned<T>::value) {
            // Check 1: Negative Underflow (a - 1 < MIN)
            if (this->value == limits<T>::min) {
                // Handle underflow
            }
        }
        else { // Unsigned types
            // Check 1: Underflow (a - 1 < 0)
            if (this->value == limits<T>::min) { // limits<T>::min is 0 for unsigned
                // Handle underflow
            }
        }

        --this->value;
        return *this;
    }

    // Postfix Decrement: a--
    constexpr SafeInteger<T> operator--(int) {
        SafeInteger<T> temp = *this;
        --(*this); // Delegate to prefix operator
        return temp;
    }

    // === Bitwise Operators ===
    // Note: Bitwise operations do not cause arithmetic overflow, but shift operations
    // must check the shift amount to avoid Undefined Behavior (UB).

    constexpr SafeInteger<T> operator^(const SafeInteger<T>& other) const {
        return SafeInteger<T>(this->value ^ other.value);
    }

    constexpr SafeInteger<T> operator&(const SafeInteger<T>& other) const {
        return SafeInteger<T>(this->value & other.value);
    }

    constexpr SafeInteger<T> operator|(const SafeInteger<T>& other) const {
        return SafeInteger<T>(this->value | other.value);
    }

    constexpr SafeInteger<T> operator~() const {
        return SafeInteger<T>(~this->value);
    }

    constexpr SafeInteger<T> operator<<(const SafeInteger<T>& other) const {
        // Check 1: Undefined Behavior (invalid shift amount)
        // Shift amount must be non-negative and strictly less than the number of bits in T.
        if ((other.value < 0) || (other.value >= sizeof(T) * 8)) {
            // Handle undefined behavior
        }
        // Check 2: Undefined Behavior (shifting into sign bit or off the end for signed types)
        else if constexpr (isSigned<T>::value) {
            // Note: This check is complex and involves bit manipulation (e.g., checking
            // if (a * 2^b) exceeds MAX). We rely on the shift amount check for primary safety.
        }

        return SafeInteger<T>(this->value << other.value);
    }

    constexpr SafeInteger<T> operator>>(const SafeInteger<T>& other) const {
        // Check 1: Undefined Behavior (invalid shift amount)
        // Shift amount must be non-negative and strictly less than the number of bits in T.
        if ((other.value < 0) || (other.value >= sizeof(T) * 8)) {
            // Handle undefined behavior
        }
        // Right shift doesn't typically cause arithmetic overflow/underflow

        return SafeInteger<T>(this->value >> other.value);
    }

    // === Comparison Operators ===

    inline constexpr bool operator==(const SafeInteger<T>& other) const {
        return value == other.value;
    }

    inline constexpr bool operator!=(const SafeInteger<T>& other) const {
        return value != other.value;
    }

    inline constexpr bool operator<(const SafeInteger<T>& other) const {
        return value < other.value;
    }

    inline constexpr bool operator<=(const SafeInteger<T>& other) const {
        return value <= other.value;
    }

    inline constexpr bool operator>(const SafeInteger<T>& other) const {
        return value > other.value;
    }

    inline constexpr bool operator>=(const SafeInteger<T>& other) const {
        return value >= other.value;
    }

private:
    T value;
};

using Int8 = SafeInteger<int8>;
using Int16 = SafeInteger<int16>;
using Int32 = SafeInteger<int32>;
using Int64 = SafeInteger<int64>;

using UInt8 = SafeInteger<uint8>;
using UInt16 = SafeInteger<uint16>;
using UInt32 = SafeInteger<uint32>;
using UInt64 = SafeInteger<uint64>;