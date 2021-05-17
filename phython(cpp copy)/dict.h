#pragma once
#include<iostream>
using namespace std;
template<class T,class W>
class dict {
	T * dict_key;
	W * dict_text;
	int space;
public:
	
	dict<T, W>(int space=16) {
		dict_key = (T*)malloc(space * sizeof(T));
		dict_text = (W*)malloc(space * sizeof(W));
		this->space = space;
	}
	~dict<T, W>() {
		delete this->dict_key;
		delete this->dict_text;
	}


	void set(T key, W text,int index) {
		if (index > this->space-1||index<0) {
			cout << "error,your index is over than max" << endl;
			return;
		}
		this->dict_key[index] = key;
		this->dict_text[index] = text;

	}

	void resetspace(int newSpace) {
		T *newKEY= (T*)malloc(space * sizeof(T));
		T *newTEXT=(W*)malloc(space * sizeof(W));
		for (int i = 0; i < space; i++) {
			newKEY[i] = this->dict_key[i];
			newTEXT[i] = this->dict_text[i];
		}
		delete this->dict_key;
		delete this->dict_text;

		this->dict_key = newKEY;
		this->dict_text = newTEXT;
		this->space = newSpace;
		return;


	}
	W operator[](T key) {
		int i = 0;
		while (i < this->space) {
			if (this->dict_key == key) {
				break;
			}
			i++;
		}
		return this->dict_text[i];

	}

	


	void show() {
		for (int i = 0; i < this->space; i++) {
			cout <<i<< "      "<< this->dict_key[i] << "：" << this->dict_text[i] << endl;
		}
		return;
	}

};
