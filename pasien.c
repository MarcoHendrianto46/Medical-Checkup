#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 5
#define MAX_HISTORY 3

typedef char string[255];

typedef struct{
        string day;
        string month;
        string year;
    }Date;

typedef struct {
    char id[20];
    string name;
    string gender;
    Date tgl_lahir;
    char blood[3];
    string address;
    string idcard;
    string bpjs;
    string telp;
    Date tgl_daftar;
    string doctor;
} Patient;


typedef struct {
	Date tgl_priksa;
    char id[20];
    float t_badan;
	float b_badan;
	int umur;
	string t_darah;
    string keluhan;
    string cat_doctor;
    string resep;
} History;

typedef struct {
    Patient patient;
    History histories[MAX_HISTORY];
    int historyCount;
} PatientData;

PatientData patients[MAX_PATIENTS];
int patientCount = 0;

int findPatientIndexById(char* id) {
	int i;
    for (i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].patient.id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void insertPatient(Patient patient) {
    if (patientCount >= MAX_PATIENTS) {
        printf("Maximum number of patients reached.\n");
        return;
    }
    if (findPatientIndexById(patient.id) != -1) {
        printf("Patient ID must be unique.\n");
        return;
    }
    PatientData data;
    data.patient = patient;
    data.historyCount = 0;
    patients[patientCount++] = data;
}

void updatePatient(Patient patient) {
    int index = findPatientIndexById(patient.id);
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }
    patients[index].patient = patient;
}

void deletePatient(char* id) {
    int index = findPatientIndexById(id),i;
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }
    for (i = index; i < patientCount - 1; i++) {
        patients[i] = patients[i + 1];
    }
    patientCount--;
}

void insertHistory(char* patientId, History history) {
    int index = findPatientIndexById(patientId);
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }
    if (patients[index].historyCount >= MAX_HISTORY) {
        printf("Maximum number of histories reached.\n");
        return;
    }
    patients[index].histories[patients[index].historyCount++] = history;
}

void updateHistory(char* patientId, History history) {
    int index = findPatientIndexById(patientId),i;
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }
    for (i = 0; i < patients[index].historyCount; i++) {
        if (strcmp(patients[index].histories[i].id, history.id) == 0) {
            patients[index].histories[i] = history;
            return;
        }
    }
    printf("History not found.\n");
}

void deleteLastHistory(char* patientId) {
    int index = findPatientIndexById(patientId);
    if (index == -1) {
        printf("Patient not found.\n");
        return;
    }
    if (patients[index].historyCount == 0) {
        printf("No history to delete.\n");
        return;
    }
    patients[index].historyCount--;
}

void printPatients() {
    int i;
    for (i = 0; i < patientCount; i++) {
        puts("+--------------------------------------------+");
        puts("|               Data Pasien                  |");
        puts("+--------------------------------------------+");
        printf("| Nomor ID Pasien : %-24s |\n", patients[i].patient.id);
        printf("| Nama            : %-24s |\n", patients[i].patient.name);
        puts("+--------------------------------------------+");
    }
}



