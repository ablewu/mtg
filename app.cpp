#include <stdio.h>
#include "mtgsdk.h"

MtgSdk* mtg_sdk = NULL;

int testmtg(const char* ip, unsigned long confid, unsigned long userid)
{
	int ret = 1;
	if (!mtg_sdk->MtgJoinConf(ip, confid, userid)) {
		printf(">> join conf failed, try again...\n");
		//if (!mtg_sdk->MtgJoinConf(ip, confid, userid)) {
		//	printf(">> join conf failed again. error!!!!!!!!\n");
		//	return 0;
		//}
		ret = 2;
	}

	mtg_sdk->MtgUserJoin();	
	mtg_sdk->MtgLeaveConf();
	
	return ret;
}

int main(int argc, char* argv[])
{
	mtg_sdk = new MtgSdk();
	mtg_sdk->MtgInit();
	
	int conn_total = 0, conn_suc = 0, conn_failed = 0, re_conn = 0;

	
	//while (1) {
		int ret = 0;
		if (argc == 1)
			ret = testmtg("202.120.197.10", 20, 100);
		else
			ret = testmtg(argv[1], 20, 100);
		
		if (1 == ret)
			conn_suc ++;
		else if (2 == ret)
			re_conn ++;
		else
			conn_failed ++;
		conn_total ++;

		printf("--------------------------------\n");
		printf("total\tsuc\tre_conn\tfailed\n");
		printf("%d\t%d\t%d\t%d\n", conn_total, conn_suc, re_conn, conn_failed);
		printf("--------------------------------\n");
		//}

	if (NULL != mtg_sdk) {
		mtg_sdk->MtgUnInit();
		printf("delete mtg\n");
		delete mtg_sdk;
		mtg_sdk = NULL;
	}
	
	return 0;
}
