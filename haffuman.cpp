#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996);
#define MaxSize 1000
#define N 1000


//��ʱ��ű����������������ݣ��������浽�ļ�
char textTemp[N];

typedef struct HuffmanNode //����������������
{
	char c;
	int weight;  //Ȩֵ
	int parent;  //���ڵ�
	int lchild, rchild;  //���Һ��ӱ��
}HuffmanNode;

typedef struct
{
	char cd[N];                 //��Ź�������
	int start;                  //��start��ʼ��cd�еĹ�������
}HCode;

//������������
void CreateHT(HuffmanNode ht[], int n)                //�������������ht[],�ͽڵ���n
{
	int i, k, lnode, rnode;
	int min1, min2;
	for (i = 0; i<2 * n - 1; i++) {
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;    //���н���������ó�ֵ-1
	}
	for (i = n; i<2 * n - 1; i++)                   //�����������
	{
		min1 = min2 = 32767;                //int�ķ�Χ��-32768-32767
		lnode = rnode = -1;                  //lnode��rnode��¼��СȨֵ���������λ��
		for (k = 0; k <= i - 1; k++)
		{
			if (ht[k].parent == -1)               //ֻ����δ����������Ľ���в���
			{
				if (ht[k].weight<min1)           //��ȨֵС����С����ڵ��Ȩֵ
				{
					min2 = min1;
					rnode = lnode;
					min1 = ht[k].weight;
					lnode = k;
				}
				else if (ht[k].weight<min2)
				{
					min2 = ht[k].weight;
					rnode = k;
				}
			}
		}
		ht[lnode].parent = i;
		ht[rnode].parent = i;                //������С�ڵ�ĸ��ڵ���i
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;       //������С�ڵ�ĸ��ڵ�ȨֵΪ������С�ڵ�Ȩֵ֮��
		ht[i].lchild = lnode;
		ht[i].rchild = rnode;                 //���ڵ����ڵ���ҽڵ�
		ht[i].parent = -1;         //��ʾ�½��Ӧ���Ǹ����
	}
}

/*
���ݹ������������������
HuffmanNode[] ��������
HCode[]  �����
*/
void CreateHCode(HuffmanNode ht[], HCode hcd[], int n) //���������
{
	int i, f, c;
	HCode hc;
	for (i = 0; i<n; i++)                            //���ݹ������������������
	{
		hc.start = n;
		c = i;
		f = ht[i].parent;
		while (f != -1)                              //ѭ��ֱ������������ѭ��
		{
			if (ht[f].lchild == c) {                        //�������ӽ��
				hc.cd[hc.start--] = '0';
			}
			else {                                    //�����Һ��ӽ��
				hc.cd[hc.start--] = '1';
			}
			c = f;
			f = ht[f].parent;
		}
		hc.start++;                               //startָ�����������hc.cd[]���ʼ�ַ�
		hcd[i] = hc;
	}
}

//�������������
void DispHCode(HuffmanNode ht[], HCode hcd[], int n)     //���������������б�
{
	//if(ht[0].weight==NULL) printf("hh");
	int i, k;
	printf("  �������������:\n");
	for (i = 0; i<n; i++)									//���data�е��������ݣ���a-z
	{
		printf("      %c:\t", ht[i].c);
		for (k = hcd[i].start; k <= n; k++)                    //�������data�����ݵı���
		{
			printf("%c", hcd[i].cd[k]);
		}
		printf("\n");
	}
}

void saveText()

{
	FILE *fp;
	char temp[20];
	printf("�Ƿ���Ҫ�ѽ�����浽�ļ�y/n");
	scanf("%s", temp);
	if (temp[0] == 'n' || temp[0] == 'N')
	{
		return;
	}
	printf("�����ļ���");
	scanf("%s", temp);
	fp = fopen(temp, "w");
	if (!fp)
	{
		printf("�򿪻��������ļ�ʧ��\n");
		return;
	}
	for (int i = 0; textTemp[i]!='\0'; i++)
	{
		fprintf(fp, "%c", textTemp[i]);
	}
	fclose(fp);
}