void printPatientAndHistories() {
    int i, j;
    for (i = 0; i < patientCount; i++) {
        puts("+--------------------------------------------+");
        puts("|            Kartu Kesehatan Pasien          |");
        puts("+--------------------------------------------+");
        printf("| %-15s | : %-22s |\n", "Nomor ID Pasien", patients[i].patient.id);
        printf("| %-15s | : %-22s |\n", "Nama", patients[i].patient.name);
        printf("| %-15s | : %-22s |\n", "Jenis Kelamin", patients[i].patient.gender);
        printf("| %-15s | : %s %s %-15s |\n", "Tanggal Lahir", patients[i].patient.tgl_lahir.day, patients[i].patient.tgl_lahir.month, patients[i].patient.tgl_lahir.year);
        printf("| %-15s | : %-22s |\n", "Golongan Darah", patients[i].patient.blood);
        printf("| %-15s | : %-22s |\n", "Alamat", patients[i].patient.address);
        printf("| %-15s | : %-22s |\n", "No. KTP", patients[i].patient.idcard);
        printf("| %-15s | : %-22s |\n", "No. BPJS/Askes", patients[i].patient.bpjs);
        printf("| %-15s | : %-22s |\n", "No. Telepon", patients[i].patient.telp);
        printf("| %-15s | : %s %s %-15s |\n", "Tanggal Daftar", patients[i].patient.tgl_daftar.day, patients[i].patient.tgl_daftar.month, patients[i].patient.tgl_daftar.year);
        printf("| %-15s | : %-22s |\n", "Dokter Pribadi", patients[i].patient.doctor);
        puts("+--------------------------------------------+");
        puts("|               Riwayat Pasien               |");
        puts("+--------------------------------------------+");
	    for (j = 0; j < patients[i].historyCount; j++) {
	    	printf("| %-15s   : %s %s %-15s |\n", "Tanggal Periksa", patients[i].histories[j].tgl_priksa.day, patients[i].histories[j].tgl_priksa.month,patients[i].histories[j].tgl_priksa.year);
            printf("| %-15s   : %-22s |\n", "ID Riwayat", patients[i].histories[j].id);
            puts("+--------------------------------------------+");
            puts("| Medical Checkup                            |");
            printf("| %-15s   : %-22.f |\n", "Tinggi Badan", patients[i].histories[j].t_badan);
            printf("| %-15s   : %-22.f |\n", "Berat Badan", patients[i].histories[j].b_badan);
            printf("| %-15s   : %-22d |\n", "Umur", patients[i].histories[j].umur);
            printf("| %-15s   : %-22s |\n", "Tekanan Darah", patients[i].histories[j].t_darah);
            puts("+--------------------------------------------+");
            printf("| %-15s   : %-22s |\n", "Keluhan", patients[i].histories[j].keluhan);
            printf("| %-15s   : %-22s |\n", "Catatan Dokter", patients[i].histories[j].cat_doctor);
            printf("| %-15s   : %-22s |\n", "Resep", patients[i].histories[j].resep);
            puts("+--------------------------------------------+");
        }
        printf("\n");
    }
}


