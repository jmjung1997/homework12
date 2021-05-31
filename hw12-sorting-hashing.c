/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	printf("JEONG JAE MIN       2018038067\n\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)//초기화 함수
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)//동적할당 해제함수
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)//출력함수
{
	if (a == NULL) {//아무것도 없을 때
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//해싱함수 key값 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//해싱함수 bucket값 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)//선택 정렬 함수
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//선택정렬
	{
		minindex = i;//minindex 설정
		min = a[i];//min 값을 정렬 시작하는 초기값으로 지정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])//만약 기존의 min값 보다 작은값을 발견하면
			{
				min = a[j];//현재 index에있는 값을 min으로 지정
				minindex = j;//현재 index를 minindex로 지정
			}
		}
		a[minindex] = a[i];//초기에 있는 값을 바꾼 index 위치로 이동
		a[i] = min;//찾은 가장 작은 값을 초기 a[i]로 보낸다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)//삽입정렬 함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)//MAX_ARRAY_SIZE수만큼 반복
	{
		t = a[i]; //i의 원소를 t에 대입한다
		j = i;//현재 시작한 인덱스 i를 j로 한다
		while (a[j-1] > t && j > 0)//뒤에서 부터 비교해가면서 삽입하는 정렬 형태로 a[j-1]>t이면 j>0일때 까지 반복하면서 앞 쪽 인덱스와 교체 해준다
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)//버블 정렬 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//전체 데이터 갯수만큼 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//j=0번째 시작 데이터로하여 오른쪽 옆 데이터와 비교하며 교체한다
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)//쉘 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//쉘 정렬하는 간격을 h/2를 반복하면서 실행한다
	{
		for (i = 0; i < h; i++)//
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//삽입정렬과 똑같은 알고리즘으로 간격 h를 두고 부분 삽입 정렬을 한다
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)//퀵정렬
{
	int v, t;
	int i, j;

	if (n > 1)//n이 초과일때
	{
		v = a[n-1];//피봇을 설정한다
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);//피봇보다 작은 수
			while(a[--j] > v);//피봇보다 큰 수

			if (i >= j) break;//low와 high가 엇갈리면 반복을 멈춘다
			t = a[i];//low와 high가 엇갈리지 않았다면 i와 j를 교체한다
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];/*피봇 값을 가운대로 교환한다*/
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);//앞부분 부터 정렬
		quickSort(a+i+1, n-i-1);//뒷부분 부터 정렬
	}


	return 0;
}

int hashCode(int key) {//해싱함수에서 key값을 반환해주는 함수
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)//해싱함수
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//해싱테이블 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)//해싱테이블 처음으로 데이터 들어갈때
		{
			hashtable[hashcode] = key;
		} else 	{//해싱테이블에 충돌이 일어날때

			index = hashcode;//현재 hashcode index로 입력

			while(hashtable[index] != -1)//비어 있는 버켓을 찾을때 까지 반복한다
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;//비어있는 버켓에 key값을 담는다
		}
	}

	return 0;
}

int search(int *ht, int key)//탐색하는 함수
{
	int index = hashCode(key);//찾고자하는 key값과 그에 해당하는 hashcode를 index에 넣는다

	if(ht[index] == key)//만약 key값과 ht[index]값이 일치하면 해당 index를 반환한다
		return index;

	while(ht[++index] != key)//만약 key값과 ht[index]값이 일치하지 않으면 선형조사법으로 찾는다
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