/*
���ݱ������ַ������б���

char* string  ��Ҫ������ַ�������
HuffmanNode[] ��������
HCode[]  �����
*/
void enHCode(char* string, HuffmanNode ht[], HCode hcd[], int n)
{
	int i, j, k;
	int count = 0;
	memset(textTemp, 0, sizeof(textTemp));
	for (i = 0; string[i] != '\0'; i++)
	{
		for (j = 0; j<n; j++)
		{
			if (string[i] == ht[j].c)            //ѭ�������������ַ���ͬ�ı�ţ���ͬ�ľ��������ַ��ı���
			{
				for (k = hcd[j].start; k <= n; k++)
				{
					printf("%c", hcd[j].cd[k]);
					textTemp[count] = hcd[j].cd[k];
					count++;
				}
				break;                      //�����ɺ�������ǰforѭ��
			}
		}
		if (j == n) {
			printf("\n%cδ���룬������в����ڸ÷���", string[i]);
			//return;
		}
		
	}
	printf("\n");
	saveText();
}
	


/*
char* temp ��Ҫ�����01�ַ���
HuffmanNode[] ��������
HCode[]  �����
*/
void deHcode(HuffmanNode ht[], int n,char* temp)
{
	int i = 0;
	int j = n * 2 - 1 - 1; //�Ӹ��ڵ㿪ʼ����;
	int count = 0;
	char te[20];
	memset(textTemp, 0, sizeof(textTemp));
	while (temp[i] != '\0')
	{
		if (temp[i] == '0')
			j = ht[j].lchild;
		else
			j = ht[j].rchild;
		if (ht[j].rchild == -1)
		{
			printf("%c", ht[j].c);
			textTemp[count] = ht[j].c;
			j = n * 2 - 1 - 1; //�Ӹ��ڵ㿪ʼ����
			count++;
		}
		i++;
	}
	printf("\n");
	saveText();
}



/*
��ȡin.txt
�ļ��и�ʽΪ
abcde //��Ҫ���ɱ�������ĸ
2 5 7 9 12 //��Ӧ��Ȩֵ

HuffmanNode[] ��������
HCode[]  �����
���ز�ͬ�ַ��ĸ���
*/
int readHC( HuffmanNode ht[])
{
	char fileCode[2][1000];
	int i = 0;
	int len = 0;
	FILE *fp = fopen("in.txt", "r");
	memset(fileCode, 0, sizeof(fileCode));
	if (NULL == fp)
	{
		printf("���ļ�ʧ��\n");
		return 1;
	}
	printf("�ļ�����Ϊ\n");
	while (!feof(fp))
	{
		fgets(fileCode[i], sizeof(fileCode) - 1, fp); // ������\n  
		printf("%s", fileCode[i]);
		i++;
	}
	while (fileCode[0][len]!='\n')  //��ȡ�ַ�
	{
		ht[len].c = fileCode[0][len];
		len++;
	}
	i = 0;
	len = 0;
	while (fileCode[1][i] != 0)//��ȡ�ַ���Ӧ��Ȩֵ
	{
		if (fileCode[1][i]-32 != 0)
		{
			ht[len].weight = fileCode[1][i]- 48;
			len++;
		}
		i++;
	}
	fclose(fp);
	printf("\n");
	return len;
}

/*
test.txt һƪ����
table.txt �ַ������26����ĸ��Сд �ͣ� �� ���԰�����Ҫ���ļ���������

HuffmanNode[] ��������
HCode[]  �����
*/

