#define _CRT_SECURE_NO_WARNINGS //防止内扩张 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3.数据设计
//用什么处理数据？------数组，链表 ---数组连续内存，链表零散内存
struct bookInfo
{
	char name[20];//书名
	float price;//价格 
	int num; //书的数量 
};
struct Node
{
	struct bookInfo data;
	struct Node* next;
 };
 struct Node* list=NULL; 
  //创建链表
 //创建表头：表头是一个结构体变量
 struct Node* createHead()
 {
 	//指针变变量进行动态内存申请 
 	struct Node* headNode=(struct Node*)malloc(sizeof(struct Node));
 	headNode->next=NULL;
 	return headNode;
 } 
  //创建节点：为插入做准备
  struct Node* createNode(struct bookInfo data) 
 {
 	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
 	 newNode->data=data;
	 newNode->next=NULL;
 	return newNode;
 }
 //插入
 void insertNodeByHead(struct Node* headNode,struct bookInfo data)
 {
 	struct Node* newNode=createNode(data);
 	newNode->next=headNode->next;
	 headNode->next=newNode; 
  } 
 // void insertNodeByTail(struct Node* headNode,int data) //表尾插入 
  //{
  	//struct Node* pMove=headNode;
	  //while(pMove->next!=NULL)
	  //{
	  	//pMove=pMove->next; 
	   //} 
	   //struct Node* newNode=createNode(data);
	   //pMove->next=newNode;
   //} 
   //指定删除 
   void deleteNodeByName(struct Node* headNode, char *bookName)
   {
   	struct Node* posLeftNode=headNode;
   	struct Node* posNode=headNode->next;
   	//书籍名字是字符串，字符串比较函数 
	   while(posNode!=NULL&&strcmp(posNode->data.name,bookName))
	   {
	   posLeftNode=posNode;
	   posNode=posLeftNode->next;
	   }
	   if(posNode==NULL)
	   return;
	   else
   	{
   		printf("删除成功！\n"); 
   		posLeftNode->next=posNode->next;
		   free(posNode);
		   posNode =NULL;
	   }
   }
   //链表查找
   struct Node* searchByName(struct Node* headNode,char* bookName)
   {
   	struct Node* posNode=headNode->next;
   	while(posNode!=NULL&&strcmp(posNode->data.name,bookName))
   	{
   		posNode=posNode->next;
	   }
	   return posNode;
	} 
 //打印链表 
