//////////////////////////////////////////////////////////////////////////
//
// ����Ŀ��GXX������������Թ���
//
// ����Ŀ�����£�
// ����ʹ�÷���
// ����Ч��
// ...

#include "..\ext\Foundation\GxxList.hpp"
#include <string>
#include <iostream>

// �ȶ����Լ��Ľڵ���
class MyNode
{
public:
	MyNode() {}
	~MyNode() {}

public:
	std::string node_info_;
};
 

// ����ڵ�������ͷź���
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

	// ��ӽڵ�
	MyNode node;

	for (int index = 0; index < 10; ++index)
	{
		char value[4096] = {0};
		sprintf_s(value, 4096, "this is the %d demo...", index);

		node.node_info_ = value;
		GxxMyNodeList->push_back(node);
	}

	// �����ڵ�
	GxxList<MyNode>::iterator iter;
	for (iter = GxxMyNodeList->begin(); iter != GxxMyNodeList->end(); ++iter)
	{
		std::cout<<iter->node_info_.c_str()<<std::endl;
	}

	// ɾ���ڵ�
	GxxList<MyNode>::MyListNode *pNode = GxxMyNodeList->pop_front_node();
	std::cout<<"�����Ľڵ�Ϊ��"<<pNode->data.node_info_.c_str()<<std::endl;

	return 0;
}