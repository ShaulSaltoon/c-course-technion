#include <stdio.h>
#include <stdbool.h>
#define N 16
#define M 4
#define MAX_BYTE_VALUE 16
#define KEY_SIZE_MESSAGE 0
#define KEY_MESSAGE 1
#define COLUMNS_MESSAGE 2
#define MESSAGE_TO_ENCRYPT 3
#define MESSAGE_ENCRYPTED 4
#define ROUND 10
/**  define more constants in this sections */

/** define the functions you need to use in this section */
void input_to_block(int m[][N], int column);
void key_input(int a[], int size);
/*main proccess functions*/
void shift_rows(int m[][M]);
void subBytes(int a[], int m[][M]);
void input_block_Test(int m[][M]);
void add_round_key(int a[], int size, int m[][M]);
void aes_round(int a[], int block[][M], int key_size, int key_code[], int m[][N], int start, bool full);
void block_round_main(int m[][N], int a[], int col, int key_size, int key_code[], int block[][M]);
/**
 *
 *
 *
 * @param message_code - the code of the message to be printed on
 *                       screen, the functionality was divided to two
 *                       print functions
 * the function prints the matching messages to the codes:
 * KEY_SIZE_MESSAGE - asks the user to enter the size of key
 * KEY_MESSAGE - asks the user to enter the key
 * COLUMNS_MESSAGE - asks the user to enter number of rows and
 *                        columns of the message
 * MESSAGE_TO_ENCRYPT - asks the user to enter a message that he want
 *                      to encrypt
 * MESSAGE_ENCRYPTED - prints a message implying that the following
 *                     message to be printed is the encrypted message
 *
 */
void print_function(int message_code);
int scanf_options(int n);
int scanf_func();

/**
 *
 * @param message - the message to be printed
 * @param rows - number of rows of the message
 * @param columns - number of columns of the message
 */
void print_message(int message[M][N], int rows, int columns);

void print_matrix(int m[][N], int n);
/** implement main program */

int main()
{
	int block[M][M] = {{0}};
	int map[MAX_BYTE_VALUE] = {10, 1, 2, 4, 7, 9, 14, 12,
							   3, 5, 6, 13, 15, 11, 8, 0};
	int rows = M, col = 0, key_size = 0;
	int main_matrix[M][N] = {{0}};

	print_function(KEY_SIZE_MESSAGE);
	scanf("%d", &key_size);
	print_function(KEY_MESSAGE);
	int key_code[key_size];

	for (int i = 0; i < key_size; i++)
	{
		scanf("%d", &key_code[i]);
	}
	print_function(COLUMNS_MESSAGE);
	scanf("%d", &col);
	print_function(MESSAGE_TO_ENCRYPT);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &main_matrix[i][j]);
		}
	}

	printf("%d", col / 4);

	block_round_main(main_matrix, map, col / 4, key_size, key_code, block);

	printf("finished\n");
	print_matrix(main_matrix, col);
	return 1;
}

/*main functions:*/
void block_round_main(int main_matrix[][N], int map[], int col, int key_size, int key_code[], int block[][M])
{
	bool full = false;
	for (int i = 0; i < col; i++)
	{

		for (int j = 0; j < M; j++)
		{
			for (int l = 0; l < M; l++)
			{
				block[j][l] = main_matrix[j][l + i * 4];
			}
		}
		printf("i is: %d \n", i);
		for (int l = 0; l < ROUND; l++)
		{
			aes_round(map, block, key_size, key_code, main_matrix, i * 4, full);
			printf("ok, ");
			full = true;
		}
		printf("\n");
	}
}
void aes_round(int a[], int block[][M], int key_size, int key_code[], int m[][N], int start, bool full)
{

	if (!full)
	{
		add_round_key(key_code, key_size, block);

		printf("false\n");
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				m[i][start + j] = block[i][j];
			}
		}
		return;
	}
	subBytes(a, block);
	shift_rows(block);
	add_round_key(key_code, key_size, block);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			m[i][start + j] = block[i][j];
		}
	}
}
/*basic operation functions:*/
void subBytes(int a[], int m[][M])
{
	int temp_m[M][M] = {{0}};
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			temp_m[i][j] = m[a[i * M + j] / 4][a[i * M + j] % 4];
		}
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			m[i][j] = temp_m[i][j];
		}
	}
}
/*void subBytes(int a[],int m[][M]){
	for(int i=0;i<M;i++){
		for(int j=0;j<M;j++){
			m[i][j]= a[i*M+j];

		}
	}
}*/
void shift_rows(int m[][M])
{
	int j;
	int a[M] = {0};
	for (int i = 0; i < M; i++)
	{
		for (j = 0; j < M; j++)
		{
			a[j] = m[i][j];
		}
		for (j = 0; j < M; j++)
		{
			m[i][j] = a[(j + i) % 4];
		}
	}
}
void add_round_key(int a[], int size, int m[][M])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			m[i][j] = (m[i][j] + a[(i + j) % size]) % MAX_BYTE_VALUE;
		}
	}
}

/** implement the functions you defined in this section */
void key_input(int a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &a[i]);
	}
}

void input_to_block(int m[][N], int column)
{
	printf("check\n");
	int n = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < column; j++)
		{
			scanf("%d", &n);
			m[i][j] = n;
		}
	}
}
/**integer scanf*/
int scanf_func()
{
	int input = 0;
	scanf("%d", &input);
	return input;
}

void print_function(int message_code)
{
	switch (message_code)
	{
	case KEY_SIZE_MESSAGE:
		printf("Enter size of key:\n");
		break;
	case KEY_MESSAGE:
		printf("Enter the key:\n");
		break;
	case COLUMNS_MESSAGE:
		printf("Enter the number of columns of the message:\n");
		break;
	case MESSAGE_TO_ENCRYPT:
		printf("Enter the message you want to encrypt:\n");
		break;
	case MESSAGE_ENCRYPTED:
		printf("Encrypted message:\n");
		break;
	}
}

void print_message(int message[M][N], int rows, int columns)
{
	print_function(MESSAGE_ENCRYPTED);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (j != columns - 1)
				printf("%d ", message[i][j]);
			else
				printf("%d\n", message[i][j]);
		}
	}
}
void input_block_Test(int m[][M])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d ", &m[i][j]);
		}
		printf("\n");
	}
}
void print_matrix(int m[][N], int n)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}
