/**
 * @file BasicString.h
 * @auther 112KA
 * @date 2017/02/14
 */

#ifndef String_cpp
#define String_cpp

#include <stdlib.h>
#include <stdarg.h>   // for va_list
#include <vector>

#ifndef DEF_ASSERT
#include <assert.h>
#define DEF_ASSERT assert
#endif


//TODO: RVALUE REFERENCE

/**
 * Simple C++ string type that can be set memory allocator
 * @class BasicString BasicString.h
 */
template<class _CharT, class _Traits, class _Allocator>
class BasicString
{
private:
    
    using char_type = typename _Traits::char_type;
    
    using __alloc_traits = std::allocator_traits<_Allocator>;
    using size_type = typename __alloc_traits::size_type;
    using reference = char_type&;
    using const_reference = const char_type&;
    using pointer = typename __alloc_traits::pointer;
    using const_pointer = typename __alloc_traits::const_pointer;

    //! allocator
    _Allocator _allocator;

    //! length of string characters
    size_t _size{0};
    size_t _bufferSize{0};
    char_type *_data;
    
    const size_t _MIN_CAPACITY = 8;
    
    void _allocate(size_t __size);
    void _reallocate(size_t __size);
    
public:
    /**
     * empty string constructor (default constructor)
     */
    BasicString();

    /**
     * constructor
     * @param __format pointer to a null-terminated multibyte string specifying how to interpret the data.
     */
    BasicString(const char_type* __format, ...);

    /**
     * copy constructor
     * @param __str Another BasicString object of the same type (with the same class template arguments charT, traits and Alloc), whose value is either copied or acquired.
     */
    BasicString(const BasicString& __str);

    /**
     * substring constructor
     * @param __str Another BasicString object of the same type (with the same class template arguments charT, traits and Alloc), whose value is either copied or acquired.
     * @param __pos The position at which the first character of the returned string begins.
     * @param __n The length of the returned string.
     */
    BasicString(size_type __pos, size_type __n, const BasicString& __str);

    /**
     * destructor
     */
    ~BasicString();
    
    /**
     * Maximum value of size_type
     * npos is a static member constant value with the greatest possible value for an element of member type size_type.
     * This value, when used as the value for a len (or sublen) parameter in BasicString's member functions, means "until the end of the string".
     */
    static const size_type npos = -1;

    /**
     * Assigns a new value to the string, replacing its current contents.
     * @param __str Pointer to a null-terminated sequence of characters.
     * @return *this
     */
    BasicString& operator= (const char_type* __str);

    /**
     * @overload
     * @param __str A BasicString object of the same type (with the same class template arguments charT, traits and Alloc).
     */
    BasicString& operator= (const BasicString& __str);


//Capacity:
    /**
     * Returns the length of the string, in terms of number of characters.
     * @return The number of characters in the string.
     */
    inline const size_t size() const noexcept { return _size; }

    /**
     * Returns the length of the string, in terms of number of characters.
     * @return The number of characters in the string.
     */
    inline const size_t length() const noexcept { return _size; }

    /**
     * Erases the contents of the BasicString, which becomes an empty string (with a length of 0 characters).
     * @return none
     */
    void clear() noexcept;

    /**
     * Returns whether the BasicString is empty (i.e. whether its length is 0).
     * @return true if the string length is 0, false otherwise.
     */
    inline bool empty() const noexcept { return _size==0; }


//Element access
    /**
     * Returns a reference to the character at position __pos in the BasicString.
     * @param __pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */
    inline reference operator[] (size_type __pos) {
        DEF_ASSERT(__pos<_size);
        return *(_data + __pos);
    }

    /**
     * Returns a const reference to the character at position __pos in the BasicString.
     * @param __pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */
    inline const_reference operator[] (size_type __pos) const {
        DEF_ASSERT(__pos<_size);
        return *(_data + __pos);
    }

    /**
     * Returns a reference to the character at position __pos in the BasicString.
     * @param __pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */
    inline reference at(size_type __pos) { return (*this)[__pos]; }

    /**
     * Returns a const reference to the character at position __pos in the BasicString.
     * @param __pos Value with the position of a character within the string.
     * @return The character at the specified position in the string.
     */
    inline const_reference at(size_type __pos) const { return (*this)[__pos]; }
    

//Modifiers:
    /**
     * Extends the BasicString by appending additional characters at the end of its current value.
     * @param __str Pointer to a null-terminated sequence of characters.The sequence is copied at the end of the string.
     * @return *this
     */
    inline BasicString& operator+= (const char_type* __str) { return append(__str); }

