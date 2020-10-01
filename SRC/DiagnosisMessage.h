#ifndef DIAGNOSISMESSAGE_H
#define DIAGNOSISMESSAGE_H

#define FILE_END -1      //����ĩβֵ";"
#define INVALID_DATA 0   //���Ϸ�ֵ
#define LEGAL_DATA 1     //�Ϸ�ֵ
#define LACKED_DATA 2    //ȱʡֵĬ��char*Ϊ"$",intΪ-1

#include <string.h>
#include <stdio.h>

typedef struct DiagnosisRecord;
typedef struct DoctorInfo;


typedef struct PatientInfo {  // ������Ϣ
    char name[20];  // ����
    int age;  // ����
    int registerId;  // �Һ�(Ψһ)
};

PatientInfo constructPatientInfo(char name[20], int age, int registerId) {
    PatientInfo patientInfo;
    strcpy(patientInfo.name, name);
    patientInfo.age = age;
    patientInfo.registerId = registerId;
    return patientInfo;
}

typedef struct Section {  // ������
    int sectionId;  // ����Id(Ψһ)
    DiagnosisRecord* nowDiagnosis; // �������
    DoctorInfo* DoctorsOfSectionHead; // ���ҵ�ҽ�����ݶ����20����
    Section* next;
};

Section constructSection(int sectionId, DiagnosisRecord* nowDiagnosis,
    DoctorInfo* DoctorsOfSectionHead, Section* next) {
    Section section;
    section.sectionId = sectionId;
    section.nowDiagnosis = nowDiagnosis;
    section.DoctorsOfSectionHead = DoctorsOfSectionHead;
    section.next = next;
    return section;
};

typedef struct DoctorInfo {  // ҽ����Ϣ
    char name[20];  // ����
    int level;  // ����
    int sectionId;  // �������ұ��
    bool consultTime[7];  // ����ʱ��
    int id;  // ����(Ψһ)
    int doctorStatus; // ҽ��״̬
    bool inPostionStatus = 1;
};

DoctorInfo constructDoctorInfo(char name[20], int level,
    int sectionId, bool consultTime[7], int id, int doctorStatus, bool inPositionStatus) {
    DoctorInfo doctorInfo;
    strcpy(doctorInfo.name, name);
    doctorInfo.level = level;
    doctorInfo.sectionId = sectionId;
    for (int i = 0; i < 7; i++) {
        doctorInfo.consultTime[i] = consultTime[i];
    }
    doctorInfo.id = id;
    doctorInfo.doctorStatus = doctorStatus;
    doctorInfo.inPostionStatus = inPositionStatus;
    return doctorInfo;
}

typedef struct DoctorNode {
    DoctorInfo doctorInfo;
    DoctorNode* next;
};

DoctorNode constructDoctorNode(DoctorInfo doctorInfo, DoctorNode* next) {
    DoctorNode doctorNode;
    doctorNode.doctorInfo = doctorInfo;
    doctorNode.next = next;
    return doctorNode;
}

typedef struct SingleCost {  // ������Ŀ�ļ۸�
    int yuan;
    int jiao;
    int fen;
};

SingleCost constructSingleCost(int yuan, int jiao, int fen) {
    SingleCost singleCost;
    singleCost.yuan = yuan;
    singleCost.jiao = jiao;
    singleCost.fen = fen;
    return singleCost;
}

typedef struct CheckInfo { // �����Ϣ
    int checkId;
    SingleCost singleCost;
    CheckInfo* next;
};

CheckInfo constructCheckInfo(int checkId, SingleCost singleCost, CheckInfo* next) {
    CheckInfo checkInfo;
    checkInfo.singleCost = singleCost;
    checkInfo.next = next;
    return checkInfo;
}

typedef struct CheckRecord {  // ����¼
    CheckInfo* checkInfoHead;  // ͷָ��
    int typeNumber;
    SingleCost totalCost;
};

CheckRecord constructCheckRecord(CheckInfo* checkInfoHead,
    int typeNumber, SingleCost totalCost) {
    CheckRecord checkRecord;
    checkRecord.checkInfoHead = checkInfoHead;
    checkRecord.typeNumber = typeNumber;
    checkRecord.totalCost = totalCost;
    return checkRecord;
}

typedef struct PrescribeInfo {
    int drugId;
    int drugNumber;
    PrescribeInfo* next;
};

PrescribeInfo constructPrescribeInfo(int drugId, int drugNumber, PrescribeInfo* next) {
    PrescribeInfo prescribeInfo;
    prescribeInfo.drugId = drugId;
    prescribeInfo.drugNumber = drugNumber;
    prescribeInfo.next = next;
    return prescribeInfo;
}

