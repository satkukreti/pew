#ifndef ZLL_H
#define ZLL_H

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T> *next = nullptr;
	Node<T> *prev = nullptr;
};

template <typename T>
class ZLL{
	private:
		Node<T> *hptr;
		Node<T> *tptr;
		int numElements;
		Node<T> *iterate;		
		
	public:
		ZLL<T>(){
			hptr = nullptr;
			tptr = nullptr;
			numElements = 0;
			iterate = hptr;
		}
		
		~ZLL<T>(){
			empty();
		}
		
		bool start(){
			iterate = hptr;
			if(hptr == nullptr){
				return false;			
			}
			return true;
		}

		bool done(){
			if(hptr == nullptr){
				return true;
			}
			if(iterate != nullptr){
				return false;			
			}
			return true;
		}

		T getNext(){
			if(this->done()){
				return 0;		
			}
			Node<T> *temp = iterate;
			iterate = iterate->next;
			return temp->data;
		}
		
		bool isEmpty(){
			if(hptr == nullptr){
				return true;
			}
			return false;		
		}
		
		bool empty(){
			while(hptr != nullptr){
				Node<T> *temp = hptr;
				hptr = hptr->next;
				delete temp;			
			}
			tptr = nullptr;
			iterate = hptr;
			numElements = 0;
			return true;
		}	
		
		bool front(const T &n){
			Node<T> *temp = new Node<T>;
			temp->data = n;
			
			if(temp == nullptr){
				return false;			
			}			
			
			if(hptr == nullptr){
				hptr = temp;
				tptr = temp;
				numElements++;
			} else {
				temp->next = hptr;
				hptr->prev = temp;
				hptr = temp;
				numElements++;
			}
			return true;
		}
		
		bool back(const T &n){
			Node<T> *temp = new Node<T>;
			temp->data = n;
			
			if(temp == nullptr){
				return false;			
			}						
			
			if(tptr == nullptr){
				hptr = temp;
				tptr = temp;
				numElements++;
			} else {
				tptr->next = temp;
				temp->prev = tptr;
				tptr = temp;
				numElements++;
			}
			return true;
		}

		bool join(ZLL<T> &other){
			if(other.hptr == nullptr){
				return true;			
			}			
			
			if(this == &other){
				return true;
			}
			
			if(hptr == nullptr){
				hptr = other.hptr;
				tptr = other.tptr;
				numElements += other.numElements;
			
				other.numElements = 0;		
				other.hptr = nullptr;
				other.tptr = nullptr;
				other.iterate = hptr;
			
				return true;	
			}

			tptr->next = other.hptr;
			other.hptr->prev = tptr;
			tptr = other.tptr;
			numElements += other.numElements;
			
			other.numElements = 0;		
			other.hptr = nullptr;
			other.tptr = nullptr;
			other.iterate = hptr;
			
			return true;
		}
		
		ZLL<T> &operator+=(const ZLL<T> &other){
			if(this != &other){
				Node<T> *temp = other.hptr;
				while(temp != nullptr){
					back(temp->data);
					temp = temp->next;
				}
				
			}
			return *this;		
		}
		
		ZLL<T> &operator-=(const ZLL<T> &other){
			if(this != &other){
				Node<T> *temp = other.hptr;
				while(temp != nullptr){
					//Node<T> *temp3 = temp->next;
					Node<T> *traverse = hptr;

					while(traverse != nullptr){
						Node<T> *temp2 = traverse->next;
						if(temp->data == traverse->data){
							Node<T> *suc = traverse->next;
							Node<T> *pred = traverse->prev;
							
							if(suc != nullptr){
								suc->prev = pred;							
							}
							if(pred != nullptr){
								pred->next = suc;							
							}
							if(traverse == hptr){
								hptr = suc;							
							}
							if(traverse == tptr){
								tptr = pred;							
							}
							delete traverse;				
						}
						
						traverse = temp2;								
					}
					temp = temp->next;		
				}
				
			}
			
			return *this;	
		}
		
		int removeZany(){
			int count = 0;
			
			Node<T> *temp = hptr;
			while(temp != nullptr){
				Node<T> *temp2 = temp->next;
				if	(isZany(temp->data)){
					Node<T> *suc = temp->next;
					Node<T> *pred = temp->prev;
			
					if(suc != nullptr){
						suc->prev = pred;							
					}
					if(pred != nullptr){
						pred->next = suc;							
					}
					if(temp == hptr){
						hptr = suc;							
					}
					if(temp == tptr){
						tptr = pred;							
					}
					delete temp;					
					
					count += 1;
					numElements--;
				}
				temp = temp2;
			}
			return count;				
		}
		
		int removeNonZany(){
			int count = 0;
			
			Node<T> *temp = hptr;
			while(temp != nullptr){
				Node<T> *temp2 = temp->next;
				if	(!(isZany(temp->data))){
					Node<T> *suc = temp->next;
					Node<T> *pred = temp->prev;
			
					if(suc != nullptr){
						suc->prev = pred;							
					}
					if(pred != nullptr){
						pred->next = suc;							
					}
					if(temp == hptr){
						hptr = suc;							
					}
					if(temp == tptr){
						tptr = pred;							
					}
					delete temp;					
					
					count += 1;
					numElements--;
				}
				temp = temp2;
			}
			return count;	
		}
		
		bool promoteZany(){
			ZLL<T> notZ;
			
			Node<T> *temp = hptr;
			while(temp != nullptr){
				notZ.back(temp->data);
				temp = temp->next;		
			}			
			
			bool toreturn;			
			
			this->removeNonZany();
			if(this->numElements == 0){
				toreturn = false;
			} else {
				toreturn = true;			
			}
			notZ.removeZany();
			this->join(notZ);
			
			return toreturn;
		}
		
		void printFront(){
			Node<T> *temp = hptr;
			while(temp != nullptr){
				cout << temp->data << endl;
				temp = temp->next;
			}
		}
		
		void printBack(){
			Node<T> *temp = tptr;
			while(temp != nullptr){
				cout << temp->data << endl;
				temp = temp->prev;
			}
		}
		
};

#endif //ZLL_H