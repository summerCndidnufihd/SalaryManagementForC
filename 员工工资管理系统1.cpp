#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct doubleList doubleList;

//动态链表，内存是动态申请，自动连接 
//No.3 管理数据系统--->结构体封装
struct zgzg{
	char id[10];
	char name[10];
	float Officesalary, Yearsalary, dutysalary, jisalary, sumsalary, perduty, realsalary;
};
/*1.链表：把结构体变量和结构体变量连接在一起*/
//双向链表类型定义语句  
struct doubleList{
	struct zgzg data;
	doubleList *front;
	doubleList *tail;
}DuLNode, *DuLinkList;

//函数声明
struct doubleList* createList();
struct doubleList* createNode(struct zgzg data);
void printMenu();
void keyDown(doubleList *list);
void modifyWorkerById(doubleList *headNode);
void deleteAppoinByid(struct doubleList *headNode);
void AddByTail(struct doubleList *headNode);
void FindById(doubleList *headNode);
void List(doubleList *headNode);
void Add(doubleList list, struct zgzg data);
void readInfoFromFile(char *fileName, doubleList *headNode);
void saveInfoToFile(char *fileName, doubleList *headNode);
void bubbleSortById(doubleList *headNode);

//No.1 创建链表
struct doubleList* createList(){
	//动态内存申请，表头，变量使用前需要初始化 
	struct doubleList* headNode = (struct doubleList*)malloc(sizeof(struct doubleList));
	headNode->front = headNode->tail = headNode;
	return headNode;
}
//创建结点--->把用户输入的数据---->结点
struct doubleList* createNode(struct zgzg data){
	//创建过程--->描述最初状态---->初始化结构变量中的成员
	//即把双向链表中的三个成员初始化 
	struct doubleList* newNode = (struct doubleList*)malloc(sizeof(struct doubleList));
	newNode->data = data;
	newNode->front = NULL;
	newNode->tail = NULL;
	return newNode;
}



//No.1做界面，菜单
void printMenu(){
	printf("\n\n\n");
	printf("\t\t\t==========================职工工资管理系统=======================\n");
	printf("\t\t\t    |———————————0.退        出—————————|\n");
	printf("\t\t\t    |———————————1.查找员工信息—————————|\n");
	printf("\t\t\t    |———————————2.修改员工信息—————————|\n");
	printf("\t\t\t    |———————————3.添加员工信息—————————|\n");
	printf("\t\t\t    |———————————4.删除员工信息—————————|\n");
	printf("\t\t\t    |———————————5.保存员工信息—————————|\n");
	printf("\t\t\t    |———————————6.浏览员工信息—————————|\n");
	//printf("\t\t\t    |———————————7.根据工号排序—————————|\n");
	printf("请输出您的选择：");
}

//No.2 按键交互
void keyDown(doubleList *list){
	int choice = 0;
	//struct zgzg data;//临时存储信息
	scanf("%d", &choice);
	switch (choice)
	{
	case 0://退出 
		printf("退出！\n");
		system("pause");
		exit(0);
		break;
	case 1://查找
		FindById(list);
		break;
	case 2://修改
		modifyWorkerById(list);
		printf("修改成功！（可按6键浏览一下哟~）");
		saveInfoToFile("zg.dat", list);
		break;
	case 3://添加
		printf("请输入要添加的员工的工号、姓名、岗位工资、薪级工资、职务津贴、绩效工资:");
		AddByTail(list);
		printf("添加成功！（可按6键浏览一下哟~）");
		saveInfoToFile("zg.dat", list);
		break;
	case 4://删除 
		deleteAppoinByid(list);
		printf("删除成功！（可按6键浏览一下哟~）");
		saveInfoToFile("zg.dat", list);
		break;
	case 5://保存
		saveInfoToFile("zg.dat", list);
		printf("保存成功！（可按6键浏览一下哟~）");
		break;
	case 6://浏览 
		List(list);
		break;
	/*case 7://排序 
		bubbleSortById(list);
		printf("排序完成！\n");
		break;*/
	default:
		printf("输入错误！");
		break;
	}
}

