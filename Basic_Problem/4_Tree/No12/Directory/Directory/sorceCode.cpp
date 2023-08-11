/*
#define NAME_MAXLEN 6
#define PATH_MAXLEN 2000


#define MAXCHILD 30


int getNameVal(char* pName, int len) {
    int ret = *pName - 'a';
    for (int i = 1; i < len; i++) {
        pName++;
        ret = ret << 5;
        ret += *pName - 'a' + 1;
    }
    return ret;
}


typedef struct DIR {
    int nameVal;
    DIR* pChild[MAXCHILD];
    DIR* pParent;
    int childCnt;
    int totalCnt;
};


DIR dir[50000];
int dirCnt = 0;
int N;


DIR* pRoot;
char str[PATH_MAXLEN];


void init(int n) {
    N = n;
    pRoot = &dir[0];


    for (int i = 0; i < N; i++) {
        dir[i].childCnt = 0;
        dir[i].nameVal = -1;
        dir[i].pParent = 0;
        dir[i].totalCnt = 0;
        for (int j = 0; j < MAXCHILD; j++)
            dir[i].pChild[j] = 0;
    }
    dirCnt = 1;
}


DIR* getPath(char path[PATH_MAXLEN]) {
    char* p = path;

    if (*p == '/') {
        p++;
    }


    DIR* ret = pRoot;
    while (*p != 0) {
        int len = 1;
        for (int i = 2; i <= NAME_MAXLEN; i++) {
            if (*(p + i) == '/') {
                len = i;
                break;
            }
        }
        if (len >= 2) {
            int val = getNameVal(p, len);
            for (int i = 0; i < ret->childCnt; i++) {
                if (ret->pChild[i] == 0) {
                    continue;
                }
                if (ret->pChild[i]->nameVal == val) {
                    ret = ret->pChild[i];
                    break;
                }
            }
        }
        p += len + 1;
    }
    return ret;
}


void updateDirCnt(DIR* pDir, int delta) {


    //if (pDir == 0) return;


    while (pDir != pRoot) {
        pDir = pDir->pParent;
        pDir->totalCnt += delta;
    }
}


void cmd_mkdir(char path[PATH_MAXLEN], char name[NAME_MAXLEN + 1]) {


    DIR* pDir = getPath(path);
    DIR* pChDir = &dir[dirCnt];
    dirCnt++;


    pChDir->childCnt = 0;
    pChDir->pParent = pDir;


    int len = 0;
    for (int i = 2; i < NAME_MAXLEN + 1; i++) {
        if (name[i] == 0) {
            len = i;
            break;
        }
    }
    pChDir->nameVal = getNameVal(name, len);


    pDir->pChild[pDir->childCnt] = pChDir;
    pDir->childCnt++;


    pDir->totalCnt++;
    updateDirCnt(pDir, 1);
}


void cmd_rm(char path[PATH_MAXLEN]) {


    DIR* pDir = getPath(path);
    DIR* pParent = pDir->pParent;


    int idx = -1;
    for (int i = 0; i < pParent->childCnt; i++) {
        if (pParent->pChild[i] == pDir) {
            idx = i;
            break;
        }
    }


    pParent->childCnt--;
    pParent->pChild[idx] = pParent->pChild[pParent->childCnt];


    pParent->totalCnt -= pDir->totalCnt + 1;
    updateDirCnt(pParent, -(pDir->totalCnt + 1));
}


void doRecur(DIR* pSrcDir, DIR* pDstDir) {
    DIR* pChDir = &dir[dirCnt];
    dirCnt++;


    pDstDir->pChild[pDstDir->childCnt] = pChDir;
    pDstDir->childCnt++;


    pChDir->nameVal = pSrcDir->nameVal;
    pChDir->pParent = pDstDir;
    pChDir->totalCnt = 0;
    pChDir->childCnt = 0;


    pDstDir->totalCnt++;
    updateDirCnt(pDstDir, 1);


    for (int i = 0; i < pSrcDir->childCnt; i++) {
        doRecur(pSrcDir->pChild[i], pChDir);
    }
}


void cmd_cp(char srcPath[PATH_MAXLEN], char dstPath[PATH_MAXLEN]) {


    DIR* pSrcDir = getPath(srcPath);
    DIR* pDstDir = getPath(dstPath);


    doRecur(pSrcDir, pDstDir);
}


void cmd_mv(char srcPath[PATH_MAXLEN], char dstPath[PATH_MAXLEN]) {


    DIR* pChDir = getPath(srcPath);
    DIR* pDstDir = getPath(dstPath);


    DIR* pParent = pChDir->pParent;


    int idx = -1;
    for (int i = 0; i < pParent->childCnt; i++) {
        if (pParent->pChild[i] == pChDir) {
            idx = i;
            break;
        }
    }


    pParent->childCnt--;
    pParent->pChild[idx] = pParent->pChild[pParent->childCnt];

    pParent->totalCnt -= (pChDir->totalCnt + 1);
    updateDirCnt(pParent, -(pChDir->totalCnt + 1));


    pChDir->pParent = pDstDir;


    pDstDir->pChild[pDstDir->childCnt] = pChDir;
    pDstDir->childCnt++;


    pDstDir->totalCnt += (pChDir->totalCnt + 1);
    updateDirCnt(pDstDir, (pChDir->totalCnt + 1));
}


int cmd_find(char path[PATH_MAXLEN]) {


    DIR* pDir = getPath(path);
    return pDir->totalCnt;
}

*/