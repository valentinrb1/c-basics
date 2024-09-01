# C Language Practices in GNU/Linux

## Date - 2022

This repository aims to review basic concepts of the C language, including the handling of C-strings, arrays, and structures. Various activities were carried out, which are described below.

### Authors:
- **Robledo, Valentín**

### 1. C-strings

**Getting information about RAM**

Implemented a C program that reads the `/proc/meminfo` file to get information about the total, free and available RAM in megabytes. Also, the occupied swap memory is obtained.

**Printing information about the CPU**

Created a C program that prints information about the CPU, using the `/proc/cpuinfo` file. The information includes the CPU model, the number of cores and the number of threads per core.

### 2. Arrays

**Reading and manipulating the `/proc/version` file**

Implemented a C program that reads the `/proc/version` file, copies the words into a dynamic array and then prints the list of words in uppercase. The allocated memory was freed.

### 3. Questions

#### How to use typedef with struct? What is it for? Example.

typedef is used to assign an alternative name to existing types, often when their normal declaration is cumbersome, potentially confusing, or likely to vary from one implementation to another. It is generally used on structs to simplify the declaration of them, resulting in much cleaner code and avoiding the <i>"struct"</i> keyword appearing everywhere. An example of using this would be:
       
```C
   typedef struct Persona { 
      char Nombre[50];
       uint8_t Edad;
       uint32_t DNI; 
   } Persona; 
```
       
#### What is packing and padding?

The concept of padding refers to aligning data in memory. To do this, one or more "padding" bytes are inserted between the memory addresses assigned to the members of the structure. The advantage of doing this is that the processor does not read the memory byte by byte, but rather by words (memory blocks with a length greater than 1 byte). Therefore, by aligning the data to form fixed-size words, reading the memory becomes more efficient. The disadvantage of this is that a larger amount of memory is used to store the structures. On the other hand, we can apply packing to prevent the compiler itself from performing padding (it is enabled by default). This is generally used to save memory and format a data structure to transmit over a network without depending on the architecture of each node. The disadvantages of doing this are that we lose processing efficiency, and also, not all processors are capable of performing packing.

#### Explain the reasons for the sizes of each of the structures.

```C
   printf("base     struct size  %lu \n", sizeof(BaseData));
   printf("reorder  struct size  %lu \n", sizeof(ReorderData));
   printf("extended struct size  %lu \n", sizeof(ExtendedData));
   printf("packed   struct size  %lu \n\n", sizeof(BaseDataPacked));
```

The memory space occupied by a structure depends on the sum of the size of the data types that make it up and the padding performed by the CPU. For example, if we have a structure composed of a char (1 byte) and an int (4 bytes), the structure needs at least (in case packing is used) a space of 5 bytes in memory. Analyzing each of the program cases: <br>

- <b>BaseData</b>: In this case, the first 2 bytes are occupied with ```char a``` and ```char b```, then the compiler fills it with a space of 2 bytes, followed by ```int x``` which occupies 4 bytes, ```unsigned short int y``` and ```char c``` plus another padding byte to complete the 4 bytes, finally ```unsigned short int z``` plus a padding of 2 bytes and finally ```char d[3]``` plus another padding byte.

```C
   typedef struct {
      char a;
      char b;
      char gap_0[2]; /* Insertado por el compilador para alinear x. */
      int  x;
      unsigned short int y;
      char c;
      char gap_1; /* Insertado por el compilador para alinear z. */
      unsigned short int z;
      char gap_2[2]; /* Insertado por el compilador para alinear d. */
      char d[3];
      char gap_3; /* Insertado por el compilador para alinear toda la estructura en una matriz. */
   } BaseData; 
      
   /* sizeof(BaseData) = 
         sizeof(char) * 5               +
         sizeof(char[2]) * 2            +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 2 +
      ------------------------------------
                               20 [Bytes]
   */
```

- <b>ReorderData</b>: As in the previous case, ```char a``` and ```char b``` occupy the first 2 bytes, the next 2 are filled and 4 bytes are occupied for the ```int x```. Then the ```unsigned short int y, z``` are placed occupying 2 bytes each. Now thanks to this order ```char c``` and ```char d[3]``` are aligned occupying 1 and 3 contiguous bytes respectively.

```C
   typedef struct {
      char a;
      char b;
      char gap_0[2]; //Insertado por el compilador para alinear x.
      int  x;
      unsigned short int y;
      unsigned short int z;
      char c;
      char d[3];
   } ReorderData;
    
   /* sizeof(BaseData) = 
         sizeof(char) * 3               +
         sizeof(char[2])                +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 2 +
      ------------------------------------
                               16 [Bytes]
   */
```

- <b>ExtendedData</b>: In this case, the first 8 bytes are occupied by ```long unsigned int ll```, ```char a``` and ```char b```, then, with ```unsigned short int y``` and filling 2 spaces to complete the 4 bytes, followed by ```int x``` which occupies 4 bytes, ```unsigned short int z```, ```unsigned short int w``` completing the 4 bytes, finally ```char c```, ```char d[3]```, which total 4 bytes.

```C
   typedef struct {
      long unsigned int ll;
      char a;
      char b;
      unsigned short int y;
      int  x;
      unsigned short int z;
      unsigned short int w;
      char c;
      char d[3];
   } ExtendedData;
      
   /* sizeof(BaseData) = 
         sizeof(char) * 3               +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 3 +
         sizeof(long unsigned int)      +
      ------------------------------------
                               24 [Bytes]
   */
```

- <b>BaseDataPacked</b>: In this case we use the packing feature, in which the compiler does not fill bytes to complete blocks of 4. This means that the processor cannot read all the memory in a single access, but rather, in most cases, it will have to use multiple reading cycles to obtain the information, making processing slower.

```C
   typedef struct  __attribute__((packed)) {
      char a;
      char b;
      int  x;
      unsigned short int y;
      char c;
      unsigned short int z;
      char d[3];
   } BaseDataPacked;
      
   /* sizeof(BaseData) = 
         sizeof(char) * 3               +
         sizeof(char[3])                +
         sizeof(int)                    +
         sizeof(unsigned short int) * 2 +
      ------------------------------------
                               14 [Bytes]
   */
```

#### Explain why the expressions that calculate ```limit``` and ```limit_aux``` generate the same result.

```C   
   char *limit = ((char *) &data + sizeof(BaseData)); 
   char *limit_aux =(char *) (&data + 1);

   printf("limit     value is %p \n", limit); 
   printf("limit_aux value is %p \n\n", limit_aux);
```

In the first case, we must start from the fact that we are casting a structure, which originally occupies 20 bytes in memory, by casting it to a pointer of type ```char*``` now it will point to a single byte. Then the sizeof(BaseData) is added, by pointer arithmetic ```p* + n``` means that the pointer will be shifted ```n``` elements of the same type, as in this case it is a char, it will be shifted byte by byte, 20 times. On the other hand, in the second case we see that the addition is done before the cast, this is very important, since now it will be shifted to the next element but of the original structure, which occupies 20 bytes. Therefore, in both cases we end up at the same memory address.

#### Explain the values ​​that are displayed on the screen in each iteration of the ```for```.

```C
    int i = 0;

    for (char *c = (char *) &data; c < limit; c++, i++){
        printf("byte %02d : 0x%02hhx \n", i, *c);
    }
```

The ```for``` goes through the memory locations where the ```data``` structure is stored byte by byte, printing the value that each of these stores on the console.
