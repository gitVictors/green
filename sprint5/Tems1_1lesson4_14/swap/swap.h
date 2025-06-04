#pragma once

// Шаблонная функция Swap обменивает значения двух объектов одного и того же типа,
// указатели на которые она принимает в качестве аргументов.
template <typename T>
void Swap(T* value1, T* value2) {  
     
      // Реализуйте тело функции самостоятельно.
        T value_tmp = *value1;
        *value1 = *value2;
        *value2 = value_tmp;

}