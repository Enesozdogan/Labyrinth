#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

char lab[MAX][MAX];
int visited[MAX][MAX];
int parent[MAX][2];

int rows;
int cols;
int bas_row;
int bas_col;
int puan=0;

enum yapi{
	bos,
	duvar,
	bitis,
	yol,
	elma
};

void delay(double number_of_seconds)
{
    
    int milli_seconds = 1000 * number_of_seconds;
  
    
    clock_t start_time = clock();
  
   
    while (clock() < start_time + milli_seconds)
        ;
}
void lab_al(char* dosya_adi){
	char c;
	int i,j;
	FILE* lab_file=fopen(dosya_adi,"r");
	
	//labirent alma islemi
	printf("satir sayisi:");
	scanf("%d",&rows);
	printf("sutun sayisi:");
	scanf("%d",&cols);
	
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {

			if ((c = getc(lab_file)) == '\n') {
				c = getc(lab_file);
			}

			lab[i][j] = c;

			if (c =='b') {
				bas_row = i;
				bas_col = j;
			}
		}
	}
	fclose(lab_file);
	
	
}
void doldur_visited(){
	int i,j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if (lab[i][j] == '+' || lab[i][j]=='-' || lab[i][j]=='|') {
				visited[i][j] = duvar;
			} 
			else if (lab[i][j] == 'c') {
				visited[i][j] = bitis;
			} 
			else if(lab[i][j]=='O'){
				visited[i][j]=elma;
			}
			else {
				visited[i][j] = bos;
			}
		}
	}
}
int dfs(int row, int col)
{
	int i=0;
	int* current = &visited[row][col];

	if (*current == bitis) {
		return 1;
	}

	if (*current == bos) {
		*current = duvar;

		if (dfs(row, col - 1)){
			*current = yol;
			
			return 1;
		} 
		if (dfs(row + 1, col)){
			*current = yol;
		
			return 1;
		} 
		if (dfs(row, col + 1)){
			*current = yol;
			
			return 1;		
		} 
		if (dfs(row - 1, col)){
			*current = yol;
			
			return 1;
		}
	}
	
	else if(*current==elma){
		*current = duvar;
		 puan+=10;
		if (dfs(row, col - 1)){
			*current = yol;
			
			return 1;
		} 
		if (dfs(row + 1, col)){
			*current = yol;
			
			return 1;
		} 
		if (dfs(row, col + 1)){
			*current = yol;
			
			return 1;		
		} 
		if (dfs(row - 1, col)){
			*current = yol;
			
			return 1;
		}
	}

	return 0;
}


void print_lab(){
	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
		
				if(lab[i][j]=='*'){
					printf("%c", lab[i][j]);
					delay(0.2);
				}
				else{
					printf("%c", lab[i][j]);
				}
		}
		printf("\n");
	}
	
			printf("\n");
}	


void print_visited(){
	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			printf("%d", visited[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
}




void patika()
{
	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if (lab[i][j] != 'b' && visited[i][j] == yol) {
				lab[i][j] = '*';
				
			}
		}
	}
}

int main(){
	
	lab_al("maze3.txt");
	doldur_visited();
	print_lab();
	print_visited();
	
	
	if(!dfs(bas_row,bas_col)){
		printf("bir yol bulunamadi");
	}
	else{
		patika();
		print_lab();
	}
	printf("puan: %d\n",puan);
	

	return 0;
}





