int readText(HuffmanNode ht[])
{
	char table[60];   //��¼��ĸ�������ж��ڵĸ���
	int tableCount[60] = { 0 };
	char text[1000][1000] = { 0 };    //��ʱ���һƬ����
	int i = 0, j = 0, len = 0,cai=0;
	char temp[60];
	FILE *fp1 = fopen("test.txt", "r");
	FILE *fp2 = fopen("table.txt", "r");
	if (NULL == fp1 || fp2 == NULL)
	{
		printf("�򲻿����ļ�\n");
		return -1;
	}
	memset(table, 0, sizeof(table));
	memset(temp, 0, sizeof(temp));
	fgets(temp, sizeof(temp) - 1, fp2);
	while (temp[len] != '\0')//��ȡ��ĸ�����ݵ�������  len��ĸ����
	{
		table[len] = temp[len];
		len++;
	}
	while (!feof(fp1))  //��ʱ���һƬ����
	{
		fgets(text[i], sizeof(text) - 1, fp1); //
		i++;
	}
	printf("�ַ�\t����\n");
	for (int k = 0; k < len; k++)   //������ĸ��Ӧ�ĸ���
	{
		i = 0;
		while (text[i][0] != '\0')//�����о�ͷ
		{
			j = 0;
			while (text[i][j] != '\0')   //�����о�ͷ
			{
				if (table[k] == text[i][j])
				{
					tableCount[k]++;
				}
				j++;
			}
			i++;
		}
		if (tableCount[k]!=0)
		{
			ht[cai].c = table[k];
			ht[cai].weight = tableCount[k];
			printf("%c\t%d\n", ht[cai].c, ht[cai].weight);
			cai++;
		}
	}
	
	fclose(fp1);
	fclose(fp2);
	return cai;//���ز�ͬ���͵��ַ�����
}

/*
char str[] �ַ�������  ����������������
HuffmanNode[] ��������
*/
int buitlHu(char str[], HuffmanNode ht[])
{
	char table[60];   //��¼��ĸ�������ж��ڵĸ���
	int tableCount[60] = { 0 };
	int i = 0, j = 0, len = 0, cai = 0;
	FILE *fp2 = fopen("table.txt", "r");
	if (fp2 == NULL)
	{
		printf("���ļ�ʧ��\n");
		return 0;
	}
	memset(table, 0, sizeof(table));
	fgets(table, sizeof(table) - 1, fp2);
	
	printf("�ַ�\t����\n");
	for (int k = 0; table[k]!='\0'; k++)   //������ĸ��Ӧ�ĸ���
	{
		i = 0;
		while (str[i] != '\0')//�����о�ͷ
		{
			if (table[k] == str[i])
			{
				tableCount[k]++;
			}
			i++;
		}
		if (tableCount[k] != '\0')
		{
			ht[cai].c = table[k];
			ht[cai].weight = tableCount[k];
			printf("%c\t%d\n", ht[cai].c, ht[cai].weight);
			cai++;
		}
	}
	fclose(fp2);
	return cai;
}

/*
���ļ��е��ַ��� ���ݱ�������Ϊ 01��
char* name �ļ���
HuffmanNode[] ��������
HCode[]  �����
int n ����������Ԫ�ظ���
*/
void textEnCode(char* name, HuffmanNode ht[], HCode hcd[], int n)
{
	char str[MaxSize];
	FILE* fp1 = fopen(name, "r");
	if (fp1==NULL)
	{
		printf("���ļ�ʧ��\n");
		return;
	}
	while (!feof(fp1))
	{
		fgets(str, sizeof(str), fp1); // ������\n  
	}
	printf("��Ҫ������ַ���Ϊ\n%s\n", str);
	printf("����Ϊ\n");
	enHCode(str, ht, hcd, n);
	fclose(fp1);
}

/*
���ļ��е�01����������
char* name �ļ���
HuffmanNode[] ��������
int n ����������Ԫ�ظ���
*/
void textDeCode(char* textNname, HuffmanNode ht[], int n)
{
	char str[MaxSize];
	FILE* fp1 = fopen(textNname, "r");
	if (fp1 == NULL)
	{
		printf("���ļ�ʧ��\n");
		return;
	}

	while (!feof(fp1))
	{
		fgets(str, sizeof(str), fp1); // ������\n  
	}
	printf("����Ϊ\n%s\n", str);
	printf("����Ϊ\n");
	deHcode( ht,n, str);
	fclose(fp1);
}
/*
1 �ܲ˵�
2 �Ӳ˵�
*/
void menu(int n)
{
	if (n==1)
	{
		printf("/****************���ı�������ϵͳ**********************************/\n");
		printf("		(1)����������������\n");
		printf("		(2)��������\n");
		printf("		(3)�����ַ������б���\n");
		printf("		(4)����01����������\n");
		printf("		(5)�ļ�����\n");
		printf("		(6)�ļ�����\n");
		printf("		(7)�뿪\n");
		printf("/********************************************************/\n");
	}
	if (n==2)
	{
		system("cls");
		printf("/*********************������������*****************************/\n");
		printf("		(0)�����ַ��������Զ�������������\n");
		//intf("		(1)�ֶ������ַ��Ͷ�ӦȨֵ�����������\n");
		printf("		(2)�Զ���ȡin.txt�е��ַ���Ȩֵ�����������\n");
		printf("		(3)�Զ���ȡһƪ������test.txt�����������\n");
		printf("		ȡ�� (��������)\n");
		printf("/********************************************************/\n");
	}

}