void printList(struct Node* headNode)
{
	struct Node* pMove=headNode->next;
	printf("书名\t价格\t数量\n"); 
	while(pMove!=NULL)
	{
		//剥洋葱 
		printf("%s\t%.1f\t%d\n",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove=pMove->next;
	}
 } 

 
//1.写界面
void makeMenu()
{
	printf("--------------------------------------------------\n"); 
	printf("小四图书管理系统\n");
	printf("\t0.退出系统\n");
	printf("\t1.登记书籍\n");
	printf("\t2.浏览书籍\n");
	printf("\t3.借阅书籍\n");
	printf("\t4.归还书籍\n");
	printf("\t5.书籍排序\n");
	printf("\t6.删除书籍\n");
	printf("\t7.查找书籍\n");
	printf("请输入(0~7)：");
	printf("--------------------------------------------------\n"); 
 } 
 //直接文件操作
 //存 
 void saveInfoToFile(const char* fileName, struct Node* headNode)
 {
 	FILE* fp=fopen(fileName,"w");
	 struct Node* pMove=headNode->next;
	 while(pMove!=NULL)
	 {
	fprintf(fp,"%s\t%.1f\t%d\n",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove=pMove->next;
	  } 
	 fclose(fp); 
  } 
  //读 
  void readInfoFile(const char* fileName, struct Node* headNode)
 {
 	FILE* fp=fopen(fileName,"r");//第一次打开文件肯定不存在 
 	if(fp==NULL)
 	{
 		fp=fopen(fileName,"w+");
		 	 }
	 struct bookInfo tempData;
	 while(fscanf(fp,"%s\t%f\t%d\n",tempData.name,&tempData.price,&tempData.num)!=EOF)
	 {
	 	insertNodeByHead(list,tempData);
	 }
	 fclose(fp); 
  } 
  //算法是一种思想（冒泡排序）
  void bubbleSortList(struct Node* headNode)
  {
  	for (struct Node* p=headNode->next;p!=NULL;p=p->next)
  	{
	for (struct Node* q=headNode->next;q!=NULL;q=q->next)
	{ 
	if(q->data.price>q->next->data.price)
	{
		//交换值
		struct bookInfo tempData=q->data;
		q->data=q->next->data;
		q->next->data=tempData; 
	 } 
	  }
   } 
   printList(headNode);
}
   
 //2.做交互，做按键处理
 void KeyDown()
 {
 	int userkey=0;
 	struct bookInfo tempBook;//产生一个临时变量存储书籍信息 
 	struct Node* result=NULL;
	 scanf("%d", & userkey); 
 	switch (userkey)
 	{
 		 case 0:
		  printf("[退出] \n");
		  printf("退出成功\n");
		  system("pause");
		  exit(0);             //关闭整个程序 
		  break;
		 case 1:
		 printf("[登记] \n");
		 printf("输入书籍信息(name,price,num):");
		 scanf("%s%f%d",tempBook.name,&tempBook.price,&tempBook.num); 
		 insertNodeByHead(list,tempBook);
		 saveInfoToFile("bookInfo.txt",list);
		 		  break;
		 case 2:
		 printf("[浏览] \n");
		 printList(list);
		  break;
		 case 3:
		 printf("[借阅] \n"); //书籍存在可以借阅
		 printf("请输入借阅的书名：");
		 scanf("%s",tempBook.name);
		 result=searchByName(list,tempBook.name);
		 if(result==NULL)
		 {
		 	printf("没有相关书籍，无法借阅！\n");
		 }
		 else
		 {
		 	if(result->data.num>0)
		 	{
		 		result->data.num--;
		 		printf("借阅成功！\n");
			 }
			 else
			 {
			 	printf("当前书籍无库存，借阅失败!\n");
			 }
		 }
		  break;
		 case 4: 
		 printf("[归还] \n");
		  printf("请输入归还的书名：");
		 scanf("%s",tempBook.name);
		 result=searchByName(list,tempBook.name);
		 if(result==NULL)
		 {
		 	printf("该书来源非法！\n");
		 }
		 else
		 {
		 	result->data.num++;
			 printf("书籍归还成功！\n"); 
		 }
		  break;
		 case 5:
		 printf("[排序] \n");
		 bubbleSortList(list);
		  break;
		 case 6:
		 printf("[删除] \n");
		 printf("请输入删除书籍的名字：");
		 scanf("%s",tempBook.name);
		 deleteNodeByName(list,tempBook.name);
		saveInfoToFile("bookInfo.txt",list);
		  break;
		 case 7:
		 printf("[查找] \n");
		 printf("请输入要查询的书籍：");
		 scanf("%s",tempBook.name);
		  result=searchByName(list,tempBook.name);
		  if(result==NULL)
		  {
		  	printf("未找到相关信息！\n");
		  }
		  else
		  {
		  	printf("书名\t价格\t数量\n");
		  	printf("%s\t%.1f\t%d\n",result->data.name,result->data.price,result->data.num);
		  }
		  break;
		 default:
		 printf("[error] \n");
		  break; 
	 }
  } 
  int main()
  {
  	//struct Node* list =createHead();
	  //  	for(int i=0;i<3;i++) //打印210 
	    //	{
	    //		insertNodeByHead(list,i);
		//	}
		//	printList(list);
		
			//	struct Node* list =createHead();
			// insertNodeByTail(list,1);
			//insertNodeByTail(list,2);
			//printList(list);
			list=createHead(); 
			readInfoFile("bookInfo.txt",list);
  	while(1)
  	{
  		makeMenu();
  		KeyDown();
  		system("pause");
		  system("cls");
		  	  }
		  	  system("pause");
		  	  return 0;
  }

