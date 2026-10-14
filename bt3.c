#include <stdio.h>

#define MAX_ZONES 10
#define MAX_QRS 50
#define MAX_TICKETS_PER_ORDER 4

struct TicketZone {
    int zone_id;
    char zone_name[30];
    float ticket_price;
    int total_capacity;
    int sold_tickets;
};

struct QrCheckIn {
    int qr_code;
    int zone_id;
    int is_used;
};

int timKhuVuc(const struct TicketZone zones[], int totalZones, int zoneId);
int timQR(const struct QrCheckIn qrs[], int totalQrs, int qrCode);
float tinhGiaVe(float ticketPrice, int isEarlyBird);
int banVe(struct TicketZone *zone, int quantity, int isEarlyBird, float *totalMoney);
int checkInQR(struct QrCheckIn *qr);
void hienThiKhuVuc(const struct TicketZone zones[], int totalZones);

int main() {
    struct TicketZone zones[MAX_ZONES] = {
        {1, "VIP", 2000000.0f, 10, 6},
        {2, "GA", 800000.0f, 20, 5},
        {3, "Zone A", 1200000.0f, 15, 10}
    };

    struct QrCheckIn qrs[MAX_QRS] = {
        {1001, 1, 0},
        {1002, 1, 0},
        {2001, 2, 1}
    };

    int totalZones = 3;
    int totalQrs = 3;
    int index;
    float totalMoney;

    printf("=== TICKETBOX LIVE CONCERT ===\n");

    printf("\n1. DANH SACH KHU VUC BAN DAU\n");
    hienThiKhuVuc(zones, totalZones);

    printf("\n2. BAN 2 VE VIP - EARLY BIRD\n");
    index = timKhuVuc(zones, totalZones, 1);
    if (index != -1) {
        totalMoney = 0;
        if (banVe(&zones[index], 2, 1, &totalMoney) == 1) {
            printf("Tong tien: %.0f VND\n", totalMoney);
        }
    }

    printf("\n3. KIEM TRA SO LUONG KHONG HOP LE\n");
    index = timKhuVuc(zones, totalZones, 2);
    if (index != -1) {
        totalMoney = 0;
        banVe(&zones[index], -2, 0, &totalMoney);
        banVe(&zones[index], 0, 0, &totalMoney);
        banVe(&zones[index], 5, 0, &totalMoney);
    }

    printf("\n4. KIEM TRA BAN VUOT SUC CHUA\n");
    index = timKhuVuc(zones, totalZones, 1);
    if (index != -1) {
        totalMoney = 0;
        banVe(&zones[index], 3, 0, &totalMoney);
    }

    printf("\n5. KIEM TRA KHU VUC KHONG TON TAI\n");
    index = timKhuVuc(zones, totalZones, 99);
    if (index == -1) {
        printf("[LOI] Khu vuc khong ton tai!\n");
    }

    printf("\n6. CHECK-IN QR 1001\n");
    index = timQR(qrs, totalQrs, 1001);
    if (index != -1) {
        checkInQR(&qrs[index]);
    } else {
        printf("[LOI] Ma QR khong ton tai!\n");
    }

    printf("\n7. QUET LAI QR 1001\n");
    index = timQR(qrs, totalQrs, 1001);
    if (index != -1) {
        checkInQR(&qrs[index]);
    } else {
        printf("[LOI] Ma QR khong ton tai!\n");
    }

    printf("\n8. CHECK-IN QR KHONG TON TAI\n");
    index = timQR(qrs, totalQrs, 9999);
    if (index != -1) {
        checkInQR(&qrs[index]);
    } else {
        printf("[LOI] Ma QR khong ton tai!\n");
    }

    printf("\n9. KIEM TRA DANH SACH RONG\n");
    if (timKhuVuc(zones, 0, 1) == -1) {
        printf("[THONG BAO] Danh sach khu vuc rong!\n");
    }
    if (timQR(qrs, 0, 1001) == -1) {
        printf("[THONG BAO] Danh sach QR rong!\n");
    }

    printf("\n10. DANH SACH KHU VUC SAU GIAO DICH\n");
    hienThiKhuVuc(zones, totalZones);

    return 0;
}

int timKhuVuc(const struct TicketZone zones[], int totalZones, int zoneId) {
    for (int i = 0; i < totalZones; i++) {
        if (zones[i].zone_id == zoneId) {
            return i;
        }
    }

    return -1;
}

int timQR(const struct QrCheckIn qrs[], int totalQrs, int qrCode) {
    for (int i = 0; i < totalQrs; i++) {
        if (qrs[i].qr_code == qrCode) {
            return i;
        }
    }

    return -1;
}

float tinhGiaVe(float ticketPrice, int isEarlyBird) {
    if (isEarlyBird == 1) {
        return ticketPrice * 0.85f;
    }

    return ticketPrice;
}

int banVe(struct TicketZone *zone, int quantity, int isEarlyBird, float *totalMoney) {
    if (quantity < 1 || quantity > MAX_TICKETS_PER_ORDER) {
        printf("[LOI] So luong mua phai tu 1 den 4 ve!\n");
        return 0;
    }

    if (zone->sold_tickets + quantity > zone->total_capacity) {
        printf("[LOI] Khu vuc %s khong du ve!\n", zone->zone_name);
        return 0;
    }

    zone->sold_tickets += quantity;
    *totalMoney = tinhGiaVe(zone->ticket_price, isEarlyBird) * quantity;

    printf("[THANH CONG] Da ban %d ve khu vuc %s.\n",
           quantity, zone->zone_name);

    return 1;
}

int checkInQR(struct QrCheckIn *qr) {
    if (qr->is_used == 1) {
        printf("[CANH BAO] QR %d da duoc su dung! Tu choi check-in.\n",
               qr->qr_code);
        return 0;
    }

    qr->is_used = 1;
    printf("[THANH CONG] QR %d check-in thanh cong.\n", qr->qr_code);

    return 1;
}

void hienThiKhuVuc(const struct TicketZone zones[], int totalZones) {
    if (totalZones == 0) {
        printf("Danh sach khu vuc rong.\n");
        return;
    }

    for (int i = 0; i < totalZones; i++) {
        printf("ID: %d | Ten: %s | Gia goc: %.0f VND | Da ban: %d | Con lai: %d\n",
               zones[i].zone_id,
               zones[i].zone_name,
               zones[i].ticket_price,
               zones[i].sold_tickets,
               zones[i].total_capacity - zones[i].sold_tickets);
    }
}
