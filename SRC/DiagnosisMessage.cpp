#include "DiagnosisMessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define FILE_END -1      //数据末尾值";"
#define INVALID_DATA 0   //不合法值
#define LEGAL_DATA 1     //合法值
#define LACKED_DATA 2    //缺省值默认char*为"$" ,int 为-1

bool IsNumber(const char* str) { //判断该字符串是否为数字
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		if (str[i] > '9' || str[i] < '0')return false;
	return true;
}

bool HasDate(int month, int day) { // 判断月日的正确性
	static const int m_day[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (day > m_day[month] || day < 0)return false;
	return true;
}

bool IsEnd(const char *str) {  // 是否读到结束符
	return strcmp(str, ";") == 0 ? true : false;
}

bool IsDefault(const char* str) { // 是否读到缺省值
	return strcmp(str, "$") == 0||strcmp(str,"-1")==0 ? true : false;
}

int IsRegisterId(const char* str) {  //判断 registerId 是否合法

	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 7) { // 出现非数字字符或长度错误
		return INVALID_DATA;
	} // 检查是否在限定范围内
	else if (strcmp(str, "1231500") > 0 || strcmp(str, "0101001") < 0) {
		return INVALID_DATA;
	}
	else {
		int id = atoi(str);
		int month = id / 100000;
		int day = id / 1000 % 100;
		if (HasDate(month, day)) {
			return LEGAL_DATA;
		}
		else {
			return INVALID_DATA; // 月日不对应
		}
	}
}

int IsDate(const char* str) {  //判断日期是否合法

	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 8) {
		return INVALID_DATA;
	}
	else {
		int date = atoi(str);
		int month = date / 1000000;
		int day = date / 10000 % 100;
		int hour = date % 10000 / 100;
		int minute = date % 100;
		if (!HasDate(month, day) || hour > 23 ||
			hour < 0 || minute > 59 || minute < 0) {
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}

int IsName(const char* str) {  //判断名字是否合法 char[40] 以内
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (strlen(str) > 40) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsAge(const char* str) {  //判断年龄是否合法
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) > 3) {  //Age不是数字或者Age太大
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsDoctorId(const char* str) {  //检查医生工号
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 4) { // 工号长度目前固定为4位
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsSection(const char* str) {  //检查科室号
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 2) { // 科室号长度目前固定为4位
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsDoctorLevel(const char* str) {  //检查医生级别 (一位数字)
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 1) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsConsultTime(const char* str) {  //检查出诊时间 协议：缺省值为默认全天出诊
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 7) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsDiagnosisFlag(const char* str) {  //检查诊疗类型编号
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 1) { //诊疗类型编号长度为1
		return INVALID_DATA;
	}
	else {
		int flag = atoi(str);
		if (0 == flag || 1 == flag || 2 == flag) {  //是三种类型之一
			return LEGAL_DATA;
		}
		else {
			return INVALID_DATA;
		}

	}
}

int IsDeposit(const char* str) { // 检查押金是否正确
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || atoi(str) % 100 != 0) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

void SetRecordDate(DiagnosisRecord* res, const char* str) { // 赋值诊疗记录的日期
	res->recordTime.month = atoi(str) / 1000000;
	res->recordTime.day = atoi(str) / 10000 % 100;
	res->recordTime.hour = atoi(str) % 10000 / 100;
	res->recordTime.minute = atoi(str) % 100;
}

// 赋值日期
void SetDate(char* str, int* month, int* day, int* hour, int* minute) {
	(*month) = atoi(str) / 1000000;
	(*day) = atoi(str) / 10000 % 100;
	(*hour) = atoi(str) % 10000 / 100;
	(*minute) = atoi(str) % 100;
}
//80
// 用于文件读入 判断检查记录的总费用 若合法则赋值总费用
int GetCost(FILE* fp, int* yuan, int* jiao, int* fen) { // 读入费用
	char cache[100]; int flag = 0;
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) return FILE_END;
	if (!IsNumber(cache)) flag = 1;  // 元
	else (*yuan) = atoi(cache);
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) return FILE_END;
	if (!IsNumber(cache)) flag = 1;  // 角
	else {
		(*jiao) = atoi(cache);
		if (atoi(cache) > 9) flag = 1;
	}
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) return FILE_END;
	if (!IsNumber(cache)) flag = 1;  // 分
	else {
		(*fen) = atoi(cache);
		if (atoi(cache) > 9) flag = 1;
	}
	return flag ? LEGAL_DATA : INVALID_DATA;
}

