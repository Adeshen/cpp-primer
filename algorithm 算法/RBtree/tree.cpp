#include "tree.h"
//初始化

tree::tree() {
	this->nil->right = this -> root;
	this->nil->left = this->root;
	this->root->father = this->nil;
}

tree::tree(treeNode Root) {
	*(this->root) = Root;
	this->nil->right = this->root;
	this->nil->left = this->root;
	this->root->father = this->nil;
}

tree::tree(treeNode* Root) {
	this->root = root;
	this->nil->right = this->root;
	this->nil->left = this->root;
	this->root->father = this->nil;
}


//旋转
void  tree::leftRotate(treeNode* x) {
	treeNode* y = x->right;
	x->right = y->left;
	if (y->left != this->nil) {
		y->left->father = x;
	};
	if (x == this->root) {
		this->root = y;
	};
	if (x == x->father->left) {
		x->father->left = y;
	};
	if (x == x->father->right) {
		x->father->right = y;
	};

	y->father = x->father;
	y->left = x;
	x->father = y;

};

void tree::rightRotate(treeNode* x) {
	treeNode* y = x->left;
	x->left = y->right;
	if (y->right != nil) {
		y->right->father = x;
	};
	if (x == this->root) {
		this->root = y;
	};
	if (x == x->father->left) {
		x->father->left = y;
	};
	if (x == x->father->right) {
		x->father->right = y;
	};
	y->father = x->father;
	y->right = x;
	x->father = y;
}

//插入

void tree::treeInsert(treeNode* z) {
	treeNode* y = this->nil;      //初始化一个节点
	treeNode* x = this->root;       //双指针
	while (x != this->nil) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else x = x->right;
	};//结束后x指向nil,y 指向x的父节点。
	z->father = y;
	if (y == this->nil)
		this->root = y;     //空树
	if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = this->nil;
	z->right = this->nil;
	z->color = red;
	insertFixup(z);

};


void tree::insertFixup(treeNode* z)
{
	if (z->father->color == black) {
		return;           
	}

	treeNode* father = z->father;
	treeNode* uncle=nullptr;
	if (father->father->left = father) {
		uncle = father->father->right;
		//红叔叔
	

		//黑叔叔    右叔叔
		if (uncle->color == black) {
			if (z == father->right) {
				leftRotate(z->father);
			}
			father->father->color = red;
			rightRotate(father->father);
			father->color = black;

		}
	}
	if (father->father->right = father) {
		uncle = father->father->left;
		
		if (uncle->color == black) {
			if (z == father->left) {
				rightRotate(z->father);
			}
			father->father->color = red;
			leftRotate(father->father);
			father->color = black;

		}



	}
	if (uncle->color == red) {
		father->color = black;
		uncle->color = black;
		father->father->color = red;
		insertFixup(father);

	}
	

};

treeNode* tree::find(int key) {
	treeNode* temp = this->root;
	while (key != temp->key && temp != nil)
	{
		if (key > temp->key) {
			temp = temp->right;
		}
		else {
			temp = temp->left;
		}
	}

	if (key = temp->key) {
		return temp;
	}
	if (key != temp->key) {
		cout << "there is not it!" << endl;
	}


}
