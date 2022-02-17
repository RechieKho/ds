#pragma once
#include <stdbool.h>
#include <cstdlib>
#include <string>

#define GET_MEDIAN_INDEX(length) length/2

template<typename T>
struct list_slot { // individual element of a list
    T data;
    struct list_slot<T> *next;
    struct list_slot<T> *prev;
}; 

template<typename T>
class List { // stores data about the list_slot chain
        unsigned int length;
        struct list_slot<T> *start;
        struct list_slot<T> *median;
        struct list_slot<T> *end;
        struct list_slot<T> *get_slot(unsigned int index);
    public:
        List();
        ~List();
        T operator[](unsigned int index); // get list_slot
        bool delete_slot(unsigned int index); // remove list_slot from the chain and free it
        void clear(); // remove all the list_slot and free it
        bool put(T data, unsigned int index);
        bool put_front(T data, unsigned int index);
        bool put_behind(T data, unsigned int index);
        bool is_in_list(T data);
        std::string get_repr();
        int get_length();
};

template<typename T>
List<T>::List(){
    length = 0;
    start = median = end = NULL;
}

template<typename T>
List<T>::~List(){
    this->clear();
}

template<typename T>
struct list_slot<T> *List<T>::get_slot(unsigned int index){
    if(index >= length) return NULL;
    
    // get which list_slot to start counting

    // start_diff = index
    int median_diff = index - GET_MEDIAN_INDEX(length);
    int end_diff = index - (length - 1) ;

    struct list_slot<T> *counter_list_slot;
    int displacement;

    if (index > abs(median_diff) && abs(median_diff) > abs(end_diff))
        {counter_list_slot = end; displacement = end_diff;}
    else if (index > abs(end_diff))
        {counter_list_slot = start; displacement = index;}
    else {counter_list_slot = median; displacement = median_diff;}


    for (int i = 0; i < abs(displacement); i++)
        counter_list_slot = displacement < 0 ? counter_list_slot->prev : counter_list_slot->next;

    return counter_list_slot;
}

template<typename T>
T List<T>::operator[](unsigned int index){
    struct list_slot<T> *slot = get_slot(index);
    if(slot) return slot->data;
    else return (T) NULL;
}

template<typename T>
bool List<T>::delete_slot(unsigned int index){
    struct list_slot<T> *target_slot = get_slot(index);
    if(!target_slot) return false; // not in list

    struct list_slot<T> *prev_slot = target_slot->prev;
    struct list_slot<T> *next_slot = target_slot->next;

    
    // Update pointers
    if (length == 1) start = median = end = NULL;
    else {
        // update median
        if(length % 2){ if(index<=GET_MEDIAN_INDEX(length)) median = median->next; }
        else if (index>=GET_MEDIAN_INDEX(length)) median = median->prev;

        // update list_slot pointers, start, and end
        if (!prev_slot){
            next_slot->prev = NULL;
            start = next_slot;
        } else if (!next_slot) {
            prev_slot->next = NULL;
            end = prev_slot;
        } else { 
            prev_slot->next = next_slot;
            next_slot->prev = prev_slot;
        }
    }
    
    length -= 1;
    delete target_slot;

    return true;
}

template<typename T>
void List<T>::clear(){
    if (!length) return;
    
    // march and delete
    struct list_slot<T> *slot = start;
    while(slot->next){
        slot = slot->next;
        delete slot->prev;
    }
    delete slot;

    // Update pointers
    start = median = end = NULL;
    length = 0;
}

template<typename T>
bool List<T>::put(T data, unsigned int index){
    if (index < length) {
        get_slot(index)->data = data; 
        return true; }
    
    struct list_slot<T> *new_slot = new list_slot<T>();
    new_slot->data = data;
    if (length){
        end->next = new_slot;
        new_slot->prev = end;
        end = new_slot;
        if(length % 2) median = median->next;
    } else {
        start = median = end = new_slot;
    }
    length += 1;
    return true;
}

template<typename T>
bool List<T>::put_front(T data, unsigned int index){
    if (index >= length) return false;
    
    
    struct list_slot<T> *target_slot = get_slot(index);
    struct list_slot<T> *new_slot = new list_slot<T>();
    new_slot->data = data;
    if(index) {new_slot->prev = target_slot->prev; target_slot->prev->next = new_slot;}
    else start = new_slot;
    new_slot->next = target_slot;
    target_slot->prev = new_slot;

    if(!(length % 2)) {if(index <= GET_MEDIAN_INDEX(length)) median = median->prev;}
    else if(index > GET_MEDIAN_INDEX(length)) median = median->next;

    length += 1;
    return true;
}

template<typename T>
bool List<T>::put_behind(T data, unsigned int index){
    if (index >= length) return false;
    
    
    struct list_slot<T> *target_slot = get_slot(index);
    struct list_slot<T> *new_slot = new list_slot<T>();
    new_slot->data = data;
    if(index == length -1) {end = new_slot;}
    else {new_slot->next = target_slot->next; target_slot->next->prev = new_slot;}
    new_slot->prev = target_slot;
    target_slot->next = new_slot;

    if(!(length % 2)) {if(index < GET_MEDIAN_INDEX(length)) median = median->prev;}
    else if(index >= GET_MEDIAN_INDEX(length)) median = median->next;

    length += 1;
    return true;
}


template<typename T>
bool List<T>::is_in_list(T data){
    struct list_slot<T> *slot = start;
    while(slot){
        if (slot->data == data) return true;
        slot = slot->next;
    }
    return false;
}
        
template<typename T>
std::string List<T>::get_repr() { 
    std::string s = "[";
    struct list_slot<T> *slot = start;
    while(slot) {
        s += std::to_string(slot->data);
        slot = slot->next;
        if(slot) s += ", ";
    }
    s += "]";
    return s;
}

template<typename T>
int List<T>::get_length() {
    return length;
}
