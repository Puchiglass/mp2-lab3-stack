#pragma once

template <typename T>
class TStack
{
protected:
  T* pMem;
  size_t size;
  int top;

public:
  TStack(int sz);
  TStack(const TStack<T>& p);
  TStack(TStack<T>&& p);
  ~TStack();

  size_t Size() const;

  bool isEmpty() const;
  bool isFull() const;

  void Push(const T& val);
  T Pop();
  T Top();

};

template<typename T>
inline TStack<T>::TStack(int sz)
{
  if (sz <= 0) throw "TStack<T>::TStack(int sz) sz <= 0";
  size = sz;
  top = -1;
  pMem = new T[size];
}

template<typename T>
inline TStack<T>::TStack(const TStack<T>& p)
{
  if (p.pMem == nullptr)
  {
    pMem = nullptr;
    size = 0;
    top = -1;
  }
  else
  {
    size = p.size;
    top = p.top;
    pMem = new T[size];
    for (int i = 0; i < top; i++)
      pMem[i] = p.pMem[i];
  }
}

template<typename T>
inline TStack<T>::TStack(TStack<T>&& p)
{
  size = p.size;
  top = p.top;
  pMem = p.pMem;

  p.pMem = nullptr;
  p.size = 0;
  p.top = -1;
}

template<typename T>
inline TStack<T>::~TStack()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
  size = 0;
  top = -1;
}

template<typename T>
inline size_t TStack<T>::Size() const
{
  return top + 1;
}

template<typename T>
inline bool TStack<T>::isEmpty() const
{
  if (top == -1) return true;
  return false;
}

template<typename T>
inline bool TStack<T>::isFull() const
{
  if (top == size - 1) return true;
  return false;
}

template<typename T>
inline void TStack<T>::Push(const T& val)
{
  if (isFull() == true) throw "TStack<T>::Push(const T& val) pMem isFull";
  pMem[++top] = val;
}

template<typename T>
inline T TStack<T>::Pop()
{
  if (isEmpty() == true) throw "TStack<T>::Pop() pMem isEmpty";
  return pMem[top--];
}

template<typename T>
inline T TStack<T>::Top()
{
  return pMem[top];
}