    /**
     * Extends the BasicString by appending additional characters at the end of its current value.
     * @param __str A BasicString object of the same type (with the same class template arguments charT, traits and Alloc), whose value is copied at the end.
     * @return *this
     */
    inline BasicString& operator+= (const BasicString& __str) { return append(__str); }

    /**
     * Extends the BasicString by appending additional characters at the end of its current value.
     * @param __format pointer to a null-terminated multibyte string specifying how to interpret the data.
     * @return *this
     */
    BasicString& append(const char_type* __format, ...);

    /**
     * @overload
     * @param __str A BasicString object of the same type (with the same class template arguments charT, traits and Alloc), whose value is copied at the end.
     */
    inline BasicString& append(const BasicString& __str) { return append(__str.c_str()); }

    /**
     * Inserts additional characters into the BasicString right before the character indicated by __pos:
     * @param __pos Insertion point: The new contents are inserted before the character at position __pos.
     * @param __format pointer to a null-terminated multibyte string specifying how to interpret the data.
     * @return *this
     */
    BasicString& insert(size_type __pos, const char_type* __format, ...);

    /**
     * @overload
     * @param __pos Insertion point: The new contents are inserted before the character at position __pos.
     * @param __str A BasicString object of the same type (with the same class template arguments charT, traits and Alloc), whose value is copied at the end.
     */
    inline BasicString& insert(size_type __pos, const BasicString& __str) { return insert(__pos, __str.c_str()); }

    /**
     * Erases part of the basic_string, reducing its length:
     * @param __pos Position of the first character to be erased.
     * @param __n Number of characters to erase (if the string is shorter, as many characters as possible are erased).
     * @return *this
     */
    BasicString& erase(size_type __pos, size_type __n);
    

//String operations:
    /**
     * Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the BasicString object.
     * @return A pointer to the c-string representation of the BasicString object's value.
     */
    inline const char_type* c_str() const noexcept { return _data; }

    /**
     * Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the BasicString object.
     * @return A pointer to the c-string representation of the BasicString object's value.
     */
    inline const char_type* data() const noexcept { return _data; }

    /**
     *　Searches the BasicString for the first occurrence of the sequence specified by its arguments.
     * @param   __str   Pointer to an array of characters.
     * @return          The position of the first character of the first match.<br />
     *                  If no matches were found, the function returns BasicString::npos.
     */
    size_type find(const char_type* __str) const;

    /**
     * @overload
     * @param   __str   Another BasicString with the subject to search for.
     */
    inline size_type find(const BasicString& __str) const  { return find(__str.c_str()); }

    /**
     * Returns a newly constructed BasicString object with its value initialized to a copy of a substring of this object.
     * @param   __pos   Position of the first character to be copied as a substring.
     * @param   __n     Number of characters to include in the substring (if the string is shorter, as many characters as possible are used).
     * @return          A BasicString object with a substring of this object. 
     */
    inline BasicString substr(size_type __pos, size_type __n = npos) const { return BasicString(__pos, __n, *this); };

    /**
     * Compares the value of the BasicString object (or a substring) to the sequence of characters specified by its arguments.
     * @param   __str   Pointer to an array of characters.
     * @return          Returns a signed integral indicating the relation between the strings:
     * - 0 They compare equal
     * - <0 Either the value of the first character that does not match is lower in the compared string, or all compared characters match but the compared string is shorter.
     * - >0 Either the value of the first character that does not match is greater in the compared string, or all compared characters match but the compared string is longer.
     */
    int compare(const char_type* __str) const noexcept;

    /**
     * @overload
     * @param __str Another BasicString object of the same type (with the same class template arguments charT, traits and Alloc), used entirely (or partially) as the comparing string.
     */
    inline int compare(const BasicString& __str) const noexcept { return compare(__str.c_str()); }
    
    
    /**
     * Splits a String object into an array of substrings by dividing it wherever the specified __delimiter parameter occurs.
     * @param __delimiter The pattern that specifies where to split this string.
     * @return A vector of substrings.
     */
    template<class _ItemAllocator=std::allocator<BasicString> >
    std::vector<BasicString, _ItemAllocator > split(const char_type* __delimiter) {
        std::vector<BasicString, _ItemAllocator > ret;
        BasicString s = *this;
        size_t index;
        while(true) {
            index = s.find(__delimiter);
            if(index!=-1) {
                ret.push_back(s.substr(0,index));
                s.erase(0,index+1);
            }
            else {
                ret.push_back(s);
                break;
            }
        }
        
        return ret;
    }
};

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>::BasicString() {
    _size = 0;
    _allocate(_MIN_CAPACITY);
}

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>::BasicString(const char_type* __format, ...) {
    if(__format!=nullptr) {
        va_list args, args2;
        va_start(args, __format);
        va_copy(args2, args);
        int len = vsnprintf(nullptr, 0, __format, args);
        _size = len;
        int n = len+1 > _MIN_CAPACITY ? len+1 : _MIN_CAPACITY;
        _allocate(n);
        vsnprintf(_data, n, __format, args2);
        va_end(args);
        va_end(args2);
    }
    else {
        _size = 0;
        _allocate(_MIN_CAPACITY);
    }
}

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>::BasicString(const BasicString& __str) {
    _size = __str.length();
    _allocate(_size+1);
    _Traits::copy(_data, __str.c_str(), _size+1);
}

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>::BasicString(size_type __pos, size_type __n, const BasicString& __str) {
    size_t len = __str.length();
    DEF_ASSERT(__pos < len);
    
    _size = __n < len - __pos ? __n : len - __pos;
    _allocate(_size+1);
    _Traits::copy(_data, __str.c_str()+__pos, _size);
}

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>::~BasicString() {
    __alloc_traits::deallocate(_allocator, _data, _size);
}

