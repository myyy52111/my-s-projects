#define _CRT_SECURE_NO_WARNINGS //��ֹ������ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3.�������
//��ʲô�������ݣ�------���飬���� ---���������ڴ棬������ɢ�ڴ�
struct bookInfo
{
	char name[20];//����
	float price;//�۸� 
	int num; //������� 
};
struct Node
{
	struct bookInfo data;
	struct Node* next;
 };
 struct Node* list=NULL; 
  //��������
 //������ͷ����ͷ��һ���ṹ�����
 struct Node* createHead()
 {
 	//ָ���������ж�̬�ڴ����� 
 	struct Node* headNode=(struct Node*)malloc(sizeof(struct Node));
 	headNode->next=NULL;
 	return headNode;
 } 
  //�����ڵ㣺Ϊ������׼��
  struct Node* createNode(struct bookInfo data) 
 {
 	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
 	 newNode->data=data;
	 newNode->next=NULL;
 	return newNode;
 }
 //����
 void insertNodeByHead(struct Node* headNode,struct bookInfo data)
 {
 	struct Node* newNode=createNode(data);
 	newNode->next=headNode->next;
	 headNode->next=newNode; 
  } 
 // void insertNodeByTail(struct Node* headNode,int data) //��β���� 
  //{
  	//struct Node* pMove=headNode;
	  //while(pMove->next!=NULL)
	  //{
	  	//pMove=pMove->next; 
	   //} 
	   //struct Node* newNode=createNode(data);
	   //pMove->next=newNode;
   //} 
   //ָ��ɾ�� 
   void deleteNodeByName(struct Node* headNode, char *bookName)
   {
   	struct Node* posLeftNode=headNode;
   	struct Node* posNode=headNode->next;
   	//�鼮�������ַ������ַ����ȽϺ��� 
	   while(posNode!=NULL&&strcmp(posNode->data.name,bookName))
	   {
	   posLeftNode=posNode;
	   posNode=posLeftNode->next;
	   }
	   if(posNode==NULL)
	   return;
	   else
   	{
   		printf("ɾ���ɹ���\n"); 
   		posLeftNode->next=posNode->next;
		   free(posNode);
		   posNode =NULL;
	   }
   }
   //�������
   struct Node* searchByName(struct Node* headNode,char* bookName)
   {
   	struct Node* posNode=headNode->next;
   	while(posNode!=NULL&&strcmp(posNode->data.name,bookName))
   	{
   		posNode=posNode->next;
	   }
	   return posNode;
	} 
 //��ӡ���� 
void printList(struct Node* headNode)
{
	struct Node* pMove=headNode->next;
	printf("����\t�۸�\t����\n"); 
	while(pMove!=NULL)
	{
		//����� 
		printf("%s\t%.1f\t%d\n",pMove->data.name,pMove->data.price,pMove->data.num);
		pMove=pMove->next;
	}
 } 

 
//1.д����
void makeMenu()
{
	printf("--------------------------------------------------\n"); 
	printf("С��ͼ�����ϵͳ\n");
	printf("\t0.�˳�ϵͳ\n");
	printf("\t1.�Ǽ��鼮\n");
	printf("\t2.����鼮\n");
	printf("\t3.�����鼮\n");
	printf("\t4.�黹�鼮\n");
	printf("\t5.�鼮����\n");
	printf("\t6.ɾ���鼮\n");
	printf("\t7.�����鼮\n");
	printf("������(0~7)��");
	printf("--------------------------------------------------\n"); 
 } 
 //ֱ���ļ�����
 //�� 
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
  //�� 
  void readInfoFile(const char* fileName, struct Node* headNode)
 {
 	FILE* fp=fopen(fileName,"r");//��һ�δ��ļ��϶������� 
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
  //�㷨��һ��˼�루ð������
  void bubbleSortList(struct Node* headNode)
  {
  	for (struct Node* p=headNode->next;p!=NULL;p=p->next)
  	{
	for (struct Node* q=headNode->next;q!=NULL;q=q->next)
	{ 
	if(q->data.price>q->next->data.price)
	{
		//����ֵ
		struct bookInfo tempData=q->data;
		q->data=q->next->data;
		q->next->data=tempData; 
	 } 
	  }
   } 
   printList(headNode);
}
   
 //2.������������������
 void KeyDown()
 {
 	int userkey=0;
 	struct bookInfo tempBook;//����һ����ʱ�����洢�鼮��Ϣ 
 	struct Node* result=NULL;
	 scanf("%d", & userkey); 
 	switch (userkey)
 	{
 		 case 0:
		  printf("[�˳�] \n");
		  printf("�˳��ɹ�\n");
		  system("pause");
		  exit(0);             //�ر��������� 
		  break;
		 case 1:
		 printf("[�Ǽ�] \n");
		 printf("�����鼮��Ϣ(name,price,num):");
		 scanf("%s%f%d",tempBook.name,&tempBook.price,&tempBook.num); 
		 insertNodeByHead(list,tempBook);
		 saveInfoToFile("bookInfo.txt",list);
		 		  break;
		 case 2:
		 printf("[���] \n");
		 printList(list);
		  break;
		 case 3:
		 printf("[����] \n"); //�鼮���ڿ��Խ���
		 printf("��������ĵ�������");
		 scanf("%s",tempBook.name);
		 result=searchByName(list,tempBook.name);
		 if(result==NULL)
		 {
		 	printf("û������鼮���޷����ģ�\n");
		 }
		 else
		 {
		 	if(result->data.num>0)
		 	{
		 		result->data.num--;
		 		printf("���ĳɹ���\n");
			 }
			 else
			 {
			 	printf("��ǰ�鼮�޿�棬����ʧ��!\n");
			 }
		 }
		  break;
		 case 4: 
		 printf("[�黹] \n");
		  printf("������黹��������");
		 scanf("%s",tempBook.name);
		 result=searchByName(list,tempBook.name);
		 if(result==NULL)
		 {
		 	printf("������Դ�Ƿ���\n");
		 }
		 else
		 {
		 	result->data.num++;
			 printf("�鼮�黹�ɹ���\n"); 
		 }
		  break;
		 case 5:
		 printf("[����] \n");
		 bubbleSortList(list);
		  break;
		 case 6:
		 printf("[ɾ��] \n");
		 printf("������ɾ���鼮�����֣�");
		 scanf("%s",tempBook.name);
		 deleteNodeByName(list,tempBook.name);
		saveInfoToFile("bookInfo.txt",list);
		  break;
		 case 7:
		 printf("[����] \n");
		 printf("������Ҫ��ѯ���鼮��");
		 scanf("%s",tempBook.name);
		  result=searchByName(list,tempBook.name);
		  if(result==NULL)
		  {
		  	printf("δ�ҵ������Ϣ��\n");
		  }
		  else
		  {
		  	printf("����\t�۸�\t����\n");
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
	  //  	for(int i=0;i<3;i++) //��ӡ210 
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

