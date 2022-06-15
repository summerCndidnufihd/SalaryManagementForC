#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct doubleList doubleList;

//��̬�����ڴ��Ƕ�̬���룬�Զ����� 
//No.3 ��������ϵͳ--->�ṹ���װ
struct zgzg{
	char id[10];
	char name[10];
	float Officesalary, Yearsalary, dutysalary, jisalary, sumsalary, perduty, realsalary;
};
/*1.�����ѽṹ������ͽṹ�����������һ��*/
//˫���������Ͷ������  
struct doubleList{
	struct zgzg data;
	doubleList *front;
	doubleList *tail;
}DuLNode, *DuLinkList;

//��������
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

//No.1 ��������
struct doubleList* createList(){
	//��̬�ڴ����룬��ͷ������ʹ��ǰ��Ҫ��ʼ�� 
	struct doubleList* headNode = (struct doubleList*)malloc(sizeof(struct doubleList));
	headNode->front = headNode->tail = headNode;
	return headNode;
}
//�������--->���û����������---->���
struct doubleList* createNode(struct zgzg data){
	//��������--->�������״̬---->��ʼ���ṹ�����еĳ�Ա
	//����˫�������е�������Ա��ʼ�� 
	struct doubleList* newNode = (struct doubleList*)malloc(sizeof(struct doubleList));
	newNode->data = data;
	newNode->front = NULL;
	newNode->tail = NULL;
	return newNode;
}



//No.1�����棬�˵�
void printMenu(){
	printf("\n\n\n");
	printf("\t\t\t==========================ְ�����ʹ���ϵͳ=======================\n");
	printf("\t\t\t    |����������������������0.��        ��������������������|\n");
	printf("\t\t\t    |����������������������1.����Ա����Ϣ������������������|\n");
	printf("\t\t\t    |����������������������2.�޸�Ա����Ϣ������������������|\n");
	printf("\t\t\t    |����������������������3.���Ա����Ϣ������������������|\n");
	printf("\t\t\t    |����������������������4.ɾ��Ա����Ϣ������������������|\n");
	printf("\t\t\t    |����������������������5.����Ա����Ϣ������������������|\n");
	printf("\t\t\t    |����������������������6.���Ա����Ϣ������������������|\n");
	//printf("\t\t\t    |����������������������7.���ݹ������򡪡���������������|\n");
	printf("���������ѡ��");
}

//No.2 ��������
void keyDown(doubleList *list){
	int choice = 0;
	//struct zgzg data;//��ʱ�洢��Ϣ
	scanf("%d", &choice);
	switch (choice)
	{
	case 0://�˳� 
		printf("�˳���\n");
		system("pause");
		exit(0);
		break;
	case 1://����
		FindById(list);
		break;
	case 2://�޸�
		modifyWorkerById(list);
		printf("�޸ĳɹ������ɰ�6�����һ��Ӵ~��");
		saveInfoToFile("zg.dat", list);
		break;
	case 3://���
		printf("������Ҫ��ӵ�Ա���Ĺ��š���������λ���ʡ�н�����ʡ�ְ���������Ч����:");
		AddByTail(list);
		printf("��ӳɹ������ɰ�6�����һ��Ӵ~��");
		saveInfoToFile("zg.dat", list);
		break;
	case 4://ɾ�� 
		deleteAppoinByid(list);
		printf("ɾ���ɹ������ɰ�6�����һ��Ӵ~��");
		saveInfoToFile("zg.dat", list);
		break;
	case 5://����
		saveInfoToFile("zg.dat", list);
		printf("����ɹ������ɰ�6�����һ��Ӵ~��");
		break;
	case 6://��� 
		List(list);
		break;
	/*case 7://���� 
		bubbleSortById(list);
		printf("������ɣ�\n");
		break;*/
	default:
		printf("�������");
		break;
	}
}

