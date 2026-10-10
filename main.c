#include <stdio.h>
#include <string.h>

struct VeMayBay {
    char maPNR[10];
    char tenHanhKhach[50];
    char hangVe[15];
    float trongLuongHanhLy;
    long phiPhuThu;
};

int main() {
    struct VeMayBay ds[50];
    int n = 0;
    int i, j;
    int trung;
    int viTri;
    int c;
    int r;
    char pnrTim[10];
    char *p;
    float klMoi;

    printf("=== HE THONG CHECK-IN VE MAY BAY ===\n");

    do {
        printf("Nhap so luong ve (1 - 50): ");
        r = scanf("%d", &n);
        if (r == EOF) {
            return 1;
        }
        if (r != 1) {
            n = 0;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        if (n < 1 || n > 50) {
            printf("So luong ve khong hop le, vui long nhap lai!\n");
        }
    } while (n < 1 || n > 50);

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        do {
            trung = 0;
            printf("Nhap ma PNR: ");
            fgets(ds[i].maPNR, sizeof(ds[i].maPNR), stdin);
            p = strchr(ds[i].maPNR, '\n');
            if (p != NULL) {
                *p = '\0';
            } else {
                while ((c = getchar()) != '\n' && c != EOF);
            }
            if (strlen(ds[i].maPNR) == 0) {
                printf("Ma PNR khong duoc de trong!\n");
                trung = 1;
                continue;
            }
            for (j = 0; j < i; j++) {
                if (strcmp(ds[j].maPNR, ds[i].maPNR) == 0) {
                    printf("Ma PNR da ton tai, vui long nhap ma khac!\n");
                    trung = 1;
                    break;
                }
            }
        } while (trung);

        printf("Nhap ho ten hanh khach: ");
        fgets(ds[i].tenHanhKhach, sizeof(ds[i].tenHanhKhach), stdin);
        p = strchr(ds[i].tenHanhKhach, '\n');
        if (p != NULL) {
            *p = '\0';
        } else {
            while ((c = getchar()) != '\n' && c != EOF);
        }

        printf("Nhap hang ve (Eco/Deluxe/Business): ");
        fgets(ds[i].hangVe, sizeof(ds[i].hangVe), stdin);
        p = strchr(ds[i].hangVe, '\n');
        if (p != NULL) {
            *p = '\0';
        } else {
            while ((c = getchar()) != '\n' && c != EOF);
        }

        do {
            printf("Nhap trong luong hanh ly (kg): ");
            r = scanf("%f", &ds[i].trongLuongHanhLy);
            if (r == EOF) {
                return 1;
            }
            if (r != 1) {
                ds[i].trongLuongHanhLy = -1;
            }
            while ((c = getchar()) != '\n' && c != EOF);
            if (ds[i].trongLuongHanhLy < 0) {
                printf("Trong luong khong hop le, vui long nhap lai!\n");
            }
        } while (ds[i].trongLuongHanhLy < 0);

        if (ds[i].trongLuongHanhLy > 7.0) {
            ds[i].phiPhuThu = (long)(((double)ds[i].trongLuongHanhLy - 7.0) * 50000 + 0.5);
        } else {
            ds[i].phiPhuThu = 0;
        }
    }

    printf("\n=== DANH SACH VE MAY BAY CHUYEN BAY ===\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("%-5s %-10s %-25s %-12s %-12s %-15s\n",
           "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
    printf("-------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d %-10s %-25s %-12s %-12.1f %-15ld\n",
               i + 1, ds[i].maPNR, ds[i].tenHanhKhach, ds[i].hangVe,
               ds[i].trongLuongHanhLy, ds[i].phiPhuThu);
    }
    printf("-------------------------------------------------------------------------------------\n");

    /* 5. Tim kiem tuyen tinh theo PNR va cap nhat */
    printf("\n=== CAP NHAT THONG TIN HANH LY ===\n");
    printf("Nhap ma PNR can cap nhat: ");
    fgets(pnrTim, sizeof(pnrTim), stdin);
    p = strchr(pnrTim, '\n');
    if (p != NULL) {
        *p = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF);
    }

    viTri = -1;
    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].maPNR, pnrTim) == 0) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        printf("Khong tim thay ma PNR hop le!\n");
    } else {
        printf("Tim thay ve cua hanh khach: %s\n", ds[viTri].tenHanhKhach);

        do {
            printf("Nhap trong luong hanh ly moi (kg): ");
            r = scanf("%f", &klMoi);
            if (r == EOF) {
                return 1;
            }
            if (r != 1) {
                klMoi = -1;
            }
            while ((c = getchar()) != '\n' && c != EOF);
            if (klMoi < 0) {
                printf("Trong luong khong hop le, vui long nhap lai!\n");
            }
        } while (klMoi < 0);

        ds[viTri].trongLuongHanhLy = klMoi;
        if (klMoi > 7.0) {
            ds[viTri].phiPhuThu = (long)(((double)klMoi - 7.0) * 50000 + 0.5);
        } else {
            ds[viTri].phiPhuThu = 0;
        }
        printf("Cap nhat thanh cong! Phi phu thu moi: %ld VND\n", ds[viTri].phiPhuThu);

        printf("\n=== DANH SACH VE MAY BAY SAU CAP NHAT ===\n");
        printf("-------------------------------------------------------------------------------------\n");
        printf("%-5s %-10s %-25s %-12s %-12s %-15s\n",
               "STT", "MA PNR", "HO TEN HANH KHACH", "HANG VE", "HANH LY(KG)", "PHI PHU THU(VND)");
        printf("-------------------------------------------------------------------------------------\n");
        for (i = 0; i < n; i++) {
            printf("%-5d %-10s %-25s %-12s %-12.1f %-15ld\n",
                   i + 1, ds[i].maPNR, ds[i].tenHanhKhach, ds[i].hangVe,
                   ds[i].trongLuongHanhLy, ds[i].phiPhuThu);
        }
        printf("-------------------------------------------------------------------------------------\n");
    }

    return 0;
}
