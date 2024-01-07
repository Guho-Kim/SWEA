#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

struct Result
{
	int mPrice;
	int mPerformance;
};

extern void init(int mCharge);
extern Result order(int mBudget);
extern int stock(int mType, int mPerformance, int mPrice, int mPosition);

/////////////////////////////////////////////////////////////////////////

#define INIT	0
#define STOCK	1
#define ORDER	2

static bool run()
{
	int cmd, ans, ans2, ret;
	int in, in2, in3, in4;
	int Q = 0;
	bool okay = false;
	Result Ret;

	scanf("%d", &Q);

	for (int q = 0; q < Q; ++q)
	{
		scanf("%d", &cmd);

		switch (cmd)
		{
		case INIT:
			scanf("%d", &in);
			init(in);
			okay = true;
			break;

		case STOCK:
			scanf("%d %d %d %d", &in, &in2, &in3, &in4);
			ret = stock(in, in2, in3, in4);
			scanf("%d", &ans);
			if (ret != ans) {
				okay = false;
				printf("Stock Error\nans: %d, my ret: %d\n", ans, ret);
			}
			break;

		case ORDER:
			scanf("%d", &in);
			Ret = order(in);
			scanf("%d %d", &ans, &ans2);
			if (Ret.mPrice != ans || Ret.mPerformance != ans2) {
				okay = false;
				printf("Order Error\nans.price: %d, my ret.price: %d\n", ans, Ret.mPrice);
				printf("ans.performance: %d, my ret.performance: %d\n", ans2, Ret.mPerformance);
			}
			break;

		default:
			okay = false;
		}
	}

	return okay;
}
int main()
{
	setbuf(stdout, NULL);
	// freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}