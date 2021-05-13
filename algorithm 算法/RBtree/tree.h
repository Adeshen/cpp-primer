#pragma once
#include<iostream>


//#define red 0;
const int red = 0;
//#define black 1;
const int black = 1;

struct treeNode {
	treeNode* father=nullptr;
	treeNode* left=nullptr;
	treeNode* right=nullptr;

	int key=0;
	int color=black;
};



class tree
{
	treeNode* root;          //根节点
	treeNode* nil;           //哨兵

	//初始化一棵树
	tree();
	tree(treeNode Root);
	tree(treeNode* Root);
	~tree()=default;

	//旋转  ：左旋、右旋
	void leftRotate(treeNode* x);    //顶点左旋      peak  is api
	void rightRotate(treeNode* x);    //顶点右旋
	
	//插入
	void insertFixup(treeNode* z);
	void treeInsert(treeNode* z);
	

	//删除
	void treeDelete(treeNode* x);

};
/*还有删除没有实现



