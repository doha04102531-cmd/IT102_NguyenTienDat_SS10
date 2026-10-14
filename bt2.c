#include <stdio.h>

#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

float tinhGiaVe(struct VeSuKien ve);
int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe);
int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi);
void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe);
void checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);
int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);

int main() {
    struct VeSuKien dsVe[MAX_VE] = {
        {1001, "Live Concert VIBE 2025", "VIP", 2000000.0f, 1, 0},
        {1002, "Live Concert VIBE 2025", "GA", 800000.0f, 0, 0},
        {1003, "Live Concert VIBE 2025", "Zone A", 1200000.0f, 1, 0}
    };

    int soLuongVe = 3;

    printf("=== TICKETBOX - LIVE CONCERT VIBE 2025 ===\n");

    printf("\n1. DANH SACH VE BAN DAU\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    printf("\n2. PHAT HANH VE MOI\n");
    struct VeSuKien veMoi = {
        1004, "Live Concert VIBE 2025", "VIP", 2500000.0f, 0, 0
    };
    soLuongVe = phatHanhVe(dsVe, soLuongVe, veMoi);

    printf("\n3. CHECK-IN VE 1001\n");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n4. QUET LAI VE 1001\n");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n5. HUY VE 1002\n");
    soLuongVe = huyVe(dsVe, soLuongVe, 1002);

    printf("\n6. CHECK-IN VE KHONG TON TAI 9999\n");
    checkInVe(dsVe, soLuongVe, 9999);

    printf("\n7. DANH SACH VE SAU CAC THAO TAC\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    return 0;
}

float tinhGiaVe(struct VeSuKien ve) {
    if (ve.isEarlyBird == 1) {
        return ve.giaGoc * 0.85f;
    }

    return ve.giaGoc;
}

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    for (int i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }

    return -1;
}

int phatHanhVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi) {
    if (soLuongVe >= MAX_VE) {
        printf("[LOI] Danh sach da day, khong the phat hanh ve!\n");
        return soLuongVe;
    }

    if (timVeTheoMa(dsVe, soLuongVe, veMoi.maVe) != -1) {
        printf("[LOI] Ma ve %d da ton tai!\n", veMoi.maVe);
        return soLuongVe;
    }

    dsVe[soLuongVe] = veMoi;
    soLuongVe++;

    printf("[THANH CONG] Da phat hanh ve %d.\n", veMoi.maVe);

    return soLuongVe;
}

void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe) {
    if (soLuongVe == 0) {
        printf("[THONG BAO] Danh sach hien khong co ve.\n");
        return;
    }

    printf("Tong so ve: %d\n", soLuongVe);

    for (int i = 0; i < soLuongVe; i++) {
        printf("Ma ve: %d | Su kien: %s | Loai ve: %s | Gia thanh toan: %.0f VND | Check-in: %s\n",
               dsVe[i].maVe,
               dsVe[i].tenSuKien,
               dsVe[i].loaiVe,
               tinhGiaVe(dsVe[i]),
               dsVe[i].daCheckIn == 1 ? "Da check-in" : "Chua check-in");
    }
}

void checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    if (soLuongVe == 0) {
        printf("[LOI] Danh sach rong, khong the check-in!\n");
        return;
    }

    int viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Ma ve %d khong ton tai!\n", maVe);
        return;
    }

    if (dsVe[viTri].daCheckIn == 1) {
        printf("[CANH BAO] Ve %d da check-in truoc do! Tu choi truy cap.\n", maVe);
        return;
    }

    dsVe[viTri].daCheckIn = 1;
    printf("[THANH CONG] Check-in ve %d thanh cong!\n", maVe);
}

int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    if (soLuongVe == 0) {
        printf("[LOI] Danh sach rong, khong co ve de huy!\n");
        return soLuongVe;
    }

    int viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Ma ve %d khong ton tai, khong the huy!\n", maVe);
        return soLuongVe;
    }

    for (int i = viTri; i < soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    soLuongVe--;

    printf("[THANH CONG] Da huy ve %d.\n", maVe);

    return soLuongVe;
}