// 获取对应的与检查有关的信息
int GetCheckInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
	char cache[100];  // 暂时存储 用于检查
	int flag = 0; // 标记是否有错误
	int retInt = 0; // 记录每次检查的返回值
	retInt = GetCost(fp, &tempInfo->checkRecord.totalCost.yuan,
		&tempInfo->checkRecord.totalCost.jiao,
		&tempInfo->checkRecord.totalCost.fen); // 检查总费用
	if (retInt != LEGAL_DATA) {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) return FILE_END;
	int count = 0;  // 记录检查数目
	if (!IsNumber(cache)) flag = 1;
	else {
		count = atoi(cache);
		tempInfo->checkRecord.typeNumber = count;
	}
	CheckInfo* nowCheck = tempInfo->checkRecord.checkInformationHead; // 当前位置指向头节点
	for (int i = 0; i < count; i++) { // 录入每种检查
		CheckInfo* nextCheck = (CheckInfo*)malloc(sizeof(CheckInfo)); // 下一个节点
		fscanf(fp, "%s", cache);
		if (!IsNumber(cache)) flag = 1;
		else nextCheck->checkId = atoi(cache); // 记录检查编号
		if (IsEnd(cache)) { // 记录提前终止
			flag = FILE_END; break;
		}
		retInt = GetCost(fp, &nextCheck->singleCost.yuan,
			&nextCheck->singleCost.jiao,
			&nextCheck->singleCost.fen); // 单种检查的费用
		nowCheck->next = nextCheck;
		nowCheck = nextCheck;
		if (retInt != LEGAL_DATA) {
			flag = 1; if (retInt == FILE_END) {
				flag = FILE_END; break;  // 记录提前终止
			}
		}
	}
	nowCheck->next = NULL; // 注意 如果检查数目超过count说明出去之后不能直接读到结束符
	if (flag) {  // 待填充 free链表 or free链表在最外层实现 或者 重复实现确保free
		if (flag == FILE_END)return FILE_END;
		else return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

// 获取对应的与开药有关的信息
int GetPrescribeInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
	char cache[100];  // 暂时存储 用于检查
	int flag = 0; // 标记是否有错误
	int retInt = 0; // 记录每次检查的返回值
	retInt = GetCost(fp, &tempInfo->checkRecord.totalCost.yuan,
		&tempInfo->checkRecord.totalCost.jiao,
		&tempInfo->checkRecord.totalCost.fen); // 检查总费用
	if (retInt != LEGAL_DATA) {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) return FILE_END;
	int count = 0;  // 记录开药种数
	if (!IsNumber(cache)) flag = 1;
	else {
		count = atoi(cache);
		tempInfo->prescribeRecord.typeNumber = count;
	}
	// 当前位置指向头节点
	PrescribeInfo* nowDrug = tempInfo->prescribeRecord.prescribeInformationHead;
	for (int i = 0; i < count; i++) { // 每种药品
		PrescribeInfo* nextDrug = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));  // 下一个节点
		fscanf(fp, "%s", cache);
		if (!IsNumber(cache)) flag = 1;
		else nextDrug->drugId = atoi(cache); // 记录药品编号
		if (IsEnd(cache)) {
			flag = FILE_END; break;
		}
		fscanf(fp, "%s", cache);
		if (!IsNumber(cache)) flag = 1;
		else nextDrug->drugNumber = atoi(cache); // 记录药品数量
		if (IsEnd(cache)) {
			flag = FILE_END; break;
		}
		nowDrug->next = nextDrug;
		nowDrug = nextDrug;
	}
	nowDrug->next = NULL;
	if (flag) {  // 待填充 free链表
		if (flag == FILE_END)return FILE_END;
		else return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

// 获取对应的与住院有关的信息
int GetInHospitalInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
	char cache[100];  // 暂时存储 用于检查
	int flag = 0; // 标记是否有错误
	int retInt = 0; // 记录每次检查的返回值
	fscanf(fp, "%s", cache);
	retInt = IsDate(cache);
	if (retInt == 1) { // 入院日期
		SetDate(cache, &tempInfo->inHospitalRecord.hospitalizedDate.month,
			&tempInfo->inHospitalRecord.hospitalizedDate.day,
			&tempInfo->inHospitalRecord.hospitalizedDate.hour,
			&tempInfo->inHospitalRecord.hospitalizedDate.minute);
	}
	else {
		flag = 1; if (retInt == -1)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	retInt = IsDate(cache);
	if (retInt == 1) { // 预计出院日期
		SetDate(cache, &tempInfo->inHospitalRecord.predictedLeaveDate.month,
			&tempInfo->inHospitalRecord.predictedLeaveDate.day,
			&tempInfo->inHospitalRecord.predictedLeaveDate.hour,
			&tempInfo->inHospitalRecord.predictedLeaveDate.minute);
	}
	else {
		flag = 1; if (retInt == -1)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	retInt = IsDeposit(cache);
	if (retInt == 1) {
		tempInfo->inHospitalRecord.deposit.yuan = atoi(cache);
	}
	else {
		flag = 1; if (retInt == -1)return FILE_END;
	}
	if (flag)return INVALID_DATA;
	else return LEGAL_DATA;
}

// 从文件读入对应的诊疗类型
int GetDiagnosisSituationInfo(FILE* fp, DiagnosisRecord* res) {
	int retInt = 0; // 记录每次检查的返回值
	DiagnosisSituationUnion* tempInfo =
		&res->diagnosisSituation.diagnosisSituationInfo;
	if (res->diagnosisSituation.setFlag == 0) {  // 检查类
		retInt = GetCheckInfo(fp, tempInfo);
	}
	else if (res->diagnosisSituation.setFlag == 1) {  // 开药类
		retInt = GetPrescribeInfo(fp, tempInfo);
	}
	else if (res->diagnosisSituation.setFlag == 2) {  // 住院类
		retInt = GetInHospitalInfo(fp, tempInfo);
	}
	else retInt = INVALID_DATA;  // 诊疗类型的编号出错
	return retInt; // 标记 该处有待考虑
}

// 从文件种获取患者相关信息
int GetPatientRecord(FILE* fp, DiagnosisRecord* res) {
	char cache[100];  // 暂时存储 用于检查
	int flag = 0; // 标记是否有错误
	int retInt = 0; // 记录每次检查的返回值
	fscanf(fp, "%s", cache);
	retInt = IsRegisterId(cache); // 检查患者挂号
	if (retInt == LEGAL_DATA) res->patientInfo.registerId = atoi(cache);  // 挂号合法
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	// 检查患者姓名长度是否正常 以20字(char[40])及以内为正常
	fscanf(fp, "%s", cache);
	retInt = IsName(cache);
	if (retInt == LEGAL_DATA) {  // 姓名合法
		strcpy(res->patientInfo.name, cache);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	// 检查患者年龄
	fscanf(fp, "%s", cache);
	retInt = IsAge(cache);
	if (retInt == LEGAL_DATA) res->patientInfo.age = atoi(cache);  // 年龄合法
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	if (flag)return INVALID_DATA;
	else return LEGAL_DATA;
}

// 从文件中获取医生相关信息
int GetDoctorRecord(FILE* fp, DiagnosisRecord* res) {
	char cache[100];  // 暂时存储 用于检查
	int flag = 0; // 标记是否有错误
	int retInt = 0; // 记录每次检查的返回值
	fscanf(fp, "%s", cache);
	retInt = IsDoctorId(cache); // 检查医生工号
	if (retInt == LEGAL_DATA) res->doctorInfo.id = atoi(cache);  // 工号合法
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	// 检查科室
	fscanf(fp, "%s", cache);
	retInt = IsSection(cache);
	if (retInt == 1) {
		res->doctorInfo.section = atoi(cache); // 科室合法
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	retInt = IsName(cache);  // 检查医生姓名 类似患者姓名
	if (retInt == 1) {  // 姓名合法
		strcpy(res->doctorInfo.name, cache);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	retInt = IsDoctorLevel(cache); // 检查医生级别
	if (retInt == 1) { // 医生级别合法
		res->doctorInfo.level = atoi(cache);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	retInt = IsConsultTime(cache); // 检查医生出诊时间
	if (retInt == 1) { // 出诊时间合法
		for (int i = 0; i < 7; i++)
			res->doctorInfo.consultTime[i] = cache[i] != '0' ? true : false;
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	if (flag)return INVALID_DATA;
	else return LEGAL_DATA;
}

DiagnosisRecord* InRecord(FILE* fp) {  // 边输入边检查,若有数据错误返回NULL
	char cache[100];  // 暂时存储 用于检查
	int flag = 0;  // 标记是否有错误
	int  retInt = 0; // 记录每次检查的返回值
	DiagnosisRecord* res = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
	while (1) {
		// 检查日期是否正确
		fscanf(fp, "%s", cache);
		retInt = IsDate(cache);
		if (retInt == LEGAL_DATA) {  // 日期合法
			SetRecordDate(res, cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		retInt = GetPatientRecord(fp, res);
		if (retInt != LEGAL_DATA) {  // 患者信息合法
			flag = 1; if (retInt == FILE_END)break;
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		retInt = GetDoctorRecord(fp, res);
		if (retInt != LEGAL_DATA) {  // 医生信息合法
			flag = 1; if (retInt == FILE_END)break;
		}
		// 检查诊疗类型编号
		fscanf(fp, "%s", cache);
		retInt = IsDiagnosisFlag(cache);
		if (retInt == 1) { // 诊疗类型编号合法
			res->diagnosisSituation.setFlag = atoi(cache);
		}
		else {
			flag = 1; if (retInt == -1)break;
		}
		retInt = GetDiagnosisSituationInfo(fp, res); // 获取相应的诊疗类型的信息
		if (retInt != LEGAL_DATA) {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);  // 读取结束符
		if (!IsEnd(cache)) {  // 该记录仍未终止,确保读完结束符,以免影响下个记录
			while (!feof(fp) && !IsEnd(cache))fscanf(fp, "%s", cache);
			flag = 1;
		}
	}
	if (flag) { // 在此处补充删除链表
		free(res);
		res = NULL;
	}
	return res;
}

void FileInput() {  // 从文件导入诊疗记录
	char writePath[] = "out.txt";
	char readPath[100];
	scanf("%s", readPath);
	FILE* fileReadPointer, *fileWritePointer;
	while ((fileReadPointer = fopen(readPath, "r")) == NULL) {
		printf("文件路径不正确,请重新输入!\n");
		scanf("%s", readPath);
	}
	fileWritePointer = fopen(writePath, "w+");
	while (!feof(fileReadPointer)) {
		DiagnosisRecord* nowRecord = InRecord(fileReadPointer);
		if (!nowRecord)continue;
		// 挂号      日期    姓名 年龄 工号 科室 姓名 级别
		fprintf(fileWritePointer, "%08d %02d%02d%02d%02d %s %d %04d %02d %s %d ",
			nowRecord->patientInfo.registerId,
			nowRecord->recordTime.month,
			nowRecord->recordTime.day,
			nowRecord->recordTime.hour,
			nowRecord->recordTime.minute,
			nowRecord->patientInfo.name,
			nowRecord->patientInfo.age,
			nowRecord->doctorInfo.id,
			nowRecord->doctorInfo.section,
			nowRecord->doctorInfo.name,
			nowRecord->doctorInfo.level
		);
		for (int i = 0; i < 7; i++)
			fprintf(fileWritePointer, "%d", nowRecord->doctorInfo.consultTime[i] ? 1 : 0); // 写入出诊时间的二进制码
		fprintf(fileWritePointer, " %d ", nowRecord->diagnosisSituation.setFlag); // 写入诊疗类型编号
		auto tempInfo = nowRecord->diagnosisSituation.diagnosisSituationInfo;  // 以下Info全用该变量代替 
		if (nowRecord->diagnosisSituation.setFlag == 0) {  // 检查类
			CheckInfo* nowPos = tempInfo.checkRecord.checkInformationHead;
			fprintf(fileWritePointer, "%d %d %d %d",
				tempInfo.checkRecord.totalCost.yuan,
				tempInfo.checkRecord.totalCost.jiao,
				tempInfo.checkRecord.totalCost.fen,
				tempInfo.checkRecord.typeNumber
			);
			for (int i = 0; i < tempInfo.checkRecord.typeNumber; i++) {
				nowPos = nowPos->next;
				fprintf(fileWritePointer, " %d %d %d %d",
					nowPos->checkId, nowPos->singleCost.yuan, nowPos->singleCost.jiao, nowPos->singleCost.fen);
			}
		}
		else if (nowRecord->diagnosisSituation.setFlag == 1) {  // 开药类
			PrescribeInfo* nowPos = tempInfo.prescribeRecord.prescribeInformationHead;
			fprintf(fileWritePointer, "%d %d %d %d",
				tempInfo.prescribeRecord.totalCost.yuan,
				tempInfo.prescribeRecord.totalCost.jiao,
				tempInfo.prescribeRecord.totalCost.fen,
				tempInfo.prescribeRecord.typeNumber
			);
			for (int i = 0; i < tempInfo.prescribeRecord.typeNumber; i++) {
				nowPos = nowPos->next;
				fprintf(fileWritePointer, " %d %d", nowPos->drugId, nowPos->drugNumber);
			}
		}
		else if (nowRecord->diagnosisSituation.setFlag == 2) {  // 住院类
			fprintf(fileWritePointer, "%02d%02d%02d%02d %02d%02d%02d%02d %d",
				tempInfo.inHospitalRecord.hospitalizedDate.month,
				tempInfo.inHospitalRecord.hospitalizedDate.day,
				tempInfo.inHospitalRecord.hospitalizedDate.hour,
				tempInfo.inHospitalRecord.hospitalizedDate.minute,
				tempInfo.inHospitalRecord.predictedLeaveDate.month,
				tempInfo.inHospitalRecord.predictedLeaveDate.day,
				tempInfo.inHospitalRecord.predictedLeaveDate.hour,
				tempInfo.inHospitalRecord.predictedLeaveDate.minute,
				tempInfo.inHospitalRecord.deposit.yuan
			);
		}
		fprintf(fileWritePointer, ";\n");
	}
	return;
}