//1.查找：
void FindById(doubleList *headNode){
	doubleList *Pmove = headNode->tail;
	char id[10];
	printf("请输入要查找的员工的工号：\n");
	scanf("%s", id);
	while (Pmove != headNode && strcmp(Pmove->data.id, id)){
		Pmove = Pmove->tail;
	}
	if (Pmove == headNode){
		printf("查找不到！\n");
	}
	else{
		printf("查找成功！\n");
		printf("工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\t应发工资\t个人所得税\t实发工资\n");
		printf("%s\t\t%s\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
	}
}
//计算实发工资、个人所得税、应发工资
void summerize(doubleList *Pmove){
	Pmove->data.sumsalary = Pmove->data.Officesalary + Pmove->data.Yearsalary + Pmove->data.dutysalary + Pmove->data.jisalary;
	if (Pmove->data.sumsalary <= 500) Pmove->data.perduty = (float)Pmove->data.sumsalary*0.05;
	else if (Pmove->data.sumsalary <= 2000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.1;
	else if (Pmove->data.sumsalary <= 5000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.15;
	else if (Pmove->data.sumsalary <= 20000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.2;
	else if (Pmove->data.sumsalary <= 40000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.25;
	else if (Pmove->data.sumsalary <= 60000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.3;
	else if (Pmove->data.sumsalary <= 80000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.35;
	else if (Pmove->data.sumsalary <= 100000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.4;
	else Pmove->data.perduty = Pmove->data.sumsalary*0.45;
	Pmove->data.realsalary = Pmove->data.sumsalary - Pmove->data.perduty;
}
//2.修改 
void modifyWorkerById(doubleList *headNode){
	doubleList *Pmove = headNode->tail;
	char id[10];
	printf("请输入要修改的员工的工号：\n");
	scanf("%s", id);
	while (Pmove != headNode && strcmp(Pmove->data.id, id)){
		Pmove = Pmove->tail;
	}
	if (Pmove == headNode){
		printf("查找不到,无法修改！\n");
	}
	else{
		int choice = 0;
		printf("工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\t应发工资\t个人所得税\t实发工资\n");
		printf("%s\t\t%s\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
		printf("\n");
		printf("=============1:修改工号=============\n"); printf("=============2:修改名字=============\n"); printf("=============3:修改岗位工资=============\n");
		printf("=============4:修改薪级工资=============\n"); printf("=============5:修改职务津贴=============\n"); printf("=============6:修改绩效工资=============\n");
		printf("请输入你的选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("请输入要修改的工号：");
			scanf("%s", Pmove->data.id);
			break;
		case 2:
			printf("请输入要修改的名字：");
			scanf("%s", Pmove->data.name);
			break;
		case 3:
			printf("请输入要修改的岗位工资：");
			scanf("%f", &Pmove->data.Officesalary);
			summerize(Pmove);
			break;
		case 4:
			printf("请输入要修改的薪级工资：");
			scanf("%f", &Pmove->data.Yearsalary);
			summerize(Pmove);
			break;
		case 5:
			printf("请输入要修改的职务津贴：");
			scanf("%f", &Pmove->data.dutysalary);
			summerize(Pmove);
			break;
		case 6:
			printf("请输入要修改的绩效工资：");
			scanf("%f", &Pmove->data.jisalary);
			summerize(Pmove);
			break;
		default:
			printf("输出错误！");
			break;
		}

	}
}
//3.添加：双向链表表尾添加（插入）
void Add(doubleList *headNode, struct zgzg data){
	//首先要将用户的数据变成一个节点 
	struct doubleList *newNode = createNode(data);
	struct doubleList *tailNode = headNode->front;
	tailNode->tail = newNode;
	newNode->front = tailNode;
	headNode->front = newNode;
	newNode->tail = headNode;
}
//
void AddByTail(doubleList *headNode){
	doubleList *Pmove = (struct doubleList*)malloc(sizeof(struct doubleList));
	struct doubleList *tailNode = headNode->front;
	scanf("%s%s%f%f%f%f", Pmove->data.id, Pmove->data.name, &Pmove->data.Officesalary, &Pmove->data.Yearsalary,
		&Pmove->data.dutysalary, &Pmove->data.jisalary);
	//计算应发工资、个人所得税、实发工资
	Pmove->data.sumsalary = Pmove->data.Officesalary + Pmove->data.Yearsalary + Pmove->data.dutysalary + Pmove->data.jisalary;
	if (Pmove->data.sumsalary <= 500) Pmove->data.perduty = Pmove->data.sumsalary*0.05;
	else if (Pmove->data.sumsalary <= 2000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.1;
	else if (Pmove->data.sumsalary <= 5000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.15;
	else if (Pmove->data.sumsalary <= 20000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.2;
	else if (Pmove->data.sumsalary <= 40000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.25;
	else if (Pmove->data.sumsalary <= 60000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.3;
	else if (Pmove->data.sumsalary <= 80000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.35;
	else if (Pmove->data.sumsalary <= 100000)  Pmove->data.perduty = (float)Pmove->data.sumsalary*0.4;
	else Pmove->data.perduty = Pmove->data.sumsalary*0.45;
	Pmove->data.realsalary = Pmove->data.sumsalary - Pmove->data.perduty;
	struct doubleList *newNode = createNode(Pmove->data);
	tailNode->tail = newNode;
	newNode->front = tailNode;
	headNode->front = newNode;
	newNode->tail = headNode;
}
//4.删除：指定位置删除
void deleteAppoinByid(doubleList *headNode){
	doubleList *delNode = headNode->tail;
	char id[10];
	printf("请输入要删除的员工的工号：\n");
	scanf("%s", id);
	while (delNode != headNode && strcmp(delNode->data.id, id)){
		delNode = delNode->tail;
	}
	if (delNode == headNode){
		printf("查找不到，无法删除！\n");
	}
	else{
		delNode->front->tail = delNode->tail;
		delNode->tail->front = delNode->front;
		free(delNode);
		delNode = NULL;
	}
}

//4.打印：输出内容
void List(doubleList *headNode){
	//因为有表头，所以要从第二个结点开始打印 
	doubleList *Pmove = headNode->tail;
	printf("工号\t姓名\t岗位工资\t薪级工资\t职务津贴\t绩效工资\t应发工资\t个人所得税\t实发工资\n");
	while (Pmove != headNode){
		printf("%s\t\t%s\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
		Pmove = Pmove->tail;
	}
	printf("\n");
}

//冒泡排序法
void bubbleSortById(doubleList *headNode){
	doubleList *firstNode = headNode->tail;
	doubleList *secondNode = headNode;
	while (firstNode != headNode){
		while (firstNode->tail != headNode){
			if (firstNode->data.id > firstNode->tail->data.id){
				//交换
				/*firstNode->front->tail = firstNode->tail;
				firstNode->tail->front = firstNode->front;
				firstNode->tail->tail = firstNode;
				firstNode->front = firstNode->tail;*/
				struct zgzg t;//不能用doubleList，转换类型不一样
				t = firstNode->data;
				firstNode->data = firstNode->tail->data;
				firstNode->tail->data = t;
			}
			firstNode = firstNode->tail;
		}
		firstNode = secondNode->tail;
		secondNode = firstNode;//第一轮冒泡结束后再到第二个冒泡
	}
}


//主函数内容
int main(){
	doubleList *list = createList();
	readInfoFromFile("zg.dat", list);
	while (1){
		printMenu();
		keyDown(list);
		system("pause");
		system("cls");
	}
	getchar();//防止闪屏 
	return 0;
}

//读取：第一次时需要把文件中的内容读取到链表中
void readInfoFromFile(char *fileName, doubleList *headNode){
	FILE *fp = fopen(fileName, "r");
	//判空
	if (fp == NULL){
		fp = fopen(fileName, "w+");//w+表示可读可写+创建功能
	}
	//fscanf读取
	struct zgzg data;//临时存储 
	while (fscanf(fp, "%s\t\t%s\t\t%f\t\t%f\t\t%f\t\t%f\t\t%f\t\t%f\t\t%f\n", data.id, data.name, &data.Officesalary,
		&data.Yearsalary, &data.dutysalary, &data.jisalary, &data.sumsalary, &data.perduty, &data.realsalary) != EOF){
		Add(headNode, data);
	}
	fclose(fp);
}
//保存文件：把链表中的内容写到文件中
void saveInfoToFile(char *fileName, doubleList *headNode){
	FILE *fp = fopen(fileName, "w");
	//判空
	//fprintf 写入
	doubleList *Pmove = headNode->tail;
	while (Pmove != headNode){
		fprintf(fp, "%s\t\t%s\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
		Pmove = Pmove->tail;
	}
	fclose(fp);
}



