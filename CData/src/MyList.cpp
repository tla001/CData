/*
 * MyList.cpp
 *
 *  Created on: 2016年9月1日
 *      Author: Administrator
 */

#include <MyList.h>

void errInfo(char *info,int status)
{
	cout<<*info<<endl;
	exit(status);
}
void normalInfo(char *info)
{
	cout<<*info<<endl;
}
void MyListTest()
{
	ArrList list1,list2,list3;
	int ret;
	ret=initList(&list1,10);
	if(ret<0){
		cout<<"init err"<<endl;
	}
	ret=isEmpty(&list1);
	if(0==ret){
		cout<<"list is empty"<<endl;
	}
	ret=initList(&list2,10);
	ret=initList(&list3,10);
	ElemType elem=1;
//	insertList(&list1,elem,0);
//	printArrList(&list1);
//	elem=2;
//	insertList(&list1,elem,0);
//	printArrList(&list1);
//	elem=3;
//	insertList(&list1,elem,1);
//	printArrList(&list1);
//	elem=4;
//	insertList(&list1,elem,3);
//	printArrList(&list1);
//	delList(&list1,2);
//	printArrList(&list1);
//	delList(&list1,0);
//	printArrList(&list1);

	int i;
	 int Bdata[5] = {1,3,2,4,6};
	for (i=0; i<5;i++) {
		insertList(&list1,  Bdata[i],  i);
	}
	//排序
	quickSort(&list1,0, list1.length-1);
	printArrList(&list1);
//	for( i=0;i<5;i++){
//		insertList(&list1,i+1,i);
//		insertList(&list2,i+2,i);
//	}
//	insertList(&list2,i+2,i);
//	mergeLists(&list1,&list2,&list3);
//	printArrList(&list1);
//	printArrList(&list2);
//	printArrList(&list3);
}

Status initList(ArrList *L,int length)
{
	if(length==0)length=ARRLIST_INIT_SIZE;
	ElemType *newbase=(ElemType *)malloc(length*sizeof(ArrList));
	L->elem=newbase;
	if(!L->elem){
		errInfo("malloc err",-1);
	}
	L->length=0;
	L->listSize=length;
	return 0;
}
Status isEmpty(ArrList *L)
{
	if(L->length==0)
		return 0;
	else
		return -1;
}
Status insertList(ArrList *L,ElemType elem,int pos)
{
	if(pos<0||pos>L->length)
		errInfo("insert:position is out of range",-1);
	if(L->length>=L->listSize){
		ElemType *newbase=(ElemType*)realloc(L->elem,(L->listSize+ARRLISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			errInfo("malloc err",-1);
		L->elem=newbase;
		L->listSize+=ARRLISTINCREMENT;
	}
	ElemType *p,*q;
	p=L->elem+pos;
	q=L->elem+L->length+1;
	while(q!=p){
		*q=*(q-1);
		q--;
	}
	*p=elem;
	L->length+=1;
	return 0;
}
Status delList(ArrList *L,int pos)
{
	if(pos<0||pos>L->length)
		errInfo("del:postion is out of range",-1);
	ElemType *p;
	p=L->elem+pos;
	while(p<L->elem+L->length){
		*p=*(p+1);
		p++;
	}
	L->length-=1;
	return 0;
}
Status mergeLists(ArrList *list1,ArrList *list2,ArrList *list3)
{
	ElemType *p1,*p2,*p3;
	list3->length=list1->length+list2->length;
	list3->elem=(ElemType*) malloc(list3->length*sizeof(ElemType));
	if(!list3->elem)
		errInfo("merger:err",-1);
	p1=list1->elem;
	p2=list2->elem;
	p3=list3->elem;
	while(p1<=&list1->elem[list1->length-1]&&p2<=&list2->elem[list2->length-1]){
		if(*p1<=*p2)*p3++=*p1++;
		else *p3++=*p2++;
	}
	while(p1<=&list1->elem[list1->length-1])*p3++=*p1++;
	while(p2<=&list2->elem[list2->length-1])*p3++=*p2++;
	return 0;
}
void printArrList(ArrList *L)
{
	for(int i=0;i<L->length;i++){
		cout<<*(L->elem+i)<<"\t";
	}
	cout<<endl;
}
Status quickSort(ArrList *list,int left,int right)
{
	if(left>right)
		return -1;
	ElemType pivotKey=list->elem[left];
	int i,j;
	ElemType temp;
	i=left;
	j=right;
	while(i!=j){
		while(list->elem[j]>=pivotKey&&i<j){
			j--;
		}
		while(list->elem[i]<=pivotKey&&i<j){
			i++;
		}
		if(i<j){
			temp=list->elem[i];
			list->elem[i]=list->elem[j];
			list->elem[j]=temp;
		}
	}
	list->elem[left]=list->elem[i];
	list->elem[i]=pivotKey;

	quickSort(list,left,i-1);
	quickSort(list,i+1,right);
	return 0;
}
/*****************************************************************************/
Status initLinkList(LinkList &list)
{
		list=(LinkList)malloc(sizeof(LNode));
		if(!list)
			errInfo("memory overflow",-1);
		list->next=NULL;
		return 0;
}
Status createLinkList(LinkList list,int n)
{
	if(!list)
		initLinkList(list);
	ElemType data;
	LinkList p1,p2=list;
	cout<<"input datas for "<<n<<" nodes"<<endl;
	for(int i=0;i<n;i++){
		p1=(LinkList)malloc(sizeof(LNode));//申请新节点
		cin>>data;
		p1->data=data;
		p1->next=p2->next;
		p2->next=p1;//p1始终指向新节点，p2始终指向尾节点
		p2=p1;
	}
	return 0;
}
Status printLinkList(LinkList list)
{
	int i=1;
	LinkList p=list->next;
	while(p!=NULL){
		cout<<"the data of "<<i<<" node = "<<p->data<<endl;
		i++;
		p=p->next;
	}
	return 0;
}
void testLinkList()
{
	LinkList list;
	initLinkList(list);
	createLinkList(list,5);
	printLinkList(list);
	insertLinkList(list,15,3);
	printLinkList(list);
	ElemType a=0;
	delLinkList(list,2,a);
	printLinkList(list);
	cout<<endl<<a<<endl;
}
Status insertLinkList(LinkList list,ElemType elem,int pos)//在pos后面插入
{
	LinkList p1,p2=list;
//	for(int i=0;i<pos;i++){
//		p2=p2->next;
//	}
	int i=0;
	while(p2&&i<pos){
		i++;
		p2=p2->next;
	}
	if(!p2->next||i>pos)
		errInfo("wrong pos",-1);
	p1=(LinkList) malloc(sizeof(LNode));
	p1->data=elem;
	p1->next=p2->next;
	p2->next=p1;
	return 0;
}
Status delLinkList(LinkList list,int pos,ElemType &elem)
{
	LinkList p1,p2=list;
	int i=0;
	while(p2&&i<pos-1){
		i++;
		p2=p2->next;
	}
	if(p2==NULL||i>pos-1)
		errInfo("err",-1);
	p1=p2->next;
	p2->next=p1->next;
	elem=p1->data;
	free(p1);
}
Status insertSort(LinkList list)
{

}
//需要对head赋值时，使用&
void mergeLinkList(LinkList &la,LinkList &lb,LinkList &lc)
{
	LinkList pa,pb,pc;
	pa=la->next;
	pb=lb->next;
	lc=pc=la;
	while(pa&&pb){
		if(pa->data>pb->data){
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}else{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}
	}
	pc->next=pa?pa:pb;
	free(pb);
}
