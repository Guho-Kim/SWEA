#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//이게 왜 더 느리지? 이유는 동적 할당 1번 더 한 것 ???
typedef struct{
    int x, y, A;
} Safety;

int countSafety(bool* Safety, int len){
    int count =0;
    for (int i=0; i<len; i++){
        if(Safety[i]) count++;
    }
    return count;
}

int main(void)
{
    bool safety[450];
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
        if(N<M) len=N;
        else len=M;
        
        // Init Mars
        int **Mars = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) 
            Mars[i] = (int *)malloc(M * sizeof(int));
        
        // Init Safety
        Safety *rowSafety = (Safety*)malloc(N * sizeof(Safety));
        Safety *colSafety = (Safety*)malloc(M * sizeof(Safety));
        // bool *safety=(bool*)malloc(len*sizeof(bool));



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
            


        // 곰팡이 갱신
        for(int i=0; i<Q; i++){
            scanf("%d %d %d", &x, &y, &A);
            x--;
            y--;
            // Mars[x][y]=A;
            if(rowSafety[x].A < A){
                rowSafety[x].y=y;
                rowSafety[x].A=A;
            }
            
            if(colSafety[y].A < A){
                colSafety[y].x=x;
                colSafety[y].A=A;
            }
            numSafety=0;
            if(N>M){
                // 여기서 i는 col값
                // x, y에서 바뀌는 값이 생겼음
                // if(safety[y] && !(rowSafety[colSafety[y].x].A == colSafety[y].A)) safety[y]=false;
                // else if(!safety[y] && (rowSafety[colSafety[y].x].A == colSafety[y].A)) safety[y]=true;

                for(int i=0; i<len; i++){
                    // if(!(rowSafety[colSafety[i].x].A == colSafety[i].A)) safety[i]=false;
                    // else safety[i]=true;
                    if(rowSafety[colSafety[i].x].A == colSafety[i].A) numSafety++;
                }
            }
            else{
                // if(safety[y] && )
                // if(safety[x] && !(colSafety[rowSafety[x].y].A == rowSafety[x].A)) safety[x]=false;
                // else if(!safety[x] && (colSafety[rowSafety[x].y].A == rowSafety[x].A)) safety[x]=true;

                for(int i=0; i<len; i++){
                    // if(!(colSafety[rowSafety[i].y].A == rowSafety[i].A)) safety[i]=false;
                    // else safety[i]=true;
                    if(colSafety[rowSafety[i].y].A == rowSafety[i].A) numSafety++;
                }
            }
            
        // numSafety = countSafety(safety, len);
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
        // free(safety);

	}
	return 0;
}


/*

1
2 3 3
1 4 3
6 5 2
2 2 10
1 3 5
2 2 20

1
5 4 3
10 40 30 50
60 55 21 22
54 34 64 66
67 47 27 20
35 45 56 77
1 1 68
2 2 61
1 1 69

*/