//1.���ң�
void FindById(doubleList *headNode){
	doubleList *Pmove = headNode->tail;
	char id[10];
	printf("������Ҫ���ҵ�Ա���Ĺ��ţ�\n");
	scanf("%s", id);
	while (Pmove != headNode && strcmp(Pmove->data.id, id)){
		Pmove = Pmove->tail;
	}
	if (Pmove == headNode){
		printf("���Ҳ�����\n");
	}
	else{
		printf("���ҳɹ���\n");
		printf("����\t����\t��λ����\tн������\tְ�����\t��Ч����\tӦ������\t��������˰\tʵ������\n");
		printf("%s\t\t%s\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
	}
}
//����ʵ�����ʡ���������˰��Ӧ������
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
//2.�޸� 
void modifyWorkerById(doubleList *headNode){
	doubleList *Pmove = headNode->tail;
	char id[10];
	printf("������Ҫ�޸ĵ�Ա���Ĺ��ţ�\n");
	scanf("%s", id);
	while (Pmove != headNode && strcmp(Pmove->data.id, id)){
		Pmove = Pmove->tail;
	}
	if (Pmove == headNode){
		printf("���Ҳ���,�޷��޸ģ�\n");
	}
	else{
		int choice = 0;
		printf("����\t����\t��λ����\tн������\tְ�����\t��Ч����\tӦ������\t��������˰\tʵ������\n");
		printf("%s\t\t%s\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
		printf("\n");
		printf("=============1:�޸Ĺ���=============\n"); printf("=============2:�޸�����=============\n"); printf("=============3:�޸ĸ�λ����=============\n");
		printf("=============4:�޸�н������=============\n"); printf("=============5:�޸�ְ�����=============\n"); printf("=============6:�޸ļ�Ч����=============\n");
		printf("���������ѡ��");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("������Ҫ�޸ĵĹ��ţ�");
			scanf("%s", Pmove->data.id);
			break;
		case 2:
			printf("������Ҫ�޸ĵ����֣�");
			scanf("%s", Pmove->data.name);
			break;
		case 3:
			printf("������Ҫ�޸ĵĸ�λ���ʣ�");
			scanf("%f", &Pmove->data.Officesalary);
			summerize(Pmove);
			break;
		case 4:
			printf("������Ҫ�޸ĵ�н�����ʣ�");
			scanf("%f", &Pmove->data.Yearsalary);
			summerize(Pmove);
			break;
		case 5:
			printf("������Ҫ�޸ĵ�ְ�������");
			scanf("%f", &Pmove->data.dutysalary);
			summerize(Pmove);
			break;
		case 6:
			printf("������Ҫ�޸ĵļ�Ч���ʣ�");
			scanf("%f", &Pmove->data.jisalary);
			summerize(Pmove);
			break;
		default:
			printf("�������");
			break;
		}

	}
}
//3.��ӣ�˫�������β��ӣ����룩
void Add(doubleList *headNode, struct zgzg data){
	//����Ҫ���û������ݱ��һ���ڵ� 
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
	//����Ӧ�����ʡ���������˰��ʵ������
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
//4.ɾ����ָ��λ��ɾ��
void deleteAppoinByid(doubleList *headNode){
	doubleList *delNode = headNode->tail;
	char id[10];
	printf("������Ҫɾ����Ա���Ĺ��ţ�\n");
	scanf("%s", id);
	while (delNode != headNode && strcmp(delNode->data.id, id)){
		delNode = delNode->tail;
	}
	if (delNode == headNode){
		printf("���Ҳ������޷�ɾ����\n");
	}
	else{
		delNode->front->tail = delNode->tail;
		delNode->tail->front = delNode->front;
		free(delNode);
		delNode = NULL;
	}
}

//4.��ӡ���������
void List(doubleList *headNode){
	//��Ϊ�б�ͷ������Ҫ�ӵڶ�����㿪ʼ��ӡ 
	doubleList *Pmove = headNode->tail;
	printf("����\t����\t��λ����\tн������\tְ�����\t��Ч����\tӦ������\t��������˰\tʵ������\n");
	while (Pmove != headNode){
		printf("%s\t\t%s\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
		Pmove = Pmove->tail;
	}
	printf("\n");
}

//ð������
void bubbleSortById(doubleList *headNode){
	doubleList *firstNode = headNode->tail;
	doubleList *secondNode = headNode;
	while (firstNode != headNode){
		while (firstNode->tail != headNode){
			if (firstNode->data.id > firstNode->tail->data.id){
				//����
				/*firstNode->front->tail = firstNode->tail;
				firstNode->tail->front = firstNode->front;
				firstNode->tail->tail = firstNode;
				firstNode->front = firstNode->tail;*/
				struct zgzg t;//������doubleList��ת�����Ͳ�һ��
				t = firstNode->data;
				firstNode->data = firstNode->tail->data;
				firstNode->tail->data = t;
			}
			firstNode = firstNode->tail;
		}
		firstNode = secondNode->tail;
		secondNode = firstNode;//��һ��ð�ݽ������ٵ��ڶ���ð��
	}
}


//����������
int main(){
	doubleList *list = createList();
	readInfoFromFile("zg.dat", list);
	while (1){
		printMenu();
		keyDown(list);
		system("pause");
		system("cls");
	}
	getchar();//��ֹ���� 
	return 0;
}

//��ȡ����һ��ʱ��Ҫ���ļ��е����ݶ�ȡ��������
void readInfoFromFile(char *fileName, doubleList *headNode){
	FILE *fp = fopen(fileName, "r");
	//�п�
	if (fp == NULL){
		fp = fopen(fileName, "w+");//w+��ʾ�ɶ���д+��������
	}
	//fscanf��ȡ
	struct zgzg data;//��ʱ�洢 
	while (fscanf(fp, "%s\t\t%s\t\t%f\t\t%f\t\t%f\t\t%f\t\t%f\t\t%f\t\t%f\n", data.id, data.name, &data.Officesalary,
		&data.Yearsalary, &data.dutysalary, &data.jisalary, &data.sumsalary, &data.perduty, &data.realsalary) != EOF){
		Add(headNode, data);
	}
	fclose(fp);
}
//�����ļ����������е�����д���ļ���
void saveInfoToFile(char *fileName, doubleList *headNode){
	FILE *fp = fopen(fileName, "w");
	//�п�
	//fprintf д��
	doubleList *Pmove = headNode->tail;
	while (Pmove != headNode){
		fprintf(fp, "%s\t\t%s\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\t\t%.lf\n", Pmove->data.id, Pmove->data.name, Pmove->data.Officesalary, Pmove->data.Yearsalary,
			Pmove->data.dutysalary, Pmove->data.jisalary, Pmove->data.sumsalary, Pmove->data.perduty, Pmove->data.realsalary);
		Pmove = Pmove->tail;
	}
	fclose(fp);
}



