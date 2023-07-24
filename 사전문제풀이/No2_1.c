#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    int x, y, A;
    bool safety;
} Safety;

int countSafety(Safety* Safety, int len){
    int count =0;
    for (int i=0; i<len; i++){
        if(Safety[i].safety) count++;
    }
    return count;
}

int main(void)
{
	int test_case;
	int T;
	setbuf(stdout, NULL);
	scanf("%d", &T);

    int N, M, Q;
    int x, y, A;
    int len;
    int numSafety;
    int sumSafety;
	for (test_case = 1; test_case <= T; ++test_case)
	{
        sumSafety=0;
        scanf("%d %d %d", &N, &M, &Q);
        
        // Init Mars
        int **Mars = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) 
            Mars[i] = (int *)malloc(M * sizeof(int));
        
        // Init Safety
        Safety *rowSafety = (Safety*)malloc(N * sizeof(Safety));
        Safety *colSafety = (Safety*)malloc(M * sizeof(Safety));


        // Set Mars
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++)
                scanf("%d", &Mars[i][j]);
        
        // Set Safety
        for(int i=0; i<N; i++){
            A=0;
            for(int j=0; j<M; j++){
                if(A<Mars[i][j]){
                    x=i;
                    y=j;
                    A=Mars[i][j];
                }
            rowSafety[i].x=x;
            rowSafety[i].y=y;
            rowSafety[i].A=A;
            }
        }
        for(int j=0; j<M; j++){
            A=0;
            for(int i=0; i<N; i++){
                if(A<Mars[i][j]){
                    x=i;
                    y=j;
                    A=Mars[i][j];
                }
            colSafety[j].x=x;
            colSafety[j].y=y;
            colSafety[j].A=A;
            }
        }
            

        Safety* Safety;
        if(N<M){
            Safety = rowSafety;
            len=N;
        }
        else{
            Safety = colSafety;
            len=M;
        }

        for(int i=0; i<Q; i++){
            scanf("%d %d %d", &x, &y, &A);
            x--;
            y--;
            Mars[x][y]=A;
            // rowSafety 갱신
            if(rowSafety[x].A < A){
                rowSafety[x].y=y;
                rowSafety[x].A=A;
            }
            
            if(colSafety[y].A < A){
                colSafety[y].x=x;
                colSafety[y].A=A;
            }
            
            for(int i=0; i<len; i++){
                if(!(rowSafety[colSafety[i].x].A == colSafety[i].A)) Safety[i].safety=false;
                else Safety[i].safety=true;
            }
            
        numSafety = countSafety(Safety, len);
        sumSafety+=numSafety;
        // printf("numSafety: %d\n",numSafety);
        }


        printf("#%d %d\n",test_case, sumSafety);


        // 동적 할당 반환
        for (int i = 0; i < N; i++) {
            free(Mars[i]);
        }
        free(Mars);
        free(rowSafety);
        free(colSafety);

	}
	return 0;
}
