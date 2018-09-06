// MemoryBlock.h  
#pragma once  
#include <iostream>  
#include <algorithm>  
#include <vector>  

using namespace std;

class MemoryBlock  
{  
public:  

   // Simple constructor that initializes the resource.  
   explicit MemoryBlock(size_t length)  
      : _length(length)  
      , _data(new int[length])  
   {  
      std::cout << "In MemoryBlock(size_t). length = "  
                << _length << "." << std::endl;  
   }  

   // Destructor.  
   ~MemoryBlock()  
   {  
      std::cout << "In ~MemoryBlock(). length = "  
                << _length << ".";  

      if (_data != nullptr)  
      {  
         std::cout << " Deleting resource.";  
         // Delete the resource.  
         delete[] _data;  
      }  

      std::cout << std::endl;  
   }  

   // Copy constructor.  
   MemoryBlock(const MemoryBlock& other)  
      : _length(other._length)  
      , _data(new int[other._length])  
   {  
      std::cout << "In MemoryBlock(const MemoryBlock&). length = "   
                << other._length << ". Copying resource." << std::endl;  

      std::copy(other._data, other._data + _length, _data);  
   }  

   MemoryBlock(MemoryBlock&& other)
   {
       std::cout << "In MemoryBlock(const MemoryBlock&&). length = "   
                << other._length << ". Moving Copying resource." << std::endl;  
        _data = other._data;
        _length = other._length;

        other._data = nullptr;
        other._length = 0;
   }

   // Copy assignment operator.  
   MemoryBlock& operator=(const MemoryBlock& other)  
   {  
      std::cout << "In operator=(const MemoryBlock&). length = "   
                << other._length << ". Copying resource." << std::endl;  

      if (this != &other)  
      {  
         // Free the existing resource.  
         delete[] _data;  

         _length = other._length;  
         _data = new int[_length];  
         std::copy(other._data, other._data + _length, _data);  
      }  
      return *this;  
   }  

   MemoryBlock& operator=(MemoryBlock&& other)
   {
       std::cout << "In operator=(MemoryBlock&&). length = "   
                << other._length << ". Move Copying resource." << std::endl;  
        if (this != &other)
        {
            delete [] _data;
            _data = other._data;
            _length = other._length;

            other._data = nullptr;
            other._length = 0;
        }
        return *this;
   }

   // Retrieves the length of the data resource.  
   size_t Length() const  
   {  
      return _length;  
   }  

private:  
   size_t _length; // The length of the resource.  
   int* _data; // The resource.  
};

 

int main()  
{  
   // Create a vector object and add a few elements to it.  
   vector<MemoryBlock> v;  
   v.reserve(10);       // 假如不reserve，那么push75时，会重新创建vector，即25又构造了一回
   v.push_back(MemoryBlock(25));  
   cout << ".....\n";
   v.push_back(MemoryBlock(75));  

    cout << "......\n";
   // Insert a new element into the second position of the vector.  
   v.insert(v.begin() + 1, MemoryBlock(50));  
}
