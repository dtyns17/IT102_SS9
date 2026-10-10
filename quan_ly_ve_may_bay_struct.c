#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;
    float baggageWeight;
    float baggageFee;
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int luaChon = 0;
    int i, j, c, r;
    int viTri, trung;
    char pnrInput[15];
    char *p;
    float khoiLuong;
    const char *tenHang[] = {"", "Eco", "Deluxe", "Business"};

    do {
        printf("\n=== HỆ THỐNG BÁN VÉ VÀ CHECK-IN MÁY BAY ===\n");
        printf("1. Thêm vé máy bay mới\n");
        printf("2. Hiển thị danh sách vé\n");
        printf("3. Cập nhật hành lý theo PNR\n");
        printf("4. Xóa vé theo PNR\n");
        printf("5. Thoát\n");
        printf("Lựa chọn của bạn: ");
        r = scanf("%d", &luaChon);
        if (r == EOF) {
            return 1;
        }
        if (r != 1) {
            luaChon = 0;
        }
        while ((c = getchar()) != '\n' && c != EOF);

        switch (luaChon) {
        case 1:
            if (soLuong >= 100) {
                printf("Danh sách vé đã đầy, không thể thêm mới!\n");
                break;
            }
            do {
                trung = 0;
                printf("\nNhập mã PNR: ");
                if (scanf("%14s", danhSachVe[soLuong].pnrCode) != 1) {
                    return 1;
                }
                while ((c = getchar()) != '\n' && c != EOF);
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, danhSachVe[soLuong].pnrCode) == 0) {
                        printf("Mã PNR đã tồn tại, vui lòng nhập mã khác!\n");
                        trung = 1;
                        break;
                    }
                }
            } while (trung);

            do {
                printf("Nhập họ tên hành khách: ");
                if (fgets(danhSachVe[soLuong].passengerName,
                          sizeof(danhSachVe[soLuong].passengerName), stdin) == NULL) {
                    return 1;
                }
                p = strchr(danhSachVe[soLuong].passengerName, '\n');
                if (p != NULL) {
                    *p = '\0';
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                if (strlen(danhSachVe[soLuong].passengerName) == 0) {
                    printf("Họ tên không được để trống!\n");
                }
            } while (strlen(danhSachVe[soLuong].passengerName) == 0);

            do {
                printf("Nhập hạng vé (1-Eco, 2-Deluxe, 3-Business): ");
                r = scanf("%d", &danhSachVe[soLuong].ticketClass);
                if (r == EOF) {
                    return 1;
                }
                if (r != 1) {
                    danhSachVe[soLuong].ticketClass = 0;
                }
                while ((c = getchar()) != '\n' && c != EOF);
                if (danhSachVe[soLuong].ticketClass < 1 || danhSachVe[soLuong].ticketClass > 3) {
                    printf("Hạng vé không hợp lệ, vui lòng nhập lại!\n");
                }
            } while (danhSachVe[soLuong].ticketClass < 1 || danhSachVe[soLuong].ticketClass > 3);

            do {
                printf("Nhập khối lượng hành lý (kg): ");
                r = scanf("%f", &danhSachVe[soLuong].baggageWeight);
                if (r == EOF) {
                    return 1;
                }
                if (r != 1) {
                    danhSachVe[soLuong].baggageWeight = -1;
                }
                while ((c = getchar()) != '\n' && c != EOF);
                if (danhSachVe[soLuong].baggageWeight < 0) {
                    printf("Khối lượng không hợp lệ, vui lòng nhập lại!\n");
                }
            } while (danhSachVe[soLuong].baggageWeight < 0);

            if (danhSachVe[soLuong].ticketClass == 3) {
                danhSachVe[soLuong].baggageFee = 0.0;
            } else if (danhSachVe[soLuong].baggageWeight <= 7.0) {
                danhSachVe[soLuong].baggageFee = 0.0;
            } else {
                danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0) * 50000.0;
            }

            printf("=> Thêm vé thành công! Cước phạt hành lý quá cân: %.0f VNĐ.\n",
                   danhSachVe[soLuong].baggageFee);
            soLuong++;
            break;

        case 2:
            if (soLuong == 0) {
                printf("Danh sách vé đang rỗng!\n");
                break;
            }
            printf("\n========================================================================================\n");
            printf("%-4s | %-11s | %-25s | %-11s | %-14s | %s\n",
                   "STT", "Mã PNR", "Họ tên hành khách", "Hạng vé", "Hành lý (kg)", "Cước quá cước");
            printf("========================================================================================\n");
            for (i = 0; i < soLuong; i++) {
                printf("%-4d | %-10s | %-20s | %-8s | %-12.1f | %.0f VNĐ\n",
                       i + 1, danhSachVe[i].pnrCode, danhSachVe[i].passengerName,
                       tenHang[danhSachVe[i].ticketClass], danhSachVe[i].baggageWeight,
                       danhSachVe[i].baggageFee);
            }
            printf("========================================================================================\n");
            break;

        case 3:
            if (soLuong == 0) {
                printf("Danh sách vé đang rỗng!\n");
                break;
            }
            printf("Nhập mã PNR cần cập nhật hành lý: ");
            if (scanf("%14s", pnrInput) != 1) {
                return 1;
            }
            while ((c = getchar()) != '\n' && c != EOF);

            viTri = -1;
            for (i = 0; i < soLuong; i++) {
                if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                    viTri = i;
                    break;
                }
            }
            if (viTri == -1) {
                printf("Không tìm thấy vé có mã PNR đã nhập!\n");
                break;
            }

            printf("Tìm thấy hành khách: %s\n", danhSachVe[viTri].passengerName);
            do {
                printf("Nhập trọng lượng hành lý mới (kg): ");
                r = scanf("%f", &khoiLuong);
                if (r == EOF) {
                    return 1;
                }
                if (r != 1) {
                    khoiLuong = -1;
                }
                while ((c = getchar()) != '\n' && c != EOF);
                if (khoiLuong < 0) {
                    printf("Trọng lượng không hợp lệ, vui lòng nhập lại!\n");
                }
            } while (khoiLuong < 0);

            danhSachVe[viTri].baggageWeight = khoiLuong;
            if (danhSachVe[viTri].ticketClass == 3) {
                danhSachVe[viTri].baggageFee = 0.0;
            } else if (khoiLuong <= 7.0) {
                danhSachVe[viTri].baggageFee = 0.0;
            } else {
                danhSachVe[viTri].baggageFee = (khoiLuong - 7.0) * 50000.0;
            }
            printf("=> Cập nhật thành công! Phí hành lý quá cước mới: %.0f VNĐ.\n",
                   danhSachVe[viTri].baggageFee);
            break;

        case 4:
            if (soLuong == 0) {
                printf("Danh sách vé đang rỗng!\n");
                break;
            }
            printf("Nhập mã PNR cần xóa: ");
            if (scanf("%14s", pnrInput) != 1) {
                return 1;
            }
            while ((c = getchar()) != '\n' && c != EOF);

            viTri = -1;
            for (i = 0; i < soLuong; i++) {
                if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                    viTri = i;
                    break;
                }
            }
            if (viTri == -1) {
                printf("Không tìm thấy vé có mã PNR đã nhập!\n");
                break;
            }

            for (j = viTri; j < soLuong - 1; j++) {
                danhSachVe[j] = danhSachVe[j + 1];
            }
            soLuong--;
            printf("=> Đã xóa thành công vé có mã PNR: %s ra khỏi hệ thống.\n", pnrInput);
            break;

        case 5:
            printf("Cảm ơn bạn đã sử dụng hệ thống. Tạm biệt!\n");
            break;

        default:
            printf("Lựa chọn không hợp lệ, vui lòng chọn từ 1 đến 5!\n");
        }
    } while (luaChon != 5);

    return 0;
}