int main() {
    int pilihan;
    char id[20];
    Patient patient;
    History history;
    do {
    	system("cls");
    	puts("+--------------------------------------------+");
        puts("|**********[ Rumah Sakit Sejahtera ]*********|");
        puts("+--------------------------------------------+");
        puts("| #Kelola Data Pasien#                       |");
        puts("| 1. Insert Data Pasien                      |");
        puts("| 2. Update Data Pasien                      |");
        puts("| 3. Delete Data Pasien                      |");
        puts("| #Kelola Data Riwayat Pasien#               |");
        puts("| 4. Insert Riwayat Pasien                   |");
        puts("| 5. Update Riwayat Pasien                   |");
        puts("| 6. Delete Riwayat Terakhir Pasien          |");
        puts("| 7. Tampilkan Data Pasien                   |");
        puts("| 8. Tampilkan Data dan Riwayat Pasien       |");
        puts("| 0. Exit                                    |");
        puts("+____________________________________________+");
        puts("Pilih Menu: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
	            printf("%-37s: ", "Masukkan ID Pasien");
				fflush(stdin);
				gets(patient.id);
				printf("%-37s: ","Masukkan Nama Pasien");
				fflush(stdin);
				gets(patient.name);
				printf("%-37s: ","Masukkan Jenis Kelamin");
				fflush(stdin);
				gets(patient.gender);
				printf("%-37s: ", "Masukkan Tanggal Lahir (dd-mmm-yyyy)");
				fflush(stdin);
				scanf("%s %s %s", patient.tgl_lahir.day, patient.tgl_lahir.month, patient.tgl_lahir.year);
				printf("%-37s: ","Masukan Golongan Darah");
				fflush(stdin);
				gets(patient.blood);
				printf("%-37s: ","Masukkan Alamat");
				fflush(stdin);
				gets(patient.address);
				printf("%-37s: ","Masukkan No. KTP");
				fflush(stdin);
				gets(patient.idcard);
				printf("%-37s: ","Masukkan No. BPJS/Askes");
				fflush(stdin);
				gets(patient.bpjs);
				printf("%-37s: ","Masukkan No. Telepon");
				fflush(stdin);
				gets(patient.telp);
				printf("%-37s: ","Masukkan Tanggal Daftar (dd-mmm-yyyy)");
				fflush(stdin);
				scanf("%s %s %s", patient.tgl_daftar.day, patient.tgl_daftar.month, patient.tgl_daftar.year);
				printf("%-37s: ","Masukkan Dokter Pribadi");
				fflush(stdin);
				gets(patient.doctor);
				insertPatient(patient);
				getch();
                break;
            case 2:
	           printf("%-37s: ", "Masukkan ID Pasien");
				fflush(stdin);
				gets(patient.id);
				printf("%-37s: ","Masukkan Nama Pasien");
				fflush(stdin);
				gets(patient.name);
				printf("%-37s: ","Masukkan Jenis Kelamin");
				fflush(stdin);
				gets(patient.gender);
				printf("%-37s: ", "Masukkan Tanggal Lahir (dd-mmm-yyyy)");
				fflush(stdin);
				scanf("%s %s %s", patient.tgl_lahir.day, patient.tgl_lahir.month, patient.tgl_lahir.year);
				printf("%-37s: ","Masukan Golongan Darah");
				fflush(stdin);
				gets(patient.blood);
				printf("%-37s: ","Masukkan Alamat");
				fflush(stdin);
				gets(patient.address);
				printf("%-37s: ","Masukkan No. KTP");
				fflush(stdin);
				gets(patient.idcard);
				printf("%-37s: ","Masukkan No. BPJS/Askes");
				fflush(stdin);
				gets(patient.bpjs);
				printf("%-37s: ","Masukkan No. Telepon");
				fflush(stdin);
				gets(patient.telp);
				printf("%-37s: ","Masukkan Tanggal Daftar (dd-mmm-yyyy)");
				fflush(stdin);
				scanf("%s %s %s", patient.tgl_daftar.day, patient.tgl_daftar.month, patient.tgl_daftar.year);
				printf("%-37s: ","Masukkan Dokter Pribadi");
				fflush(stdin);
				gets(patient.doctor);
                updatePatient(patient);
                getch();
                break;
            case 3:
                printf("%-37s: ","Masukkan ID Pasien");
                scanf("%s", id);
                deletePatient(id);
                getch();
                break;
           case 4:
			    printf("%-37s: ","Masukkan ID Pasien");
			    fflush(stdin);
			    gets(id);
			    printf("%-37s: ","Masukkan ID Riwayat");
			    fflush(stdin);
			    gets(history.id);
			    printf("%-37s: ","Masukkan Tanggal Periksa (dd-mmm-yyyy)");
			    fflush(stdin);
			    scanf("%s %s %s", history.tgl_priksa.day, history.tgl_priksa.month, history.tgl_priksa.year);
			    printf("%-37s: ","Masukkan Tinggi Badan");
			    scanf("%f", &history.t_badan);
			    printf("%-37s: ","Masukkan Berat Badan");
			    scanf("%f", &history.b_badan);
			    printf("%-37s: ","Masukkan Umur");
			    scanf("%d", &history.umur);
			    printf("%-37s: ","Masukkan Tekanan Darah");
			    fflush(stdin);
			    gets(history.t_darah);
			    printf("%-37s: ","Masukkan Keluhan");
			    fflush(stdin);
			    gets(history.keluhan);
			    printf("%-37s: ","Masukkan Catatan Dokter");
			    fflush(stdin);
			    gets(history.cat_doctor);
			    printf("%-37s: ","Masukkan Resep");
			    fflush(stdin);
			    gets(history.resep);
			    insertHistory(id, history);
			    getch();
			    break;
			case 5:
			    printf("%-37s: ","Masukkan ID Pasien");
			    fflush(stdin);
			    gets(id);
			    printf("%-37s: ","Masukkan ID Riwayat");
			    fflush(stdin);
			    gets(history.id);
			    printf("%-37s: ","Masukkan Tanggal Periksa (dd-mmm-yyyy)");
			    fflush(stdin);
			    scanf("%s %s %s", history.tgl_priksa.day, history.tgl_priksa.month, history.tgl_priksa.year);
			    printf("%-37s: ","Masukkan Tinggi Badan");
			    scanf("%f", &history.t_badan);
			    printf("%-37s: ","Masukkan Berat Badan");
			    scanf("%f", &history.b_badan);
			    printf("%-37s: ","Masukkan Umur");
			    scanf("%d", &history.umur);
			    printf("%-37s: ","Masukkan Tekanan Darah");
			    fflush(stdin);
			    gets(history.t_darah);
			    printf("%-37s: ","Masukkan Keluhan");
			    fflush(stdin);
			    gets(history.keluhan);
			    printf("%-37s: ","Masukkan Catatan Dokter");
			    fflush(stdin);
			    gets(history.cat_doctor);
			    printf("%-37s: ","Masukkan Resep");
			    fflush(stdin);
			    gets(history.resep);
			    updateHistory(id, history);
			    getch();
			    break;
            case 6:
                printf("%-37s: ","Masukkan ID Pasien");
                scanf("%s", id);
                deleteLastHistory(id);
                getch();
                break;
            case 7:
                printPatients();
                getch();
                break;
            case 8:
                printPatientAndHistories();
                getch();
                break;
            case 0:
                break;
            default:
                printf("Menu tidak ditemukan!\n");
                getch();
                break;
        }
    } while (pilihan != 0);
    return 0;
}