typedef struct PrescribeRecord {  // ��ҩ��
    PrescribeInfo* prescribeInfoHead; // ͷָ��
    int typeNumber;
    SingleCost totalCost;
};

PrescribeRecord constructPrescribeRecord(PrescribeInfo* prescribeInfoHead,
    int typeNumber, SingleCost totalCost) {
    PrescribeRecord prescribeRecord;
    prescribeRecord.totalCost = totalCost;
    prescribeRecord.typeNumber = typeNumber;
    prescribeRecord.prescribeInfoHead = prescribeInfoHead;
    return prescribeRecord;
}

typedef struct TimeRecord {  // ����
    int month;
    int day;
    int hour;
    int minute;
};

TimeRecord constructTimeRecord(int month, int day, int hour, int minute) {
    TimeRecord timeRecord;
    timeRecord.month = month;
    timeRecord.day = day;
    timeRecord.hour = hour;
    timeRecord.minute = minute;
    return timeRecord;
}

typedef struct InHospitalRecord {  // סԺ��
    TimeRecord hospitalizedDate;
    TimeRecord predictedLeaveDate;
    SingleCost deposit;
    int spendDay;
};

InHospitalRecord constructInHospitalRecord(TimeRecord hospitalizedDate,
    TimeRecord predictedLeaveDate, SingleCost deposit, int spendDay) {
    InHospitalRecord inHospitalRecord;
    inHospitalRecord.hospitalizedDate = hospitalizedDate;
    inHospitalRecord.predictedLeaveDate = predictedLeaveDate;
    inHospitalRecord.deposit = deposit;
    inHospitalRecord.spendDay = spendDay;
    return inHospitalRecord;
}

typedef union DiagnosisSituationUnion {  // ���������Ϣ
    CheckRecord checkRecord;
    PrescribeRecord prescribeRecord;
    InHospitalRecord inHospitalRecord;
};

typedef struct DiagnosisSituation {  // �������
    int setFlag;
    DiagnosisSituationUnion diagnosisSituationInfo;
};

DiagnosisSituation constructDiagnosisSituation(int setFlag,
    DiagnosisSituationUnion diagnosisSituationInfo) {
    DiagnosisSituation diagnosisSituation;
    diagnosisSituation.setFlag = setFlag;
    diagnosisSituation.diagnosisSituationInfo = diagnosisSituationInfo;
    return diagnosisSituation;
}

typedef struct DiagnosisRecord {  // ���Ƽ�¼
    TimeRecord recordTime; // ��¼ʱ��
    PatientInfo patientInfo;  // ������Ϣ
    DoctorInfo doctorinfo;  // ҽ����Ϣ
    DiagnosisSituation diagnosisSituation;  // �������
    DiagnosisRecord* next;
};

DiagnosisRecord constructDiagnosisRecord(TimeRecord recordTime, PatientInfo patientInfo,
    DoctorInfo doctorInfo, DiagnosisSituation diagnosisSituation,
    DiagnosisRecord* next) {
    DiagnosisRecord diagnosisRecord;
    diagnosisRecord.recordTime = recordTime;
    diagnosisRecord.patientInfo = patientInfo;
    diagnosisRecord.doctorinfo = doctorInfo;
    diagnosisRecord.diagnosisSituation = diagnosisSituation;
    diagnosisRecord.next = next;
    return diagnosisRecord;
}

typedef struct Ward {
    int wardId;
    int nursingType;
    int bedType;
    int totalBedNum;
    int occupiedBedNum;
    bool bedSituation[10];
    Ward* next;
};

Ward constructWard(int wardId, int nursingType, int bedType, int totalBedNum, int occupiedBedNum,
    bool bedSituation[10], Ward* next) {
    Ward ward;
    ward.wardId = wardId;
    ward.nursingType = nursingType;
    ward.bedType = bedType;
    ward.totalBedNum = totalBedNum;
    ward.occupiedBedNum = occupiedBedNum;
    ward.next = next;
    for (int i = 0; i < 10; i++)
        ward.bedSituation[i] = bedSituation[i];
}

bool checkError(DiagnosisRecord); // ������Ƽ�¼�Ƿ��д�

void FileInput(); // ���ļ��������Ƽ�¼

SingleCost add(SingleCost costA, SingleCost costB) {
    costA.fen += costB.fen;
    costA.jiao += costB.jiao;
    costA.yuan += costB.yuan;
    while (costA.fen >= 100) {
        costA.fen -= 100;
        costA.jiao++;
    }
    while (costA.jiao >= 100) {
        costA.jiao -= 100;
        costA.yuan++;
    }
    return costA;
}

#endif