#include <iostream>
#include <string>

using namespace std;


struct Node {
    string tu;    // Tu luu tru
    int dem;      // So lan xuat hien cua tu
    Node* next;   // Con tro tro den node tiep theo
};

// Them node moi 
void themNode(Node*& p, const string& tu) {
    Node* current = p;
    Node* previous = NULL;

    // Kiem tra xem tu da ton tai chua
    while (current != nullptr) {
        if (current->tu == tu) { // Neu tu ton tai
            current->dem++;
            return;
        }
        previous = current;
        current = current->next;
    }

    // Neu tu chua ton tai, them vao danh sach
    Node* newNode = new Node;
    newNode->tu = tu;  // Gan tu vao node moi
    newNode->dem = 1;  // Khoi tao so lan xuat hien la 1
    newNode->next = nullptr;

    if (previous == nullptr) { // Danh sach rong
        p = newNode;
    } else {
        previous->next = newNode;
    }
}

// Tim tu xuat hien nhieu nhat
void tuXuatHienNhieuNhat(Node* p) {
    Node* current = p;
    string tuNhieuNhat;
    int maxDem = 0;

    // Duyet danh sach de tim tu co so lan xuat hien lon nhat
    while (current != NULL) {
        if (current->dem > maxDem) {
            maxDem = current->dem;       // Cap nhat so lan xuat hien lon nhat
            tuNhieuNhat = current->tu;   // Luu tu xuat hien nhieu nhat
        }
        current = current->next;
    }

    // In ket qua
    cout << "Tu xuat hien nhieu nhat: " << tuNhieuNhat << " (xuat hien " << maxDem << " lan)" << endl;
}

// Loaitu lay
void loaiBoTuLay(Node*& p) {
    Node* current = p;
    Node* previous = NULL;

    // Duyet danh sach de tim va bo tu lay
    while (current != NULL) {
        if (current->tu.size() > 3) { // Kiem tra tu co do dai lon hon 3
            int n = current->tu.size() / 2;
            if (current->tu.substr(0, n) == current->tu.substr(n, n)) { // So sanh hai phan cua tu
                // Loai bo node
                if (previous == NULL) { // Neu node can loai la node dau
                    p = current->next;
                } else {
                    previous->next = current->next;
                }
                Node* temp = current;
                current = current->next;
                delete temp;
                continue; // Bo qua buoc cap nhat previous
            }
        }
        previous = current;
        current = current->next;
    }
}

// Dem tong so tu vung
int demSoTu(Node* p) {
    int dem = 0;
    Node* current = p;

    // Duyet danh sach de dem so node
    while (current != NULL) {
        dem++;
        current = current->next;
    }
    return dem;
}

// Giai phong bo nho
void giaiPhongDanhSach(Node*& p) {
    while (p != NULL) {
        Node* temp = p;
        p = p->next;
        delete temp; 
    }
}

// Tach thanh cac tu
void tachChuoi(const string& cau, Node*& p) {
    size_t start = 0, end;

    while ((end = cau.find(' ', start)) != string::npos) {
        string tu = cau.substr(start, end - start); // Lay tu tu vi tri start
        themNode(p, tu);
        start = end + 1; // Cap nhat vi tri bat dau cua tu moi
    }
    if (start < cau.size()) {
        themNode(p, cau.substr(start)); // Them tu cuoi cung
    }
}

//Chuong trinh chinh
int main() {
    Node* p = NULL; // Khoi tao danh sach rong

    // Nhap cau
    cout << "Nhap mot cau: ";
    string cau;
    getline(cin, cau); // Doc mot dong van ban

    // Tach cau thanh cac tu va them vao danh sach
    tachChuoi(cau, p);

    // Xac dinh tu xuat hien nhieu nhat
    tuXuatHienNhieuNhat(p);

    // Loai bo tu lay
    loaiBoTuLay(p);

    // Dem so tu vung
    cout << "Tong so tu vung: " << demSoTu(p) << endl;

    // Giai phong danh sach
    giaiPhongDanhSach(p);

    return 0;
}