template <class _CharT, class _Traits, class _Allocator>
void BasicString<_CharT, _Traits, _Allocator>::_allocate(size_t __size) {
    _bufferSize = __size;
    _data = __alloc_traits::allocate(_allocator, _bufferSize);
}

template <class _CharT, class _Traits, class _Allocator>
void BasicString<_CharT, _Traits, _Allocator>::_reallocate(size_t __size) {
    pointer old_pointer = _data;
    size_t old_size = _bufferSize;
    _bufferSize = __size;
    _data = __alloc_traits::allocate(_allocator, _bufferSize);
    _Traits::copy(_data, old_pointer, old_size);
    __alloc_traits::deallocate(_allocator, old_pointer, old_size);
}

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>&
BasicString<_CharT, _Traits, _Allocator>::operator=(const char_type* __str) {

    if(__str!=nullptr) {
        size_t size = strlen(__str);
        if(size+1 > _bufferSize) {
            _reallocate(size+1);
        }
        _size = size;
        _Traits::copy(_data, __str, _size+1);
    }
    else {
        clear();
    }

    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>&
BasicString<_CharT, _Traits, _Allocator>::operator=(const BasicString& __str) {
    size_t size = __str.length();
    if(size+1 > _bufferSize) {
        _reallocate(size+1);
    }
    _size = size;
    
    _Traits::copy(_data, __str.c_str(), _size+1);
    
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
void
BasicString<_CharT, _Traits, _Allocator>::clear() noexcept {
    _Traits::assign(*_data, char_type());
    _size = 0;
}


template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>&
BasicString<_CharT, _Traits, _Allocator>::append(const char_type* __format, ...) {
    va_list args, args2;
    va_start(args, __format);
    va_copy(args2, args);
    int n = vsnprintf(nullptr, 0, __format, args);
    if(_size+n+1 > _bufferSize) {
        _reallocate(_size+n+1);
    }
    vsnprintf(_data+_size, n+1, __format, args2);
    _size += n;
    va_end(args);
    va_end(args2);
    
    return *this;
}


template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>&
BasicString<_CharT, _Traits, _Allocator>::insert(size_type __pos, const char_type* __format, ...) {
    va_list args, args2;
    va_start(args, __format);
    va_copy(args2, args);
    int n = vsnprintf(nullptr, 0, __format, args);
    if(_size+n+1 > _bufferSize) {
        _reallocate(_size+n+1);
    }
    
    //Temporary evacuation of line feed position character that disappears when using vsnprintf
    const char_type tmp_c = (*this)[__pos];
    
    _Traits::move(_data+__pos+n, _data+__pos, _size-__pos+1);
    vsnprintf(_data+__pos, n+1, __format, args2);
    
    //Return missing character
    _Traits::copy(_data+__pos+n, &tmp_c, 1);
    _size += n;
    va_end(args);
    va_end(args2);
    
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
BasicString<_CharT, _Traits, _Allocator>&
BasicString<_CharT, _Traits, _Allocator>::erase(size_type __pos, size_type __n) {
    DEF_ASSERT(__pos<_size-1);
    if(__pos+__n<_size) {
        _Traits::move(_data+__pos, _data+__pos+__n, _size-__pos-__n+1);
        _size -= __n;
    }
    else {
        _data[__pos] = '\0';
        _size = __pos;
    }
    return *this;
}

template <class _CharT, class _Traits, class _Allocator>
typename BasicString<_CharT, _Traits, _Allocator>::size_type
BasicString<_CharT, _Traits, _Allocator>::find(const char_type* __str) const {
    size_t len = strlen(__str);
    if (len >= _size)
        return npos;
    
    char_type* c = std::search(_data, _data+_size, __str, __str+len);
    if (c == _data + _size)
        return npos;
    
    return static_cast<size_type>(c - _data);
}

template <class _CharT, class _Traits, class _Allocator>
int
BasicString<_CharT, _Traits, _Allocator>::compare(const char_type* __str) const noexcept
{
    size_t __lhs_sz = _size;
    size_t __rhs_sz = strlen(__str);
    size_t n = __lhs_sz < __rhs_sz ? __lhs_sz : __rhs_sz;
    int __result = _Traits::compare(_data, __str, n);
    if (__result != 0)
        return __result;
    if (__lhs_sz < __rhs_sz)
        return -1;
    if (__lhs_sz > __rhs_sz)
        return 1;
    return 0;
}

// operator==

template<class _CharT, class _Traits, class _Allocator>
inline
bool
operator==(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
           const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept
{
size_t __lhs_sz = __lhs.size();
return __lhs_sz == __rhs.size() && _Traits::compare(__lhs.data(), __rhs.data(), __lhs_sz) == 0;
}

template<class _CharT, class _Traits, class _Allocator>
inline
bool
operator==(const _CharT* __lhs, const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept
{
return __rhs.compare(__lhs) == 0;
}

template<class _CharT, class _Traits, class _Allocator>
inline
bool
operator==(const BasicString<_CharT,_Traits,_Allocator>& __lhs, const _CharT* __rhs) noexcept
{
return __lhs.compare(__rhs) == 0;
}

// operator!=

template<class _CharT, class _Traits, class _Allocator>
inline
bool
operator!=(const BasicString<_CharT,_Traits,_Allocator>& __lhs,
           const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept
{
return !(__lhs == __rhs);
}

template<class _CharT, class _Traits, class _Allocator>
inline
bool
operator!=(const _CharT* __lhs,
           const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept
{
return !(__lhs == __rhs);
}

template<class _CharT, class _Traits, class _Allocator>
inline
bool
operator!=(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
           const _CharT* __rhs) noexcept
{
return !(__lhs == __rhs);
}

// operator+

template<class _CharT, class _Traits, class _Allocator>
inline BasicString<_CharT,_Traits,_Allocator> operator+ (const BasicString<_CharT,_Traits,_Allocator>& __lhs, 
                                const _CharT* __rhs) { 
    return BasicString<_CharT,_Traits,_Allocator>("%s%s", __lhs.c_str(), __rhs);
}

template<class _CharT, class _Traits, class _Allocator>
inline BasicString<_CharT,_Traits,_Allocator> operator+ (const BasicString<_CharT,_Traits,_Allocator>& __lhs, 
                                const BasicString<_CharT,_Traits,_Allocator>& __rhs) { 
    return BasicString<_CharT,_Traits,_Allocator>("%s%s", __lhs.c_str(), __rhs.c_str());
}

template<class _CharT, class _Traits, class _Allocator>
inline BasicString<_CharT,_Traits,_Allocator> operator+ (const _CharT* __lhs, 
                                const BasicString<_CharT,_Traits,_Allocator>& __rhs) { 
    return BasicString<_CharT,_Traits,_Allocator>("%s%s", __lhs, __rhs.c_str());
}


// operator<
template <class _CharT, class _Traits, class _Allocator>
bool operator<(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __lhs.compare(__rhs) < 0;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator<(const _CharT* __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __rhs.compare(__lhs) > 0;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator<(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
                 const _CharT* __rhs) noexcept {
    return __lhs.compare(__rhs) < 0;
}


// operator<=
template <class _CharT, class _Traits, class _Allocator>
bool operator<=(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __lhs.compare(__rhs) <= 0;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator<=(const _CharT* __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __rhs.compare(__lhs) >= 0;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator<=(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
                 const _CharT* __rhs) noexcept {
    return __lhs.compare(__rhs) <= 0;
}


// operator>
template <class _CharT, class _Traits, class _Allocator>
bool operator>(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __rhs < __lhs;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator>(const _CharT* __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __rhs < __lhs;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator>(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
                 const _CharT* __rhs) noexcept {
    return __rhs < __lhs;
}


// operator>=
template <class _CharT, class _Traits, class _Allocator>
bool operator>=(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __lhs.compare(__rhs) >= 0;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator>=(const _CharT* __lhs,
             const BasicString<_CharT, _Traits, _Allocator>& __rhs) noexcept {
    return __rhs.compare(__lhs) <= 0;
}

template <class _CharT, class _Traits, class _Allocator>
bool operator>=(const BasicString<_CharT, _Traits, _Allocator>& __lhs,
                 const _CharT* __rhs) noexcept {
    return __lhs.compare(__rhs) >= 0;
}

#endif