//�Ӳ˵�
void menue2(int &num, HuffmanNode ht[], HCode hcd[])
{
	int select;
	char str[MaxSize];
	menu(2);
	if (ht[0].c == NULL)
	{
		printf("\n!!!!!���Ƚ�����������!!!!!!!\n");
	}
	printf("����嵥��ѡ��һ������: ");
	scanf("%d", &select);
	//���ѡ�����½������������������������
	if (select == 0||select == 1 || select == 2 || select == 3)
	{
		memset(ht, 0, sizeof(ht)*N);
		memset(hcd, 0, sizeof(hcd)*MaxSize);
	}

	switch (select)
	{
	case 0:
		printf("����һ���ַ���\n");
		scanf("%s", str);
		num=buitlHu(str, ht);
		break;
	case 1:
		printf("��������볤�ȣ����26����");
		scanf("%d", &num);
		while (num>26)
		{
			printf("\n����Ƿ�����������\n");
			scanf("%d", &num);
		}
		for (int i = 0; i<num; i++)
		{
			printf("�������%d�ַ���", i + 1);
			getchar();
			ht[i].c = getchar();
			getchar();
			printf("������Ȩֵ��");
			scanf("%d", &(ht[i].weight));
		}
		break;
	case 2:
		num = readHC(ht);
		break;
	case 3:
		num = readText(ht);
		break;
	default:
		return;
	}
	if (num==0)
	{
		printf("����ʧ��\n");
		return;
	}
	CreateHT(ht, num);
	CreateHCode(ht, hcd, num);
	printf("!!�������������������!!\n");

	Sleep(2000);
	return;

}
//�˵�
void menue1(HuffmanNode ht[],HCode hcd[])
{
	int select=1;
	int num=0;
	int flag = 0;
	char temp[MaxSize]; //Ҫ�������
	char string[MaxSize];//Ҫ�����
	while (1)
	{
		memset(temp, 0, sizeof(temp));
		memset(temp, 0, sizeof(string));
		menu(1);
		if (ht[0].c==NULL)
		{
			printf("���Ƚ�����������");
			select = 1;
		}
		switch (select)
		{
		case 1:
			menue2(num, ht, hcd);
			flag = 1;
			system("cls");
			menu(1);
			break;
		case 2:	
			DispHCode(ht, hcd, num); 
			break;
		case 3: 
			printf("������Ҫ����ı���(���200���ַ�):");
			scanf("%s", string, MaxSize);                       //��Ҫ���б�����ַ�������string������
			printf("\n���������:\n");
			enHCode(string, ht, hcd, num);
			
			break;
		case 4: 
			
			printf("������Ҫ�����0,1���봮��������(���200���ַ�)");
			scanf("%s", temp, MaxSize);
			printf("����Ϊ:");
			deHcode(ht, num, temp);
			break;
		case 5:
			printf("�����ļ���:  ");
			scanf("%s", temp);
			textEnCode(temp, ht, hcd, num);
			//textEnCode("code.txt", ht, hcd, num);
			break;
		case 6:
			printf("�����ļ���:  ");
			scanf("%s", temp);
			textDeCode(temp, ht,num);
			//textDeCode("encode.txt", ht, num);
			break;
		case 7:
			exit(2);
			break;
		default:
			printf("�������ָ������������\n");
			break;
		}
		printf("����嵥��ѡ��һ������: ");
		scanf("%d", &select);
		system("cls");
	}
}
int main() //������
{
	HuffmanNode ht[N];
	HCode hcd[MaxSize];
	menue1(ht, hcd);
}
