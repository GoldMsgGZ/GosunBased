//////////////////////////////////////////////////////////////////////////
//
// 本项目是GXX基础库链表测试工程
//
// 测试目标如下：
// 链表使用范例
// 链表效率
// ...

#include "..\ext\Foundation\GxxList.hpp"
#include <string>
#include <iostream>

// 先定义自己的节点类
class MyNode
{
public:
	MyNode() {}
	~MyNode() {}

public:
	std::string node_info_;
};
 

// 定义节点申请和释放函数
//StruGxxListNode<MyNode>* _FunPtrCallocNode(void *pUserData)
//{
//	StruGxxListNode<MyNode>* node = new StruGxxListNode<MyNode>;
//	node->data.node_info_ = ""
//}
//
//void _FunPtrFreeNode(StruGxxListNode<MyNode>* pNode, void *pUserData)
//{
//
//}

int main(int argc, const char *argv[])
{
	GxxList<MyNode> *GxxMyNodeList = new GxxList<MyNode>;

	// 添加节点
	MyNode node;

	for (int index = 0; index < 10; ++index)
	{
		char value[4096] = {0};
		sprintf_s(value, 4096, "this is the %d demo...", index);

		node.node_info_ = value;
		GxxMyNodeList->push_back(node);
	}

	// 遍历节点
	GxxList<MyNode>::iterator iter;
	for (iter = GxxMyNodeList->begin(); iter != GxxMyNodeList->end(); ++iter)
	{
		std::cout<<iter->node_info_.c_str()<<std::endl;
	}

	// 删除节点
	GxxList<MyNode>::MyListNode *pNode = GxxMyNodeList->pop_front_node();
	std::cout<<"弹出的节点为："<<pNode->data.node_info_.c_str()<<std::endl;

	return 0;
}