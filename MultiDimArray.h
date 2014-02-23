#include <vector>
#include <numeric>
#include <cstdarg>
#include <cstddef>
#include <stdexcept>

class MultiDimArrayException:public std::runtime_error{
public:
  MultiDimArrayException(const std::string& msg):std::runtime_error(msg){}
};

/*
this class stores and manages an n-dimensional grid with the number of dimensions and their extents not known until compile time
*/
template <typename T>
class MultiDimArray{
public:
MultiDimArray(const std::vector<size_t>& dimExtents);

//returns a the number of dimensions
size_t getNumDims() const;
//returns a copy of the vector of extents of the dimensions
std::vector<size_t> getDimExtents() const;
//returns the total number of elements (size of the flattened array)
size_t getTotalSize() const;

//get a reference to the element at the given index
template <typename ...OtherIndex>
T& getElement(const size_t firstIndex,const OtherIndex ...otherIndex);

//get a reference to the element at the index specified in the vector
T& getElement(const std::vector<size_t>& indexes);

private:
std::vector<size_t> _dimExtents;
std::vector<T> _array;

//TODO make sure operator[] isn't publicly accessible? T& operator[](const size_t firstIndex,const size_t ...I);

//initialization funciton for common code used by all constructors.
void _init();

//cacluates the index into the flat member _array from multidimensional indexes
size_t _calcFlatIndex(const std::vector<size_t>& indexes) const;
};



template <typename T>
MultiDimArray<T>::MultiDimArray(const std::vector<size_t>& dimExtents):_dimExtents(dimExtents){
  _init();
}

template <typename T>
size_t MultiDimArray<T>::getNumDims() const{
//returns a copy of the size of _dimExtents
  return _dimExtents.size();
}

template <typename T>
size_t MultiDimArray<T>::getTotalSize() const{
//returns a copy of the size of _array
  return _array.size();
}
template <typename T>
std::vector<size_t> MultiDimArray<T>::getDimExtents() const{
//returns a copy of _dimExtents
  return _dimExtents;
}

template <typename T>
void MultiDimArray<T>::_init(){
/*loop through _dimExtents getting their sum (the total size of all of the
 *  dimensions flattened into one) and checking for non-terminal zero extents
 */
  size_t totalSize=0;
  for(auto it=_dimExtents.begin();it!=_dimExtents.end();++it){
    if(*it<1 && it!=_dimExtents.end()-1){
      throw(MultiDimArrayException("non terminal zero extent encountered at dimension "+std::to_string(it-_dimExtents.begin())+" is not allowed"));
    }
    totalSize+=*it;
  }
//set size of _array to totalSize
  _array.resize(totalSize);
}

template <typename T> //class's template parameter(s)
template <typename ...OtherIndex> //function's template parameter(s)
T& MultiDimArray<T>::getElement(const size_t firstIndex,const OtherIndex ...otherIndex){
//store all indexes in a vector for ease of counting and looping
  std::vector<size_t> indexes{firstIndex,otherIndex...};
//call the getElement that takes a vector
  return getElement(indexes);
}

template <typename T> //class's template parameter(s)
T& getElement(const std::vector<size_t>& indexes){

//throw error if incorrect number of indexes
  if(indexes.size()!=getNumDims()){
//throw error
	throw( MultiDimArrayException("incorrect number of dimensions. Was given "+std::to_string(indexes.size())+" but required "+std::to_string(getNumDims())+"."));
  }
}

template <typename T> //class's template parameter(s)
size_t MultiDimArray<T>::_calcFlatIndex(const std::vector<size_t>& indexes) const{
  //TODO
}
