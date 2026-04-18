# Google Test And Debugging Writeup

## Things I Thought To Test
1. Test that swap correctly exchanges two values using pointers
2. Test that sorting an already sorted array leaves it unchanged
3. Test that sorting a reverse sorted array produces correct order
4. Test that sorting handles duplicate values correctly
5. Test that the original array is not modified when making a sorted copy
6. Test that copy_array returns a different memory location, not the same pointer
7. Test that min_index_of_array returns the index of the first minimum when duplicates exist
8. Test that parse_args correctly converts command line strings to integers

## Bugs

### Bug 1

### Location
sorintg.cpp
56

```c++
 return ar[min_index];
```

### How the bug was located

I noticed that
min_index_of_array was returning ar[min_index] instead

### Description
The function should be returning the min_index, not 
the element at min index

### Fix 

by returning only the min_index

```c++
 return min_index;
```

### Bug 2

### Location
sorintg.cpp
24

```c++
int min_index = min_index_of_array(ar + i, len); 
```

### How the bug was located

When I was going through the make_sorted function I noticed
that ar + i was being passed to shift the start of the array
forward, but len was not being reduced to match. 

### Description

When we pass the substring into the the function
min_index_of_array(ar + i, len) the len should reduce by 1, or else when we traverse the 
array we would go out of bound
### Fix

By shrinking the len by 1 each time we call the function
with a substring, we would not go out of bound

```c++
int min_index = min_index_of_array(ar + i, len - i);
```

### Bug 3

### Location
sorintg.cpp
66-68

```c++
  int* temp = a;
  a = b;
  b = temp;
```

### How the bug was located

When I was writing the swap test I noticed the values were
not being exchanged after calling swap. I looked at the
implementation and saw it was reassigning the pointer
variables locally rather than modifying the values at
those addresses. Since pointers are passed by value in C++,
the changes to a and b were not visible outside the function.

### Description

The function takes int* pointers but the implementation
swaps the pointer variables themselves instead of the
values they point to. Since C++ passes pointers by value,
swapping a and b locally has no effect on the caller.
The dereference operator * is needed to access and modify
the actual values stored at those addresses.

### Fix

By dereferencing the pointers with * we modify the actual
values stored at those memory addresses rather than the
local pointer variables. A temporary plain int is used
to hold one value during the swap.

```c++
int temp = *a;
*a = *b;
*b = temp;
```

### Bug 4

### Location
sorintg.cpp
13

```c++
make_sorted(ar, len);
```

### How the bug was located

make_sorted was being called with ar (the original array)
instead of sorted_ar (the copy). Since make_sorted sorts in
place, this would modify the original array instead of the
copy, defeating the purpose of get_sorted which should leave
the original unchanged

### Description
The wrong array is being passed
into the make_sorted function. The array passed should
be a copy of the original array, not 
the original array itself.


### Fix

By replacing the original array with 
it's copy. 

```c++
make_sorted(sorted_ar, len);
```

### Bug 5

### Location
sorintg.cpp
36-37

```c++
  int* copy = ar;
  return copy;
```

### How the bug was located

running the
SimpleCopyWasMade test I noticed that arr and copy had
the same memory address. I looked at copy_array and saw
that it was just assigning the pointer ar to copy, which
means both variables point to the same memory location
rather than creating an independent copy.

### Description
The original code only copies the pointer and does not
have any content in it 

### Fix
Should allocate a new memory 
and copy the elements into the 
memory

```c++
  int* copy = new int[len];
  for (int i = 0 ; i < len ; i++) {
    copy[i] = ar[i];
  }
```
### Bug 6

### Location
sorintg.cpp
24-25

```c++
 int min_index = min_index_of_array(ar + i, len - 1);
    swap(ar + i, ar + min_index);
```

### How the bug was located

make_sorted
was not producing correctly sorted results. I traced through
the selection sort logic manually and found two problems:
first, len - 1 was being passed instead of len - i, meaning
the last element was never considered in the search window.
Second, the result of min_index_of_array is relative to the
subarray starting at ar + i, so it needs to be offset by i
to correctly index into the original array.

### Description
This means it searches one fewer element each time 
and doesn't account for the offset i correctly

### Fix
pass len-i to shrink
the search window, Also 
min_index needs to minus 
by i to get correct position 
in original array

```c++
int min_index = min_index_of_array(ar + i, len - i);
swap(ar + i, ar + i + min_index);
```

### Bug 7

### Location
formatting.cpp
24-25

```c++
for(int i = 0; i < len; --i)
```

### How the bug was located



### Description
This loop i is decremented no incremented, so the
loop goes on for infinity 

### Fix
change the --i to i++

```c++
  for(int i = 0; i < len; ++i)
```
### Bug 8

### Location
formatting.cpp
34

```c++
 ar_out = (int*)malloc(*len_out);
```

### How the bug was located
When I was going through parse_args I noticed malloc was
only being passed len_out as the size. Since malloc takes
a number of bytes and an int is 4 bytes on most systems,
this would only allocate enough memory for len_out bytes
rather than len_out integers, causing a buffer overflow
when storing values.

### Description
allocates len_out BYTES, which is 
not enough space for ints

### Fix
multiply by sizeof(int) to get 
correct number of bytes

```c++
ar_out = (int*)malloc(*len_out * sizeof(int));
```

### Bug 9

### Location
formatting.cpp
36

```c++
sscanf(argv[i], "%d", ar_out[i]);
```

### How the bug was located

When I was testing parse_args I noticed no values were
being stored. I looked at the sscanf call and saw two
problems: argv[0] is the program name so argv[i] skips
the first argument, and passing ar_out[i] gives sscanf
the value at that index rather than its address, which
is needed for sscanf to write into it.

### Description
argv[i] should be argv[i+1],
ar_out[i] should be &ar_out[i] because we 
need to address not the value

### Fix
by replacing argv[i] with argv[i+1] and ar_out[i] with
&ar_out[i]
```c++sscanf(argv[i + 1], "%d", &ar_out[i]);
```