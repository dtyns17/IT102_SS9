#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[15];
    char tenHanhKhach[50];
    char hangVe[20];
    float canNangHanhLy;
    double cuocHanhLy;
};

int main() {
    struct VeMayBay danhSachVe[MAX_VE];
    int soLuong = 0;
    int n, i, j, c, r;
    int trung, hopLe, viTri, iMax;
    char maTim[15];
    char *p;
    float canMoi;
    double tongCuoc;

    printf("Nhập số lượng vé máy bay: ");
    r = scanf("%d", &n);
    if (r != 1) {
        printf("Số lượng vé không hợp lệ!\n");
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);
    if (n < 1 || n > MAX_VE) {
        printf("Số lượng vé phải nằm trong khoảng từ 1 đến %d!\n", MAX_VE);
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\n--- Nhập thông tin vé thứ %d ---\n", i + 1);

        do {
            trung = 0;
            printf("Mã vé PNR: ");
            if (scanf("%14s", danhSachVe[i].maVe) != 1) {
                return 1;
            }
            while ((c = getchar()) != '\n' && c != EOF);
            for (j = 0; j < i; j++) {
                if (strcmp(danhSachVe[j].maVe, danhSachVe[i].maVe) == 0) {
                    printf("Mã vé đã tồn tại, vui lòng nhập mã khác!\n");
                    trung = 1;
                    break;
                }
            }
        } while (trung);

        do {
            printf("Họ tên hành khách: ");
            if (fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin) == NULL) {
                return 1;
            }
            p = strchr(danhSachVe[i].tenHanhKhach, '\n');
            if (p != NULL) {
                *p = '\0';
            } else {
                while ((c = getchar()) != '\n' && c != EOF);
            }
            if (strlen(danhSachVe[i].tenHanhKhach) == 0) {
                printf("Họ tên không được để trống!\n");
            }
        } while (strlen(danhSachVe[i].tenHanhKhach) == 0);

        do {
            printf("Hạng vé (Business/Deluxe/Eco): ");
            if (scanf("%19s", danhSachVe[i].hangVe) != 1) {
                return 1;
            }
            while ((c = getchar()) != '\n' && c != EOF);
            hopLe = strcmp(danhSachVe[i].hangVe, "Business") == 0
                 || strcmp(danhSachVe[i].hangVe, "Deluxe") == 0
                 || strcmp(danhSachVe[i].hangVe, "Eco") == 0;
            if (!hopLe) {
                printf("Hạng vé không hợp lệ, vui lòng nhập lại!\n");
            }
        } while (!hopLe);

        do {
            printf("Khối lượng hành lý ký gửi (kg): ");
            r = scanf("%f", &danhSachVe[i].canNangHanhLy);
            if (r == EOF) {
                return 1;
            }
            if (r != 1) {
                danhSachVe[i].canNangHanhLy = -1;
            }
            while ((c = getchar()) != '\n' && c != EOF);
            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Khối lượng không hợp lệ, vui lòng nhập lại!\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20) {
                danhSachVe[i].cuocHanhLy = 0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20) * 50000.0;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000.0;
        }
        soLuong++;
    }

    printf("\n================================ DANH SÁCH VÉ MÁY BAY CHUYẾN BAY =================================\n");
    printf("%-5s %-14s %-30s %-15s %12s %20s\n",
           "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
    printf("--------------------------------------------------------------------------------------\n");
    tongCuoc = 0;
    iMax = 0;
    for (i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        tongCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[iMax].canNangHanhLy) {
            iMax = i;
        }
    }
    printf("--------------------------------------------------------------------------------------\n");
    printf("Tổng tiền cước hành lý toàn chuyến: %.0f VNĐ\n", tongCuoc);
    printf("Vé có hành lý ký gửi nặng nhất: %s - %s (%.1f kg)\n",
           danhSachVe[iMax].maVe, danhSachVe[iMax].tenHanhKhach, danhSachVe[iMax].canNangHanhLy);

    printf("\nNhập mã vé PNR cần cập nhật hành lý: ");
    if (scanf("%14s", maTim) != 1) {
        return 1;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    viTri = -1;
    for (i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, maTim) == 0) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        printf("Không tìm thấy mã vé PNR này trong hệ thống!\n");
        return 0;
    }

    do {
        printf("Nhập cân nặng hành lý ký gửi mới (kg): ");
        r = scanf("%f", &canMoi);
        if (r == EOF) {
            return 1;
        }
        if (r != 1) {
            canMoi = -1;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        if (canMoi < 0) {
            printf("Khối lượng không hợp lệ, vui lòng nhập lại!\n");
        }
    } while (canMoi < 0);

    danhSachVe[viTri].canNangHanhLy = canMoi;
    if (strcmp(danhSachVe[viTri].hangVe, "Business") == 0) {
        if (canMoi <= 20) {
            danhSachVe[viTri].cuocHanhLy = 0;
        } else {
            danhSachVe[viTri].cuocHanhLy = (canMoi - 20) * 50000.0;
        }
    } else {
        danhSachVe[viTri].cuocHanhLy = canMoi * 50000.0;
    }

    printf("\n--- CẬP NHẬT THÔNG TIN HÀNH LÝ ---\n");
    printf("Tìm thấy mã vé %s. Đã cập nhật cước hành lý mới: %.0f VNĐ.\n",
           danhSachVe[viTri].maVe, danhSachVe[viTri].cuocHanhLy);

    printf("\n============================== DANH SÁCH VÉ MÁY BAY SAU CẬP NHẬT ===============================\n");
    printf("%-5s %-14s %-30s %-15s %12s %20s\n",
           "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
    printf("--------------------------------------------------------------------------------------\n");
    for (i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
    }
    printf("--------------------------------------------------------------------------------------\n");

    return 0;
}
